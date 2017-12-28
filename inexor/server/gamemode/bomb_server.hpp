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

    void setup();

    bool parsespawnloc(ucharbuf &p, bool commit);

    void updatelimbo();

    void leavegame(clientinfo *ci, bool disconnecting);

    void sendspawnlocs(bool resuscitate = false);

    bool gamerunning();

    bool canspawn(clientinfo *ci, bool connecting);

    void pushentity(int type, vec o);

    void died(clientinfo *target, clientinfo *actor);

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam);

    void cleanup()
    {
        spawnlocs.deletecontents();
    }

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override;
};




} // ns server
