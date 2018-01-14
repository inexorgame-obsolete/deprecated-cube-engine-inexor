#pragma once

#include "inexor/engine/octree.hpp"
#include "inexor/shared/ents.hpp"
#include "inexor/shared/geom.hpp"

struct clipplanes;
struct extentity;
struct vec;

extern bool pointincube(const clipplanes &p, const vec &v);
extern bool overlapsdynent(const vec &o, float radius);
extern void rotatebb(vec &center, vec &radius, int yaw);
extern float shadowray(const vec &o, const vec &ray, float radius, int mode, extentity *t = nullptr);
struct ShadowRayCache;

extern ShadowRayCache *newshadowraycache();
extern void freeshadowraycache(ShadowRayCache *&cache);
extern void resetshadowraycache(ShadowRayCache *cache);
extern float shadowray(ShadowRayCache *cache, const vec &o, const vec &ray, float radius, int mode, extentity *t = nullptr);
