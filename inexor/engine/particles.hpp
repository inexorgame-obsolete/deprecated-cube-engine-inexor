#pragma once

#include "inexor/shared/ents.hpp"
#include "inexor/shared/geom.hpp"

struct Texture;

enum
{
    PART_BLOOD = 0,
    PART_WATER,
    PART_SMOKE,
    PART_STEAM,
    PART_FLAME,
    PART_FIREBALL1, PART_FIREBALL2, PART_FIREBALL3,
    PART_STREAK, PART_LIGHTNING,
    PART_EXPLOSION, PART_EXPLOSION_BLUE,
    PART_SPARK, PART_EDIT,
    PART_SNOW,
    PART_MUZZLE_FLASH1, PART_MUZZLE_FLASH2, PART_MUZZLE_FLASH3,
    PART_HUD_ICON,
    PART_HUD_ICON_GREY,
    PART_TEXT,
    PART_METER, PART_METER_VS,
    PART_LENS_FLARE
};

enum
{
    PT_PART = 0,
    PT_TAPE,
    PT_TRAIL,
    PT_TEXT,
    PT_TEXTUP,
    PT_METER,
    PT_METERVS,
    PT_FIREBALL,
    PT_LIGHTNING,
    PT_FLARE,

    PT_MOD    = 1<<8,
    PT_RND4   = 1<<9,
    PT_LERP   = 1<<10, // use very sparingly - order of blending issues
    PT_TRACK  = 1<<11,
    PT_GLARE  = 1<<12,
    PT_SOFT   = 1<<13,
    PT_HFLIP  = 1<<14,
    PT_VFLIP  = 1<<15,
    PT_ROT    = 1<<16,
    PT_CULL   = 1<<17,
    PT_FEW    = 1<<18,
    PT_ICON   = 1<<19,
    PT_NOTEX  = 1<<20,
    PT_SHADER = 1<<21,
    PT_FLIP  = PT_HFLIP | PT_VFLIP | PT_ROT
};

struct particleemitter
{
    extentity *ent;
    vec bbmin, bbmax;
    vec center;
    float radius;
    ivec cullmin, cullmax;
    int maxfade, lastemit, lastcull;

    particleemitter(extentity *ent)
            : ent(ent), bbmin(ent->o), bbmax(ent->o), maxfade(-1), lastemit(0), lastcull(0)
    {}

    void finalize();

    void extendbb(const vec &o, float size = 0);

    void extendbb(float z, float size = 0);
};

struct particle
{
    vec o, d;
    int gravity, fade, millis;
    bvec color;
    uchar flags;
    float size;
    union
    {
        const char *text;
        float val;
        physent *owner;
        struct
        {
            uchar color2[3];
            uchar progress;
        };
    };
};

struct partvert
{
    vec pos;
    bvec4 color;
    vec2 tc;
};

#define COLLIDERADIUS 8.0f
#define COLLIDEERROR 1.0f

struct partrenderer
{
    Texture *tex;
    const char *texname;
    int texclamp;
    uint type;
    int collide;
    string info;

    partrenderer(const char *texname, int texclamp, int type, int collide = 0)
            : tex(nullptr), texname(texname), texclamp(texclamp), type(type), collide(collide)
    {
    }
    partrenderer(int type, int collide = 0)
            : tex(nullptr), texname(nullptr), texclamp(0), type(type), collide(collide)
    {
    }
    virtual ~partrenderer()
    {
    }

    virtual void init(int n) { }
    virtual void reset() = 0;
    virtual void resettracked(physent *owner) { }
    virtual particle *addpart(const vec &o, const vec &d, int fade, int color, float size, int gravity = 0) = 0;
    virtual int adddepthfx(vec &bbmin, vec &bbmax) { return 0; }
    virtual void update() { }
    virtual void render() = 0;
    virtual bool haswork() = 0;
    virtual int count() = 0; //for debug
    virtual void cleanup() {}

    virtual void seedemitter(particleemitter &pe, const vec &o, const vec &d, int fade, float size, int gravity)
    {
    }

    //blend = 0 => remove it
    void calc(particle *p, int &blend, int &ts, vec &o, vec &d, bool step = true);

    const char *debuginfo();
};
extern partrenderer *parts[24];

struct listparticle : particle
{
    listparticle *next;
};


struct listrenderer : partrenderer
{
    static listparticle *parempty;
    listparticle *list;

    listrenderer(const char *texname, int texclamp, int type, int collide = 0)
            : partrenderer(texname, texclamp, type, collide), list(nullptr)
    {
    }
    listrenderer(int type, int collide = 0)
            : partrenderer(type, collide), list(nullptr)
    {
    }

    ~listrenderer() override
    {
    }

    virtual void killpart(listparticle *p)
    {
    }

    void reset() override;

    void resettracked(physent *owner) override;

    particle *addpart(const vec &o, const vec &d, int fade, int color, float size, int gravity) override;

    int count() override;

    bool haswork() override;

    virtual void startrender() = 0;
    virtual void endrender() = 0;
    virtual void renderpart(listparticle *p, const vec &o, const vec &d, int blend, int ts) = 0;

    void render() override;
};
