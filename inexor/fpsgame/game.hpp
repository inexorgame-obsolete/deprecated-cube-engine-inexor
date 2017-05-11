/// @file game.h
/// definitions of network protocol, game modes, entities, guns, monsters, mastermode
/// pickups, triggers, team scores, armour, permission levels, 
///
///
///

/// pragmaonce protectes this file from being included twice
#pragma once

#include "inexor/shared/cube.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/network/legacy/game_types.hpp"
#include "inexor/network/legacy/administration.hpp"

#include "inexor/fpsgame/gamemode.hpp"
#include "inexor/engine/particles.hpp"
#include "inexor/fpsgame/fpsstate.hpp"

#include "inexor/fpsgame/ai.hpp"

/// network quantization scale
#define DMF 16.0f   /// for world locations
#define DNF 100.0f  /// for normalized vectors
#define DVELF 1.0f  /// for playerspeed based velocity vectors


/// (door) triggers in singleplayer maps (sp and dmsp game modes)
/// @warning may becomes deprecated if visual scripting will be implemented one day...
enum
{
    TRIGGER_RESET = 0,
    TRIGGERING,
    TRIGGERED,
    TRIGGER_RESETTING,
    TRIGGER_DISAPPEARED
};


/// trigger handler
struct fpsentity : extentity
{
    int triggerstate, lasttrigger;
    fpsentity() : triggerstate(TRIGGER_RESET), lasttrigger(0) {} 
};

/// master mode states: server rights management
enum
{
    MM_START = -1,
    MM_OPEN = 0,   // anyone can claim master
    MM_VETO,       // anyone can vote for maps and join
    MM_LOCKED,     // newly joined players start in spectator mode
    MM_PRIVATE,
    MM_PASSWORD,
};

/// static strings for server description in master server list
static const char * const mastermodenames[] =  { "default",   "open",   "veto",   "locked",     "private",    "password" };
static const char * const mastermodecolors[] = { "",    COL_GREEN,  COL_YELLOW,   COL_YELLOW,     COL_RED,    COL_RED};
static const char * const mastermodeicons[] =  { "server", "server", "serverlock", "serverlock", "serverpriv", "serverpriv" };


/// important teamspecific declarations
#define MAXTEAMS 128
#define MAXNAMELEN 15  /// max player name length
#define MAXTEAMLEN 4   /// max team name length
#define MAXTAGLEN 8    /// max player tag length
#define BOTTAG "Bot"   /// all bots share this tag

enum
{
    TEAM_NONE,
    TEAM_OWN,
    TEAM_OPPONENT,
    TEAM_NUM
};

/// const radar blip colors
static const char * const teamblipcolor[TEAM_NUM] = 
{
    "_neutral", /// = 'gray'
    "_blue",
    "_red"
};

/// Bomberman constants
#define MAXRAYS 20
#define EXP_SELFDAMDIV 2
#define EXP_SELFPUSH 2.5f
#define EXP_DISTSCALE 1.5f
#define BOMB_DAMRAD 20

// mostly players can be described with this
struct fpsent : dynent, fpsstate
{
    int weight;                         // affects the effectiveness of hitpush
    int clientnum, privilege, lastupdate, plag, ping;
    int lifesequence;                   // sequence id for each respawn, used in damage test
    int respawned, suicided;
    int lastpain;
    int lastaction, lastattackgun;
    bool attacking;
    int attacksound, attackchan, idlesound, idlechan;
    int lasttaunt;
    int lastpickup, lastpickupmillis, lastbase, lastrepammo, flagpickup, tokens;
    vec lastcollect;
    int frags, flags, deaths, teamkills, totaldamage, totalshots;
    editinfo *edit;
    float deltayaw, deltapitch, deltaroll, newyaw, newpitch, newroll;
    int smoothmillis;

    string name, tag, team, info;
    int playermodel;
    int fov;                            // field of view

    ai::aiinfo *ai;
    int ownernum, lastnode;

    vec muzzle;

