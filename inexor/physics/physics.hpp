#pragma once

#include "inexor/engine/octree.hpp"
#include "inexor/shared/ents.hpp"
#include "inexor/shared/geom.hpp"  // for vec

struct clipplanes;
struct dynent;
struct entity;
struct extentity;
struct physent;
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

enum { RAY_BB = 1, RAY_POLY = 3, RAY_ALPHAPOLY = 7, RAY_ENTS = 9, RAY_CLIPMAT = 16, RAY_SKIPFIRST = 32, RAY_EDITMAT = 64, RAY_SHADOW = 128, RAY_PASS = 256, RAY_SKIPSKY = 512 };

extern float raycube   (const vec &o, const vec &ray,     float radius = 0, int mode = RAY_CLIPMAT, int size = 0, extentity *t = nullptr);
extern float raycubepos(const vec &o, const vec &ray, vec &hit, float radius = 0, int mode = RAY_CLIPMAT, int size = 0);
extern float rayfloor  (const vec &o, vec &floor, int mode = 0, float radius = 0);
extern bool  raycubelos(const vec &o, const vec &dest, vec &hitpos);


extern vec collidewall;
extern bool collideinside;
extern physent *collideplayer;

extern void moveplayer(physent *pl, int moveres, bool local);
extern bool moveplayer(physent *pl, int moveres, bool local, int curtime);
extern bool ellipseboxcollide(physent *d, const vec &dir, const vec &o, const vec &center, float yaw, float xr, float yr, float hi, float lo);
extern bool ellipsecollide(physent *d, const vec &dir, const vec &o, const vec &center, float yaw, float xr, float yr, float hi, float lo);
extern bool collide(physent *d, const vec &dir = vec(0, 0, 0), float cutoff = 0.0f, bool playercol = true);
extern bool bounce(physent *d, float secs, float elasticity, float waterfric, float grav);
extern bool bounce(physent *d, float elasticity, float waterfric, float grav);
extern void avoidcollision(physent *d, const vec &dir, physent *obstacle, float space);
extern bool movecamera(physent *pl, const vec &dir, float dist, float stepdist);
extern void physicsframe();
extern void dropenttofloor(entity *e);
extern bool droptofloor(vec &o, float radius, float height);

extern void vecfromyawpitch(float yaw, float pitch, int move, int strafe, vec &m);
extern void vectoyawpitch(const vec &v, float &yaw, float &pitch);
extern bool moveplatform(physent *p, const vec &dir);
extern void updatephysstate(physent *d);
extern void cleardynentcache();
extern void updatedynentcache(physent *d);
extern bool entinmap(dynent *d, bool avoidplayers = false);
extern void findplayerspawn(dynent *d, int forceent = -1, int tag = 0);

