#pragma once

// Decals are used to temporarily blend over the texture of a wall/model because of some past event.
// Could get superseeded by a background world loader/updater.

#include "inexor/shared/geom.hpp"

extern void initdecals();
extern void cleardecals();
extern void renderdecals(bool mainpass = false);

// decal
enum
{
    DECAL_SCORCH = 0,
    DECAL_BLOOD,
    DECAL_BULLET
};

extern void adddecal(int type, const vec &center, const vec &surface, float radius, const bvec &color = bvec(0xFF, 0xFF, 0xFF), int info = 0);
