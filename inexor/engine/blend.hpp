#pragma once

#include "inexor/io/legacy/stream.hpp"
// Blendmaps, used to blend two different images together.
#include "inexor/network/SharedTree.hpp"
#include "inexor/network/SharedVar.hpp"  // for SharedVar
#include "inexor/shared/cube_types.hpp"  // for uchar, uint
#include "inexor/shared/cube_vector.hpp"

struct ivec;
struct stream;
struct vec;


extern SharedVar<int> blendpaintmode;

struct BlendMapCache;

extern BlendMapCache *newblendmapcache();
extern void freeblendmapcache(BlendMapCache *&cache);
extern bool setblendmaporigin(BlendMapCache *cache, const ivec &o, int size);
extern bool hasblendmap(BlendMapCache *cache);
extern uchar lookupblendmap(BlendMapCache *cache, const vec &pos);
extern void resetblendmap();
extern void enlargeblendmap();
extern void shrinkblendmap(int octant);
extern void optimizeblendmap();
extern void stoppaintblendmap();
extern void trypaintblendmap();
extern void renderblendbrush(uint tex, float x, float y, float w, float h);
extern void renderblendbrush();
extern bool loadblendmap(stream *f, int info);
extern void saveblendmap(stream *f);
extern uchar shouldsaveblendmap();
