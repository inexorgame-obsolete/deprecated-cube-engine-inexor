#pragma once

// Shadowmaps are used to add a shadow to dynamically moving entities.
// They are basically low resultion renderings from the perspective of the light.

#include "inexor/network/SharedVar.hpp"  // for SharedVar
#include "inexor/shared/geom.hpp"        // for vec (ptr only), matrix4

struct vtxarray;

extern SharedVar<int> shadowmap;
extern int shadowmapcasters;
extern bool shadowmapping;
extern matrix4 shadowmatrix;

extern bool isshadowmapcaster(const vec &o, float rad);
extern bool addshadowmapcaster(const vec &o, float xyrad, float zrad);
extern bool isshadowmapreceiver(vtxarray *va);
extern void rendershadowmap();
extern void pushshadowmap();
extern void popshadowmap();
extern void rendershadowmapreceivers();
extern void guessshadowdir();
