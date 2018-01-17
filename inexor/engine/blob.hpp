#pragma once

#include "inexor/network/SharedVar.hpp"  // for SharedVar
#include "inexor/shared/geom.hpp"

// Blob shadows. legacy dynamic shadows which occasionally shine through walls.

enum
{
    BLOB_STATIC = 0,
    BLOB_DYNAMIC
};

extern SharedVar<int> showblobs;

extern void initblobs(int type = -1);
extern void resetblobs();
extern void renderblob(int type, const vec &o, float radius, float fade = 1);
extern void flushblobs();