    fpsent() : weight(100), clientnum(-1), privilege(PRIV_NONE), lastupdate(0), plag(0), ping(0), lifesequence(0), respawned(-1), suicided(-1), lastpain(0), attacksound(-1), attackchan(-1), idlesound(-1), idlechan(-1),
                frags(0), flags(0), deaths(0), teamkills(0), totaldamage(0), totalshots(0), edit(NULL), smoothmillis(-1), playermodel(-1), fov(100), ai(NULL), ownernum(-1), muzzle(-1, -1, -1)
    {
        name[0] = team[0] = tag[0] = info[0] = 0;
        respawn();
    }
    ~fpsent()
    {
        freeeditinfo(edit);
        if(attackchan >= 0) inexor::sound::stopsound(attacksound, attackchan);
        if(idlechan >= 0) inexor::sound::stopsound(idlesound, idlechan);
        if(ai) delete ai;
    }

    /// apply push event to object's velocity vector
    void hitpush(int damage, const vec &dir, fpsent *actor, int gun)
    {
        vec push(dir);
        push.mul((actor==this && guns[gun].exprad ? EXP_SELFPUSH : 1.0f)*guns[gun].hitpush*damage/weight);
        vel.add(push);
    }

    /// @see stopsound
    void stopattacksound()
    {
        if(attackchan >= 0) inexor::sound::stopsound(attacksound, attackchan, 250);
        attacksound = attackchan = -1;
    }

    /// @see stopsound
    void stopidlesound()
    {
        if(idlechan >= 0) inexor::sound::stopsound(idlesound, idlechan, 100);
        idlesound = idlechan = -1;
    }

    /// respawn item
    void respawn()
    {
        dynent::reset();
        fpsstate::respawn();
        respawned = suicided = -1;
        lastaction = 0;
        lastattackgun = gunselect;
        attacking = false;
        lasttaunt = 0;
        lastpickup = -1;
        lastpickupmillis = 0;
        lastbase = lastrepammo = -1;
        flagpickup = 0;
        tokens = 0;
        lastcollect = vec(-1e10f, -1e10f, -1e10f);
        stopattacksound();
        lastnode = -1;
    }
};


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// team handling

/// @warning those limits should be increased
#define MAXNAMELEN 15
#define MAXTEAMLEN 4
#define MAXTEAMS 128

/// many competetive team modes allow more than 2 teams
/// allow sorting multiple teams using team scores
struct teamscore
{
    const char *team;
    int score;
    teamscore() {}
    teamscore(const char *s, int n) : team(s), score(n) {}

    // used for quicksort template to compare teams
    static bool compare(const teamscore &x, const teamscore &y)
    {
        if(x.score > y.score) return true;
        if(x.score < y.score) return false;
        return strcmp(x.team, y.team) < 0;
    }
};

/// create hashes to access hashmaps
static inline uint hthash(const teamscore &t) { return hthash(t.team); }

/// compare two teamnames
static inline bool htcmp(const char *key, const teamscore &t) { return htcmp(key, t.team); }

/// scoreboard team block description
struct teaminfo
{
    char team[MAXTEAMLEN+1];
    int frags;
};

/// create hash for hashsts
static inline uint hthash(const teaminfo &t) { return hthash(t.team); }

/// compare two team names
static inline bool htcmp(const char *team, const teaminfo &t) { return !strcmp(team, t.team); }

/// entity handling
/// entity system will be replaced with new entity system later...

namespace entities
{
    extern vector<extentity *> ents;

    extern const char *entmdlname(int type);
    extern const char *itemname(int i);
    extern int itemicon(int i);

    extern void preloadentities();
    extern void renderentities();
    extern void resettriggers();
    extern void checktriggers();
    extern void checkitems(fpsent *d);
    extern void checkquad(int time, fpsent *d);
    extern void resetspawns();
    extern void spawnitems(bool force = false);
    extern void putitems(packetbuf &p);
    extern void setspawn(int i, bool on);
    extern void teleport(int n, fpsent *d);
    extern void pickupeffects(int n, fpsent *d);
    extern void teleporteffects(fpsent *d, int tp, int td, bool local = true);
    extern void jumppadeffects(fpsent *d, int jp, bool local = true);

    extern void repammo(fpsent *d, int type, bool local = true);
}

// full game handling

namespace game
{
    struct scoregroup : teamscore
    {
        vector<fpsent *> players;

