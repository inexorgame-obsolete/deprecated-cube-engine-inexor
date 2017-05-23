/// @file static map entities ("entity") and dynamic entities (players/monsters, "dynent")
/// the gamecode extends these types to add game specific functionality.

#pragma once

#include "inexor/shared/geom.hpp"

/// ET_*: the only static entity types dictated by the engine... rest are gamecode dependent.
/// We differ them because the serialisation system provides backwards compatibility!
/// We try not to change these values if possible.
enum {
    ET_EMPTY = 0,
    ET_LIGHT,
    ET_MAPMODEL,
    ET_PLAYERSTART,
    ET_ENVMAP,
    ET_PARTICLES,
    ET_SOUND,
    ET_SPOTLIGHT,
    ET_GAMESPECIFIC,
    // the last two are here for providing backwards compatibility with the sauerbomber maps:
    ET_BOMBS = 14,
    ET_OBSTACLE = 34
};

/// static entity types (including game specifc ones)
/// @warning this system may becomes deprecated because of the new entity system!
/// Otherwise merge both enums.
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

    I_SHELLS, I_BULLETS, I_ROCKETS, I_ROUNDS, I_GRENADES, I_CARTRIDGES, /// ammo pickups
    I_BOMBS = ET_BOMBS,         /// bomberman game mode
    I_BOMBRADIUS,               /// bomb radius (see bomberman game mode)
    I_BOMBDELAY,                /// bomberman game mode
    I_HEALTH, I_BOOST,
    I_GREENARMOUR, I_YELLOWARMOUR,
    I_QUAD,

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

/// persistent map entity.
struct entity
{
    vec o;                                      // position
    short attr1, attr2, attr3, attr4, attr5;
    uchar type;                                 // type is one of the above
    uchar reserved;
};

struct entitylight
{
    vec color, dir;
    int millis;

    entitylight() : color(1, 1, 1), dir(0, 0, 1), millis(-1) {}
};

enum
{
    EF_NOVIS     = 1<<0,
    EF_NOSHADOW  = 1<<1,
    EF_NOCOLLIDE = 1<<2,
    EF_ANIM      = 1<<3,
    EF_OCTA      = 1<<4,
    EF_RENDER    = 1<<5,
    EF_SOUND     = 1<<6,
    EF_SPAWNED   = 1<<7
};

struct extentity : entity                       // part of the entity that doesn't get saved to disk
{
    int flags;  // the only dynamic state of a map entity
    entitylight light;
    extentity *attached;

    extentity() : flags(0), attached(NULL) {}

    bool spawned() const { return (flags&EF_SPAWNED) != 0; }
    void setspawned(bool val) { if(val) flags |= EF_SPAWNED; else flags &= ~EF_SPAWNED; }
    void setspawned() { flags |= EF_SPAWNED; }
    void clearspawned() { flags &= ~EF_SPAWNED; }
};

#define MAXENTS 10000

//extern vector<extentity *> ents;                // map entities

enum { CS_ALIVE = 0, CS_DEAD, CS_SPAWNING, CS_LAGGED, CS_EDITING, CS_SPECTATOR };

enum { PHYS_FLOAT = 0, PHYS_FALL, PHYS_SLIDE, PHYS_SLOPE, PHYS_FLOOR, PHYS_STEP_UP, PHYS_STEP_DOWN, PHYS_BOUNCE };

enum { ENT_PLAYER = 0, ENT_AI, ENT_INANIMATE, ENT_CAMERA, ENT_BOUNCE }; // ENT_INANIMATE is a moveable (e.g. moving platform)

enum { COLLIDE_NONE = 0, COLLIDE_ELLIPSE, COLLIDE_OBB, COLLIDE_ELLIPSE_PRECISE };

struct physent                                  // base entity type, can be affected by physics
{
    vec o, vel, falling;                        // origin, velocity
    vec deltapos, newpos;                       // movement interpolation
    float yaw, pitch, roll;
    float maxspeed;                             // cubes per second, 100 for player
    int timeinair;
    float radius, eyeheight, aboveeye;          // bounding box size
    float xradius, yradius, zmargin;
    vec floor;                                  // the normal of floor the dynent is on

    int inwater;
    bool jumping;
    char move, strafe;

    uchar physstate;                            // one of PHYS_* above
    uchar state, editstate;                     // one of CS_* above
    uchar type;                                 // one of ENT_* above
    uchar collidetype;                          // one of COLLIDE_* above           

    bool blocked;                               // used by physics to signal ai

    physent() : o(0, 0, 0), deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(100), 
               radius(4.1f), eyeheight(14), aboveeye(1), xradius(4.1f), yradius(4.1f), zmargin(0),
               state(CS_ALIVE), editstate(CS_ALIVE), type(ENT_PLAYER),
               collidetype(COLLIDE_ELLIPSE),
               blocked(false)
               { reset(); }
              
    void resetinterp()
    {
        newpos = o;
        deltapos = vec(0, 0, 0);
    }

    void reset()
    {
        inwater = 0;
        timeinair = 0;
        jumping = false;
        strafe = move = 0;
        physstate = PHYS_FALL;
        vel = falling = vec(0, 0, 0);
        floor = vec(0, 0, 1);
    }

