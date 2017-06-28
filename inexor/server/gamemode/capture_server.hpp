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

    void setup()
    {
        reset(false);
        if(notgotitems || ments.empty()) return;
        loopv(ments)
        {
            entity &e = ments[i];
            if(e.type != BASE) continue;
            int ammotype = e.attr1;
            addbase(ammotype, e.o);
        }
        notgotbases = false;
        sendbases();
        loopv(clients) if(clients[i]->state.state==CS_ALIVE) entergame(clients[i]);
    }

    void newmap()
    {
        reset(true);
    }

    void stealbase(int n, const char *team)
    {
        baseinfo &b = bases[n];
        loopv(clients)
        {
            clientinfo *ci = clients[i];
            if(ci->state.state==CS_ALIVE && ci->team[0] && !strcmp(ci->team, team) && insidebase(b, ci->state.o))
                b.enter(ci->team);
        }
        sendbaseinfo(n);
    }

    void replenishammo(clientinfo *ci)
    {
        if(m_noitems || notgotbases || ci->state.state!=CS_ALIVE || !ci->team[0]) return;
        loopv(bases)
        {
            baseinfo &b = bases[i];
            if(b.valid() && insidebase(b, ci->state.o) && !ci->state.hasmaxammo(b.ammotype-1+I_SHELLS) && b.takeammo(ci->team))
            {
                sendbaseinfo(i);
                sendf(-1, 1, "riii", N_REPAMMO, ci->clientnum, b.ammotype);
                ci->state.addammo(b.ammotype);
                break;
            }
        }
    }

    void movebases(const char *team, const vec &oldpos, bool oldclip, const vec &newpos, bool newclip)
    {
        if(!team[0] || gamemillis>=gamelimit) return;
        loopv(bases)
        {
            baseinfo &b = bases[i];
            if(!b.valid()) continue;
            bool leave = !oldclip && insidebase(b, oldpos),
                enter = !newclip && insidebase(b, newpos);
            if(leave && !enter && b.leave(team)) sendbaseinfo(i);
            else if(enter && !leave && b.enter(team)) sendbaseinfo(i);
            else if(leave && enter && b.steal(team)) stealbase(i, team);
        }
    }

    void leavebases(const char *team, const vec &o)
    {
        movebases(team, o, false, vec(-1e10f, -1e10f, -1e10f), true);
    }

    void enterbases(const char *team, const vec &o)
    {
        movebases(team, vec(-1e10f, -1e10f, -1e10f), true, o, false);
    }

    void addscore(int base, const char *team, int n)
    {
        if(!n) return;
        score &cs = findscore(team);
        cs.total += n;
        sendf(-1, 1, "riisi", N_BASESCORE, base, team, cs.total);
    }

    void regenowners(baseinfo &b, int ticks)
    {
        loopv(clients)
        {
            clientinfo *ci = clients[i];
            if(ci->state.state==CS_ALIVE && ci->team[0] && !strcmp(ci->team, b.owner) && insidebase(b, ci->state.o))
            {
                bool notify = false;
                if(ci->state.health < ci->state.maxhealth)
                {
                    ci->state.health = min(ci->state.health + ticks*REGENHEALTH, ci->state.maxhealth);
                    notify = true;
                }
                if(ci->state.armourtype != A_GREEN || ci->state.armour < itemstats[I_GREENARMOUR-I_SHELLS].max)
                {
                    if(ci->state.armourtype != A_GREEN)
                    {
                        ci->state.armourtype = A_GREEN;
                        ci->state.armour = 0;
                    }
                    ci->state.armour = min(ci->state.armour + ticks*REGENARMOUR, itemstats[I_GREENARMOUR-I_SHELLS].max);
                    notify = true;
                }
                if(b.valid())
                {
                    int ammotype = b.ammotype-1+I_SHELLS;
                    if(!ci->state.hasmaxammo(ammotype))
                    {
                        ci->state.addammo(b.ammotype, ticks*REGENAMMO, 100);
                        notify = true;
                    }
                }
                if(notify)
                    sendf(-1, 1, "ri6", N_BASEREGEN, ci->clientnum, ci->state.health, ci->state.armour, b.ammotype, b.valid() ? ci->state.ammo[b.ammotype] : 0);
            }
        }
    }

    void update()
    {
        if(gamemillis>=gamelimit) return;
        endcheck();
        int t = gamemillis/1000 - (gamemillis-curtime)/1000;
        if(t<1) return;
        loopv(bases)
        {
            baseinfo &b = bases[i];
            if(!b.valid()) continue;
            if(b.enemy[0])
            {
                if(!b.owners || !b.enemies) b.occupy(b.enemy, OCCUPYBONUS*(b.enemies ? 1 : -1) + OCCUPYPOINTS*(b.enemies ? b.enemies : -(1+b.owners))*t);
                sendbaseinfo(i);
            } else if(b.owner[0])
            {
                b.capturetime += t;

                int score = b.capturetime/SCORESECS - (b.capturetime-t)/SCORESECS;
                if(score) addscore(i, b.owner, score);

                if(m_regencapture)
                {
                    int regen = b.capturetime/REGENSECS - (b.capturetime-t)/REGENSECS;
                    if(regen) regenowners(b, regen);
                } else
                {
                    int ammo = b.capturetime/AMMOSECS - (b.capturetime-t)/AMMOSECS;
                    if(ammo && b.addammo(ammo)) sendbaseinfo(i);
                }
            }
        }
    }

    void sendbaseinfo(int i)
    {
        baseinfo &b = bases[i];
        sendf(-1, 1, "riissii", N_BASEINFO, i, b.owner, b.enemy, b.enemy[0] ? b.converted : 0, b.owner[0] ? b.ammo : 0);
    }

    void sendbases()
    {
        packetbuf p(MAXTRANS, ENET_PACKET_FLAG_RELIABLE);
        initclient(NULL, p, false);
        sendpacket(-1, 1, p.finalize());
    }

    void initclient(clientinfo *ci, packetbuf &p, bool connecting)
    {
        if(connecting)
        {
            loopv(scores)
            {
                score &cs = scores[i];
                putint(p, N_BASESCORE);
                putint(p, -1);
                sendstring(cs.team, p);
                putint(p, cs.total);
            }
        }
        putint(p, N_BASES);
        putint(p, bases.length());
        loopv(bases)
        {
            baseinfo &b = bases[i];
            putint(p, b.ammotype);
            sendstring(b.owner, p);
            sendstring(b.enemy, p);
            putint(p, b.converted);
            putint(p, b.ammo);
        }
    }

    void endcheck()
    {
        const char *lastteam = NULL;

        loopv(bases)
        {
            baseinfo &b = bases[i];
            if(!b.valid()) continue;
            if(b.owner[0])
            {
                if(!lastteam) lastteam = b.owner;
                else if(strcmp(lastteam, b.owner))
                {
                    lastteam = NULL;
                    break;
                }
            } else
            {
                lastteam = NULL;
                break;
            }
        }

        if(!lastteam) return;
        findscore(lastteam).total = 10000;
        sendf(-1, 1, "riisi", N_BASESCORE, -1, lastteam, 10000);
        startintermission();
    }

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

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
        if(notgotbases || ci->gameclip) return;
        leavebases(oldteam, ci->state.o);
        enterbases(newteam, ci->state.o);
    }

    void parsebases(ucharbuf &p, bool commit)
    {
        int numbases = getint(p);
        loopi(numbases)
        {
            int ammotype = getint(p);
            vec o;
            loopk(3) o[k] = max(getint(p)/DMF, 0.0f);
            if(p.overread()) break;
            if(commit && notgotbases) addbase(ammotype>=GUN_SG && ammotype<=GUN_PISTOL ? ammotype : min(ammotype, 0), o);
        }
        if(commit && notgotbases)
        {
            notgotbases = false;
            sendbases();
            loopv(clients) if(clients[i]->state.state==CS_ALIVE) entergame(clients[i]);
        }
    }

    bool extinfoteam(const char *team, ucharbuf &p)
    {
        int numbases = 0;
        loopvj(bases) if(!strcmp(bases[j].owner, team)) numbases++;
        putint(p, numbases);
        loopvj(bases) if(!strcmp(bases[j].owner, team)) putint(p, j);
        return true;
    }

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override
    {
        switch(type)
        {
            case N_BASES:
                parsebases(p, (ci->state.state!=CS_SPECTATOR || ci->privilege || ci->local) && !strcmp(ci->clientmap, smapname));
                return true;

            case N_REPAMMO:
                if((ci->state.state!=CS_SPECTATOR || ci->local || ci->privilege) && cq) replenishammo(cq);
                return true;
        }
        return false;
    }
};




} // ns server
