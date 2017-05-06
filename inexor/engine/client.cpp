// fpsgame/client.cpp 
// client.cpp, mostly network related client game code
// implementation of connect and disconnect
// implementation of enet network parser

#include "inexor/engine/engine.hpp"
#include "inexor/network/legacy/game_types.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/ui.hpp"

using namespace inexor::util; //needed for quoted()

// (mostly) network related stuff

ENetHost *clienthost = NULL;
ENetPeer *curpeer = NULL, *connpeer = NULL;
int connmillis = 0, connattempts = 0, discmillis = 0;

// is player in multiplayer
// also print multiplayer restricted game function warnings
bool multiplayer(bool msg)
{
    bool val = curpeer || hasnonlocalclients(); 
    if(val && msg) spdlog::get("global")->error("operation not available in multiplayer");
    return val;
}

// set network bandwidth rate (in kilobytes)
void setrate(int rate)
{
   if(!curpeer) return;
   enet_host_bandwidth_limit(clienthost, rate*1024, rate*1024);
}
VARF(rate, 0, 0, 1024, setrate(rate));

// forward of network throttle
void throttle();
VARF(throttle_interval, 0, 5, 30, throttle());
VARF(throttle_accel,    0, 2, 32, throttle());
VARF(throttle_decel,    0, 2, 32, throttle());

// implementation fo network throttle
void throttle()
{
    if(!curpeer) return;
    ASSERT(ENET_PEER_PACKET_THROTTLE_SCALE==32);
    enet_peer_throttle_configure(curpeer, throttle_interval*1000, throttle_accel, throttle_decel);
}

// is game connected or trying to connect
bool isconnected(bool attempt, bool local)
{
    return curpeer || (attempt && connpeer) || (local && haslocalclients());
}
ICOMMAND(isconnected, "bb", (int *attempt, int *local), intret(isconnected(*attempt > 0, *local != 0) ? 1 : 0));

// return the current network address
const ENetAddress *connectedpeer()
{
    return curpeer ? &curpeer->address : NULL;
}

// return the ip of the current server
ICOMMAND(connectedip, "", (),
{
    const ENetAddress *address = connectedpeer();
    string hostname;
    result(address && enet_address_get_host_ip(address, hostname, sizeof(hostname)) >= 0 ? hostname : "");
});

// return the port of the current server
ICOMMAND(connectedport, "", (),
{
    const ENetAddress *address = connectedpeer();
    intret(address ? address->port : -1);
});

// servername and connection port (?)
SVARP(connectname, "");
VARP(connectport, 0, 0, 0xFFFF);

// abort attempt to connect
void abortconnect()
{
    if(!connpeer) return;
    game::connectfail();
    if(connpeer->state!=ENET_PEER_STATE_DISCONNECTED) enet_peer_reset(connpeer);
    connpeer = NULL;
    if(curpeer) return;
    enet_host_destroy(clienthost);
    clienthost = NULL;
}

// connect to a server (serverpassword only for mastermode 3 servers)
void connectserv(const char *servername, int serverport, const char *serverpassword)
{   
    if(connpeer)
    {
        spdlog::get("global")->info("aborting connection attempt");
        abortconnect();
    }

    if(serverport <= 0) serverport = server_port();

    ENetAddress address;
    address.port = serverport;

    if(servername)
    {
        if(strcmp(servername, connectname)) setsvar("connectname", servername);
        if(serverport != connectport) setvar("connectport", serverport);
        spdlog::get("global")->info("attempting to connect to {0}:{1}", servername, serverport);
        if(!resolverwait(servername, &address))
        {
            spdlog::get("global")->error("could not resolve server {0}", servername);
            return;
        }
    }
    else
    {
        setsvar("connectname", "");
        setvar("connectport", 0);
        spdlog::get("global")->info("attempting to connect over LAN");
        address.host = ENET_HOST_BROADCAST;
    }

    if(!clienthost) 
    {
        clienthost = enet_host_create(NULL, 2, NUM_ENET_CHANNELS, rate*1024, rate*1024);
        if(!clienthost)
        {
            spdlog::get("global")->error("could not connect to server");
            return;
        }
        clienthost->duplicatePeers = 0;
    }

    connpeer = enet_host_connect(clienthost, &address, NUM_ENET_CHANNELS, 0);
    enet_host_flush(clienthost);
    connmillis = totalmillis;
    connattempts = 0;

    game::connectattempt(servername ? servername : "", serverpassword ? serverpassword : "", address);
}

