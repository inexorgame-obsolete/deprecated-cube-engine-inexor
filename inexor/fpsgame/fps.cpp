/// implementation of basic game functionsand cubescript bindings

#include "inexor/fpsgame/game.hpp"
#include "inexor/fpsgame/entities.hpp"
#include "inexor/filesystem/mediadirs.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::sound;

namespace game
{
    // general game functionality (spawn, attack, spectate...)

    fpsent *player1 = NULL; /// our client
    vector<fpsent *> players; /// other clients

    bool intermission = false;
    int maptime = 0, maprealtime = 0, maplimit = -1;
    int respawnent = -1;
    int lasthit = 0, lastspawnattempt = 0;
    int following = -1, followdir = 0;
    int savedammo[NUMGUNS];

    /// send taunt network animation message to server
    /// taunt animation is this "im gonna kill you" gesture 
    /// that can be seen by other players
    void taunt()
    {
        if(player1->state!=CS_ALIVE || player1->physstate<PHYS_SLOPE) return;
        if(lastmillis-player1->lasttaunt<1000) return;
        player1->lasttaunt = lastmillis;
        addmsg(N_TAUNT, "rc", player1);
    }
    COMMAND(taunt, "");


    /// cubescript: get the player I am following
    ICOMMAND(getfollow, "", (),
    {
        fpsent *f = followingplayer();
        intret(f ? f->clientnum : -1);
    });


	/// follow a specific player if you are in spectator mode
    /// @param arg either the player's name or his client number
    /// @seee parseplayer
    void follow(char *arg)
    {
        if(arg[0] ? player1->state==CS_SPECTATOR : following>=0)
        {
            following = arg[0] ? parseplayer(arg) : -1;
            if(following==player1->clientnum) following = -1;
            followdir = 0;
            spdlog::get("global")->info("follow {}", (following >= 0 ? "on" : "off"));
        }
	}
    COMMAND(follow, "s");


	/// follow previous/next client number
    /// @param dir either forwards (1) or backwards (-1)
    void nextfollow(int dir)
    {
        if(player1->state!=CS_SPECTATOR || clients.empty())
        {
            stopfollowing();
            return;
        }
        int cur = following >= 0 ? following : (dir < 0 ? clients.length() - 1 : 0);
        loopv(clients)
        {
            cur = (cur + dir + clients.length()) % clients.length();
            if(clients[cur] && clients[cur]->state!=CS_SPECTATOR)
            {
                if(following<0) spdlog::get("global")->info("follow on");
                following = cur;
                followdir = dir;
                return;
            }
        }
        stopfollowing();
    }
    ICOMMAND(nextfollow, "i", (int *dir), nextfollow(*dir < 0 ? -1 : 1));


    /// get client map name
    const char *getclientmap() 
    {
        return clientmap;
    }

    /// reset game state in singleplayer
    /// reset all monsters, triggers, bouncers, movables, and projectiles
    void resetgamestate()
    {
        if(m_obstacles) clearmovables();
        clearprojectiles();
        clearbouncers();
    }

    /// reset player state not persistent accross spawns
    /// @param d the affected fpsent ("player"/"monster"/"bot")
    fpsent *spawnstate(fpsent *d) 
    {
        d->respawn();
        d->spawnstate(gamemode);
        return d;
    }

    /// Send "I would like to spawn" to server
    void respawnself()
    {
        if(ispaused()) return;
        int seq = (player1->lifesequence<<16)|((lastmillis/1000)&0xFFFF);
        if(player1->respawned!=seq) 
        {
            addmsg(N_TRYSPAWN, "rc", player1);
            player1->respawned = seq;
        }
    }

    /// Give me the player I am aiming at
    fpsent *pointatplayer()
    {
        loopv(players) if(players[i] != player1 && intersect(players[i], player1->o, worldpos)) return players[i];
        return NULL;
    }

    /// stop spectating a specific player and start free camery fly
    void stopfollowing()
    {
        if(following<0) return;
        following = -1;
        followdir = 0;
        spdlog::get("global")->info("follow off");
    }

    /// Give me the fpsent instance of the player you are currently spectating
    fpsent *followingplayer()
    {
        if(player1->state!=CS_SPECTATOR || following<0) return NULL;
        fpsent *target = getclient(following);
        if(target && target->state!=CS_SPECTATOR) return target;
        return NULL;
    }

    /// Receive the fov the currently followed player got or -1 on failure.
    int getfollowingfov()
    {
        fpsent *d = followingplayer();
        return d ? d->fov : -1;
    }
    ICOMMAND(getfollowingfov, "", (), intret(getfollowingfov()));