        /// Returns whether this scoregroup is a clan/playing-group, whatever.
        /// @return the shared tag if all tags are the same, otherwise null.
        char *sametag()
        {
            fpsent *prev = NULL;
            loopv(players)
            {
                fpsent *p = players[i];
                if(!p->tag[0]) return NULL; 
                if(!prev) { prev = p; continue; }
                if(strcmp(p->tag, prev->tag)) return NULL; //two tags are not matching
            }
            return prev ? prev->tag : NULL;
        }
    };

    struct clientmode
    {
        virtual ~clientmode() {}

        virtual void preload() {}
        virtual int clipconsole(int w, int h) { return 0; }
        virtual void drawhud(fpsent *d, int w, int h) {}
        virtual bool isinvisible(fpsent *d) { return false; }
        virtual void rendergame() {}
        virtual void respawned(fpsent *d) {}
        virtual void setup() {}
        virtual void checkitems(fpsent *d) {}
        virtual int respawnwait(fpsent *d) { return 0; }
        virtual void pickspawn(fpsent *d) { findplayerspawn(d); }
        virtual void senditems(packetbuf &p) {}
        virtual void removeplayer(fpsent *d) {}
        virtual void gameover() {}
        virtual bool hidefrags() { return false; }
        virtual int getteamscore(const char *team) { return 0; }
        virtual void getteamscores(vector<teamscore> &scores) {}
        virtual void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests) {}
        virtual bool aicheck(fpsent *d, ai::aistate &b) { return false; }
        virtual bool aidefend(fpsent *d, ai::aistate &b) { return false; }
        virtual bool aipursue(fpsent *d, ai::aistate &b) { return false; }
        virtual void killed(fpsent *d, fpsent *actor) {}
        virtual void gameconnect(fpsent *d) {}
        virtual void renderscoreboard(g3d_gui &g, scoregroup &sg, int fgcolor, int bgcolor) {}
    };

    extern clientmode *cmode;
    extern void setclientmode();

    // fps
    extern int gamemode, nextmode;
    extern string clientmap;
    extern bool intermission;
    extern int maptime, maprealtime, maplimit;
    extern fpsent *player1;
    extern vector<fpsent *> players, clients;
    extern int lastspawnattempt;
    extern int lasthit;
    extern int respawnent;
    extern int following;
    extern SharedVar<int> smoothmove, smoothdist;

    // osd
    extern int hudannounce_begin;
    extern int hudannounce_timeout;
    extern int hudannounce_effect;
    extern char* hudannounce_text;


    extern bool clientoption(const char *arg);
    extern fpsent *getclient(int cn);
    extern fpsent *newclient(int cn);
    extern const char *colorname(fpsent *d, const char *name = NULL, const char *prefix = "", const char *alt = NULL);
    extern const char *teamcolorname(fpsent *d, const char *alt = "you");
    extern const char *teamcolor(const char *name, bool sameteam, const char *alt = NULL);
    extern const char *teamcolor(const char *name, const char *team, const char *alt = NULL);
    extern fpsent *pointatplayer();
    extern fpsent *hudplayer();
    extern fpsent *followingplayer();
    extern void stopfollowing();
    extern void clientdisconnected(int cn, bool notify = true);
    extern void clearclients(bool notify = true);
    extern void startgame();
    extern void spawnplayer(fpsent *);
    extern void deathstate(fpsent *d, bool restore = false);
    extern void damaged(int damage, fpsent *d, fpsent *actor, bool local = true);
    extern void killed(fpsent *d, fpsent *actor);
    extern void timeupdate(int timeremain);
    extern void msgsound(int n, physent *d = NULL);
    extern void drawicon(int icon, float x, float y, float sz = 120);
    const char *mastermodecolor(int n, const char *unknown);
    const char *mastermodeicon(int n, const char *unknown);

    // client
    extern bool connected, remote, demoplayback;
    extern string servinfo;
    extern vector<uchar> messages;

    extern int parseplayer(const char *arg);
    extern void ignore(int cn);
    extern void unignore(int cn);
    extern bool isignored(int cn);
    extern bool addmsg(int type, const char *fmt = NULL, ...);
    extern void switchname(const char *name, const char *tag);
    extern void switchteam(const char *name);
    extern void switchplayermodel(int playermodel);
    extern void sendmapinfo();
    extern void stopdemo();
    extern void changemap(const char *name, int mode);
    extern void forceintermission();
    extern void c2sinfo(bool force = false);
    extern void sendposition(fpsent *d, bool reliable = false);

    // movable
    struct movable;
    extern vector<movable *> movables;

    extern void clearmovables();
    extern void stackmovable(movable *d, physent *o);
    extern void updatemovables(int curtime);
    extern void rendermovables();
    extern void suicidemovable(movable *m);
    extern void hitmovable(int damage, movable *m, fpsent *at, const vec &vel, int gun);
    extern bool isobstaclealive(movable *m);

    // weapon
    enum 
	{ 
		BNC_GRENADE, 
		BNC_BOMB, 
		BNC_SPLINTER, 
		BNC_GIBS, 
		BNC_DEBRIS, 
		BNC_BARRELDEBRIS
	};

    struct projectile
    {
        vec dir, o, to, offset;
        float speed;
        fpsent *owner;
        int gun;
        bool local;
        int offsetmillis;
        int id;
        entitylight light;
    };
    extern vector<projectile> projs;

    struct bouncer : physent
    {
        int lifetime, bounces;
        float lastyaw, roll;
        bool local;
        fpsent *owner;
        int bouncetype, variant;
        vec offset;
        int offsetmillis;
        int id;
        entitylight light;
        int generation;

        bouncer() : bounces(0), roll(0), variant(0)
        {
            type = ENT_BOUNCE;
        }
    };
    extern vector<bouncer *> bouncers;

    extern int getweapon(const char *name);
    extern void shoot(fpsent *d, const vec &targ);
    extern void shoteffects(int gun, const vec &from, const vec &to, fpsent *d, bool local, int id, int prevaction);
    extern void explode(bool local, fpsent *owner, const vec &v, dynent *safe, int dam, int gun);
    extern void explodeeffects(int gun, fpsent *d, bool local, int id = 0);
    extern void damageeffect(int damage, fpsent *d, bool thirdperson = true);
    extern void gibeffect(int damage, const vec &vel, fpsent *d);
    extern float intersectdist;
    extern bool intersect(dynent *d, const vec &from, const vec &to, float &dist = intersectdist);
    extern dynent *intersectclosest(const vec &from, const vec &to, fpsent *at, float &dist = intersectdist);
    extern void clearbouncers();
    extern void updatebouncers(int curtime);
    extern void removebouncers(fpsent *owner);
    extern void renderbouncers();
    extern void clearprojectiles();
    extern void updateprojectiles(int curtime);
    extern void removeprojectiles(fpsent *owner);
    extern void renderprojectiles();
    extern void preloadbouncers();
    extern void removeweapons(fpsent *owner);
    extern void updateweapons(int curtime);
    extern void gunselect(int gun, fpsent *d);
    extern void weaponswitch(fpsent *d);
    extern void avoidweapons(ai::avoidset &obstacles, float radius);

    // scoreboard
    extern void showscores(bool on);
    extern void getbestplayers(vector<fpsent *> &best);
    extern void getbestteams(vector<const char *> &best);
    extern void clearteaminfo();
    extern void setteaminfo(const char *team, int frags);

    // render
    struct playermodelinfo
    {
        const char *ffa, *blueteam, *redteam, *hudguns,
                   *vwep, *quad, *armour[3],
                   *ffaicon, *blueicon, *redicon;
        bool ragdoll;
    };

    extern SharedVar<int> playermodel, teamskins, testteam;

    extern void saveragdoll(fpsent *d);
    extern void clearragdolls();
    extern void moveragdolls();
    extern void changedplayermodel();
    extern const playermodelinfo &getplayermodelinfo(fpsent *d);
    extern int chooserandomplayermodel(int seed);
    extern void swayhudgun(int curtime);
    extern vec hudgunorigin(int gun, const vec &from, const vec &to, fpsent *d);
}

namespace server
{
    extern const char *modename(int n, const char *unknown = "unknown");
    extern const char *mastermodename(int n, const char *unknown = "unknown");
    extern void startintermission();
    extern void forceintermission();
    extern void stopdemo();
    extern void forcemap(const char *map, int mode);
    extern void forcepaused(bool paused);
    extern void forcegamespeed(int speed);
    extern void forcepersist(bool persist);
}

