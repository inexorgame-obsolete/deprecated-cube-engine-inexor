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
#include "inexor/fpsgame/network_types.hpp"

/// game console entry types
enum
{
    CON_CHAT       = 1<<8,
    CON_TEAMCHAT   = 1<<9,
    CON_GAMEINFO   = 1<<10,
    CON_FRAG_SELF  = 1<<11,
    CON_FRAG_OTHER = 1<<12,
    CON_TEAMKILL   = 1<<13
};


/// network quantization scale
#define DMF 16.0f   /// for world locations
#define DNF 100.0f  /// for normalized vectors
#define DVELF 1.0f  /// for playerspeed based velocity vectors

/// SVARP radardir defines the directory of radar images (arrows, frame, flags, skulls..)
extern char *radardir;


/// static entity types
/// @warning this system may becomes deprecated because of the new entity system!
enum
{
    NOTUSED = ET_EMPTY,         /// entity slot not in used in maps
    LIGHT = ET_LIGHT,           /// lightsource, attr1 = radius, attr2 = intensity
    MAPMODEL = ET_MAPMODEL,     /// attr1 = z-angle, attr2 = idx
    PLAYERSTART,                /// attr1 = z-angle, attr2 = team
    ENVMAP = ET_ENVMAP,         /// attr1 = radius
    PARTICLES = ET_PARTICLES,   /// particles (may becomes deprecated because of the new particle system)
    MAPSOUND = ET_SOUND,        /// sounds
    SPOTLIGHT = ET_SPOTLIGHT,   /// cone-shaped spotlights

    /// prefix I_ stands for "Inexor"...
    I_SHELLS, I_BULLETS, I_ROCKETS, I_ROUNDS, I_GRENADES, I_CARTRIDGES, /// ammo pickups
    I_BOMBS = ET_BOMBS,         /// bomberman game mode
    I_BOMBRADIUS,               /// bomb radius (see bomberman game mode)
    I_BOMBDELAY,                /// bomberman game mode
	I_HEALTH, I_BOOST,          /// bomberman game mode
    I_GREENARMOUR, I_YELLOWARMOUR, /// bomberman game mode
    I_QUAD,                     /// bomberman game mode

    TELEPORT,                   /// attr1 = idx, attr2 = model, attr3 = tag
    TELEDEST,                   /// attr1 = z-angle, attr2 = idx
    MONSTER,                    /// attr1 = z-angle, attr2 = monstertype
    CARROT,                     /// attr1 = tag, attr2 = type
    JUMPPAD,                    /// attr1 = z-push, attr2 = y-push, attr3 = x-push
    BASE,                       /// base (regencapture and capture game modes)
    RESPAWNPOINT,               /// singleplayer: respawn points ('respawnpoint set' :))
    BOX,                        /// attr1 = z-angle, attr2 = idx, attr3 = weight
    BARREL,                     /// attr1 = z-angle, attr2 = idx, attr3 = weight, attr4 = health
    PLATFORM,                   /// attr1 = z-angle, attr2 = idx, attr3 = tag, attr4 = speed
    ELEVATOR,                   /// attr1 = z-angle, attr2 = idx, attr3 = tag, attr4 = speed
    FLAG,                       /// attr1 = z-angle, attr2 = team
    OBSTACLE = ET_OBSTACLE,     /// attr1 = z-angle, attr2 = idx (mapmodel index), attr3 = health, attr4 = weight, attr5 = respawnmillis
    MAXENTTYPES
};


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

/// static gun and projectile enumeration
/// TODO: replace this hardcoded stuff and move on to JSON!
enum 
{
	GUN_FIST = 0,	/// fist
	GUN_SG,			/// shotgun
	GUN_CG,			/// 
	GUN_RL,			/// rocket launcher
	GUN_RIFLE,		/// rifle
	GUN_GL,			/// grenade launcher
	GUN_PISTOL,		/// pistol
	GUN_BOMB,		/// BOMBERMAN gamemode: bomb
	GUN_FIREBALL,	/// monster/bot: fireball
	GUN_ICEBALL,	/// monster/bot: iceball
	GUN_SLIMEBALL,	/// monster/bot: slimeball
	GUN_BITE,		/// bite
	GUN_BARREL,		/// barrel damage
	GUN_SPLINTER,	/// splinter
	NUMGUNS         /// 
};