    /// Give me the fpsent instance of the player whose coordinates will be used to calculate my camera's position
    /// @see followingplayer
    fpsent *hudplayer()
    {
        if(thirdperson) return player1;
        fpsent *target = followingplayer();
        return target ? target : player1;
    }

    /// initialise camera when entering spectator mode
    /// @see followingplayer
    void setupcamera()
    {
        fpsent *target = followingplayer();
        if(target)
        {
            player1->yaw = target->yaw;
            player1->pitch = target->state==CS_DEAD ? 0 : target->pitch;
            player1->o = target->o;
            player1->resetinterp();
        }
    }

	/// check if it is neccesary to detach the camera from first person view
	/// to third person view. this is mostly triggered by player death
    /// @see hudplayer
    bool detachcamera()
    {
        fpsent *d = hudplayer();
        return d->state==CS_DEAD;
    }

    /// check if camera collision detection is neccesary
    /// @see followingplayer
    bool collidecamera()
    {
        switch(player1->state)
        {
            case CS_EDITING: return false;
            case CS_SPECTATOR: return followingplayer()!=NULL;
        }
        return true;
    }

	/// interpolation factor for player positions
	/// low smoothmove means jumpily player movement
    VARP(smoothmove, 0, 75, 100);

    /// distance in which interpolation will be applied (?)
    VARP(smoothdist, 0, 32, 64);

	/// use latency and assume player movement to
	/// predict a player's new position. Improves visual appearance
	/// of his movement tremendous - even under lag
    /// @see moveplayer
    void predictplayer(fpsent *d, bool move)
    {
        d->o = d->newpos;
        d->yaw = d->newyaw;
        d->pitch = d->newpitch;
        d->roll = d->newroll;

        if(move)
        {
            moveplayer(d, 1, false);
            d->newpos = d->o;
        }
        float k = 1.0f - float(lastmillis - d->smoothmillis)/smoothmove;
        if(k>0)
        {
            d->o.add(vec(d->deltapos).mul(k));
            d->yaw += d->deltayaw*k;
            if(d->yaw<0) d->yaw += 360;
            else if(d->yaw>=360) d->yaw -= 360;
            d->pitch += d->deltapitch*k;
            d->roll += d->deltaroll*k;
        }
    }

	/// parse player state, move players, predict their position,
	/// handle ragdoll, check for lag
    /// @see updateworld
    /// @see moveragdoll
    /// @see predictplayer
    void otherplayers(int curtime)
    {
        loopv(players)
        {
            fpsent *d = players[i];
            if(d == player1 || d->ai) continue; // do not handle bots and myself

            if(d->state==CS_DEAD && d->ragdoll) moveragdoll(d);
            else if(!intermission)
            {
                if(lastmillis - d->lastaction >= d->gunwait) d->gunwait = 0;
                if(d->quadmillis) entities::checkquad(curtime, d);
            }

            const int lagtime = totalmillis-d->lastupdate;
            if(!lagtime || intermission) continue;
            else if(lagtime>1000 && d->state==CS_ALIVE)
            {
                d->state = CS_LAGGED;
                continue;
            }
            if(d->state==CS_ALIVE || d->state==CS_EDITING)
            {
                if(smoothmove && d->smoothmillis>0) predictplayer(d, true);
                else moveplayer(d, 1, false);
            }
            else if(d->state==CS_DEAD && !d->ragdoll && lastmillis-d->lastpain<2000) moveplayer(d, 1, true);
        }
    }

    /// called in game loop to the update game world
    void updateworld()        
    {
        if(!maptime) { maptime = lastmillis; maprealtime = totalmillis; return; }
        if(!curtime) { gets2c(); if(player1->clientnum>=0) c2sinfo(); return; }

        physicsframe();
        ai::navigate();
        if(player1->state != CS_DEAD && !intermission)
        {
            if(player1->quadmillis) entities::checkquad(curtime, player1);
        }
        updateweapons(curtime);
        otherplayers(curtime);
        ai::update();
        moveragdolls();
        gets2c();
        updatemovables(curtime);
        if(connected)
        {
            if(player1->state == CS_DEAD)
            {
                if(player1->ragdoll) moveragdoll(player1);
                else if(lastmillis-player1->lastpain<2000)
                {
                    player1->move = player1->strafe = 0;
                    moveplayer(player1, 10, true);
                }
            }
            else if (!intermission || player1->state == CS_SPECTATOR)
            {
                if(player1->ragdoll) cleanragdoll(player1);
                moveplayer(player1, 10, true);
                swayhudgun(curtime);
                entities::checkitems(player1);
                if(cmode) cmode->checkitems(player1);
            }
        }

        if(player1->clientnum>=0) c2sinfo();   // do this last, to reduce the effective frame lag
    }

