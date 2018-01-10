
#pragma once

#include "inexor/physics/bih.hpp"
#include "inexor/shared/ents.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/texture/texture.hpp"
#include "inexor/engine/shader.hpp"


enum { MDL_MD2 = 0, MDL_MD3, MDL_MD5, MDL_OBJ, MDL_SMD, MDL_IQM, NUMMODELTYPES };
enum { MDL_CULL_VFC = 1<<0, MDL_CULL_DIST = 1<<1, MDL_CULL_OCCLUDED = 1<<2, MDL_CULL_QUERY = 1<<3, MDL_SHADOW = 1<<4, MDL_DYNSHADOW = 1<<5, MDL_LIGHT = 1<<6, MDL_DYNLIGHT = 1<<7, MDL_FULLBRIGHT = 1<<8, MDL_NORENDER = 1<<9, MDL_LIGHT_FAST = 1<<10, MDL_HUD = 1<<11, MDL_GHOST = 1<<12 };

struct model;
struct modelattach
{
    const char *tag, *name;
    int anim, basetime;
    vec *pos;
    model *m;

    modelattach() : tag(nullptr), name(nullptr), anim(-1), basetime(0), pos(nullptr), m(nullptr) {}
    modelattach(const char *tag, const char *name, int anim = -1, int basetime = 0) : tag(tag), name(name), anim(anim), basetime(basetime), pos(nullptr), m(nullptr) {}
    modelattach(const char *tag, vec *pos) : tag(tag), name(nullptr), anim(-1), basetime(0), pos(pos), m(nullptr) {}
};

extern void startmodelbatches();
extern void endmodelbatches();
extern void rendermodel(entitylight *light, const char *mdl, int anim, const vec &o, float yaw = 0, float pitch = 0, int cull = MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED | MDL_LIGHT, dynent *d = nullptr, modelattach *a = nullptr, int basetime = 0, int basetime2 = 0, float trans = 1);
extern void abovemodel(vec &o, const char *mdl);
extern void rendershadow(dynent *d);
extern void renderclient(dynent *d, const char *mdlname, modelattach *attachments, int hold, int attack, int attackdelay, int lastaction, int lastpain, float fade = 1, bool ragdoll = false);
extern void interpolateorientation(dynent *d, float &interpyaw, float &interppitch);
extern void setbbfrommodel(dynent *d, const char *mdl);
extern const char *mapmodelname(int i);
extern model *loadmodel(const char *name, int i = -1, bool msg = false);
extern void preloadmodel(const char *name);
extern void flushpreloadedmodels(bool msg = true);

struct model
{
    char *name;
    float spinyaw, spinpitch, offsetyaw, offsetpitch;
    bool collide, ellipsecollide, shadow, alphadepth, depthoffset;
    float scale;
    vec translate;
    BIH *bih;
    vec bbcenter, bbradius, bbextend, collidecenter, collideradius;
    float rejectradius, eyeheight, collidexyradius, collideheight;
    int batch;

    model(const char *name) : name(name ? newstring(name) : nullptr), spinyaw(0), spinpitch(0), offsetyaw(0), offsetpitch(0), collide(true), ellipsecollide(false), shadow(true), alphadepth(true), depthoffset(false), scale(1.0f), translate(0, 0, 0), bih(nullptr), bbcenter(0, 0, 0), bbradius(-1, -1, -1), bbextend(0, 0, 0), collidecenter(0, 0, 0), collideradius(-1, -1, -1), rejectradius(-1), eyeheight(0.9f), collidexyradius(0), collideheight(0), batch(-1) {}
    virtual ~model()
    {
        delete[] name;
        name = nullptr;
        delete bih;
        bih = nullptr;
    }
    virtual void calcbb(vec &center, vec &radius) = 0;
    virtual void render(int anim, int basetime, int basetime2, const vec &o, float yaw, float pitch, dynent *d, modelattach *a = nullptr, const vec &color = vec(0, 0, 0), const vec &dir = vec(0, 0, 0), float transparent = 1) = 0;
    virtual bool load() = 0;
    virtual int type() const = 0;
    virtual BIH *setBIH() { return nullptr; }
    virtual bool envmapped() { return false; }
    virtual bool skeletal() const { return false; }

    virtual void setshader(Shader *shader) {}
    virtual void setenvmap(float envmapmin, float envmapmax, Texture *envmap) {}
    virtual void setspec(float spec) {}
    virtual void setambient(float ambient) {}
    virtual void setglow(float glow, float glowdelta, float glowpulse) {}
    virtual void setglare(float specglare, float glowglare) {}
    virtual void setalphatest(float alpha) {}
    virtual void setalphablend(bool blend) {}
    virtual void setfullbright(float fullbright) {}
    virtual void setcullface(bool cullface) {}

    virtual void preloadBIH() { if(!bih) setBIH(); }
    virtual void preloadshaders(bool force = false) {}
    virtual void preloadmeshes() {}
    virtual void cleanup() {}

    virtual void startrender() {}
    virtual void endrender() {}

    void boundbox(vec &center, vec &radius)
    {
        if(bbradius.x < 0)
        {
            calcbb(bbcenter, bbradius);
            bbradius.add(bbextend);
        }
        center = bbcenter;
        radius = bbradius;
    }

    float collisionbox(vec &center, vec &radius)
    {
        if(collideradius.x < 0)
        {
            boundbox(collidecenter, collideradius);
            if(collidexyradius)
            {
                collidecenter.x = collidecenter.y = 0;
                collideradius.x = collideradius.y = collidexyradius;
            }
            if(collideheight)
            {
                collidecenter.z = collideradius.z = collideheight/2;
            }
            rejectradius = collideradius.magnitude();
        }
        center = collidecenter;
        radius = collideradius;
        return rejectradius;
    }

    float boundsphere(vec &center)
    {
        vec radius;
        boundbox(center, radius);
        return radius.magnitude();
    }

    float above()
    {
        vec center, radius;
        boundbox(center, radius);
        return center.z+radius.z;
    }
};

