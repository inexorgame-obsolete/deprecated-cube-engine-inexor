#pragma once
#include "inexor/server/game_management.hpp"
#include "inexor/server/client_management.hpp"
#include "inexor/fpsgame/game.hpp"

// TODO: make vector<players> extendable by mode

namespace server {

// true when map has changed and waiting for clients to send item
extern bool notgotitems;

extern int gamemode;

extern string smapname;

extern int interm;

extern int gamelimit;

extern vector<entity> ments;
extern vector<server_entity> sents;

struct servmode
{
    virtual ~servmode() {}

    virtual void entergame(clientinfo *ci) {}
    virtual void leavegame(clientinfo *ci, bool disconnecting = false) {}
    virtual void connected(clientinfo *ci) {}

    virtual void moved(clientinfo *ci, const vec &oldpos, bool oldclip, const vec &newpos, bool newclip) {}
    virtual bool canspawn(clientinfo *ci, bool connecting = false) { return true; }
    virtual void spawned(clientinfo *ci) {}
    virtual int fragvalue(clientinfo *victim, clientinfo *actor)
    {
        if(victim==actor || isteam(victim->team, actor->team)) return -1;
        return 1;
    }
    virtual bool canhit(clientinfo *victim, clientinfo *actor) { return true; }
    virtual void died(clientinfo *victim, clientinfo *actor) {}
    virtual bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam) { return true; }
    virtual void changeteam(clientinfo *ci, const char *oldteam, const char *newteam) {}
    virtual void initclient(clientinfo *ci, packetbuf &p, bool connecting) {}
    virtual void update() {}
    virtual void updatelimbo() {}
    virtual void cleanup() {}
    virtual void setup() {}
    virtual void newmap() {}
    virtual void intermission() {}
    virtual bool hidefrags() { return false; }
    virtual int getteamscore(const char *team) { return 0; }
    virtual void getteamscores(vector<teamscore> &scores) {}
    virtual bool extinfoteam(const char *team, ucharbuf &p) { return false; }

    /// process gamemode specific network messages.
    /// @param ci the sender.
    /// @param cq the currently focused player (sender or bot from senders pc)
    /// @return whether this messages got processed.
    virtual bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) = 0;
};
} // ns server
