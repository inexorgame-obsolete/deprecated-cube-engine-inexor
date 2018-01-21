#pragma once
#include "inexor/gamemode/bomb_common.hpp"             // for bombmode, spaw...
#include "inexor/network/legacy/buffer_types.hpp"      // for packetbuf (ptr...
#include "inexor/server/gamemode/gamemode_server.hpp"  // for servmode
#include "inexor/shared/cube_vector.hpp"               // for vector

struct vec;

namespace server {
struct clientinfo;

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
