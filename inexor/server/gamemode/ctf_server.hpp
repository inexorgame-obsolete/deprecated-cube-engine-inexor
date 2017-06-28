#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/ctf_common.hpp"
#include "inexor/server/gamemode/gamemode_server.hpp"
#include "inexor/util/legacy_time.hpp"

namespace server {

struct ctfservermode : servmode, ctfmode
{
    bool addflag(int i, const vec &o, int team, int invistime = 0);

    void ownflag(int i, int owner, int owntime)
    {
        flag &f = flags[i];
        f.owntime = owntime;
        f.owner_id = owner;
        if(owner == f.dropper) { if(f.dropcount < INT_MAX) f.dropcount++; } else f.dropcount = 0;
        f.dropper = -1;
        f.invistime = 0;
    }

    void returnflag(int i, int invistime = 0)
    {
        flag &f = flags[i];
        f.droptime = 0;
        f.dropcount = 0;
        f.owner_id = f.dropper = -1;
        f.invistime = invistime;
        f.runstart = 0;
    }

    static const int RESETFLAGTIME = 10000;
    static const int INVISFLAGTIME = 20000;

    bool notgotflags;

    ctfservermode() : notgotflags(false) {}

    void reset(bool empty)
    {
        resetflags();
        notgotflags = !empty;
    }

    void cleanup()
    {
        reset(false);
    }

    void setupholdspawns()
    {
        if(!m_hold || holdspawns.empty()) return;
        while(flags.length() < HOLDFLAGS)
        {
            int i = flags.length();
            if(!addflag(i, vec(0, 0, 0), 0, 0)) break;
            flag &f = flags[i];
            spawnflag(i);
            sendf(-1, 1, "ri6", N_RESETFLAG, i, ++f.version, f.spawnindex, 0, 0);
        }
    }

    void setup()
    {
        reset(false);
        if(notgotitems || ments.empty()) return;
        if(m_hold)
        {
            loopv(ments)
            {
                entity &e = ments[i];
                if(e.type != BASE) continue;
                if(!addholdspawn(e.o)) break;
            }
            setupholdspawns();
        } else loopv(ments)
        {
            entity &e = ments[i];
            if(e.type != FLAG || e.attr2 < 1 || e.attr2 > 2) continue;
            if(!addflag(flags.length(), e.o, e.attr2, m_protect ? lastmillis : 0)) break;
        }
        notgotflags = false;
    }

    void newmap()
    {
        reset(true);
    }

    void dropflag(int i, const vec &o, int droptime, int dropper = -1, bool penalty = false)
    {
        flag &f = flags[i];
        f.droploc = o;
        f.droptime = droptime;
        if(dropper < 0) f.dropcount = 0;
        else if(penalty) f.dropcount = INT_MAX;
        f.dropper = dropper;
        f.owner_id = -1;
        f.invistime = 0;
        f.owner = NULL;
        if(!f.vistime) f.vistime = droptime;
    }

    void dropflag(clientinfo *ci, clientinfo *dropper = NULL)
    {
        if(notgotflags) return;
        loopv(flags) if(flags[i].owner_id == ci->clientnum)
        {
            flag &f = flags[i];
            if(m_protect && insidebase(f, ci->state.o))
            {
                returnflag(i);
                sendf(-1, 1, "ri4", N_RETURNFLAG, ci->clientnum, i, ++f.version);
            } else
            {
                ivec o(vec(ci->state.o).mul(DMF));
                sendf(-1, 1, "ri7", N_DROPFLAG, ci->clientnum, i, ++f.version, o.x, o.y, o.z);
                dropflag(i, vec(o).div(DMF), lastmillis, dropper ? dropper->clientnum : ci->clientnum, dropper && dropper!=ci);
            }
        }
    }

    void leavegame(clientinfo *ci, bool disconnecting = false)
    {
        dropflag(ci);
        loopv(flags) if(flags[i].dropper == ci->clientnum) { flags[i].dropper = -1; flags[i].dropcount = 0; }
    }

    void died(clientinfo *ci, clientinfo *actor);

    bool canspawn(clientinfo *ci, bool connecting)
    {
        return m_efficiency || !m_protect ? connecting || !ci->state.lastdeath || gamemillis+curtime-ci->state.lastdeath >= RESPAWNSECS*1000 : true;
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
        return ctfteamflag(newteam) > 0;
    }

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
        dropflag(ci);
    }

    void spawnflag(int i)
    {
        if(holdspawns.empty()) return;
        int spawnindex = flags[i].spawnindex;
        loopj(4)
        {
            spawnindex = rnd(holdspawns.length());
            if(spawnindex != flags[i].spawnindex) break;
        }
        flags[i].spawnindex = spawnindex;
    }