    /// spawn yourself im the game world, also called for monsters/AI in singleplayer
    /// of course not used for other players in multiplayer because everyone determins his spawn point for himself.
    /// @see spawnstate
    void spawnplayer(fpsent *d)   
    {
        if(cmode) cmode->pickspawn(d);
        else findplayerspawn(d, d==player1 && respawnent>=0 ? respawnent : -1);
        spawnstate(d);
        if(d==player1)
        {
            if(editmode) d->state = CS_EDITING;
            else if(d->state != CS_SPECTATOR) d->state = CS_ALIVE;
        }
        else d->state = CS_ALIVE;
    }

	// time interval until next spawen is possible
	// in local singleplayer (botmatch e.g.)
    VARP(spawnwait, 0, 0, 1000);

	/// spawn myself in SP and DMSP game mode (singleplayer only)
    /// @see changemap
    void respawn(int gamemode = 0)
    {
        if(player1->state==CS_DEAD)
        {
            player1->attacking = false;
            int wait = cmode ? cmode->respawnwait(player1) : 0;
            if(wait>0)
            {
                lastspawnattempt = lastmillis;
                //spdlog::get("gameplay")->info() << "you must wait %d second%s before respawn!", wait, wait!=1 ? "s" : "");
                return;
            }
            if(lastmillis < player1->lastpain + spawnwait) return;
            respawnself();
        }
    }

    // mutiplayer game functionality


    /// filter attack attempts
    /// not possible in intermission or if player's state is CS_DEAD
    void doattack(bool on)
    {
        if(!connected || intermission) return;
        if((player1->attacking = on)) respawn(gamemode);
    }

    /// check if I am allowed to jump at the moment
    /// called every time before jump command is executed
    /// @see respawn
    bool canjump()
    {
        if(!connected || intermission) return false;
        respawn(gamemode);
        return player1->state!=CS_DEAD;
    }

	/// check if I am allowed to move
    bool allowmove(physent *d)
    {
        if(d->type!=ENT_PLAYER) return true;
        return !((fpsent *)d)->lasttaunt || lastmillis-((fpsent *)d)->lasttaunt>=1000;
    }

	// play a sound when you hit a player
    VARP(hitsound, 0, 0, 1);

	/// an fpsent (player/monster/bot) took damage
    /// @see damageeffect
    void damaged(int damage, fpsent *d, fpsent *actor, bool local)
    {
        if((d->state!=CS_ALIVE && d->state != CS_LAGGED && d->state != CS_SPAWNING) || intermission) return;

        if(local) damage = d->dodamage(damage);
        else if(actor==player1) return;

        fpsent *h = hudplayer();
        if(h!=player1 && actor==h && d!=actor)
        {
            if(hitsound && lasthit != lastmillis) playsound(S_HIT);
            lasthit = lastmillis;
        }
        if(d==h)
        {
            damageblend(damage);
            damagecompass(damage, actor->o);
        }
        damageeffect(damage, d, d!=h);

        ai::damaged(d, actor);

        if(d->health<=0) { if(local) killed(d, actor); }
        else if(d==h) playsound(S_PAIN6);
        else playsound(S_PAIN1+rnd(5), &d->o);
    }

    // show score at death
    VARP(deathscore, 0, 1, 1);

    /// mark players as dead and update their state data
    void deathstate(fpsent *d, bool restore)
    {
        d->state = CS_DEAD;
        d->lastpain = lastmillis;
        if(!restore) gibeffect(max(-d->health, 0), d->vel, d);
        if(d==player1)
        {
            if(deathscore) showscores(true);
            disablezoom();
            if(!restore) loopi(NUMGUNS) savedammo[i] = player1->ammo[i];
            d->attacking = false;
            if(!restore) d->deaths++;
            //d->pitch = 0;
            d->roll = 0;
            /// play a random death sound
            playsound(S_DIE1+rnd(2));
        }
        else
        {
            d->move = d->strafe = 0;
            d->resetinterp();
            d->smoothmillis = 0;
            /// play a random death sound
            playsound(S_DIE1 + rnd(2), &d->o);
        }
    }

    /// highlight frags in team colors
    VARP(teamcolorfrags, 0, 1, 1);

