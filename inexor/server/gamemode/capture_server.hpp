#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/capture_common.hpp"
#include "inexor/server/gamemode/gamemode_server.hpp"
#include "inexor/util/legacy_time.hpp"

namespace server {

struct captureservermode : servmode, capturemode_common
{
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

    void update();

    void sendbaseinfo(int i);

    void sendbases();

    void initclient(clientinfo *ci, packetbuf &p, bool connecting);

    void endcheck();

    void entergame(clientinfo *ci)
    {
        if(notgotbases || ci->state.state!=CS_ALIVE || ci->gameclip) return;
        enterbases(ci->team, ci->state.o);
    }

    void spawned(clientinfo *ci)
    {
        if(notgotbases || ci->gameclip) return;
        enterbases(ci->team, ci->state.o);
    }

    void leavegame(clientinfo *ci, bool disconnecting = false)
    {
        if(notgotbases || ci->state.state!=CS_ALIVE || ci->gameclip) return;
        leavebases(ci->team, ci->state.o);
    }

    void died(clientinfo *ci, clientinfo *actor)
    {
        if(notgotbases || ci->gameclip) return;
        leavebases(ci->team, ci->state.o);
    }

    bool canspawn(clientinfo *ci, bool connecting)
    {
        return m_regencapture || connecting || !ci->state.lastdeath || gamemillis+curtime-ci->state.lastdeath >= RESPAWNSECS*1000;
    }

    void moved(clientinfo *ci, const vec &oldpos, bool oldclip, const vec &newpos, bool newclip)
    {
        if(notgotbases) return;
        movebases(ci->team, oldpos, oldclip, newpos, newclip);
    }

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam);

    void parsebases(ucharbuf &p, bool commit);

    bool extinfoteam(const char *team, ucharbuf &p);

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override;
};




} // ns server
