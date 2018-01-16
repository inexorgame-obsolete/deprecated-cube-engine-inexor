#pragma once

#include "inexor/network/SharedVar.hpp"
#include "inexor/shared/cube_types.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/engine/octree.hpp"

// world.h
// contains general enumerations and structures to describe world, map format and environment


// bump if map format changes, see worldio.cpp last sauerbraten-one was 33
#define MAPVERSION 40

// constant macros to describe visual appearance of game world
#define WATER_AMPLITUDE 0.4f
#define WATER_OFFSET 1.1f
#define TEX_SCALE 8.0f

extern SharedVar<char*> maptitle;

// hardcoded texture numbers
enum
{
    DEFAULT_SKY = 0,
    DEFAULT_GEOM
};

/// octree header structure as its found in the ogz files.
/// ogz files are gz-compressed as the name suggests.
struct octaheader
{
    char magic[4];              // "OCTA"
    int version;                // any >8bit quantity is little endian
    int headersize;             // sizeof(header)
    int worldsize;
    int numents;
    int numpvs;
    int lightmaps;
    int blendmap;
    int numvars;
    int numvslots;
};

/// more intense map file header used when loading.
struct compatheader
{
    char magic[4];              // "OCTA"
    int version;                // any >8bit quantity is little endian
    int headersize;             // sizeof(header)
    int worldsize;
    int numents;
    int numpvs;
    int lightmaps;
    int lightprecision, lighterror, lightlod;
    uchar ambient;
    uchar watercolour[3];
    uchar blendmap;
    uchar lerpangle, lerpsubdiv, lerpsubdivsize;
    uchar bumperror;
    uchar skylight[3];
    uchar lavacolour[3];
    uchar waterfallcolour[3];
    uchar reserved[10];
    char maptitle[128];
};

// enumeration for material visibility
enum
{
    MATSURF_NOT_VISIBLE = 0,
    MATSURF_VISIBLE,
    MATSURF_EDIT_ONLY
};

struct vertex
{
    vec pos;        // vertex position
    bvec4 norm;     // normal vector
    vec2 tc;        // Texture UV coordinates
    svec2 lm;       // light map UV coordinates
    bvec4 tangent;	// tangents (for skinning/animation ?)
};


extern vector<int> outsideents;

extern void entcancel();
extern void entitiesinoctanodes();
extern void attachentities();
extern void freeoctaentities(cube &c);
extern bool pointinsel(const selinfo &sel, const vec &o);

extern void resetmap();
extern void startmap(const char *name);

extern char *entname(entity &e);
extern bool haveselent();
extern undoblock *copyundoents(undoblock *u);
extern void pasteundoent(int idx, const entity &ue);
extern void pasteundoents(undoblock *u);

extern vector<int> entgroup;

extern SharedVar<int> worldscale, worldsize;
extern SharedVar<int> mapversion;


extern bool emptymap(int factor, bool force, const char *mname = "", bool usecfg = true);
extern bool enlargemap(bool force);
extern int findentity(int type, int index = 0, int attr1 = -1, int attr2 = -1);
extern void findents(int low, int high, bool notspawned, const vec &pos, const vec &radius, vector<int> &found);
extern extentity *newentity(bool local, const vec &o, int type, int v1, int v2, int v3, int v4, int v5, int &idx);
extern void attachentity(extentity &e);
extern bool modifyoctaent(int flags, int id);
extern void mpeditent(int i, const vec &o, int type, int attr1, int attr2, int attr3, int attr4, int attr5, bool local);

extern vec getselpos();
extern int getworldsize();
extern int getmapversion();
extern void renderentcone(const extentity &e, const vec &dir, float radius, float angle);
extern void renderentarrow(const extentity &e, const vec &dir, float radius);
extern void renderentattachment(const extentity &e);
extern void renderentsphere(const extentity &e, float radius);
extern void renderentring(const extentity &e, float radius, int axis = 0);

