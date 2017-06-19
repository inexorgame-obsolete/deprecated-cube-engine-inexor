// server.cpp: little more than enhanced multicaster

#include "inexor/engine/engine.hpp"
#include "inexor/crashreporter/CrashReporter.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/network/legacy/game_types.hpp"
#include "inexor/shared/cube_queue.hpp"
#include "inexor/util/legacy_time.hpp"
#include "inexor/server/windows_integration.hpp"
#include "inexor/server/client_management.hpp"

const char *initscript = NULL;

#ifdef STANDALONE

void conline(int type, const char *sf) {};

void cleanupserver();
void fatal(const char *fmt, ...)
{
    cleanupserver(); 
	defvformatstring(msg,fmt,fmt);
	spdlog::get("global")->critical(msg);
#ifdef WIN32
	MessageBox(NULL, msg, "Inexor fatal error", MB_OK|MB_SYSTEMMODAL);
#else
    fprintf(stderr, "server error: %s\n", msg);
#endif
    exit(EXIT_FAILURE); 
}

/// Fatal crash: log/display crash message and clean up server.
void fatal(std::vector<std::string> &output)
{
    cleanupserver();
    std::string completeoutput;
    for(auto message : output) {
        spdlog::get("global")->critical(message);
        completeoutput = inexor::util::fmt << completeoutput << message.c_str();
    }
#ifdef WIN32
    MessageBox(NULL, completeoutput.c_str(), "Inexor fatal error", MB_OK | MB_SYSTEMMODAL);
#else
    fprintf(stderr, "server error: %s\n", completeoutput.c_str());
#endif
    exit(EXIT_FAILURE);
}

#endif


ENetHost *serverhost = NULL;
int laststatus = 0; 
ENetSocket pongsock = ENET_SOCKET_NULL, lansock = ENET_SOCKET_NULL;


void cleanupserver()
{
    if(serverhost) enet_host_destroy(serverhost);
    serverhost = NULL;

    if(pongsock != ENET_SOCKET_NULL) enet_socket_destroy(pongsock);
    if(lansock != ENET_SOCKET_NULL) enet_socket_destroy(lansock);
    pongsock = lansock = ENET_SOCKET_NULL;
}

void process(ENetPacket *packet, int sender, int chan);

int getservermtu() { return serverhost ? serverhost->mtu : -1; }

void process(ENetPacket *packet, int sender, int chan)   // sender may be -1
{
    packetbuf p(packet);
    server::parsepacket(sender, chan, p);
    if(p.overread()) { disconnect_client(sender, DISC_EOP); return; }
}

#ifdef STANDALONE
bool resolverwait(const char *name, ENetAddress *address)
{
    return enet_address_set_host(address, name) >= 0;
}

int connectwithtimeout(ENetSocket sock, const char *hostname, const ENetAddress &remoteaddress)
{
    return enet_socket_connect(sock, &remoteaddress);
}
#endif

ENetAddress serveraddress = { ENET_HOST_ANY, ENET_PORT_ANY };

static ENetAddress pongaddr;

void sendserverinforeply(ucharbuf &p)
{
    ENetBuffer buf;
    buf.data = p.buf;
    buf.dataLength = p.length();
    enet_socket_send(pongsock, &pongaddr, &buf, 1);
}

#define MAXPINGDATA 32

/// Reply all server info requests
void checkserversockets()
{
    static ENetSocketSet readset, writeset;
    ENET_SOCKETSET_EMPTY(readset);
    ENET_SOCKETSET_EMPTY(writeset);
    ENetSocket maxsock = pongsock;
    ENET_SOCKETSET_ADD(readset, pongsock);

    if(lansock != ENET_SOCKET_NULL)
    {
        maxsock = max(maxsock, lansock);
        ENET_SOCKETSET_ADD(readset, lansock);
    }
    if(enet_socketset_select(maxsock, &readset, &writeset, 0) <= 0) return;

    ENetBuffer buf;
    uchar pong[MAXTRANS];
    loopi(2)
    {
        ENetSocket sock = i ? lansock : pongsock;
        if(sock == ENET_SOCKET_NULL || !ENET_SOCKETSET_CHECK(readset, sock)) continue;

        buf.data = pong;
        buf.dataLength = sizeof(pong);
        int len = enet_socket_receive(sock, &pongaddr, &buf, 1);
        if(len < 0 || len > MAXPINGDATA) continue;
        ucharbuf req(pong, len), p(pong, sizeof(pong));
        p.len += len;
        server::serverinforeply(req, p);
    }
}

VAR(serveruprate, 0, 0, INT_MAX);
SVAR(serverip, "");
VARF(serverport, 0, INEXOR_SERVER_PORT, MAX_POSSIBLE_PORT, { if(!serverport) serverport = server_port(); });


