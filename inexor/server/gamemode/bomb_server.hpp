#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/bomb_common.hpp"
#include "inexor/server/gamemode/gamemode_server.hpp"

namespace server {
extern void sendspawn(clientinfo *ci);

struct bombservermode : servmode, bombmode
{
    bool notgotspawnlocations;
    vector<spawnloc*> spawnlocs;
    int sequence, timecounter, countdown;

    static constexpr int COUNTDOWNSECONDS = 3;

    void setup() override;

    bool parsespawnloc(ucharbuf &p, bool commit);

    void updatelimbo() override;

    void leavegame(clientinfo *ci, bool disconnecting) override;

    void sendspawnlocs(bool resuscitate = false);

    bool gamerunning();

    bool canspawn(clientinfo *ci, bool connecting) override;

    void pushentity(int type, vec o);

    void died(clientinfo *target, clientinfo *actor) override;

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam) override;

    void cleanup() override
    {
        spawnlocs.deletecontents();
    }

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override;
};




} // ns server
