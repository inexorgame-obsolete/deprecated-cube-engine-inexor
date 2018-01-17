#pragma once

#include "inexor/shared/geom.hpp"  // for vec

struct physent;
struct vtxarray;
// Dynlights (dynamic lights) are really primitive shaders which light up the near field
// area of the light source. It does not take into account occlusion.

extern void updatedynlights();
extern int finddynlights();
extern void calcdynlightmask(vtxarray *va);
extern int setdynlights(vtxarray *va);

enum
{
    DL_SHRINK = 1<<0,
    DL_EXPAND = 1<<1,
    DL_FLASH  = 1<<2
};

extern void adddynlight(const vec &o, float radius, const vec &color, int fade = 0, int peak = 0, int flags = 0, float initradius = 0, const vec &initcolor = vec(0, 0, 0), physent *owner = nullptr);
extern void dynlightreaching(const vec &target, vec &color, vec &dir, bool hud = false);
extern void removetrackeddynlights(physent *owner = nullptr);