/// armour type enumeration... take 20/40/60 % off
enum 
{
	A_BLUE,
	A_GREEN,
	A_YELLOW
};

/// Artificial intelligence: BOT states
/// "Artificial intelligence is the perpetuum mobile of computer science"
enum 
{ 
	M_NONE = 0,
	M_SEARCH,
	M_HOME,
	M_ATTACKING,
	M_PAIN,
	M_SLEEP,
	M_AIMING
};  


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// game mode specific code

/// basic game mode bitmask "FLAGS"
/// (NOT game modes but attributes of game modes!)
enum
{
    M_TEAM       = 1<<0,   /// game mode contains teams
    M_NOITEMS    = 1<<1,   /// game mode has no items
    M_NOAMMO     = 1<<2,   /// game mode has no ammo?
    M_INSTA      = 1<<3,   /// game mode has an instagib modifier
    M_EFFICIENCY = 1<<4,   /// game mode has an efficiency modifier
    M_TACTICS    = 1<<5,   /// game mode offers random spawn weapons (see tactics mode)
    M_CAPTURE    = 1<<6,   /// game mode is about capturing bases
    M_REGEN      = 1<<7,   /// game mode is about capturing supply bases (see regencapture mode)
    M_CTF        = 1<<8,   /// game mode is about capturing a flag
    M_PROTECT    = 1<<9,   /// game mode is about protecting a flag
    M_HOLD       = 1<<10,  /// game mode is about holding a flag (for 20 seconds)
    M_OVERTIME   = 1<<11,  /// game mode allows overtime (?)
    M_EDIT       = 1<<12,  /// game mode allows cooperative editing (coopedit)
    M_DEMO       = 1<<13,  /// game mode is a demo playback
    M_LOCAL      = 1<<14,  /// game mode is played in singleplayer only (locally)
    M_LOBBY      = 1<<15,  /// game mode does not imply certain grouped gameplay but also allows to built lobbys (pseudoteams working against each other)
    M_DMSP       = 1<<16,  /// death match single player
    M_CLASSICSP  = 1<<17,  /// classic singleplayer
    M_SLOWMO     = 1<<18,  /// game mode is played in slow motion
    M_COLLECT    = 1<<19,  /// game mode is about collecting skulls

    M_LMS        = 1<<20,  /// 
    M_BOMB       = 1<<21,  /// 
    M_TIMEFORWARD= 1<<22,  ///
    M_OBSTACLES  = 1<<23,  ///
    M_HIDEANDSEEK= 1<<24,  /// 
    //M_RACE       = 1<<25,
};


/// structure for game mode description
static struct gamemodeinfo
{
    const char *name; /// game mode's name
    int flags;        /// a bitmask container (see flags above)
} gamemodes[] =
{
    { "SP", M_LOCAL | M_CLASSICSP},
    { "DMSP", M_LOCAL | M_DMSP},
    { "demo", M_DEMO | M_LOCAL},
    { "ffa", M_LOBBY},
    { "coop edit", M_EDIT},
    { "teamplay", M_TEAM},
    { "instagib", M_NOITEMS | M_INSTA},
    { "insta team", M_NOITEMS | M_INSTA | M_TEAM},
    { "efficiency", M_NOITEMS | M_EFFICIENCY},
    { "effic team", M_NOITEMS | M_EFFICIENCY | M_TEAM},
    { "tactics", M_NOITEMS | M_TACTICS},
    { "tac team", M_NOITEMS | M_TACTICS | M_TEAM},
    { "capture", M_NOAMMO | M_TACTICS | M_CAPTURE | M_TEAM},
    { "regen capture", M_NOITEMS | M_CAPTURE | M_REGEN | M_TEAM},
    { "ctf", M_CTF | M_TEAM},
    { "insta ctf", M_NOITEMS | M_INSTA | M_CTF | M_TEAM},
    { "protect", M_CTF | M_PROTECT | M_TEAM},
    { "insta protect", M_NOITEMS | M_INSTA | M_CTF | M_PROTECT | M_TEAM},
    { "hold", M_CTF | M_HOLD | M_TEAM},
    { "insta hold", M_NOITEMS | M_INSTA | M_CTF | M_HOLD | M_TEAM},
    { "effic ctf", M_NOITEMS | M_EFFICIENCY | M_CTF | M_TEAM},
    { "effic protect", M_NOITEMS | M_EFFICIENCY | M_CTF | M_PROTECT | M_TEAM},
    { "effic hold", M_NOITEMS | M_EFFICIENCY | M_CTF | M_HOLD | M_TEAM},
    { "collect", M_COLLECT | M_TEAM},
    { "insta collect", M_NOITEMS | M_INSTA | M_COLLECT | M_TEAM},
    { "effic collect", M_NOITEMS | M_EFFICIENCY | M_COLLECT | M_TEAM},
    { "bomberman", M_LMS | M_BOMB | M_OBSTACLES},
    { "bomberman team", M_LMS | M_BOMB | M_TEAM | M_OBSTACLES},
    { "hideandseek"},
};


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// game mode validation and attribute handling

