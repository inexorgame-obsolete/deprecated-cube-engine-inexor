#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/shared/cube_vector.hpp"  // for vector
#include "inexor/shared/ents.hpp"         // for entity (ptr only), ::I_BOOST

struct fpsent;
struct packetbuf;


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

namespace entities {

/// Returns whether the ammo entity gets spawned at mapstart.
inline bool delayspawn(int type)
{
    switch(type)
    {
        case I_GREENARMOUR:
        case I_YELLOWARMOUR:
        case I_BOOST:
        case I_QUAD:
            return true;
    }
    return false;
}

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

extern void editent(int i, bool local);
extern const char *entnameinfo(entity &e);
extern const char *entname(int i);
extern int extraentinfosize();
extern void writeent(entity &e, char *buf);
extern void readent(entity &e, char *buf, int ver);
extern float dropheight(entity &e);
extern bool hasmapmodel(const extentity &e);
extern void fixentity(extentity &e);
extern void entradius(extentity &e, bool color);
extern bool mayattach(extentity &e);
extern bool attachent(extentity &e, extentity &a);
extern bool printent(extentity &e, char *buf, int len);
extern extentity *newentity();
extern void deleteentity(extentity *e);
extern void clearents();
extern vector<extentity *> &getents();
extern const char *entmodel(const entity &e);
extern void animatemapmodel(const extentity &e, int &anim, int &basetime);

} // ns entities
