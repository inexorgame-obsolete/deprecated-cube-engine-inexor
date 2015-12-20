/// @file Legacy texture slot loading.

#include "inexor/engine/engine.hpp"
#include "inexor/shared/filesystem.hpp"

const struct slottex
{
    const char *name;
    int id;
} slottexs[] =
{
    { "c", TEX_DIFFUSE },
    { "u", TEX_UNKNOWN },
    { "d", TEX_DECAL },
    { "n", TEX_NORMAL },
    { "g", TEX_GLOW },
    { "s", TEX_SPEC },
    { "z", TEX_DEPTH },
    { "e", TEX_ENVMAP }
};

int findslottex(const char *name)
{
    loopi(sizeof(slottexs) / sizeof(slottex))
    {
        if(!strcmp(slottexs[i].name, name)) return slottexs[i].id;
    }
    return -1;
}

void texture(char *type, char *name, int *rot, int *xoffset, int *yoffset, float *scale)
{
    if(slots.length() >= 0x10000) return;
    if(!type || !name) return;

    static int lastmatslot = -1;
    int tnum = findslottex(type), matslot = findmaterial(type);
    if(tnum < 0) tnum = atoi(type);
    if(tnum == TEX_DIFFUSE) lastmatslot = matslot;
    else if(lastmatslot >= 0) matslot = lastmatslot;
    else if(slots.empty()) return;
    Slot &s = matslot >= 0 ? lookupmaterialslot(matslot, false) : *(tnum != TEX_DIFFUSE ? slots.last() : slots.add(new Slot(slots.length())));
    s.loaded = 0;
    s.texmask |= 1 << tnum;
    if(s.sts.length() >= 8) conoutf(CON_WARN, "warning: too many textures in slot %d", slots.length() - 1);

    s.addtexture(tnum, name);

    if(tnum == TEX_DIFFUSE)
    {
        setslotshader(s);
        VSlot &vs = matslot >= 0 ? lookupmaterialslot(matslot, false) : *emptyvslot(s);
        vs.reset();
        vs.rotation = clamp(*rot, 0, 5);
        vs.offset = ivec2(*xoffset, *yoffset).max(0);
        vs.scale = *scale <= 0 ? 1 : *scale;
        propagatevslot(&vs, (1 << VSLOT_NUM) - 1);
    }
    //conoutf(CON_WARN, "old texture loaded, should it be converted?")
}
COMMAND(texture, "ssiiif");

///// LEGACY TEX MODIFIERS ////

void autograss(char *name)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    DELETEA(s.autograss);
    s.autograss = name[0] ? newstring(makerelpath(getcurexecdir(), name, NULL, "<premul>")) : NULL;
}
COMMAND(autograss, "s");

void texscroll(float *scrollS, float *scrollT)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    s.variants->scroll = vec2(*scrollS, *scrollT).div(1000.0f);
    propagatevslot(s.variants, 1 << VSLOT_SCROLL);
}
COMMAND(texscroll, "ff");

void texoffset_(int *xoffset, int *yoffset)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    s.variants->offset = ivec2(*xoffset, *yoffset).max(0);
    propagatevslot(s.variants, 1 << VSLOT_OFFSET);
}
COMMANDN(texoffset, texoffset_, "ii");

void texrotate_(int *rot)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    s.variants->rotation = clamp(*rot, 0, 5);
    propagatevslot(s.variants, 1 << VSLOT_ROTATION);
}
COMMANDN(texrotate, texrotate_, "i");

void texscale(float *scale)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    s.variants->scale = *scale <= 0 ? 1 : *scale;
    propagatevslot(s.variants, 1 << VSLOT_SCALE);
}
COMMAND(texscale, "f");

void texlayer(int *layer, char *name, int *mode, float *scale)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    s.variants->layer = *layer < 0 ? max(slots.length() - 1 + *layer, 0) : *layer;
    s.layermaskname = name[0] ? newstring(path(makerelpath(getcurexecdir(), name))) : NULL;
    s.layermaskmode = *mode;
    s.layermaskscale = *scale <= 0 ? 1 : *scale;
    propagatevslot(s.variants, 1 << VSLOT_LAYER);
}
COMMAND(texlayer, "isif");

void texalpha(float *front, float *back)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    s.variants->alphafront = clamp(*front, 0.0f, 1.0f);
    s.variants->alphaback = clamp(*back, 0.0f, 1.0f);
    propagatevslot(s.variants, 1 << VSLOT_ALPHA);
}
COMMAND(texalpha, "ff");

void texcolor(float *r, float *g, float *b)
{
    if(slots.empty()) return;
    Slot &s = *slots.last();
    s.variants->colorscale = vec(clamp(*r, 0.0f, 1.0f), clamp(*g, 0.0f, 1.0f), clamp(*b, 0.0f, 1.0f));
    propagatevslot(s.variants, 1 << VSLOT_COLOR);
}
COMMAND(texcolor, "fff");