    /// this callback is called when player actor kills d
    /// prints death messages to all kind of consoles
    void killed(fpsent *d, fpsent *actor)
    {
        if(d->state==CS_EDITING)
        {
            d->editstate = CS_DEAD;
            if(d==player1) d->deaths++;
            else d->resetinterp();
            return;
        }
        else if((d->state!=CS_ALIVE && d->state != CS_LAGGED && d->state != CS_SPAWNING) || intermission) return;

        fpsent *h = followingplayer();
        if(!h) h = player1;
        auto frag_logger = d==h || actor==h ? spdlog::get("frag_involved") : spdlog::get("frag_not_involved");
        const char *dname = "", *aname = "";
        if(m_teammode && teamcolorfrags)
        {
            dname = teamcolorname(d, "you");
            aname = teamcolorname(actor, "you");
        }
        else
        {
            dname = colorname(d, NULL, "", "you");
            aname = colorname(actor, NULL, "", "you");
        }
        if(actor->type==ENT_AI)
            frag_logger->info("{0} got killed by {1}", dname, aname);
        else if(d==actor || actor->type==ENT_INANIMATE)
            frag_logger->info("{} suicided{}", dname, (d==player1 ? "!" : ""));
        else if(isteam(d->team, actor->team))
        {
            actor->teamkills++;
            if(actor==player1) frag_logger->info("{0} fragged a teammate ({1})", aname, dname);
            else if(d==player1) frag_logger->info("{0} got fragged by a teammate ({1})", dname, aname);
            else frag_logger->info("{0} fragged a teammate ({1}", aname, dname);
        }
        else
        {
            if(d==player1) frag_logger->info("{0} got fragged by {1}", dname, aname);
            else frag_logger->info("{0} fragged {1}", aname, dname);
        }
        deathstate(d);
        ai::killed(d, actor);
        if(cmode) cmode->killed(d, actor);
    }

    /// update game session time
    /// display intermission statistics in console
    void timeupdate(int secs)
    {
        if(secs > 0)
        {
            maplimit = lastmillis + secs*1000;
        }
        else
        {
            intermission = true;
            player1->attacking = false;
            if(cmode) cmode->gameover();
            spdlog::get("gameplay")->info("intermission:");
            spdlog::get("gameplay")->info("game has ended!");
            if(m_ctf) spdlog::get("gameplay")->info("player frags: {0}, flags: {1}, deaths: {2}", player1->frags, player1->flags, player1->deaths);
            else if(m_collect) spdlog::get("gameplay")->info("player frags: {0}, skulls: {1}, deaths: {2}", player1->frags, player1->flags, player1->deaths);
            else spdlog::get("gameplay")->info("player frags: {0}, deaths: {1}", player1->frags, player1->deaths);

            int accuracy = (player1->totaldamage*100)/max(player1->totalshots, 1);
            spdlog::get("gameplay")->info("player total damage dealt: {0}, damage wasted: {1}, accuracy: {2}%",
                                          player1->totaldamage, (player1->totalshots-player1->totaldamage), accuracy);

            showscores(true);
            disablezoom();
            
            if(identexists("intermission")) execute("intermission");
        }
    }

    /// return a player's statistics to cubescript
    ICOMMAND(getfrags, "", (), intret(player1->frags));
    ICOMMAND(getflags, "", (), intret(player1->flags));
    ICOMMAND(getdeaths, "", (), intret(player1->deaths));
    ICOMMAND(getteamkills, "", (), intret(player1->teamkills));
    ICOMMAND(getaccuracy, "", (), intret((player1->totaldamage*100)/max(player1->totalshots, 1)));
    ICOMMAND(gettotaldamage, "", (), intret(player1->totaldamage));
    ICOMMAND(gettotalshots, "", (), intret(player1->totalshots));

    /// other clients connected to this server
    vector<fpsent *> clients;

    /// ensure new client is a valid entity
    fpsent *newclient(int cn)
    {
        if(cn < 0 || cn > max(0xFF, MAXCLIENTS + MAXBOTS))
        {
            neterr("clientnum", false);
            return NULL;
        }

        if(cn == player1->clientnum) return player1;

        while(cn >= clients.length()) clients.add(NULL);
        if(!clients[cn])
        {
            fpsent *d = new fpsent;
            d->clientnum = cn;
            clients[cn] = d;
            players.add(d);
        }
        return clients[cn];
    }

	/// access fpsent object safely using index
    /// @return NULL if index is invalid
    fpsent *getclient(int cn)   
    {
        if(cn == player1->clientnum) return player1;
        return clients.inrange(cn) ? clients[cn] : NULL;
    }

    /// notify my client to change data when another clients disconnect
    void clientdisconnected(int cn, bool notify)
    {
        if(!clients.inrange(cn)) return;
        if(following==cn)
        {
            if(followdir) nextfollow(followdir);
            else stopfollowing();
        }
        /// remove client number from ingore list
        unignore(cn);

        fpsent *d = clients[cn];
        if(!d) return;
        if(notify && d->name[0]) spdlog::get("gameplay")->info("{0}leave:{1} {2}", COL_GREY, COL_WHITE, colorname(d));
        removeweapons(d);
        removetrackedparticles(d);
        removetrackeddynlights(d);
        if(cmode) cmode->removeplayer(d);
        players.removeobj(d);
        DELETEP(clients[cn]);
        cleardynentcache();
    }

