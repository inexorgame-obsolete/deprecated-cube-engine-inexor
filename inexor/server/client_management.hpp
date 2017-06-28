#pragma once

#include "inexor/shared/cube_types.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/ents.hpp"
#include "inexor/fpsgame/fpsstate.hpp"
#include "inexor/network/SharedTree.hpp"
#include "inexor/network/legacy/administration.hpp"

#include <enet/enet.h>

#include <algorithm>

extern void *getclientinfo(int i);
extern ENetPeer *getclientpeer(int i);

extern SharedVar<int> maxclients;
extern SharedVar<int> maxdupclients;

#define DEFAULTCLIENTS 16

/// server side version of "dynent" type
struct client
{
    bool connected;
    int num;
    ENetPeer *peer;
    string hostname;
    void *info;
};
extern vector<client *> clients;

extern client &addclient();
extern void delclient(client *c);
extern void disconnect_client(int n, int reason);
extern bool has_clients();
extern int get_num_clients();


namespace server {


static constexpr int DEATHMILLIS = 300;

extern int nextexceeded;

template <int N>
struct projectilestate
{
    int projs[N];
    int numprojs;

    projectilestate() : numprojs(0) {}

    void reset() { numprojs = 0; }

    void add(int val)
    {
        if(numprojs>=N) numprojs = 0;
        projs[numprojs++] = val;
    }

    bool remove(int val)
    {
        loopi(numprojs) if(projs[i]==val)
        {
            projs[i] = projs[--numprojs];
            return true;
        }
        return false;
    }
};

/// server specialisation of the fpsstate (?)
struct gamestate : fpsstate
{
    vec o;
    int state, editstate;
    int lastdeath, deadflush, lastspawn, lifesequence;
    int lastshot;
    projectilestate<8> rockets, grenades, bombs;
    int frags, flags, deaths, teamkills,
        shotdamage, //all damage your shots could have made
        damage, tokens;
    int lasttimeplayed, timeplayed;
    float effectiveness;

    gamestate() : state(CS_DEAD), editstate(CS_DEAD), lifesequence(0) {}

    bool isalive(int gamemillis)
    {
        return state==CS_ALIVE || (state==CS_DEAD && gamemillis - lastdeath <= DEATHMILLIS);
    }

    bool waitexpired(int gamemillis)
    {
        return gamemillis - lastshot >= gunwait;
    }

    void reset()
    {
        if(state!=CS_SPECTATOR) state = editstate = CS_DEAD;
        maxhealth = 100;
        rockets.reset();
        grenades.reset();
        bombs.reset();

        timeplayed = 0;
        effectiveness = 0;
        frags = flags = deaths = teamkills = shotdamage = damage = tokens = 0;

        lastdeath = 0;

        respawn();
    }

    void respawn()
    {
        fpsstate::respawn();
        o = vec(-1e10f, -1e10f, -1e10f);
        deadflush = 0;
        lastspawn = -1;
        lastshot = 0;
        tokens = 0;
    }

    void reassign()
    {
        respawn();
        rockets.reset();
        grenades.reset();
        bombs.reset();
    }

    void setbackupweapon(int weapon)
    {
        fpsstate::backupweapon = weapon;
    }
};

struct clientinfo;

// Events

struct gameevent
{
    virtual ~gameevent() {}

    virtual bool flush(clientinfo *ci, int fmillis);
    virtual void process(clientinfo *ci) {}

    virtual bool keepable() const { return false; }
};

struct timedevent : gameevent
{
    int millis;

    bool flush(clientinfo *ci, int fmillis);
};

struct hitinfo
{
    int target;
    int lifesequence;
    int rays;
    float dist;
    vec dir;
};

struct shotevent : timedevent
{
    int id, gun;
    vec from, to;
    vector<hitinfo> hits;

    void process(clientinfo *ci);
};

struct explodeevent : timedevent
{
    int id, gun;
    vector<hitinfo> hits;

    bool keepable() const { return true; }

    void process(clientinfo *ci);
};

struct suicideevent : gameevent
{
    void process(clientinfo *ci);
};

struct pickupevent : gameevent
{
    int ent;