// use stored data of last connected server to connect again
void reconnect(const char *serverpassword)
{
    if(!connectname[0] || connectport <= 0)
    {
        spdlog::get("global")->error("no previous connection");
        return;
    }
    connectserv(connectname, connectport, serverpassword);
}

// disconnect from a server
void disconnect(bool async, bool cleanup)
{
    if(curpeer) 
    {
        if(!discmillis)
        {
            enet_peer_disconnect(curpeer, DISC_NONE);
            enet_host_flush(clienthost);
            discmillis = totalmillis;
        }
        if(curpeer->state!=ENET_PEER_STATE_DISCONNECTED)
        {
            if(async) return;
            enet_peer_reset(curpeer);
        }
        curpeer = NULL;
        discmillis = 0;
        spdlog::get("global")->info("disconnected");
        game::gamedisconnect(cleanup);
        mainmenu = 1;
        // inexor::ui::cef_app->GetUserInterface()->SetMainMenu(true);
    }
    if(!connpeer && clienthost)
    {
        enet_host_destroy(clienthost);
        clienthost = NULL;
    }
}

// try to disconnect (attempting, connected or locally)
void trydisconnect(bool local)
{
    if(connpeer)
    {
        spdlog::get("global")->info("aborting connection attempt");
        abortconnect();
    }
    else if(curpeer)
    {
        spdlog::get("global")->info("attempting to disconnect...");
		// try to disconnect synchronously for a while then disconnect asynchronously
        disconnect(!discmillis);
    }
    else if(local && haslocalclients()) localdisconnect();
    else spdlog::get("global")->info("not connected");
}

// commands to establish and destroy network connections
ICOMMAND(connect, "sis", (char *name, int *port, char *pw), connectserv(name, *port, pw));
COMMAND(reconnect, "s");
ICOMMAND(disconnect, "b", (int *local), trydisconnect(*local != 0));

// see startlistenserver command to start local servers in game
ICOMMAND(lanconnect, "is", (int *port, char *pw), connectserv(NULL, *port, pw));
ICOMMAND(localconnect, "", (), { if(!isconnected()) localconnect(); });
ICOMMAND(localdisconnect, "", (), { if(haslocalclients()) localdisconnect(); });

// send network packet to server
void sendclientpacket(ENetPacket *packet, int chan)
{
    if(curpeer) enet_peer_send(curpeer, chan, packet);
    else localclienttoserver(chan, packet);
}

// empty network message queue (?)
void flushclient()
{
    if(clienthost) enet_host_flush(clienthost);
}

// print illegal network message to console (wrong protocol?)
void neterr(const char *s, bool disc)
{
    spdlog::get("global")->error("illegal network message \"{0}\"", s);
    if(disc) disconnect();
}

// processes any updates from the server
void localservertoclient(int chan, ENetPacket *packet)
{
    packetbuf p(packet);
    game::parsepacketclient(chan, p);
}

// send ping to server (?)
void clientkeepalive() 
{ 
	if(clienthost) enet_host_service(clienthost, NULL, 0); 
}

// get updates from the server
void gets2c()           
{
    ENetEvent event;
    if(!clienthost) return;
    if(connpeer && totalmillis/3000 > connmillis/3000)
    {
        spdlog::get("global")->info("attempting to connect...");
        connmillis = totalmillis;
        ++connattempts; 
        if(connattempts > 3)
        {
            spdlog::get("global")->error("could not connect to server");
            abortconnect();
            return;
        }
    }
    while(clienthost && enet_host_service(clienthost, &event, 0)>0)
    switch(event.type)
    {
        case ENET_EVENT_TYPE_CONNECT:
            disconnect(false, false); 
            localdisconnect(false);
            curpeer = connpeer;
            connpeer = NULL;
            spdlog::get("global")->info("connected to server");
            throttle();
            if(rate) setrate(rate);
            game::gameconnect(true);
            break;
         
        case ENET_EVENT_TYPE_RECEIVE:
            if(discmillis) spdlog::get("global")->info("attempting to disconnect...");
            else localservertoclient(event.channelID, event.packet);
            enet_packet_destroy(event.packet);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            if(event.data>=DISC_NUM) event.data = DISC_NONE;
            if(event.peer==connpeer)
            {
                spdlog::get("global")->error("could not connect to server");
                abortconnect();
            }
            else
            {
                if(!discmillis || event.data)
                {
                    const char *msg = disconnectreason(event.data);
                    if(msg) spdlog::get("global")->error("server network error, disconnecting ({0}) ...", msg);
                    else spdlog::get("global")->error("server network error, disconnecting...");
                }
                disconnect();
            }
            return;

        default:
            break;
    }
}
