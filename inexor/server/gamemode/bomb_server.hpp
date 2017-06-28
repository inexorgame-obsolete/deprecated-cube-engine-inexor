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

    void setup()
    {
        sequence = 0;
        countdown = COUNTDOWNSECONDS;
        timecounter = totalmillis;
        pausegame(true);
        notgotspawnlocations = true;
        spawnlocs.deletecontents();
        if(!notgotitems)
        {
            loopv(ments)
            {
                if(ments[i].type != PLAYERSTART) continue;
                entity& e = ments[i];
                spawnlocs.add(new spawnloc(e.o, e.attr2, i));
            }
            notgotspawnlocations = false;
            sendspawnlocs();
        }
    }

    bool parsespawnloc(ucharbuf &p, bool commit)
    {
        int numsploc = getint(p);
        loopi(numsploc)
        {
            vec o;
            loopk(3) o[k] = max(getint(p)/DMF, 0.0f);
            int team = getint(p), index = getint(p);
            if(p.overread()) break;
            if(m_teammode ? team < 1 || team > 2 : team) return false;
            if(commit && notgotspawnlocations) spawnlocs.add(new spawnloc(o, team, index));
        }
        if(commit && notgotspawnlocations)
        {
            notgotspawnlocations = false;
            sendspawnlocs(true);
        }
        return true;
    }

    void updatelimbo()
    {
        if(notgotspawnlocations) return;
        switch(sequence)
        {
            case 0:
                if(totalmillis - timecounter >= 10000)
                {
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_BOTTOM, "Map load complete (grannies left behind)");
                } else
                {
                    loopv(spawnlocs)
                    {
                        if(spawnlocs[i]->cn == -1) continue;
                        clientinfo* ci = get_client_info(spawnlocs[i]->cn);
                        if(!ci || ci->state.state==CS_SPECTATOR || ci->state.aitype != AI_NONE || ci->clientmap[0] || ci->mapcrc) continue;
                        return;
                    }
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_BOTTOM, "Map load complete");
                }
                sequence = 1;
                timecounter = totalmillis;
                return;

            case 1:
            {
                int remaining = COUNTDOWNSECONDS*1000 - (totalmillis - timecounter);
                if(remaining <= 0)
                {
                    sequence = 2;
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 2000, E_ZOOM_IN, "F I G H T");
                    pausegame(false);
                } else if(remaining/1000 != countdown)
                {
                    defformatstring(msg, "- %d -", countdown--);
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 2000, E_ZOOM_IN, msg);
                }
                break;
            }

            case 2: break;
        }
    }

    void leavegame(clientinfo *ci, bool disconnecting)
    {
        if(!disconnecting) return;
        loopv(spawnlocs) if(spawnlocs[i]->cn == ci->clientnum)
        {
            spawnlocs[i]->cn = -1;
            break;
        }
    }

#define bombteamname(s) (!strcmp(s, "good") ? 1 : (!strcmp(s, "evil") ? 2 : 0))

    void sendspawnlocs(bool resuscitate = false)
    {
        vector<clientinfo*> activepl;
        loopv(clients)
        {
            clientinfo* ci = clients[i];
            if(ci->state.state == CS_SPECTATOR) continue;
            activepl.add(ci);
        }
        vector<spawnloc*> pool[3];
        loopv(spawnlocs) pool[spawnlocs[i]->team].add(spawnlocs[i]);
        loopi(3) pool[i].shuffle();
        for(int i = 0; i < activepl.length(); i++)
        {
            vector<spawnloc*>& tpool = pool[m_teammode ? bombteamname(activepl[i]->team) : 0];
            if(tpool.length())
            {
                tpool[0]->cn = activepl[i]->clientnum;
                sendf(tpool[0]->cn, 1, "ri2", N_SPAWNLOC, tpool[0]->index);
                if(resuscitate) sendspawn(activepl[i]);
                tpool.removeunordered(0);
            }
        }
    }

    bool gamerunning()
    {
        for(int cn = 0; cn < clients.length(); cn++)
            if(clients[cn]->state.deaths > 0) return true;
        return false;
    }

    bool canspawn(clientinfo *ci, bool connecting)
    {
        if(!m_lms) return true;
        if(gamerunning()) { spdlog::get("global")->info("game is running"); return false; }
        if(notgotspawnlocations) { spdlog::get("global")->info("not got spawn locations yet"); return false; }
        int i = 0;
        for(; i < spawnlocs.length(); i++) if(spawnlocs[i]->cn == ci->clientnum) break;
        if(i == spawnlocs.length()) { spdlog::get("global")->info("player has got no spawn location"); return false; }
        if(ci->state.deaths==0) { spdlog::get("global")->info("player has no deaths"); return true; } // ci->state.aitype!=AI_NONE &&
        sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1250, E_ZOOM_IN, "You cannot respawn this round");
        return false;
    }

    void pushentity(int type, vec o)
    {
        entity &e = ments.add();
        e.o = o;
        e.type = type;
        server_entity se ={NOTUSED, 0, false};
        while(sents.length()<=ments.length()+1) sents.add(se);
        int id = sents.length()-1;
        sents[id].type = ments[id].type;
        sents[id].spawned = true;
        ivec io(o.mul(DMF));
        sendf(-1, 1, "ri6", N_ITEMPUSH, id, type, io.x-120+rnd(240), io.y-120+rnd(240), io.z + rnd(2)*180);
    }

    void died(clientinfo *target, clientinfo *actor)
    {
        int leftitems = 0;
        for(int i=0; i<target->state.ammo[GUN_BOMB]/2; i++) { pushentity(I_BOMBS, target->state.o); leftitems++; }
        for(int i=0; i<target->state.bombradius/2; i++) { pushentity(I_BOMBRADIUS, target->state.o); leftitems++; }
        for(int i=0; i<target->state.bombdelay/3; i++) { pushentity(I_BOMBDELAY, target->state.o); leftitems++; }
        if(leftitems > 0)
        {
            defformatstring(msg, "%s died and left %d %s!", target->name, leftitems, leftitems > 1 ? "items" : "item");
            sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1250, E_ZOOM_OUT, msg);
        } else
        {
            defformatstring(msg, "%s died!", target->name);
            sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1250, E_ZOOM_OUT, msg);
        }
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
        return m_teammode && bombteamname(newteam) > 0;
    }

    void cleanup()
    {
        spawnlocs.deletecontents();
    }

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override
    {
        switch(type)
        {
            /*
            case N_KILLMOVABLE:
            {
            int id = getint(p);
            // if(m_bomb) bombmode.kill(flag, version, spawnindex, team, score);
            break;
            }
            */

            case N_SPAWNLOC:
            {
                if(!parsespawnloc(p, (ci->state.state!=CS_SPECTATOR || ci->privilege || ci->local) && !strcmp(ci->clientmap, smapname)))
                    disconnect_client(ci->clientnum, DISC_MSGERR);
                return true;
            }
        }
        return false;
    }
};




} // ns server
