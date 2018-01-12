#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/collect_common.hpp"          // for collectmode_co...
#include "inexor/gamemode/gamemode.hpp"                // for isteam
#include "inexor/network/legacy/buffer_types.hpp"      // for packetbuf (ptr...
#include "inexor/server/client_management.hpp"         // for clientinfo
#include "inexor/server/gamemode/gamemode_server.hpp"  // for servmode
#include "inexor/util/legacy_time.hpp"                 // for curtime, gamem...

struct vec;

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

    void cleanup() override
    {
        reset(false);
    }

    void setup() override;

    void newmap() override
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

    void leavegame(clientinfo *ci, bool disconnecting = false) override;

    void died(clientinfo *ci, clientinfo *actor) override
    {
        droptokens(ci, !actor || isteam(actor->team, ci->team));
    }

    bool canspawn(clientinfo *ci, bool connecting) override
    {
        return connecting || !ci->state.lastdeath || gamemillis+curtime-ci->state.lastdeath >= RESPAWNSECS*1000;
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam) override
    {
        return collectteambase(newteam) > 0;
    }

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam) override
    {
    }

    void deposittokens(clientinfo *ci, int basenum);

    void taketoken(clientinfo *ci, int id);

    void update() override;

    void initclient(clientinfo *ci, packetbuf &p, bool connecting) override;

    void parsebases(ucharbuf &p, bool commit);

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override;
};



} // ns server
