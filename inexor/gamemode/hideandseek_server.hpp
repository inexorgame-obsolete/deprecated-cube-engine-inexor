#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/hideandseek_common.hpp"
#include "inexor/gamemode/gamemode_server.hpp"

#define ishider(ci) (strcmp(ci->team, TEAM_HIDE) == 0 && ci->state.state != CS_SPECTATOR ? true : false)
#define isseeker(ci) (strcmp(ci->team, TEAM_SEEK) == 0 && ci->state.state != CS_SPECTATOR ? true : false)

namespace server {

struct hideandseekservermode : servmode, hideandseekmode
{
    struct seekersinfo
    {
        int cn;
        bool freezed;
        seekersinfo(int cn_, bool freezed_) : cn(cn_), freezed(freezed_) {}
    };

    vector<seekersinfo*> seekersinfos;
    int lastupdatecheck;

    void setup()
    {
        lastupdatecheck = totalmillis;
        seekersinfos.deletecontents();
        initplayers();
    }

    void initplayers()
    {
        loopv(clients) initplayer(clients[i]);
        vector<clientinfo*> activeplayers = getactiveplayers();
        if(activeplayers.length() < 2) return;
        int seeker = rnd(activeplayers.length());
        setseeker(activeplayers[seeker]);
    }

    void initplayer(clientinfo *ci)
    {
        sethider(ci);
    }

    void initclient(clientinfo *ci, packetbuf &p, bool connecting)
    {
        setseeker(ci);
    }

    void connected(clientinfo *ci)
    {
        setseeker(ci);
    }

    void leavegame(clientinfo *ci, bool disconnecting)
    {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum)
        {
            seekersinfos[i]->cn = -1;
        }
    }

    void cleanup()
    {
        seekersinfos.deletecontents();
    }

    bool checkfinished()
    {
        if(interm) return false;
        // if all seekers are freezed and there are at least 2 players
        if(getactiveplayers().length() >= 2 && getnonfreezedseekers() == 0) return true;
        // check if no hider is alive
        loopv(clients) if(ishider(clients[i])) return false;
        return true;
    }

    void update()
    {
        if(totalmillis > lastupdatecheck + 1000)
        {
            lastupdatecheck = totalmillis;
            if(checkfinished()) forceintermission();
        }
    }

    void intermission()
    {
    }

    void spawned(fpsent *d)
    {
    }

    bool canspawn(clientinfo *ci, bool connecting)
    {
        return true;
    }

    bool canhit(clientinfo *target, clientinfo *actor)
    {
        // teamkills and suicides are disabled; hiders can't kill
        // defformatstring(msg)("sameplayer:%s sameteam:%s ishider(actor):%s", actor==target?"true":"false", isteam(actor->team, target->team)?"true":"false", ishider(actor)?"true":"false");
        // sendservmsg(msg);
        // if(!m_freeze && isteam(actor->team, target->team) || ishider(actor)) return false;
        if(!actor || !target || actor==target) return false;
        if(isteam(actor->team, target->team) || ishider(actor)) return false;
        return true;
    }

    void died(clientinfo *target, clientinfo *actor)
    {
        if(target && ishider(target))
        {
            setseeker(target);
            int remaining = getremaininghiders();
            if(!actor)
            {
                if(remaining > 0)
                {
                    defformatstring(msg, "%s suicided! %d Hiders remaining!", target->name, remaining);
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                } else
                {
                    defformatstring(msg, "%s suicided! All Hiders eliminated!", target->name);
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                }
            } else
            {
                if(remaining > 0)
                {
                    defformatstring(msg, "%s killed %s! %d Hiders remaining!", actor->name, target->name, remaining);
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                } else
                {
                    defformatstring(msg, "%s killed %s! All Hiders eliminated!", actor->name, target->name);
                    sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                }
            }
        }
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
        return false;
    }

    void setseeker(clientinfo *ci)
    {
        copystring(ci->team, TEAM_SEEK, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
        seekersinfos.add(new seekersinfo(ci->clientnum, false));
    }

    void sethider(clientinfo *ci)
    {
        copystring(ci->team, TEAM_HIDE, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
    }

    vector<clientinfo*> getactiveplayers()
    {
        vector<clientinfo*> activepl;
        loopv(clients)
        {
            clientinfo* ci = clients[i];
            if(ci->state.state == CS_SPECTATOR) continue;
            activepl.add(ci);
        }
        return activepl;
    }

    int getremaininghiders()
    {
        int numhiders = 0;
        loopv(clients) if(ishider(clients[i])) numhiders++;
        return numhiders;
    }

    bool isfreezed(clientinfo *ci)
    {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum && seekersinfos[i]->freezed) return true;
        return false;
    }

    void setfreezedstate(clientinfo *ci, bool state)
    {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum) seekersinfos[i]->freezed = state;
    }

    int getnonfreezedseekers()
    {
        int numseekers = 0;
        loopv(seekersinfos) if(seekersinfos[i]->cn != -1 && !seekersinfos[i]->freezed) numseekers++;
        return numseekers;
    }

    void announceseekers(char* msg)
    {
        loopv(clients) if(isseeker(clients[i]))
        {
            sendf(clients[i]->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_TOP, msg);
        }
    }

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override
    {
        switch(type)
        {
            /*
            case N_RACEFINISH:
            {
            break;
            }
            */
            default: break;
        }
        return false;
    }
};




} // ns server
