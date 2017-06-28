#include "inexor/shared/cube.hpp"
#include "inexor/shared/stream.hpp"
#include "inexor/gamemode/gamemode.hpp"
#include "inexor/server/demos.hpp"
#include "inexor/server/client_management.hpp"
#include "inexor/server/map_management.hpp"
#include "inexor/server/network_send.hpp"

namespace server {

vector<demofile> demos;

bool demonextmatch = false;
stream *demotmp = nullptr, *demorecord = nullptr, *demoplayback = nullptr;
int nextplayback = 0, demomillis = 0;

VAR(maxdemos, 0, 5, 25);
VAR(maxdemosize, 0, 16, 31);

void prunedemos(int extra = 0)
{
    int n = clamp(demos.length() + extra - maxdemos, 0, demos.length());
    if(n <= 0) return;
    loopi(n) delete[] demos[i].data;
    demos.remove(0, n);
}

void adddemo()
{
    if(!demotmp) return;
    int len = (int)min(demotmp->size(), stream::offset((maxdemosize<<20) + 0x10000));
    demofile &d = demos.add();
    time_t t = time(NULL);
    char *timestr = ctime(&t), *trim = timestr + strlen(timestr);
    while(trim>timestr && iscubespace(*--trim)) *trim = '\0';
    formatstring(d.info, "%s: %s, %s, %.2f%s", timestr, modename(gamemode), smapname, len > 1024*1024 ? len/(1024*1024.f) : len/1024.0f, len > 1024*1024 ? "MB" : "kB");
    sendservmsgf("demo \"%s\" recorded", d.info);
    d.data = new uchar[len];
    d.len = len;
    demotmp->seek(0, SEEK_SET);
    demotmp->read(d.data, len);
    DELETEP(demotmp);
}

void enddemorecord()
{
    if(!demorecord) return;

    DELETEP(demorecord);

    if(!demotmp) return;
    if(!maxdemos || !maxdemosize) { DELETEP(demotmp); return; }

    prunedemos(1);
    adddemo();
}

void writedemo(int chan, void *data, int len)
{
    if(!demorecord) return;
    int stamp[3] ={gamemillis, chan, len};
    lilswap(stamp, 3);
    demorecord->write(stamp, sizeof(stamp));
    demorecord->write(data, len);
    if(demorecord->rawtell() >= (maxdemosize<<20)) enddemorecord();
}

void recordpacket(int chan, void *data, int len)
{
    writedemo(chan, data, len);
}

extern int welcomepacket(packetbuf &p, clientinfo *ci);
extern void sendwelcome(clientinfo *ci);

void setupdemorecord()
{
    if(m_edit) return;

    demotmp = opentempfile("demorecord", "w+b");
    if(!demotmp) return;

    stream *f = opengzfile(NULL, "wb", demotmp);
    if(!f) { DELETEP(demotmp); return; }

    sendservmsg("recording demo");

    demorecord = f;

    demoheader hdr;
    memcpy(hdr.magic, DEMO_MAGIC, sizeof(hdr.magic));
    hdr.version = DEMO_VERSION;
    hdr.protocol = PROTOCOL_VERSION;
    lilswap(&hdr.version, 2);
    demorecord->write(&hdr, sizeof(demoheader));

    packetbuf p(MAXTRANS, ENET_PACKET_FLAG_RELIABLE);
    welcomepacket(p, NULL);
    writedemo(1, p.buf, p.len);
}

void listdemos(int cn)
{
    packetbuf p(MAXTRANS, ENET_PACKET_FLAG_RELIABLE);
    putint(p, N_SENDDEMOLIST);
    putint(p, demos.length());
    loopv(demos) sendstring(demos[i].info, p);
    sendpacket(cn, 1, p.finalize());
}

void cleardemos(int n)
{
    if(!n)
    {
        loopv(demos) delete[] demos[i].data;
        demos.shrink(0);
        sendservmsg("cleared all demos");
    }
    else if(demos.inrange(n-1))
    {
        delete[] demos[n-1].data;
        demos.remove(n-1);
        sendservmsgf("cleared demo %d", n);
    }
}


static void freegetdemo(ENetPacket *packet)
{
    loopv(clients)
    {
        clientinfo *ci = clients[i];
        if(ci->getdemo == packet) ci->getdemo = NULL;
    }
}

void senddemo(clientinfo *ci, int num)
{
    if(ci->getdemo) return;
    if(!num) num = demos.length();
    if(!demos.inrange(num-1)) return;
    demofile &d = demos[num-1];
    if((ci->getdemo = sendf(ci->clientnum, 2, "rim", N_SENDDEMO, d.len, d.data)))
        ci->getdemo->freeCallback = freegetdemo;
}

void enddemoplayback()
{
    if(!demoplayback) return;
    DELETEP(demoplayback);

    loopv(clients) sendf(clients[i]->clientnum, 1, "ri3", N_DEMOPLAYBACK, 0, clients[i]->clientnum);

    sendservmsg("demo playback finished");

    gamemode = 0;
    loopv(clients) sendwelcome(clients[i]);
}

void setupdemoplayback()
{
    if(demoplayback) return;
    demoheader hdr;
    string msg;
    msg[0] = '\0';
    defformatstring(file, "%s.dmo", smapname);
    demoplayback = opengzfile(file, "rb");
    if(!demoplayback) formatstring(msg, "could not read demo \"%s\"", file);
    else if(demoplayback->read(&hdr, sizeof(demoheader))!=sizeof(demoheader) || memcmp(hdr.magic, DEMO_MAGIC, sizeof(hdr.magic)))
        formatstring(msg, "\"%s\" is not a demo file", file);
    else
    {
        lilswap(&hdr.version, 2);
        if(hdr.version!=DEMO_VERSION) formatstring(msg, "demo \"%s\" requires an %s version of Inexor", file, hdr.version<DEMO_VERSION ? "older" : "newer");
        else if(hdr.protocol!=PROTOCOL_VERSION) formatstring(msg, "demo \"%s\" requires an %s version of Inexor", file, hdr.protocol<PROTOCOL_VERSION ? "older" : "newer");
    }
    if(msg[0])
    {
        DELETEP(demoplayback);
        sendservmsg(msg);
        return;
    }

    sendservmsgf("playing demo \"%s\"", file);

    demomillis = 0;
    sendf(-1, 1, "ri3", N_DEMOPLAYBACK, 1, -1);

    if(demoplayback->read(&nextplayback, sizeof(nextplayback))!=sizeof(nextplayback))
    {
        enddemoplayback();
        return;
    }
    lilswap(&nextplayback, 1);
}

void readdemo()
{
    if(!demoplayback) return;
    demomillis += curtime;
    while(demomillis>=nextplayback)
    {
        int chan, len;
        if(demoplayback->read(&chan, sizeof(chan))!=sizeof(chan) ||
           demoplayback->read(&len, sizeof(len))!=sizeof(len))
        {
            enddemoplayback();
            return;
        }
        lilswap(&chan, 1);
        lilswap(&len, 1);
        ENetPacket *packet = enet_packet_create(NULL, len+1, 0);
        if(!packet || demoplayback->read(packet->data+1, len)!=size_t(len))
        {
            if(packet) enet_packet_destroy(packet);
            enddemoplayback();
            return;
        }
        packet->data[0] = N_DEMOPACKET;
        sendpacket(-1, chan, packet);
        if(!packet->referenceCount) enet_packet_destroy(packet);
        if(!demoplayback) break;
        if(demoplayback->read(&nextplayback, sizeof(nextplayback))!=sizeof(nextplayback))
        {
            enddemoplayback();
            return;
        }
        lilswap(&nextplayback, 1);
    }
}

void stopdemo()
{
    if(m_demo) enddemoplayback();
    else enddemorecord();
}

} // ns server