/// the first 3 game modes are not used in multiplayer
#define STARTGAMEMODE (-3)

/// macro to determine the amount of available game modes
/// division: (size of array) / (size of one gamemodeinfo instance)
#define NUMGAMEMODES ((int)(sizeof(gamemodes)/sizeof(gamemodes[0])))

/// validate game mode number (array index)
#define m_valid(mode)          ((mode) >= STARTGAMEMODE && (mode) < STARTGAMEMODE + NUMGAMEMODES)
/// validate game mode number and attribute (to check if this gamemode has items or bases e.g.)
#define m_check(mode, flag)    (m_valid(mode) && gamemodes[(mode) - STARTGAMEMODE].flags&(flag))
/// validate game mode number and check if game mode does NOT have these attribuges
#define m_checknot(mode, flag) (m_valid(mode) && !(gamemodes[(mode) - STARTGAMEMODE].flags&(flag)))
/// validate game mode number and check if game mode supports parameter flag bit masks
/// to check if this game mode supports multiple attributes (EFFICIENCY | CTF  e.g.)
#define m_checkall(mode, flag) (m_valid(mode) && (gamemodes[(mode) - STARTGAMEMODE].flags&(flag)) == (flag))

/// those game mode check macros are built on top of the layer above
#define m_noitems      (m_check(gamemode, M_NOITEMS))
#define m_noammo       (m_check(gamemode, M_NOAMMO|M_NOITEMS))
#define m_insta        (m_check(gamemode, M_INSTA))
#define m_tactics      (m_check(gamemode, M_TACTICS))
#define m_efficiency   (m_check(gamemode, M_EFFICIENCY))
#define m_capture      (m_check(gamemode, M_CAPTURE))
#define m_regencapture (m_checkall(gamemode, M_CAPTURE | M_REGEN))
#define m_ctf          (m_check(gamemode, M_CTF))
#define m_protect      (m_checkall(gamemode, M_CTF | M_PROTECT))
#define m_hold         (m_checkall(gamemode, M_CTF | M_HOLD))
#define m_collect      (m_check(gamemode, M_COLLECT))
#define m_teammode     (m_check(gamemode, M_TEAM))
#define m_overtime     (m_check(gamemode, M_OVERTIME))
#define isteam(a,b)    (m_teammode && strcmp(a, b)==0)

#define m_lms          (m_check(gamemode, M_LMS))
#define m_bomb         (m_check(gamemode, M_BOMB))
#define m_hideandseek  (m_check(gamemode, M_HIDEANDSEEK))

#define m_obstacles    (m_check(gamemode, M_OBSTACLES))
#define m_timeforward  (m_check(gamemode, M_TIMEFORWARD))

#define m_demo         (m_check(gamemode, M_DEMO))
#define m_edit         (m_check(gamemode, M_EDIT))
#define m_lobby        (m_check(gamemode, M_LOBBY))
#define m_timed        (m_checknot(gamemode, M_DEMO|M_EDIT|M_LOCAL))
#define m_botmode      (m_checknot(gamemode, M_DEMO|M_LOCAL))
#define m_mp(mode)     (m_checknot(mode, M_LOCAL))

