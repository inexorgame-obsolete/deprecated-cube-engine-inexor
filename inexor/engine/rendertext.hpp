#pragma once

#include <math.h>                             // for ceil

#include "inexor/shared/cube_formatting.hpp"  // for PRINTFARGS
#include "inexor/shared/cube_tools.hpp"       // for DELETEA
// Simplistic bitmap text rendering
#include "inexor/shared/cube_vector.hpp"      // for vector

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
    ~font() { delete name; name = nullptr; }
};

#define FONTH (curfont->scale)
#define FONTW (FONTH/2)
#define MINRESW 640
#define MINRESH 480

extern font *curfont;
extern const matrix4x3 *textmatrix;
extern bool setfont(const char *name);
extern void pushfont();
extern bool popfont();
extern void gettextres(int &w, int &h);
extern void draw_text(const char *str, int left, int top, int r = 255, int g = 255, int b = 255, int a = 255, int cursor = -1, int maxwidth = -1);
extern void draw_textf(const char *fstr, int left, int top, ...) PRINTFARGS(1, 4);
extern float text_widthf(const char *str);
extern void text_boundsf(const char *str, float &width, float &height, int maxwidth = -1);
extern int text_visible(const char *str, float hitx, float hity, int maxwidth);
extern void text_posf(const char *str, int cursor, float &cx, float &cy, int maxwidth);

static inline int text_width(const char *str)
{
    return int(ceil(text_widthf(str)));
}

static inline void text_bounds(const char *str, int &width, int &height, int maxwidth = -1)
{
    float widthf, heightf;
    text_boundsf(str, widthf, heightf, maxwidth);
    width = int(ceil(widthf));
    height = int(ceil(heightf));
}

static inline void text_pos(const char *str, int cursor, int &cx, int &cy, int maxwidth)
{
    float cxf, cyf;
    text_posf(str, cursor, cxf, cyf, maxwidth);
    cx = int(cxf);
    cy = int(cyf);
}