    /// delete all clients
    /// @see disconnect
	void clearclients(bool notify)
    {
        loopv(clients) if(clients[i]) clientdisconnected(i, notify);
    }

    void initclient()
    {
        player1 = spawnstate(new fpsent);
        filtertext(player1->name, "unnamed", false, false, MAXNAMELEN);
        players.add(player1);
    }

    /// show game mode description text during map load
    VARP(showmodeinfo, 0, 1, 1);

    /// clear all game data to start a new game
    void startgame()
    {
        clearmovables();
        clearprojectiles();
        clearbouncers();
        clearragdolls();
        clearteaminfo();

        // reset perma-state
        loopv(players)
        {
            fpsent *d = players[i];
            d->frags = d->flags = 0;
            d->deaths = 0;
            d->totaldamage = 0;
            d->totalshots = 0;
            d->maxhealth = 100;
            d->lifesequence = -1;
            d->respawned = d->suicided = -2;
        }

        setclientmode();

        intermission = false;
        maptime = maprealtime = 0;
        maplimit = -1;

        if(cmode)
        {
            cmode->preload();
            cmode->setup();
        }

        spdlog::get("gameplay")->info("game mode is {}", modename(gamemode));

        if(player1->playermodel != playermodel) switchplayermodel(playermodel);

        showscores(false);
        disablezoom();
        lasthit = 0;

        if(identexists("mapstart")) execute("mapstart"); /// execute cube script map start macro
    }

    /// called just after a map load
    /// send CRC32 to server
    /// @see sendmapinfo
    void startmap(const char *name)   
    {
        ai::savewaypoints();
        ai::clearwaypoints(true);

        respawnent = -1; // so we don't respawn at an old spot
        findplayerspawn(player1, -1);
        entities::resetspawns();
        copystring(clientmap, name ? name : "");
        
        /// send CRC32 checksum of my current map
        /// yeah if you would like to cheat this is the code passage you must modify you little ****** *
        sendmapinfo();
    }

    const char *getclientmode()
    {
        return modename(gamemode, NULL);
    }

    /// trigger sound effects depending on the material you enter
    void physicstrigger(physent *d, bool local, int floorlevel, int waterlevel, int material)
    {
        if(d->type==ENT_INANIMATE) return;
        if(waterlevel>0) 
        {
            /// as long as you do not enter lava play a splash sound
            if(material!=MAT_LAVA) playsound(S_SPLASH1, d==player1 ? NULL : &d->o); 
        }
        else if(waterlevel<0) playsound(material==MAT_LAVA ? S_BURN : S_SPLASH2, d==player1 ? NULL : &d->o);
        /// only send server message if I entered the water and fpsent d is not a bot
        if(floorlevel>0) { if(d==player1 || d->type!=ENT_PLAYER || ((fpsent *)d)->ai) msgsound(S_JUMP, d); }
        else if(floorlevel<0) { if(d==player1 || d->type!=ENT_PLAYER || ((fpsent *)d)->ai) msgsound(S_LAND, d); }
    }

    /// push monsters (or objects) together when they hit walls or other objects
    void dynentcollide(physent *d, physent *o, const vec &dir)
    {
        switch(d->type)
        {
            case ENT_INANIMATE: if(dir.z > 0) stackmovable((movable *)d, o); break;
        }
    }

    /// play sound and send sound notification to server
    /// @see playsound
    void msgsound(int n, physent *d)
    {
        if(!d || d==player1)
        {
            addmsg(N_SOUND, "ci", d, n);
            playsound(n);
        }
        else
        {
            if(d->type==ENT_PLAYER && ((fpsent *)d)->ai)
                addmsg(N_SOUND, "ci", d, n);
            playsound(n, &d->o);
        }
    }

    /// return the sum of dynamic entities currently in scene
    int numdynents() { return players.length() + movables.length(); }

    /// iterate through all dynamic entities and return entity with index [i]
    /// @returned a player, monster or movable (all dynamic entities)
    dynent *iterdynents(int i)
    {
        if(i<players.length()) return players[i];
        i -= players.length();
        if(i<movables.length()) return (dynent *)movables[i];
        return NULL;
    }

    // player name coloring


	/// color team names in frag notifications in game console in red/blue, depending on my team
    VARP(teamcolortext, 0, 1, 1);

    /// are there any duplicate names in our client list?
    /// in case this is true, their client numbers will be displayed behind both nicknames
    bool duplicatename(fpsent *d, const char *name = NULL, const char *alt = NULL)
    {
        if(!name) name = d->name;
        if(alt && d != player1 && !strcmp(name, alt)) return true;
        loopv(players) if(d!=players[i] && !strcmp(name, players[i]->name)) return true;
        return false;
    }

