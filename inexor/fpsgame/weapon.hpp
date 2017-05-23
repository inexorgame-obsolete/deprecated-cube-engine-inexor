#pragma once
#include "inexor/engine/sound.hpp" // dependency should be inverted: sound should include weapon.hpp
#include "inexor/engine/3dgui.hpp" // dependency should be inverted: 3dgui should include weapon.hpp
#include "inexor/engine/particles.hpp" // dependency should be inverted: particles should include weapon.hpp

#define MAXRAYS 20
#define EXP_SELFDAMDIV 2
#define EXP_SELFPUSH 2.5f
#define EXP_DISTSCALE 1.5f
#define BOMB_DAMRAD 20


/// gun and projectile enumeration
enum
{
    GUN_FIST = 0,
    GUN_SG,         /// shotgun
    GUN_CG,         /// chaingun
    GUN_RL,         /// rocket launcher
    GUN_RIFLE,
    GUN_GL,         /// grenade launcher
    GUN_PISTOL,
    GUN_BOMB,       /// BOMBERMAN gamemode: bomb
    GUN_FIREBALL,   /// monster/bot: fireball
    GUN_ICEBALL,    /// monster/bot: iceball
    GUN_SLIMEBALL,  /// monster/bot: slimeball
    GUN_BITE,       /// bite
    GUN_BARREL,     /// barrel damage
    GUN_SPLINTER,
    NUMGUNS
};


/// armour type enumeration... take 20/40/60 % off
/// TODO find better file (or make obsolete)
enum
{
    A_BLUE,
    A_GREEN,
    A_YELLOW
};

// hard coded weapons and pickups

/// pickup description structure
struct itemstat
{
    int add,  // additional ammo/amount for one pickup
        max,  // max amount
        sound;// pickup sound
    const char *name;
    int icon, info;
};

/// create an array of itemstat instances ('pickups')
static const itemstat itemstats[] =
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
struct guninfo
{
    int sound, attackdelay, damage, spread, projspeed;
    int kickamount, range, rays, hitpush, exprad, ttl;
    const char *name, *file; short part;
};

/// create an array of guninfo instances ('guns')
static const guninfo guns[NUMGUNS] =
{
    {S_PUNCH1,    250,  50,   0,   0,  0,   14,  1,  80,   0,    0, "fist",            "chainsaw",        0},
    {S_SG,       1400,  10, 400,   0, 20, 1024, 20,  80,   0,    0, "shotgun",         "shotgun",         0},
    {S_CG,        100,  30, 100,   0,  7, 1024,  1,  80,   0,    0, "chaingun",        "chaingun",        0},
    {S_RLFIRE,    800, 120,   0, 320, 10, 1024,  1, 160,  40,    0, "rocketlauncher",  "rocket",          0},
    {S_RIFLE,    1500, 100,   0,   0, 30, 2048,  1,  80,   0,    0, "rifle",           "rifle",           0},
    {S_FLAUNCH,   600,  90,   0, 200, 10, 1024,  1, 250,  45, 1500, "grenadelauncher", "grenadelauncher", 0},
    {S_PISTOL,    500,  35,  50,   0,  7, 1024,  1,  80,   0,    0, "pistol",          "pistol",          0},
    {S_FEXPLODE,  375, 200,   8,  20,  0, 1024,  1, 150,  40, 1500, "bomb",            "cannon",          0},
    {S_FLAUNCH,   200,  20,   0, 200,  1, 1024,  1,  80,  40,    0, "fireball",        nullptr,           PART_FIREBALL1},
    {S_ICEBALL,   200,  40,   0, 120,  1, 1024,  1,  80,  40,    0, "iceball",         nullptr,           PART_FIREBALL2},
    {S_SLIMEBALL, 200,  30,   0, 640,  1, 1024,  1,  80,  40,    0, "slimeball",       nullptr,           PART_FIREBALL3},
    {S_PIGR1,     250,  50,   0,   0,  1,   12,  1,  80,   0,    0, "bite",            nullptr,           0},
    {-1,            0, 120,   0,   0,  0,    0,  1,  80,  40,    0, "barrel",          nullptr,           0},
    {S_FEXPLODE,  375, 200,   8,  20,  0, 1024,  1, 150,  40, 1500, "bomb_splinter",   nullptr,           0},

};