#define m_sp           (m_check(gamemode, M_DMSP | M_CLASSICSP))
#define m_dmsp         (m_check(gamemode, M_DMSP))
#define m_classicsp    (m_check(gamemode, M_CLASSICSP))

/// master mode states: server rights managment
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


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// sound list and description of administrative levels

/// hardcoded sounds, defined in sounds.cfg
enum
{
    S_JUMP = 0, S_LAND, S_RIFLE, S_PUNCH1, S_SG, S_CG,
    S_RLFIRE, S_RLHIT, S_WEAPLOAD, S_ITEMAMMO, S_ITEMHEALTH,
    S_ITEMARMOUR, S_ITEMPUP, S_ITEMSPAWN, S_TELEPORT, S_NOAMMO, S_PUPOUT,
    S_PAIN1, S_PAIN2, S_PAIN3, S_PAIN4, S_PAIN5, S_PAIN6,
    S_DIE1, S_DIE2,
    S_FLAUNCH, S_FEXPLODE,
    S_SPLASH1, S_SPLASH2,
    S_GRUNT1, S_GRUNT2, S_RUMBLE,
    S_PAINO,
    S_PAINR, S_DEATHR,
    S_PAINE, S_DEATHE,
    S_PAINS, S_DEATHS,
    S_PAINB, S_DEATHB,
    S_PAINP, S_PIGGR2,
    S_PAINH, S_DEATHH,
    S_PAIND, S_DEATHD,
    S_PIGR1, S_ICEBALL, S_SLIMEBALL,
    S_JUMPPAD, S_PISTOL,
    S_V_BASECAP, S_V_BASELOST,
    S_V_FIGHT,
    S_V_BOOST, S_V_BOOST10,
    S_V_QUAD, S_V_QUAD10,
    S_V_RESPAWNPOINT,
    S_FLAGPICKUP,
    S_FLAGDROP,
    S_FLAGRETURN,
    S_FLAGSCORE,
    S_FLAGRESET,
    S_BURN,
    S_CHAINSAW_ATTACK,
    S_CHAINSAW_IDLE,
    S_HIT,
    S_FLAGFAIL
};

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


/// enumeration for icons
enum
{
    HICON_BLUE_ARMOUR = 0,
    HICON_GREEN_ARMOUR,
    HICON_YELLOW_ARMOUR,

    HICON_HEALTH,

    HICON_FIST,
    HICON_SG,
    HICON_CG,
    HICON_RL,
    HICON_RIFLE,
    HICON_GL,
    HICON_PISTOL,
    HICON_BOMB,

    HICON_QUAD,

    HICON_RED_FLAG,
    HICON_BLUE_FLAG,
    HICON_NEUTRAL_FLAG,

    HICON_TOKEN,
	
	// bomberman
    HICON_BOMBRADIUS,
    HICON_BOMBDELAY,

    HICON_X       = 20,
    HICON_Y       = 1650,
    HICON_TEXTY   = 1644,
    HICON_STEP    = 490,
    HICON_SIZE    = 120,
    HICON_SPACE   = 40
};


/// Bomberman: HUD announce effects
enum hudannounceeffects 
{
    E_STATIC_CENTER = 0,
    E_STATIC_LEFT,
    E_STATIC_RIGHT,
    E_STATIC_TOP,
    E_STATIC_BOTTOM,
    E_FADE_LEFT_RIGHT,
    E_FADE_RIGHT_LEFT,
    E_FADE_TOP_BOTTOM,
    E_FADE_BOTTOM_TOP,
    E_ZOOM_IN,
    E_ZOOM_OUT,
    E_BLINK_CENTER
};

/// Bomberman constants
#define MAXRAYS 20
#define EXP_SELFDAMDIV 2
#define EXP_SELFPUSH 2.5f
#define EXP_DISTSCALE 1.5f
#define BOMB_DAMRAD 20


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// hard coded weapons and pickups

/// pickup description structure
static struct itemstat 
{ 
	int add, max, sound; 
	const char *name; 
	int icon, info;
}