    /// add colored client number in [] brackets behind the name 
    /// in case another player has the same name (duplicated name)
    /// @warning not safe.
    /// @warning resets color to white afterwards!
    /// @see duplicatename
    const char *colorname(fpsent *d, const char *name, const char *prefix, const char *alt)
    {
        if(!name) name = alt && d == player1 ? alt : d->name; 
        bool dup = !name[0] || duplicatename(d, name, alt) || d->aitype != AI_NONE;
        if(dup || prefix[0])
        {
            // ugly workaround to be removed
            if(dup) return tempformatstring(d->aitype == AI_NONE ? "%s%s %s(%d)%s" : "%s%s %s[%d]%s", prefix, name, COL_MAGENTA, d->clientnum, COL_WHITE);
            else return tempformatstring("%s%s%s", prefix, name, COL_WHITE);
        }
        return name;
    }

    /// color name depending on my team in red or blue
    const char *teamcolorname(fpsent *d, const char *alt)
    {
        if(!teamcolortext || !m_teammode) return colorname(d, NULL, "", alt);
        return colorname(d, NULL, isteam(d->team, player1->team) ? COL_BLUE : COL_RED, alt);
    }

	/// color player name blue if you have the same team (\f1) otherwise red (\f3)
    /// @warning not safe.
    const char *teamcolor(const char *name, bool sameteam, const char *alt)
    {
        if(!teamcolortext || !m_teammode) return sameteam || !alt ? name : alt;
        return tempformatstring(sameteam ? "\fs\f1%s\fr" : "\fs\f3%s\fr", sameteam || !alt ? name : alt);
    }

    /// this function calls the function above but also validates that team is a valid char pointer
    /// it is not possible to return memory to an invalid char* pointer!7
    /// @see teamcolor
    const char *teamcolor(const char *name, const char *team, const char *alt)
    {
        return teamcolor(name, team && isteam(team, player1->team), alt);
    }

    /// suicide your player
    void suicide(physent *d)
    {
        if(d==player1 || (d->type==ENT_PLAYER && ((fpsent *)d)->ai))
        {
            if(d->state!=CS_ALIVE) return;
            fpsent *pl = (fpsent *)d;
            int seq = (pl->lifesequence<<16)|((lastmillis/1000)&0xFFFF);
            if(pl->suicided!=seq) { addmsg(N_SUICIDE, "rc", pl); pl->suicided = seq; }
        }
        else if(d->type==ENT_INANIMATE) suicidemovable((movable *)d);
    }
    ICOMMAND(suicide, "", (), suicide(player1));

    // hud rendering

    /// checks if minimap is required for this game mode
    bool needminimap()
	{ 
		return m_ctf || m_protect || m_hold || m_capture || m_collect|| m_bomb; 
	}

	/// draw (blit) item texture (weapon, flags, armours, quad) on screen at x,y
    void drawicon(int icon, float x, float y, float sz)
    {
        bind_items_texture();
        float tsz = 0.25f, tx = tsz*(icon%4), ty = tsz*(icon/4);
        gle::defvertex(2);
        gle::deftexcoord0();
        gle::begin(GL_TRIANGLE_STRIP);
        gle::attribf(x,    y);    gle::attribf(tx,     ty);
        gle::attribf(x+sz, y);    gle::attribf(tx+tsz, ty);
        gle::attribf(x,    y+sz); gle::attribf(tx,     ty+tsz);
        gle::attribf(x+sz, y+sz); gle::attribf(tx+tsz, ty+tsz);
        gle::end();
    }

	/// calculate distance of hud from bottom of my screen depending on player state
	/// referenced only in gl_drawhud in render.cpp
	float abovegameplayhud(int w, int h)
    {
        switch(hudplayer()->state)
        {
            case CS_EDITING:
            case CS_SPECTATOR:
                return 1;
            default:
                return 1650.0f/1800.0f;
        }
    }

	/// this static data is used to describe the sorting of the 3 next weapons in your holster preview.
    int ammohudup[3] = { GUN_CG, GUN_RL, GUN_GL },
        ammohuddown[3] = { GUN_RIFLE, GUN_SG, GUN_PISTOL },
        ammohudcycle[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };

