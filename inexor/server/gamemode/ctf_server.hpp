#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/ctf_common.hpp"              // for ctfmode, ctfmo...
#include "inexor/gamemode/gamemode.hpp"                // for m_efficiency
#include "inexor/network/legacy/buffer_types.hpp"      // for packetbuf (ptr...
#include "inexor/server/client_management.hpp"         // for clientinfo
#include "inexor/server/gamemode/gamemode_server.hpp"  // for servmode
#include "inexor/util/legacy_time.hpp"                 // for curtime, gamem...

struct vec;

namespace server {

struct ctfservermode : servmode, ctfmode
{
    bool addflag(int i, const vec &o, int team, int invistime = 0);

    void ownflag(int i, int owner, int owntime);

    void returnflag(int i, int invistime = 0);

    static const int RESETFLAGTIME = 10000;
    static const int INVISFLAGTIME = 20000;

    bool notgotflags;

    ctfservermode() : notgotflags(false) {}

    void reset(bool empty)
    {
        resetflags();
        notgotflags = !empty;
    }

    void cleanup() override
    {
        reset(false);
    }

    void setupholdspawns();

    void setup() override;

    void newmap() override
    {
        reset(true);
    }

    void dropflag(int i, const vec &o, int droptime, int dropper = -1, bool penalty = false);

    void dropflag(clientinfo *ci, clientinfo *dropper = nullptr);

    void leavegame(clientinfo *ci, bool disconnecting = false) override;

    void died(clientinfo *ci, clientinfo *actor) override;

    bool canspawn(clientinfo *ci, bool connecting) override
    {
        return m_efficiency || !m_protect ? connecting || !ci->state.lastdeath || gamemillis+curtime-ci->state.lastdeath >= RESPAWNSECS*1000 : true;
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam) override
    {
        return ctfteamflag(newteam) > 0;
    }

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam) override
    {
        dropflag(ci);
    }

    void spawnflag(int i);

    void scoreflag(clientinfo *ci, int goal, int relay = -1);

    void takeflag(clientinfo *ci, int i, int version);

    void update() override;

    void initclient(clientinfo *ci, packetbuf &p, bool connecting) override;

    void parseflags(ucharbuf &p, bool commit);

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override;
};




} // ns server