    void process(clientinfo *ci);
};


struct clientinfo
{
    int clientnum, ownernum, connectmillis, sessionid, overflow;
    string name, tag, team, mapvote;
    int playermodel;
    int fov;
    int modevote;
    int privilege;
    bool connected, local, timesync;
    int gameoffset, lastevent, pushed, exceeded;
    gamestate state;
    vector<gameevent *> events;
    vector<uchar> position, messages;
    uchar *wsdata;
    int wslen;
    vector<clientinfo *> bots;
    int ping, aireinit;
    string clientmap;
    int mapcrc;
    bool warned, gameclip;
    ENetPacket *getdemo, *getmap, *clipboard;
    int lastclipboard, needclipboard;

    clientinfo() : getdemo(NULL), getmap(NULL), clipboard(NULL) { reset(); }
    ~clientinfo() { events.deletecontents(); cleanclipboard(); }

    void addevent(gameevent *e)
    {
        if(state.state==CS_SPECTATOR || events.length()>100) delete e;
        else events.add(e);
    }

    enum
    {
        PUSHMILLIS = 3000
    };

    int calcpushrange()
    {
        ENetPeer *peer = getclientpeer(ownernum);
        return PUSHMILLIS + (peer ? peer->roundTripTime + peer->roundTripTimeVariance : ENET_PEER_DEFAULT_ROUND_TRIP_TIME);
    }

    bool checkpushed(int millis, int range)
    {
        return millis >= pushed - range && millis <= pushed + range;
    }

    void scheduleexceeded()
    {
        if(state.state!=CS_ALIVE || !exceeded) return;
        int range = calcpushrange();
        if(!nextexceeded || exceeded + range < nextexceeded) nextexceeded = exceeded + range;
    }

    void setexceeded()
    {
        if(state.state==CS_ALIVE && !exceeded && !checkpushed(gamemillis, calcpushrange())) exceeded = gamemillis;
        scheduleexceeded();
    }

    void setpushed()
    {
        pushed = std::max(pushed, gamemillis);
        if(exceeded && checkpushed(exceeded, calcpushrange())) exceeded = 0;
    }

    bool checkexceeded()
    {
        return state.state==CS_ALIVE && exceeded && gamemillis > exceeded + calcpushrange();
    }

    void mapchange()
    {
        mapvote[0] = 0;
        modevote = INT_MAX;
        state.reset();
        events.deletecontents();
        overflow = 0;
        timesync = false;
        lastevent = 0;
        exceeded = 0;
        pushed = 0;
        clientmap[0] = '\0';
        mapcrc = 0;
        warned = false;
        gameclip = false;
    }

    void reassign()
    {
        state.reassign();
        events.deletecontents();
        timesync = false;
        lastevent = 0;
    }

    void cleanclipboard(bool fullclean = true)
    {
        if(clipboard) { if(--clipboard->referenceCount <= 0) enet_packet_destroy(clipboard); clipboard = NULL; }
        if(fullclean) lastclipboard = 0;
    }

    void reset()
    {
        name[0] = team[0] = tag[0] = 0;
        playermodel = -1;
        fov = 100;
        privilege = PRIV_NONE;
        connected = local = false;
        position.setsize(0);
        messages.setsize(0);
        ping = 0;
        aireinit = 0;
        needclipboard = 0;
        cleanclipboard();
        mapchange();
    }

    int geteventmillis(int servmillis, int clientmillis)
    {
        if(!timesync || (events.empty() && state.waitexpired(servmillis)))
        {
            timesync = true;
            gameoffset = servmillis - clientmillis;
            return servmillis;
        } else return gameoffset + clientmillis;
    }
};

extern vector<clientinfo *> connects, clients, bots;

/// Also recognizes bots.
/// ToDo: Merge both functions (getclientinfo and clientinfo) or better both structures client and clientinfo.
extern clientinfo *getinfo(int n);

struct ban
{
    int time, expire;
    uint ip;
};

namespace aiman
{
extern void removeai(clientinfo *ci);
extern void clearai();
extern void checkai();
extern void reqadd(clientinfo *ci, int skill);
extern void reqdel(clientinfo *ci);
extern void setbotlimit(clientinfo *ci, int limit);
extern void setbotbalance(clientinfo *ci, bool balance);
extern void changemap();
extern void addclient(clientinfo *ci);
extern void changeteam(clientinfo *ci);
}

} // ns server

#define MM_MODE 0xF
#define MM_AUTOAPPROVE 0x1000
#define MM_PRIVSERV (MM_MODE | MM_AUTOAPPROVE)
#define MM_PUBSERV ((1<<MM_OPEN) | (1<<MM_VETO))
#define MM_COOPSERV (MM_AUTOAPPROVE | MM_PUBSERV | (1<<MM_LOCKED))