    /// those 3 functions are used to rotate in circles through your weapons
	/// so you see different preview images of the other weapons in your holsters
    ICOMMAND(ammohudup, "V", (tagval *args, int numargs), // 1 up
    {
        loopi(3) ammohudup[i] = i < numargs ? getweapon(args[i].getstr()) : -1;
    });
    ICOMMAND(ammohuddown, "V", (tagval *args, int numargs), // 1 down
    {
        loopi(3) ammohuddown[i] = i < numargs ? getweapon(args[i].getstr()) : -1;
    });
    ICOMMAND(ammohudcycle, "V", (tagval *args, int numargs), // begin again
    {
        loopi(8) ammohudcycle[i] = i < numargs ? getweapon(args[i].getstr()) : -1;
    });

	/// decide if you want to display the little icons of your other weapons in the slot
    VARP(ammohud, 0, 1, 1);

	/// draw other weapons in weapon slots beside the icon of the currently selected weapon
    void drawammohud(fpsent *d)
    {
        float x = HICON_X + 2*HICON_STEP, y = HICON_Y, sz = HICON_SIZE;
        pushhudmatrix();
        hudmatrix.scale(1/3.2f, 1/3.2f, 1);
        flushhudmatrix();
        float xup = (x+sz)*3.2f, yup = y*3.2f + 0.1f*sz;
        loopi(3)
        {
            int gun = ammohudup[i];
            if(gun < GUN_FIST || gun > GUN_BOMB || gun == d->gunselect || !d->ammo[gun]) continue;
            drawicon(HICON_FIST+gun, xup, yup, sz);
            yup += sz;
        }
        float xdown = x*3.2f - sz, ydown = (y+sz)*3.2f - 0.1f*sz;
        loopi(3)
        {
            int gun = ammohuddown[3-i-1];
            if(gun < GUN_FIST || gun > GUN_BOMB || gun == d->gunselect || !d->ammo[gun]) continue;
            ydown -= sz;
            drawicon(HICON_FIST+gun, xdown, ydown, sz);
        }
        int offset = 0, num = 0;
        loopi(8)
        {
            int gun = ammohudcycle[i];
            if(gun < GUN_FIST || gun > GUN_BOMB) continue;
            if(gun == d->gunselect) offset = i + 1;
            else if(d->ammo[gun]) num++;
        }
        float xcycle = (x+sz/2)*3.2f + 0.5f*num*sz, ycycle = y*3.2f-sz;
        loopi(8)
        {
            int gun = ammohudcycle[(i + offset)%8];
            if(gun < GUN_FIST || gun > GUN_BOMB || gun == d->gunselect || !d->ammo[gun]) continue;
            xcycle -= sz;
            drawicon(HICON_FIST+gun, xcycle, ycycle, sz);
        }
        pophudmatrix();
    }

