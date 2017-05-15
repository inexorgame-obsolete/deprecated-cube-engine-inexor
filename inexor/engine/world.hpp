#pragma once

// world.h
// contains general enumerations and structures to describe world, map format and environment


// bump if map format changes, see worldio.cpp last sauerbraten-one was 33
#define MAPVERSION 40

// constant macros to describe visual appearance of game world
#define WATER_AMPLITUDE 0.4f
#define WATER_OFFSET 1.1f
#define TEX_SCALE 8.0f

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
