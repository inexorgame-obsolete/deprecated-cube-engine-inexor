
#include "inexor/fpsgame/teaminfo.hpp"           // for MAXTEAMLEN
#include "inexor/gamemode/gamemode.hpp"          // for isteam
#include "inexor/network/legacy/game_types.hpp"  // for ::N_HUDANNOUNCE, ::N...
#include "inexor/server/gamemode/hideandseek_server.hpp"
#include "inexor/server/network_send.hpp"        // for sendf
#include "inexor/shared/cube_formatting.hpp"     // for defformatstring
#include "inexor/shared/cube_loops.hpp"          // for i, loopv
#include "inexor/shared/cube_tools.hpp"          // for copystring
#include "inexor/shared/tools.hpp"               // for rnd
#include "inexor/ui/legacy/3dgui.hpp"            // for hudannounceeffects::...
#include "inexor/util/legacy_time.hpp"           // for totalmillis

namespace server {


    void hideandseekservermode::setup() {
        lastupdatecheck = totalmillis;
        seekersinfos.deletecontents();
        initplayers();
    }

    void hideandseekservermode::initplayers() {
        loopv(clients) initplayer(clients[i]);
        vector<clientinfo*> activeplayers = getactiveplayers();
        if(activeplayers.length() < 2) return;
        int seeker = rnd(activeplayers.length());
        setseeker(activeplayers[seeker]);
    }

    void hideandseekservermode::leavegame(clientinfo *ci, bool disconnecting) {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum)
            {
                seekersinfos[i]->cn = -1;
            }
    }

    bool hideandseekservermode::checkfinished() {
        if(interm) return false;
        // if all seekers are freezed and there are at least 2 players
        if(getactiveplayers().length() >= 2 && getnonfreezedseekers() == 0) return true;
        // check if no hider is alive
        loopv(clients) if(ishider(clients[i])) return false;
        return true;
    }

    void hideandseekservermode::update() {
        if(totalmillis > lastupdatecheck + 1000)
        {
            lastupdatecheck = totalmillis;
            if(checkfinished()) startintermission();
        }
    }

    bool hideandseekservermode::canhit(clientinfo *target, clientinfo *actor) {
        // teamkills and suicides are disabled; hiders can't kill
        // defformatstring(msg)("sameplayer:%s sameteam:%s ishider(actor):%s", actor==target?"true":"false", isteam(actor->team, target->team)?"true":"false", ishider(actor)?"true":"false");
        // sendservmsg(msg);
        // if(!m_freeze && isteam(actor->team, target->team) || ishider(actor)) return false;
        if(!actor || !target || actor==target) return false;
        if(isteam(actor->team, target->team) || ishider(actor)) return false;
        return true;
    }

    void hideandseekservermode::died(clientinfo *target, clientinfo *actor) {
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

    void hideandseekservermode::setseeker(clientinfo *ci) {
        copystring(ci->team, TEAM_SEEK, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
        seekersinfos.add(new seekersinfo(ci->clientnum, false));
    }

    void hideandseekservermode::sethider(clientinfo *ci) {
        copystring(ci->team, TEAM_HIDE, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
    }

    vector<clientinfo *> hideandseekservermode::getactiveplayers() {
        vector<clientinfo*> activepl;
        loopv(clients)
        {
            clientinfo* ci = clients[i];
            if(ci->state.state == CS_SPECTATOR) continue;
            activepl.add(ci);
        }
        return activepl;
    }

    int hideandseekservermode::getremaininghiders() {
        int numhiders = 0;
        loopv(clients) if(ishider(clients[i])) numhiders++;
        return numhiders;
    }

    void hideandseekservermode::announceseekers(char *msg) {
        loopv(clients) if(isseeker(clients[i]))
            {
                sendf(clients[i]->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_TOP, msg);
            }
    }

    int hideandseekservermode::getnonfreezedseekers() {
        int numseekers = 0;
        loopv(seekersinfos) if(seekersinfos[i]->cn != -1 && !seekersinfos[i]->freezed) numseekers++;
        return numseekers;
    }

    void hideandseekservermode::setfreezedstate(clientinfo *ci, bool state) {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum) seekersinfos[i]->freezed = state;
    }

    bool hideandseekservermode::isfreezed(clientinfo *ci) {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum && seekersinfos[i]->freezed) return true;
        return false;
    }
} // ns server