    /// draw health icon, armour icon and icon of selected gun
	/// other gun's preview icons are not included here
    void drawhudicons(fpsent *d)
    {
        pushhudmatrix();
        hudmatrix.scale(2, 2, 1);
        flushhudmatrix();

        draw_textf("%d", (HICON_X + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, d->state==CS_DEAD ? 0 : d->health);
        if(d->state!=CS_DEAD)
        {
            if(d->armour) draw_textf("%d", (HICON_X + HICON_STEP + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, d->armour);
            draw_textf("%d", (HICON_X + 2*HICON_STEP + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, d->ammo[d->gunselect]);
        }

        pophudmatrix();

        drawicon(HICON_HEALTH, HICON_X, HICON_Y);
        if(d->state!=CS_DEAD)
        {
            if(d->armour) drawicon(HICON_BLUE_ARMOUR+d->armourtype, HICON_X + HICON_STEP, HICON_Y);
            drawicon(HICON_FIST+d->gunselect, HICON_X + 2*HICON_STEP, HICON_Y);
            if(d->quadmillis) drawicon(HICON_QUAD, HICON_X + 3*HICON_STEP, HICON_Y);
            if(ammohud) drawammohud(d);
        }
    }

	/// draw announcement for upcoming pickup entities in BOMBERMAN mode
    void drawhudannounce(int w, int h)
    {
        if(hudannounce_timeout < totalmillis) return;
        int fw, fh;
        float zoom = 1.0f;
        float scale = 500.0f;
        int left = 0;
        int top = 0;
        int duration = hudannounce_timeout - hudannounce_begin;
        int remaining = hudannounce_timeout - totalmillis;

        switch(hudannounce_effect) {
            case E_STATIC_CENTER:
                break;
            case E_STATIC_LEFT:
                left = 500;
                break;
            case E_STATIC_RIGHT:
                left = -500;
                break;
            case E_STATIC_TOP:
                top = 400;
                break;
            case E_STATIC_BOTTOM:
                top = -400;
                break;
            case E_ZOOM_IN:
                zoom = 0.5f + ((float) remaining / duration);
                scale = scale * zoom;
                break;
            case E_ZOOM_OUT:
                zoom = 1.5f - ((float) remaining / duration);
                scale = scale * zoom;
                break;

        }
        glPushMatrix();
        glScalef(h/scale, h/scale, 1);
        // glTranslatef(0, 0, +0.9f);
        text_bounds(hudannounce_text, fw, fh);
        draw_text(hudannounce_text, w*scale/h - fw/2 - left, scale - fh/2 - top); // , 255, 255, 255, 0);
        glPopMatrix();

    }

	/// render game hud depending on hudplayer's state and "SPECTATOR" in spectator mode
    void gameplayhud(int w, int h)
    {
        pushhudmatrix();
        hudmatrix.scale(h/1800.0f, h/1800.0f, 1);
        flushhudmatrix();

        if(player1->state==CS_SPECTATOR)
        {
            int pw, ph, tw, th, fw, fh;
            text_bounds("  ", pw, ph);
            text_bounds("SPECTATOR", tw, th);
            th = max(th, ph);
            fpsent *f = followingplayer();
            text_bounds(f ? colorname(f) : " ", fw, fh);
            fh = max(fh, ph);
            draw_text("SPECTATOR", w*1800/h - tw - pw, 1650 - th - fh);
            if(f) 
            {
                int color = f->state!=CS_DEAD ? 0xFFFFFF : 0x606060;
                if(f->privilege)
                {
                    color = f->privilege>=PRIV_ADMIN ? 0xFF8000 : 0x40FF80;
                    if(f->state==CS_DEAD) color = (color>>1)&0x7F7F7F; // darken name of dead players
                }
                draw_text(colorname(f), w*1800/h - fw - pw, 1650 - fh, (color>>16)&0xFF, (color>>8)&0xFF, color&0xFF);
            }
        }

        fpsent *d = hudplayer();
        if(d->state!=CS_EDITING)
        {
            if(d->state!=CS_SPECTATOR) drawhudicons(d);
            drawhudannounce(w, h);
            if(cmode) cmode->drawhud(d, w, h);
        }

        pophudmatrix();
    }

    int clipconsole(int w, int h)
    {
        if(cmode) return cmode->clipconsole(w, h);
        return 0;
    }

    /// use blue blocking crosshair when pointing at a teamate
    VARP(teamcrosshair, 0, 1, 1);

	/// displaying a hit crosshair increases the players hit impression ('feel')
    VARP(hitcrosshair, 0, 425, 1000);

	// crosshair file names are stored in a constant functions
	// that return strings depending on indices
    const char *defaultcrosshair(int index)
    {
        switch(index)
        {
            case 2: return "default_hit.png";
            case 1: return "default_teammate.png";
            default: return "default.png";
        }
    }

	/// switch crosshair depending on player state and player health
    int selectcrosshair(vec &color)
    {
        fpsent *d = hudplayer();
        if(d->state==CS_SPECTATOR || d->state==CS_DEAD) return -1;

        if(d->state!=CS_ALIVE) return 0;

        int crosshair = 0;
        if(lasthit && lastmillis - lasthit < hitcrosshair) crosshair = 2;
        else if(teamcrosshair)
        {
            dynent *o = intersectclosest(d->o, worldpos, d);
            if(o && o->type==ENT_PLAYER && isteam(((fpsent *)o)->team, d->team))
            {
                crosshair = 1;
                color = vec(0, 0, 1);
            }
        }

        if(crosshair!=1 && !editmode && !m_insta)
        {
            if(d->health<=25) color = vec(1, 0, 0);
            else if(d->health<=50) color = vec(1, 0.5f, 0);
        }
        if(d->gunwait) color.mul(0.5f); // darken crosshair during reload
        return crosshair;
    }

	// - this functions is not enabled -
    void lighteffects(dynent *e, vec &color, vec &dir)
    {
        /// #if 0 is another way to comment out like this: /**/
        /// because it is a macro it is evern more powerful than /**/
#if 0
        fpsent *d = (fpsent *)e;
        if(d->state!=CS_DEAD && d->quadmillis)
        {
            float t = 0.5f + 0.5f*sinf(2*M_PI*lastmillis/1000.0f);
            color.y = color.y*(1-t) + t;
        }
#endif
    }

    // any data written into this vector will get saved with the map data.
    // must take care to do own versioning, and endianess if applicable.
    // will not get called when loading maps from other games, so provide defaults.
    void writegamedata(vector<char> &extras) {}
    void readgamedata(vector<char> &extras) {}

    const char *savedconfig() { return "config/saved.cfg"; }
    const char *restoreconfig() { return "config/restore.cfg"; }
    const char *defaultconfig() { return "config/defaults.cfg"; }
    const char *autoexec() { return "config/autoexec.cfg"; }
    const char *savedservers() { return "config/servers.cfg"; }
}