/// create an array of itemstat instances ('pickups')
/// TODO: replace this hardcoded stuff and move on to JSON!
itemstats[] =
{
    {10,    30,    S_ITEMAMMO,   "SG", HICON_SG,            GUN_SG},
    {20,    60,    S_ITEMAMMO,   "CG", HICON_CG,            GUN_CG},
    {5,     15,    S_ITEMAMMO,   "RL", HICON_RL,            GUN_RL},
    {5,     15,    S_ITEMAMMO,   "RI", HICON_RIFLE,         GUN_RIFLE},
    {10,    30,    S_ITEMAMMO,   "GL", HICON_GL,            GUN_GL},
    {30,    120,   S_ITEMAMMO,   "PI", HICON_PISTOL,        GUN_PISTOL},
	{1,     12,    S_ITEMAMMO,   "BO", HICON_BOMB,          GUN_BOMB},
    {1,     10,    S_ITEMPUP,    "BR", HICON_BOMBRADIUS,    -1},
    {1,     7,     S_ITEMPUP,    "BD", HICON_BOMBDELAY,     -1},
    {25,    100,   S_ITEMHEALTH, "H",  HICON_HEALTH,        -1},
    {10,    1000,  S_ITEMHEALTH, "MH", HICON_HEALTH,        -1},
    {100,   100,   S_ITEMARMOUR, "GA", HICON_GREEN_ARMOUR,  A_GREEN},
    {200,   200,   S_ITEMARMOUR, "YA", HICON_YELLOW_ARMOUR, A_YELLOW},
    {20000, 30000, S_ITEMPUP,    "Q",  HICON_QUAD,          -1}
};

/// weapon description structure
static const struct guninfo
{ 
	int sound, attackdelay, damage, spread, projspeed;
	int kickamount, range, rays, hitpush, exprad, ttl; 
	const char *name, *file; short part;
}

/// create an array of guninfo instances ('guns')
/// TODO: replace this hardcoded stuff and move on to JSON!
guns[NUMGUNS] =
{
    { S_PUNCH1,    250,  50,   0,   0,  0,   14,  1,  80,   0,    0, "fist",            "chainsaw",        0 },
    { S_SG,       1400,  10, 400,   0, 20, 1024, 20,  80,   0,    0, "shotgun",         "shotgun",         0 },
    { S_CG,        100,  30, 100,   0,  7, 1024,  1,  80,   0,    0, "chaingun",        "chaingun",        0 },
    { S_RLFIRE,    800, 120,   0, 320, 10, 1024,  1, 160,  40,    0, "rocketlauncher",  "rocket",          0 },
    { S_RIFLE,    1500, 100,   0,   0, 30, 2048,  1,  80,   0,    0, "rifle",           "rifle",           0 },
    { S_FLAUNCH,   600,  90,   0, 200, 10, 1024,  1, 250,  45, 1500, "grenadelauncher", "grenadelauncher", 0 },
    { S_PISTOL,    500,  35,  50,   0,  7, 1024,  1,  80,   0,    0, "pistol",          "pistol",          0 },
    { S_FEXPLODE,  375, 200,   8,  20,  0, 1024,  1, 150,  40, 1500, "bomb",            "cannon",          0 },
    { S_FLAUNCH,   200,  20,   0, 200,  1, 1024,  1,  80,  40,    0, "fireball",        NULL,              PART_FIREBALL1 },
    { S_ICEBALL,   200,  40,   0, 120,  1, 1024,  1,  80,  40,    0, "iceball",         NULL,              PART_FIREBALL2 },
    { S_SLIMEBALL, 200,  30,   0, 640,  1, 1024,  1,  80,  40,    0, "slimeball",       NULL,              PART_FIREBALL3 },
    { S_PIGR1,     250,  50,   0,   0,  1,   12,  1,  80,   0,    0, "bite",            NULL,              0 },
    { -1,            0, 120,   0,   0,  0,    0,  1,  80,  40,    0, "barrel",          NULL,              0 },
    { S_FEXPLODE,  375, 200,   8,  20,  0, 1024,  1, 150,  40, 1500, "bomb_splinter",   NULL,              0 },

};