/// main server update
void serverslice(uint timeout)
{
    if(!serverhost)
    {
        server::serverupdate();
        server::sendpackets();
        return;
    }

    // below is network only

    updatetime(server::ispaused(), server::gamespeed);
    server::serverupdate();

    checkserversockets();

    if(totalmillis-laststatus>60*1000)   // display bandwidth stats, useful for server ops
    {
        laststatus = totalmillis;
        if(has_clients() || serverhost->totalSentData || serverhost->totalReceivedData)
            spdlog::get("global")->debug("status: {0} remote clients, {1} send, {2} rec (K/sec)",
                                         get_num_clients(), (serverhost->totalSentData/60.0f/1024), (serverhost->totalReceivedData/60.0f/1024));
        serverhost->totalSentData = serverhost->totalReceivedData = 0;
    }

    ENetEvent event;
    bool serviced = false;
    while(!serviced)
    {
        if(enet_host_check_events(serverhost, &event) <= 0)
        {
            if(enet_host_service(serverhost, &event, timeout) <= 0) break;
            serviced = true;
        }
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
            {
                client &c = addclient();
                c.peer = event.peer;
                c.peer->data = &c;
                string hn;
                copystring(c.hostname, (enet_address_get_host_ip(&c.peer->address, hn, sizeof(hn))==0) ? hn : "unknown");
                spdlog::get("global")->info("client connected ({0})", c.hostname);
                int reason = server::clientconnect(c.num, c.peer->address.host);
                if(reason) disconnect_client(c.num, reason);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                client *c = (client *)event.peer->data;
                if(c) process(event.packet, c->num, event.channelID);
                if(event.packet->referenceCount==0) enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
            {
                client *c = (client *)event.peer->data;
                if(!c) break;
                spdlog::get("global")->info("disconnected client ({0})", c->hostname);
                server::clientdisconnect(c->num);
                delclient(c);
                break;
            }
            default:
                break;
        }
    }
    if(server::sendpackets()) enet_host_flush(serverhost);
}

void flushserver(bool force)
{
    if(server::sendpackets(force) && serverhost) enet_host_flush(serverhost);
}

void run_server()
{
    spdlog::get("global")->info("dedicated server started, waiting for clients...");
#ifdef WIN32
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    for(;;)
    {
        MSG msg;
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT) exit(EXIT_SUCCESS);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        serverslice(5);
    }
#else
    for(;;) serverslice(5);
#endif
    }


bool servererror(const char *desc)
{
    fatal("%s", desc);
    return false;
}

bool setup_network_sockets()
{
    ENetAddress address ={ENET_HOST_ANY, enet_uint16(serverport <= 0 ? server_port() : serverport)};
    if(*serverip)
    {
        if(enet_address_set_host(&address, serverip)<0) spdlog::get("global")->warn("WARNING: server ip not resolved");
        else serveraddress.host = address.host;
    }
    serverhost = enet_host_create(&address, min(maxclients + server::reserveclients(), MAXCLIENTS), NUM_ENET_CHANNELS, 0, serveruprate);
    if(!serverhost) return servererror("could not create server host");
    serverhost->duplicatePeers = maxdupclients ? maxdupclients : MAXCLIENTS;
    address.port = server_info_port(serverport > 0 ? serverport : -1);
    pongsock = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
    if(pongsock != ENET_SOCKET_NULL && enet_socket_bind(pongsock, &address) < 0)
    {
        enet_socket_destroy(pongsock);
        pongsock = ENET_SOCKET_NULL;
    }
    if(pongsock == ENET_SOCKET_NULL) return servererror("could not create server info socket");
    else enet_socket_set_option(pongsock, ENET_SOCKOPT_NONBLOCK, 1);
    address.port = lan_info_port();
    lansock = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
    if(lansock != ENET_SOCKET_NULL && (enet_socket_set_option(lansock, ENET_SOCKOPT_REUSEADDR, 1) < 0 || enet_socket_bind(lansock, &address) < 0))
    {
        enet_socket_destroy(lansock);
        lansock = ENET_SOCKET_NULL;
    }
    if(lansock == ENET_SOCKET_NULL) spdlog::get("global")->warn("WARNING: could not create LAN server info socket");
    else enet_socket_set_option(lansock, ENET_SOCKOPT_NONBLOCK, 1);
    return true;
}

bool serveroption(const char *opt)
{
    switch(opt[1])
    {
        case 'u': setvar("serveruprate", atoi(opt+2)); return true;
        case 'c': setvar("maxclients", atoi(opt+2)); return true;
        case 'i': setsvar("serverip", opt+2); return true;
        case 'j': setvar("serverport", atoi(opt+2)); return true;
        case 'k': spdlog::get("global")->debug("Adding package directory: {}", opt); addpackagedir(opt+2); return true;
        case 'x': spdlog::get("global")->debug("Setting server init script: {}", opt); initscript = opt+2; return true;
        case 'n': setsvar("serverdesc", &opt[2]); return true;
        case 'y': setsvar("serverpass", &opt[2]); return true;
        case 'p': setsvar("adminpass", &opt[2]); return true;
        case 'o': setvar("publicserver", atoi(&opt[2])); return true;

        default: return false;
    }
}

void parseoptions(int argc, char **argv)
{
    for(int i = 1; i<argc; i++) if(argv[i][0]!='-' || !serveroption(argv[i]))
        spdlog::get("global")->error("unknown command-line option: {0}", argv[i]);
}

inexor::util::Logging logging;

int main(int argc, char **argv)
{
    logging.initDefaultLoggers();
    UNUSED inexor::crashreporter::CrashReporter SingletonStackwalker; // We only need to initialse it, not use it.
    if(enet_initialize()<0) fatal("Unable to initialise network module");
    atexit(enet_deinitialize);
    enet_time_set(0);

    parseoptions(argc, argv);

    server::serverinit();

    if(initscript) execfile(initscript);
    else execfile("server-init.cfg", false);

    setup_network_sockets();

    run_server(); // never returns
    return EXIT_SUCCESS;
}
