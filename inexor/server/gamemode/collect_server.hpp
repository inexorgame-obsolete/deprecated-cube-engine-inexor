#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/collect_common.hpp"
#include "inexor/server/gamemode/gamemode_server.hpp"

namespace server {

struct collectservermode : servmode, collectmode_common
{
    token &droptoken(const vec &o, int yaw, int team, int droptime, int dropper);
    bool notgotbases = false;

    void reset(bool empty)
    {
        resetbases();
        notgotbases = !empty;
    }

    void cleanup()
    {
        reset(false);
    }

    void setup();

    void newmap()
    {
        reset(true);
    }

#if 0
    void losetokens(clientinfo *ci)
    {
        if(notgotbases || ci->state.tokens <= 0) return;
        sendf(-1, 1, "ri2", N_LOSETOKENS, ci->clientnum);
        ci->state.tokens = 0;
    }
#endif

    void droptokens(clientinfo *ci, bool penalty = false);

    void leavegame(clientinfo *ci, bool disconnecting = false);

    void died(clientinfo *ci, clientinfo *actor)
    {
        droptokens(ci, !actor || isteam(actor->team, ci->team));
    }

    bool canspawn(clientinfo *ci, bool connecting)
    {
        return connecting || !ci->state.lastdeath || gamemillis+curtime-ci->state.lastdeath >= RESPAWNSECS*1000;
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
        return collectteambase(newteam) > 0;
    }

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
    }

    void deposittokens(clientinfo *ci, int basenum);

    void taketoken(clientinfo *ci, int id);

    void update();

    void initclient(clientinfo *ci, packetbuf &p, bool connecting);

    void parsebases(ucharbuf &p, bool commit);

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override;
};



} // ns server