#include "inexor/fpsgame/ai.hpp"


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// fpsstate and fpsent definitions

/// inherited by fpsent and server clients
struct fpsstate
{
    int health, maxhealth;
    int armour, armourtype;
    int quadmillis;
    int gunselect, gunwait;
    int ammo[NUMGUNS];
    int aitype, skill;
    int backupweapon; //no ammo - weapon
    int bombradius;
    int bombdelay;

    fpsstate() : maxhealth(100), aitype(AI_NONE), skill(0), backupweapon(GUN_FIST) {}

    /// set initial ammo
    void baseammo(int gun, int k = 2, int scale = 1)
    {
        ammo[gun] = (itemstats[gun-GUN_SG].add*k)/scale;
    }

    /// add ammo
    void addammo(int gun, int k = 1, int scale = 1)
    {
        itemstat &is = itemstats[gun-GUN_SG];
        ammo[gun] = min(ammo[gun] + (is.add*k)/scale, is.max);
    }

    /// ammo limitation reached/exceeded?
    bool hasmaxammo(int type)
    {
       const itemstat &is = itemstats[type-I_SHELLS];
       return ammo[type-I_SHELLS+GUN_SG]>=is.max;
    }

    /// check if I can pick up this item depending on the radius
    bool canpickup(int type)
    {
        if(type<I_SHELLS || type>I_QUAD) return false;
			itemstat &is = itemstats[type-I_SHELLS];
	        switch(type)
	        {
	            case I_BOOST: return maxhealth<is.max;
	            case I_HEALTH: return health<maxhealth;
	                case I_GREENARMOUR:
	                    // (100h/100g only absorbs 200 damage)
	                    if(armourtype==A_YELLOW && armour>=100) return false;
	            case I_YELLOWARMOUR: return !armourtype || armour<is.max;
	            case I_QUAD: return quadmillis<is.max;
                case I_BOMBRADIUS:
                    return bombradius<is.max;
                    break;
                case I_BOMBDELAY:
                    return bombdelay<is.max;
                    break;
	            default: return ammo[is.info]<is.max;
	    	}
		}

    /// pick up this item
    void pickup(int type)
    {
        if(type<I_SHELLS || type>I_QUAD) return;
            itemstat &is = itemstats[type-I_SHELLS];
            switch(type)
            {
                case I_BOOST:
                    maxhealth = min(maxhealth+is.add, is.max);
                case I_HEALTH: // boost also adds to health
                    health = min(health+is.add, maxhealth);
                    break;
                case I_GREENARMOUR:
                case I_YELLOWARMOUR:
                    armour = min(armour+is.add, is.max);
                    armourtype = is.info;
                    break;
                case I_QUAD:
                    quadmillis = min(quadmillis+is.add, is.max);
                    break;
                case I_BOMBRADIUS:
                    bombradius = min(bombradius+is.add, is.max);
                    break;
                case I_BOMBDELAY:
                    bombdelay = min(bombdelay+is.add, is.max);
                    break;
                default:
                    ammo[is.info] = min(ammo[is.info]+is.add, is.max);
                    break;
            }
        }

    /// reset all members when spawning
    void respawn()
    {
        health = maxhealth;
        armour = 0;
        armourtype = A_BLUE;
        quadmillis = 0;
        gunselect = GUN_PISTOL;
        gunwait = 0;
        bombradius = 1;
        bombdelay = 1;
        loopi(NUMGUNS) ammo[i] = 0;
        ammo[backupweapon] = 1;
    }

