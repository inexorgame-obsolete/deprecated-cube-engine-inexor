#pragma once

#include "inexor/shared/cube_tools.hpp"   // for DELETEA
// Simplistic bitmap text rendering
#include "inexor/shared/cube_vector.hpp"  // for vector
#include "inexor/shared/geom.hpp"
#include "inexor/texture/texture.hpp"

struct Texture;
struct matrix4x3;

struct font
{
    struct charinfo
    {
        short x, y, w, h, offsetx, offsety, advance, tex;
    };

    char *name;
    vector<Texture *> texs;
    vector<charinfo> chars;
    int charoffset, defaultw, defaulth, scale;

    font() : name(nullptr) {}
    ~font() { DELETEA(name); }
};

#define FONTH (curfont->scale)
#define FONTW (FONTH/2)
#define MINRESW 640
#define MINRESH 480

extern font *curfont;
extern const matrix4x3 *textmatrix;
