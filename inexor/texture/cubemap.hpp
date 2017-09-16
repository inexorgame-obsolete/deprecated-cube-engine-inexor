/// @file cubemap.hpp
/// environment map loading routine.

#pragma once

#include "inexor/engine/engine.hpp"

struct cubemapside
{
    GLenum target;
    const char *name;
    bool flipx, flipy, swapxy;
};

extern cubemapside cubemapsides[6];

extern Texture *cubemapload(const char *name, bool mipit = true, bool msg = true, bool transient = false);
extern Texture *cubemaploadwildcard(Texture *t, const char *name, bool mipit, bool msg, bool transient = false);

extern void initenvmaps();
extern void genenvmaps();
extern void clearenvmaps();

extern ushort closestenvmap(const vec &o);
extern ushort closestenvmap(int orient, const ivec &co, int size);
extern GLuint lookupenvmap(ushort emid);
extern GLuint lookupenvmap(Slot &slot);

// rendergl.cpp:
extern void drawcubemap(int size, const vec &o, float yaw, float pitch, const cubemapside &side);