    void scoreflag(clientinfo *ci, int goal, int relay = -1)
    {
        int flagruntime = m_ctf && flags.inrange(relay) && flags[relay].runstart > 0 ? clamp(lastmillis-flags[relay].runstart, 0, 600000)/100 : 0;
        returnflag(relay >= 0 ? relay : goal, m_protect ? lastmillis : 0);
        ci->state.flags++;
        int team = ctfteamflag(ci->team), score = addscore(team, 1);
        if(m_hold) spawnflag(goal);
        sendf(-1, 1, "rii9i", N_SCOREFLAG, ci->clientnum, relay, relay >= 0 ? ++flags[relay].version : -1, goal, ++flags[goal].version, flags[goal].spawnindex, team, score, ci->state.flags, flagruntime);
        if(score >= FLAGLIMIT) startintermission();
    }

    void takeflag(clientinfo *ci, int i, int version)
    {
        if(notgotflags || !flags.inrange(i) || ci->state.state!=CS_ALIVE || !ci->team[0]) return;
        flag &f = flags[i];
        if((m_hold ? f.spawnindex < 0 : !ctfflagteam(f.team)) || f.owner_id>=0 || f.version != version || (f.droptime && f.dropper == ci->clientnum && f.dropcount >= 1)) return;
        int team = ctfteamflag(ci->team);
        if(m_hold || m_protect == (f.team==team))
        {
            loopvj(flags) if(flags[j].owner_id==ci->clientnum) return;
            if(!f.droptime) f.runstart = lastmillis;
            ownflag(i, ci->clientnum, lastmillis);
            sendf(-1, 1, "ri4", N_TAKEFLAG, ci->clientnum, i, ++f.version);
        } else if(m_protect)
        {
            if(!f.invistime) scoreflag(ci, i);
        } else if(f.droptime)
        {
            returnflag(i);
            sendf(-1, 1, "ri4", N_RETURNFLAG, ci->clientnum, i, ++f.version);
        } else
        {
            loopvj(flags) if(flags[j].owner_id==ci->clientnum) { scoreflag(ci, i, j); break; }
        }
    }

    void update()
    {
        if(gamemillis>=gamelimit || notgotflags) return;
        loopv(flags)
        {
            flag &f = flags[i];
            if(f.owner_id<0 && f.droptime && lastmillis - f.droptime >= RESETFLAGTIME)
            {
                returnflag(i, m_protect ? lastmillis : 0);
                if(m_hold) spawnflag(i);
                sendf(-1, 1, "ri6", N_RESETFLAG, i, ++f.version, f.spawnindex, m_hold ? 0 : f.team, m_hold ? 0 : addscore(f.team, m_protect ? -1 : 0));
            }
            if(f.invistime && lastmillis - f.invistime >= INVISFLAGTIME)
            {
                f.invistime = 0;
                sendf(-1, 1, "ri3", N_INVISFLAG, i, 0);
            }
            if(m_hold && f.owner_id>=0 && lastmillis - f.owntime >= HOLDSECS*1000)
            {
                clientinfo *ci = get_client_info(f.owner_id);
                if(ci) scoreflag(ci, i);
                else
                {
                    spawnflag(i);
                    sendf(-1, 1, "ri6", N_RESETFLAG, i, ++f.version, f.spawnindex, 0, 0);
                }
            }
        }
    }

    void initclient(clientinfo *ci, packetbuf &p, bool connecting)
    {
        putint(p, N_INITFLAGS);
        loopk(2) putint(p, scores[k]);
        putint(p, flags.length());
        loopv(flags)
        {
            flag &f = flags[i];
            putint(p, f.version);
            putint(p, f.spawnindex);
            putint(p, f.owner_id);
            putint(p, f.invistime ? 1 : 0);
            if(f.owner_id < 0)
            {
                putint(p, f.droptime ? 1 : 0);
                if(f.droptime)
                {
                    putint(p, int(f.droploc.x*DMF));
                    putint(p, int(f.droploc.y*DMF));
                    putint(p, int(f.droploc.z*DMF));
                }
            }
        }
    }

    void parseflags(ucharbuf &p, bool commit)
    {
        int numflags = getint(p);
        loopi(numflags)
        {
            int team = getint(p);
            vec o;
            loopk(3) o[k] = max(getint(p)/DMF, 0.0f);
            if(p.overread()) break;
            if(commit && notgotflags)
            {
                if(m_hold) addholdspawn(o);
                else addflag(i, o, team, m_protect ? lastmillis : 0);
            }
        }
        if(commit && notgotflags)
        {
            if(m_hold) setupholdspawns();
            notgotflags = false;
        }
    }

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override
    {
        switch(type)
        {
            case N_TRYDROPFLAG:
            {
                if((ci->state.state!=CS_SPECTATOR || ci->local || ci->privilege) && cq) dropflag(cq);
                return true;
            }

            case N_TAKEFLAG:
            {
                int flag = getint(p), version = getint(p);
                if((ci->state.state!=CS_SPECTATOR || ci->local || ci->privilege) && cq) takeflag(cq, flag, version);
                return true;
            }

            case N_INITFLAGS:
                parseflags(p, (ci->state.state!=CS_SPECTATOR || ci->privilege || ci->local) && !strcmp(ci->clientmap, smapname));
                return true;
        }
        return false;
    }
};




} // ns server
