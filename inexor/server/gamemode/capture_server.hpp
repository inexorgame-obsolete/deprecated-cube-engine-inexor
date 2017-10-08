#pragma once
#include "inexor/gamemode/capture_common.hpp"          // for capturemode_co...
#include "inexor/gamemode/gamemode.hpp"                // for m_regencapture
#include "inexor/network/legacy/buffer_types.hpp"      // for packetbuf (ptr...
#include "inexor/server/client_management.hpp"         // for clientinfo
#include "inexor/server/gamemode/gamemode_server.hpp"  // for servmode
#include "inexor/shared/ents.hpp"                      // for ::CS_ALIVE
#include "inexor/shared/geom.hpp"                      // for vec
#include "inexor/util/legacy_time.hpp"                 // for curtime, gamem...

namespace server {

struct captureservermode : servmode, capturemode_common
{
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

    void stealbase(int n, const char *team);

    void replenishammo(clientinfo *ci);

    void movebases(const char *team, const vec &oldpos, bool oldclip, const vec &newpos, bool newclip);

    void leavebases(const char *team, const vec &o)
    {
        movebases(team, o, false, vec(-1e10f, -1e10f, -1e10f), true);
    }

    void enterbases(const char *team, const vec &o)
    {
        movebases(team, vec(-1e10f, -1e10f, -1e10f), true, o, false);
    }

    void addscore(int base, const char *team, int n);

    void regenowners(baseinfo &b, int ticks);

    void update() override;

    void sendbaseinfo(int i);

    void sendbases();

    void initclient(clientinfo *ci, packetbuf &p, bool connecting) override;

    void endcheck();

    void entergame(clientinfo *ci) override
    {
        if(notgotbases || ci->state.state!=CS_ALIVE || ci->gameclip) return;
        enterbases(ci->team, ci->state.o);
    }

    void spawned(clientinfo *ci) override
    {
        if(notgotbases || ci->gameclip) return;
        enterbases(ci->team, ci->state.o);
    }

    void leavegame(clientinfo *ci, bool disconnecting = false) override
    {
        if(notgotbases || ci->state.state!=CS_ALIVE || ci->gameclip) return;
        leavebases(ci->team, ci->state.o);
    }

    void died(clientinfo *ci, clientinfo *actor) override
    {
        if(notgotbases || ci->gameclip) return;
        leavebases(ci->team, ci->state.o);
    }

    bool canspawn(clientinfo *ci, bool connecting) override
    {
        return connecting || !ci->state.lastdeath || gamemillis+curtime-ci->state.lastdeath >= (m_regencapture ? REGENRESPAWNSECS : RESPAWNSECS)*1000;
    }

    void moved(clientinfo *ci, const vec &oldpos, bool oldclip, const vec &newpos, bool newclip) override
    {
        if(notgotbases) return;
        movebases(ci->team, oldpos, oldclip, newpos, newclip);
    }

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam) override;

    void parsebases(ucharbuf &p, bool commit);

    bool extinfoteam(const char *team, ucharbuf &p) override;

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override;
};




} // ns server