    vec feetpos(float offset = 0) const { return vec(o).add(vec(0, 0, offset - eyeheight)); }
    vec headpos(float offset = 0) const { return vec(o).add(vec(0, 0, offset)); }
    vec abovehead() { return vec(o).add(vec(0, 0, aboveeye+4)); }

    bool maymove() const { return timeinair || physstate < PHYS_FLOOR || vel.squaredlen() > 1e-4f || deltapos.squaredlen() > 1e-4f; } 
};

enum
{
    ANIM_DEAD = 0, ANIM_DYING, ANIM_IDLE,
    ANIM_FORWARD, ANIM_BACKWARD, ANIM_LEFT, ANIM_RIGHT,
    ANIM_HOLD1, ANIM_HOLD2, ANIM_HOLD3, ANIM_HOLD4, ANIM_HOLD5, ANIM_HOLD6, ANIM_HOLD7,
    ANIM_ATTACK1, ANIM_ATTACK2, ANIM_ATTACK3, ANIM_ATTACK4, ANIM_ATTACK5, ANIM_ATTACK6, ANIM_ATTACK7,
    ANIM_PAIN,
    ANIM_JUMP, ANIM_SINK, ANIM_SWIM,
    ANIM_EDIT, ANIM_LAG, ANIM_TAUNT, ANIM_WIN, ANIM_LOSE,
    ANIM_GUN_IDLE, ANIM_GUN_SHOOT,
    ANIM_VWEP_IDLE, ANIM_VWEP_SHOOT, ANIM_SHIELD, ANIM_POWERUP,
    ANIM_MAPMODEL, ANIM_TRIGGER,
    NUMANIMS
};

static const char * const animnames[] =
{
    "dead", "dying", "idle",
    "forward", "backward", "left", "right",
    "hold 1", "hold 2", "hold 3", "hold 4", "hold 5", "hold 6", "hold 7",
    "attack 1", "attack 2", "attack 3", "attack 4", "attack 5", "attack 6", "attack 7",
    "pain",
    "jump", "sink", "swim",
    "edit", "lag", "taunt", "win", "lose",
    "gun idle", "gun shoot",
    "vwep idle", "vwep shoot", "shield", "powerup",
    "mapmodel", "trigger"
};

#define ANIM_ALL         0x7F
#define ANIM_INDEX       0x7F
#define ANIM_LOOP        (1<<7)
#define ANIM_START       (1<<8)
#define ANIM_END         (1<<9)
#define ANIM_REVERSE     (1<<10)
#define ANIM_CLAMP       (ANIM_START|ANIM_END)
#define ANIM_DIR         0x780
#define ANIM_SECONDARY   11
#define ANIM_NOSKIN      (1<<22)
#define ANIM_SETTIME     (1<<23)
#define ANIM_FULLBRIGHT  (1<<24)
#define ANIM_REUSE       (1<<25)
#define ANIM_NORENDER    (1<<26)
#define ANIM_RAGDOLL     (1<<27)
#define ANIM_SETSPEED    (1<<28)
#define ANIM_NOPITCH     (1<<29)
#define ANIM_GHOST       (1<<30)
#define ANIM_FLAGS       (0x1FF<<22)

struct animinfo // description of a character's animation
{
    int anim, frame, range, basetime;
    float speed;
    uint varseed;

    animinfo() : anim(0), frame(0), range(0), basetime(0), speed(100.0f), varseed(0) { }

    bool operator==(const animinfo &o) const { return frame==o.frame && range==o.range && (anim&(ANIM_SETTIME|ANIM_DIR))==(o.anim&(ANIM_SETTIME|ANIM_DIR)) && (anim&ANIM_SETTIME || basetime==o.basetime) && speed==o.speed; }
    bool operator!=(const animinfo &o) const { return frame!=o.frame || range!=o.range || (anim&(ANIM_SETTIME|ANIM_DIR))!=(o.anim&(ANIM_SETTIME|ANIM_DIR)) || (!(anim&ANIM_SETTIME) && basetime!=o.basetime) || speed!=o.speed; }
};

struct animinterpinfo // used for animation blending of animated characters
{
    animinfo prev, cur;
    int lastswitch;
    void *lastmodel;

    animinterpinfo() : lastswitch(-1), lastmodel(NULL) {}

    void reset() { lastswitch = -1; }
};

#define MAXANIMPARTS 3

struct occludequery;
struct ragdolldata;

struct dynent : physent                         // animated characters, or characters that can receive input
{
    bool k_left, k_right, k_up, k_down;         // see input code

    entitylight light;
    animinterpinfo animinterp[MAXANIMPARTS];
    ragdolldata *ragdoll;
    occludequery *query;
    int occluded, lastrendered;

    dynent() : ragdoll(NULL), query(NULL), occluded(0), lastrendered(0)
    { 
        reset(); 
    }

    ~dynent()
    {
#ifndef STANDALONE
        extern void cleanragdoll(dynent *d);
        if(ragdoll) cleanragdoll(this);
#endif
    }
               
    void stopmoving()
    {
        k_left = k_right = k_up = k_down = jumping = false;
        move = strafe = 0;
    }
        
    void reset()
    {
        physent::reset();
        stopmoving();
        loopi(MAXANIMPARTS) animinterp[i].reset();
    }
};


