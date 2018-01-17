// 6-directional octree heightfield map format

#pragma once

#include "inexor/engine/material.hpp"    // for ::MAT_AIR, ::MATF_VOLUME
#include "inexor/engine/octree.hpp"      // for cubeext (ptr only), faceboun...
#include "inexor/engine/world.hpp"       // for worldsize
#include "inexor/network/SharedVar.hpp"  // for SharedVar
#include "inexor/shared/cube_types.hpp"  // for uint, ushort, uchar
#include "inexor/shared/geom.hpp"        // for ivec, vec, vec::(anonymous u...

extern cube *newcubes(uint face = F_EMPTY, int mat = MAT_AIR);
extern cubeext *growcubeext(cubeext *ext, int maxverts);
extern void setcubeext(cube &c, cubeext *ext);
extern cubeext *newcubeext(cube &c, int maxverts = 0, bool init = true);
extern void getcubevector(cube &c, int d, int x, int y, int z, ivec &p);
extern void setcubevector(cube &c, int d, int x, int y, int z, const ivec &p);
extern int familysize(const cube &c);
extern void freeocta(cube *c);
extern void discardchildren(cube &c, bool fixtex = false, int depth = 0);
extern void optiface(uchar *p, cube &c);
extern void validatec(cube *c, int size = 0);
extern bool isvalidcube(const cube &c);
extern ivec lu;
extern int lusize;
extern cube &lookupcube(const ivec &to, int tsize = 0, ivec &ro = lu, int &rsize = lusize);
extern const cube *neighbourstack[32];
extern int neighbourdepth;
extern const cube &neighbourcube(const cube &c, int orient, const ivec &co, int size, ivec &ro = lu, int &rsize = lusize);
extern void resetclipplanes();
extern int getmippedtexture(const cube &p, int orient);
extern void forcemip(cube &c, bool fixtex = true);
extern bool subdividecube(cube &c, bool fullcheck=true, bool brighten=true);
extern void edgespan2vectorcube(cube &c);
extern int faceconvexity(const ivec v[4]);
extern int faceconvexity(const ivec v[4], int &vis);
extern int faceconvexity(const vertinfo *verts, int numverts, int size);
extern int faceconvexity(const cube &c, int orient);
extern void calcvert(const cube &c, const ivec &co, int size, ivec &vert, int i, bool solid = false);
extern void calcvert(const cube &c, const ivec &co, int size, vec &vert, int i, bool solid = false);
extern uint faceedges(const cube &c, int orient);
extern bool collapsedface(const cube &c, int orient);
extern bool touchingface(const cube &c, int orient);
extern bool flataxisface(const cube &c, int orient);
extern bool collideface(const cube &c, int orient);
extern int genclipplane(const cube &c, int i, vec *v, plane *clip);
extern void genclipplanes(const cube &c, const ivec &co, int size, clipplanes &p, bool collide = true);
extern bool visibleface(const cube &c, int orient, const ivec &co, int size, ushort mat = MAT_AIR, ushort nmat = MAT_AIR, ushort matmask = MATF_VOLUME);
extern int classifyface(const cube &c, int orient, const ivec &co, int size);
extern int visibletris(const cube &c, int orient, const ivec &co, int size, ushort nmat = MAT_ALPHA, ushort matmask = MAT_ALPHA);
extern int visibleorient(const cube &c, int orient);
extern void genfaceverts(const cube &c, int orient, ivec v[4]);
extern int calcmergedsize(int orient, const ivec &co, int size, const vertinfo *verts, int numverts);
extern void invalidatemerges(cube &c, const ivec &co, int size, bool msg);
extern void calcmerges();

extern int mergefaces(int orient, facebounds *m, int sz);
extern void mincubeface(const cube &cu, int orient, const ivec &o, int size, const facebounds &orig, facebounds &cf, ushort nmat = MAT_AIR, ushort matmask = MATF_VOLUME);

static inline cubeext &ext(cube &c)
{
    return *(c.ext ? c.ext : newcubeext(c));
}

extern int lookupmaterial(const vec &o);

static inline bool insideworld(const vec &o)
{
    return o.x>=0 && o.x<worldsize && o.y>=0 && o.y<worldsize && o.z>=0 && o.z<worldsize;
}

static inline bool insideworld(const ivec &o)
{
    return uint(o.x)<uint(worldsize) && uint(o.y)<uint(worldsize) && uint(o.z)<uint(worldsize);
}
extern const ivec cubecoords[8];
extern const ivec facecoords[6][4];
extern const uchar fv[6][4];
extern const uchar fvmasks[64];
extern const uchar faceedgesidx[6][4];