    /// configure spawn settings (weapons, ammo, health...) depending on game mode
    void spawnstate(int gamemode)
    {
        if(m_demo)
        {
            gunselect = GUN_FIST;
            backupweapon = GUN_FIST;
        }
        else if(m_insta)
        {
            armour = 0;
            health = 1;
            gunselect = GUN_RIFLE;
            ammo[GUN_RIFLE] = 100;
            backupweapon = GUN_FIST;
        }
        else if(m_regencapture)
        {
            armourtype = A_BLUE;
            armour = 25;
            gunselect = GUN_PISTOL;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
            backupweapon = GUN_FIST;
        }
        else if(m_tactics)
        {
            armourtype = A_GREEN;
            armour = 100;
            ammo[GUN_PISTOL] = 40;
            backupweapon = GUN_FIST;
            int spawngun1 = rnd(5)+1, spawngun2;
            gunselect = spawngun1;
            baseammo(spawngun1, m_noitems ? 2 : 1);
            do spawngun2 = rnd(5)+1; while(spawngun1==spawngun2);
            baseammo(spawngun2, m_noitems ? 2 : 1);
            if(m_noitems) ammo[GUN_GL] += 1;
        }
        else if(m_efficiency)
        {
            armourtype = A_GREEN;
            armour = 100;
            loopi(5) baseammo(i+1);
            gunselect = GUN_CG;
            ammo[GUN_CG] /= 2;
            backupweapon = GUN_FIST;
        }
        else if(m_ctf || m_collect)
        {
            armourtype = A_BLUE;
            armour = 50;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
            backupweapon = GUN_FIST;
        }
        else if(m_bomb)
        {
            health = 1;
            armourtype = A_GREEN;
            armour = 0;
            gunselect = GUN_BOMB;
            backupweapon = GUN_BOMB;
        }
        else if(m_hideandseek)
        {
            health = 100;
            armour = 0;
            gunselect = GUN_RL;
            ammo[GUN_RL] = 10;
            ammo[GUN_PISTOL] = 0;
            ammo[GUN_GL] = 0;
            backupweapon = GUN_FIST;
        }
        else if(m_sp)
        {
            if(m_dmsp) 
            {
                armourtype = A_BLUE;
                armour = 25;
            }
            ammo[GUN_PISTOL] = 80;
            ammo[GUN_GL] = 1;
            backupweapon = GUN_FIST;
        }
        else
        {
            armourtype = A_BLUE;
            armour = 25;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
            backupweapon = GUN_FIST;
        }
    }

    /// just subtract damage here, we can set death, etc. later in code calling this
    int dodamage(int damage)
    {
        int ad = damage*(armourtype+1)*25/100; // let armour absorb when possible
        if(ad>armour) ad = armour;
        armour -= ad;
        damage -= ad;
        health -= damage;
        return damage;
    }

    /// is there ammo left for this gun
    int hasammo(int gun, int exclude = -1)
    {
        return gun >= 0 && gun <= NUMGUNS && gun != exclude && ammo[gun] > 0;
    }
};

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

	/// used for quicksort template to compare teams
    static bool compare(const teamscore &x, const teamscore &y)
    {
        if(x.score > y.score) return true;
        if(x.score < y.score) return false;
        return strcmp(x.team, y.team) < 0;
    }
};

/// create hashes to access hashmaps
static inline uint hthash(const teamscore &t) 
{
	return hthash(t.team); 
}

/// compare two teamnames
static inline bool htcmp(const char *key, const teamscore &t) 
{
	return htcmp(key, t.team);
}

/// scoreboard team block description
struct teaminfo
{
    char team[MAXTEAMLEN+1];
    int frags;
};

/// create hash for hashsts
static inline uint hthash(const teaminfo &t) 
{ 
	return hthash(t.team); 
}

/// compare two team names
static inline bool htcmp(const char *team, const teaminfo &t)
{
	return !strcmp(team, t.team);
}

/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// full game handling

namespace game
{
    struct scoregroup : teamscore
    {
        vector<fpsent *> players;

        char *sametag() //returns whether this scoregroup is a clan/playing-group, whatever. it returns null if players in this group have different tags and the tag if they all share the same one
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

    // monster
    struct monster;
    extern vector<monster *> monsters;

    extern void clearmonsters();
    extern void preloadmonsters();
    extern void stackmonster(monster *d, physent *o);
    extern void updatemonsters(int curtime);
    extern void rendermonsters();
    extern void suicidemonster(monster *m);
    extern void hitmonster(int damage, monster *m, fpsent *at, const vec &vel, int gun);
    extern void monsterkilled();
    extern void endsp(bool allkilled);
    extern void spsummary(int accuracy);

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
    extern void hashpassword(int cn, int sessionid, const char *pwd, char *result, int maxlen = MAXSTRLEN);
    extern int msgsizelookup(int msg);
}

