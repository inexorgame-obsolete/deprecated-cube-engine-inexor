/// @file Header for the internal GLSL shader organisation

#pragma once

#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/cube_loops.hpp"
#include "inexor/shared/cube_types.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/network/SharedTree.hpp"
#include "inexor/engine/glexts.hpp"

#include <SDL.h>
#include <SDL_opengl.h>

#include <algorithm>

struct GlobalShaderParamState
{
    const char *name;
    union
    {
        float fval[32];
        int ival[32];
        uint uval[32];
        uchar buf[32*sizeof(float)];
    };
    int version;

    static int nextversion;

    void resetversions();

    void changed()
    {
        if(++nextversion < 0) resetversions();
        version = nextversion;
    }
};

struct ShaderParamBinding
{
    int loc, size;
    GLenum format;
};

struct GlobalShaderParamUse : ShaderParamBinding
{

    GlobalShaderParamState *param;
    int version;

    void flush()
    {
        if(version == param->version) return;
        switch(format)
        {
            case GL_BOOL:
            case GL_FLOAT:      glUniform1fv_(loc, size, param->fval); break;
            case GL_BOOL_VEC2:
            case GL_FLOAT_VEC2: glUniform2fv_(loc, size, param->fval); break;
            case GL_BOOL_VEC3:
            case GL_FLOAT_VEC3: glUniform3fv_(loc, size, param->fval); break;
            case GL_BOOL_VEC4:
            case GL_FLOAT_VEC4: glUniform4fv_(loc, size, param->fval); break;
            case GL_INT:        glUniform1iv_(loc, size, param->ival); break;
            case GL_INT_VEC2:   glUniform2iv_(loc, size, param->ival); break;
            case GL_INT_VEC3:   glUniform3iv_(loc, size, param->ival); break;
            case GL_INT_VEC4:   glUniform4iv_(loc, size, param->ival); break;
            case GL_FLOAT_MAT2: glUniformMatrix2fv_(loc, 1, GL_FALSE, param->fval); break;
            case GL_FLOAT_MAT3: glUniformMatrix3fv_(loc, 1, GL_FALSE, param->fval); break;
            case GL_FLOAT_MAT4: glUniformMatrix4fv_(loc, 1, GL_FALSE, param->fval); break;
        }
        version = param->version;
    }
};

struct LocalShaderParamState : ShaderParamBinding
{
    const char *name;
};

struct SlotShaderParam
{
    const char *name;
    int loc;
    float val[4];
};

struct SlotShaderParamState : LocalShaderParamState
{
    float val[4];

    SlotShaderParamState() {}
    SlotShaderParamState(const SlotShaderParam &p)
    {
        name = p.name;
        loc = -1;
        size = 1;
        format = GL_FLOAT_VEC4;
        memcpy(val, p.val, sizeof(val));
    }
};

enum
{
    SHADER_DEFAULT    = 0,
    SHADER_NORMALSLMS = 1<<0,
    SHADER_ENVMAP     = 1<<1,
    SHADER_OPTION     = 1<<3,

    SHADER_INVALID    = 1<<8,
    SHADER_DEFERRED   = 1<<9
};

#define MAXSHADERDETAIL 3
#define MAXVARIANTROWS 5

extern SharedVar<int> shaderdetail;

class Slot;
class VSlot;

struct UniformLoc
{
    const char *name, *blockname;
    int loc, version, binding, stride, offset, size;
    void *data;
    UniformLoc(const char *name = NULL, const char *blockname = NULL, int binding = -1, int stride = -1) : name(name), blockname(blockname), loc(-1), version(-1), binding(binding), stride(stride), offset(-1), size(-1), data(NULL) {}
};

struct AttribLoc
{
    const char *name;
    int loc;
    AttribLoc(const char *name = NULL, int loc = -1) : name(name), loc(loc) {}
};

struct Shader
{
    static Shader *lastshader;

    char *name, *vsstr, *psstr, *defer;
    int type;
    GLuint program, vsobj, psobj;
    vector<SlotShaderParamState> defaultparams;
    vector<GlobalShaderParamUse> globalparams;
    vector<LocalShaderParamState> localparams;
    vector<uchar> localparamremap;
    Shader *detailshader, *variantshader, *altshader, *fastshader[MAXSHADERDETAIL];
    vector<Shader *> variants;
    ushort *variantrows;
    bool standard, forced, used;
    Shader *reusevs, *reuseps;
    vector<UniformLoc> uniformlocs;
    vector<AttribLoc> attriblocs;
    const void *owner;

    Shader() : name(NULL), vsstr(NULL), psstr(NULL), defer(NULL), type(SHADER_DEFAULT), program(0), vsobj(0), psobj(0), detailshader(NULL), variantshader(NULL), altshader(NULL), variantrows(NULL), standard(false), forced(false), used(false), reusevs(NULL), reuseps(NULL), owner(NULL)
    {
        loopi(MAXSHADERDETAIL) fastshader[i] = this;
    }

    ~Shader()
    {
        DELETEA(name);
        DELETEA(vsstr);
        DELETEA(psstr);
        DELETEA(defer);
        DELETEA(variantrows);
    }

    void fixdetailshader(bool force = true, bool recurse = true);
    void allocparams(Slot *slot = NULL);
    void setslotparams(Slot &slot);
    void setslotparams(Slot &slot, VSlot &vslot);
    void bindprograms();

    void flushparams(Slot *slot = NULL)
    {
        if(!used) { allocparams(slot); used = true; }
        loopv(globalparams) globalparams[i].flush();
    }

    void force();

    bool invalid() const { return (type&SHADER_INVALID)!=0; }
    bool deferred() const { return (type&SHADER_DEFERRED)!=0; }
    bool loaded() const { return detailshader!=NULL; }

    static inline bool isnull(const Shader *s) { return !s; }

    bool isnull() const { return isnull(this); }

    int numvariants(int row) const
    {
        if(row < 0 || row >= MAXVARIANTROWS || !variantrows) return 0;
        return variantrows[row+1] - variantrows[row];
    }

    Shader *getvariant(int col, int row) const
    {
        if(row < 0 || row >= MAXVARIANTROWS || col < 0 || !variantrows) return NULL;
        int start = variantrows[row], end = variantrows[row+1];
        return col < end - start ? variants[start + col] : NULL;
    }

    bool hasoption(int row)
    {
        if(detailshader)
        {
            Shader *s = getvariant(0, row);
            if(s) return (s->type&SHADER_OPTION)!=0;
        }
        return false;
    }

    void addvariant(int row, Shader *s)
    {
        if(row < 0 || row >= MAXVARIANTROWS || variants.length() >= USHRT_MAX) return;
        if(!variantrows) { variantrows = new ushort[MAXVARIANTROWS+1]; memset(variantrows, 0, (MAXVARIANTROWS+1)*sizeof(ushort)); }
        variants.insert(variantrows[row+1], s);
        for(int i = row+1; i <= MAXVARIANTROWS; ++i) ++variantrows[i];
    }

    void setvariant_(int col, int row, Shader *fallbackshader)
    {
        Shader *s = fallbackshader;
        if(detailshader->variantrows)
        {
            int start = detailshader->variantrows[row], end = detailshader->variantrows[row+1];
            for(col = std::min(start + col, end-1); col >= start; --col)
            {
                if(!detailshader->variants[col]->invalid()) { s = detailshader->variants[col]; break; }
            }
        }
        if(lastshader!=s) s->bindprograms();
    }

    void setvariant(int col, int row, Shader *fallbackshader)
    {
        if(isnull() || !loaded()) return;
        setvariant_(col, row, fallbackshader);
        lastshader->flushparams();
    }

    void setvariant(int col, int row)
    {
        if(isnull() || !loaded()) return;
        setvariant_(col, row, detailshader);
        lastshader->flushparams();
    }

    void setvariant(int col, int row, Slot &slot, VSlot &vslot, Shader *fallbackshader)
    {
        if(isnull() || !loaded()) return;
        setvariant_(col, row, fallbackshader);
        lastshader->flushparams(&slot);
        lastshader->setslotparams(slot, vslot);
    }

    void setvariant(int col, int row, Slot &slot, VSlot &vslot)
    {
        if(isnull() || !loaded()) return;
        setvariant_(col, row, detailshader);
        lastshader->flushparams(&slot);
        lastshader->setslotparams(slot, vslot);
    }

    void set_()
    {
        if(lastshader!=detailshader) detailshader->bindprograms();
    }

    void set()
    {
        if(isnull() || !loaded()) return;
        set_();
        lastshader->flushparams();
    }

    void set(Slot &slot, VSlot &vslot)
    {
        if(isnull() || !loaded()) return;
        set_();
        lastshader->flushparams(&slot);
        lastshader->setslotparams(slot, vslot);
    }

    bool compile();
    void cleanup(bool invalid = false);

    static int uniformlocversion();
};

struct GlobalShaderParam
{
    const char *name;
    GlobalShaderParamState *param;

    GlobalShaderParam(const char *name) : name(name), param(NULL) {}

    GlobalShaderParamState *resolve()
    {
        extern GlobalShaderParamState *getglobalparam(const char *name);
        if(!param) param = getglobalparam(name);
        param->changed();
        return param;
    }

    void setf(float x = 0, float y = 0, float z = 0, float w = 0)
    {
        GlobalShaderParamState *g = resolve();
        g->fval[0] = x;
        g->fval[1] = y;
        g->fval[2] = z;
        g->fval[3] = w;
    }
    void set(const vec &v, float w = 0) { setf(v.x, v.y, v.z, w); }
    void set(const vec2 &v, float z = 0, float w = 0) { setf(v.x, v.y, z, w); }
    void set(const vec4 &v) { setf(v.x, v.y, v.z, v.w); }
    void set(const plane &p) { setf(p.x, p.y, p.z, p.offset); }
    void set(const matrix2 &m) { memcpy(resolve()->fval, m.a.v, sizeof(m)); }
    void set(const matrix3 &m) { memcpy(resolve()->fval, m.a.v, sizeof(m)); }
    void set(const matrix4 &m) { memcpy(resolve()->fval, m.a.v, sizeof(m)); }

    template<class T>
    void setv(const T *v, int n = 1) { memcpy(resolve()->buf, v, n*sizeof(T)); }

    void seti(int x = 0, int y = 0, int z = 0, int w = 0)
    {
        GlobalShaderParamState *g = resolve();
        g->ival[0] = x;
        g->ival[1] = y;
        g->ival[2] = z;
        g->ival[3] = w;
    }
    void set(const ivec &v, int w = 0) { seti(v.x, v.y, v.z, w); }
    void set(const ivec2 &v, int z = 0, int w = 0) { seti(v.x, v.y, z, w); }
    void set(const ivec4 &v) { seti(v.x, v.y, v.z, v.w); }

    void setu(uint x = 0, uint y = 0, uint z = 0, uint w = 0)
    {
        GlobalShaderParamState *g = resolve();
        g->uval[0] = x;
        g->uval[1] = y;
        g->uval[2] = z;
        g->uval[3] = w;
    }

    template<class T>
    T *reserve(int n = 1) { return (T *)resolve()->buf; }
};

struct LocalShaderParam
{
    const char *name;
    int loc;

    LocalShaderParam(const char *name) : name(name), loc(-1) {}

    LocalShaderParamState *resolve()
    {
        Shader *s = Shader::lastshader;
        if(!s) return NULL;
        if(!s->localparamremap.inrange(loc))
        {
            extern int getlocalparam(const char *name);
            if(loc == -1) loc = getlocalparam(name);
            if(!s->localparamremap.inrange(loc)) return NULL;
        }
        uchar remap = s->localparamremap[loc];
        return s->localparams.inrange(remap) ? &s->localparams[remap] : NULL;
    }

    void setf(float x = 0, float y = 0, float z = 0, float w = 0)
    {
        ShaderParamBinding *b = resolve();
        if(b) switch(b->format)
        {
            case GL_BOOL:
            case GL_FLOAT:      glUniform1f_(b->loc, x); break;
            case GL_BOOL_VEC2:
            case GL_FLOAT_VEC2: glUniform2f_(b->loc, x, y); break;
            case GL_BOOL_VEC3:
            case GL_FLOAT_VEC3: glUniform3f_(b->loc, x, y, z); break;
            case GL_BOOL_VEC4:
            case GL_FLOAT_VEC4: glUniform4f_(b->loc, x, y, z, w); break;
            case GL_INT:        glUniform1i_(b->loc, int(x)); break;
            case GL_INT_VEC2:   glUniform2i_(b->loc, int(x), int(y)); break;
            case GL_INT_VEC3:   glUniform3i_(b->loc, int(x), int(y), int(z)); break;
            case GL_INT_VEC4:   glUniform4i_(b->loc, int(x), int(y), int(z), int(w)); break;
        }
    }
    void set(const vec &v, float w = 0) { setf(v.x, v.y, v.z, w); }
    void set(const vec2 &v, float z = 0, float w = 0) { setf(v.x, v.y, z, w); }
    void set(const vec4 &v) { setf(v.x, v.y, v.z, v.w); }
    void set(const plane &p) { setf(p.x, p.y, p.z, p.offset); }
    void setv(const float *f, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform1fv_(b->loc, n, f); }
    void setv(const vec *v, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform3fv_(b->loc, n, v->v); }
    void setv(const vec2 *v, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform2fv_(b->loc, n, v->v); }
    void setv(const vec4 *v, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform4fv_(b->loc, n, v->v); }
    void setv(const plane *p, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform4fv_(b->loc, n, p->v); }
    void setv(const matrix2 *m, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniformMatrix2fv_(b->loc, n, GL_FALSE, m->a.v); }
    void setv(const matrix3 *m, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniformMatrix3fv_(b->loc, n, GL_FALSE, m->a.v); }
    void setv(const matrix4 *m, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniformMatrix4fv_(b->loc, n, GL_FALSE, m->a.v); }
    void set(const matrix2 &m) { setv(&m); }
    void set(const matrix3 &m) { setv(&m); }
    void set(const matrix4 &m) { setv(&m); }

    template<class T>
    void sett(T x, T y, T z, T w)
    {
        ShaderParamBinding *b = resolve();
        if(b) switch(b->format)
        {
            case GL_FLOAT:      glUniform1f_(b->loc, x); break;
            case GL_FLOAT_VEC2: glUniform2f_(b->loc, x, y); break;
            case GL_FLOAT_VEC3: glUniform3f_(b->loc, x, y, z); break;
            case GL_FLOAT_VEC4: glUniform4f_(b->loc, x, y, z, w); break;
            case GL_BOOL:
            case GL_INT:        glUniform1i_(b->loc, x); break;
            case GL_BOOL_VEC2:
            case GL_INT_VEC2:   glUniform2i_(b->loc, x, y); break;
            case GL_BOOL_VEC3:
            case GL_INT_VEC3:   glUniform3i_(b->loc, x, y, z); break;
            case GL_BOOL_VEC4:
            case GL_INT_VEC4:   glUniform4i_(b->loc, x, y, z, w); break;
        }
    }
    void seti(int x = 0, int y = 0, int z = 0, int w = 0) { sett<int>(x, y, z, w); }
    void set(const ivec &v, int w = 0) { seti(v.x, v.y, v.z, w); }
    void set(const ivec2 &v, int z = 0, int w = 0) { seti(v.x, v.y, z, w); }
    void set(const ivec4 &v) { seti(v.x, v.y, v.z, v.w); }
    void setv(const int *i, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform1iv_(b->loc, n, i); }
    void setv(const ivec *v, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform3iv_(b->loc, n, v->v); }
    void setv(const ivec2 *v, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform2iv_(b->loc, n, v->v); }
    void setv(const ivec4 *v, int n = 1) { ShaderParamBinding *b = resolve(); if(b) glUniform4iv_(b->loc, n, v->v); }
};

#define LOCALPARAM(name, vals) do { static LocalShaderParam param( #name ); param.set(vals); } while(0)
#define LOCALPARAMF(name, ...) do { static LocalShaderParam param( #name ); param.setf(__VA_ARGS__); } while(0)
#define LOCALPARAMI(name, ...) do { static LocalShaderParam param( #name ); param.seti(__VA_ARGS__); } while(0)
#define LOCALPARAMV(name, vals, num) do { static LocalShaderParam param( #name ); param.setv(vals, num); } while(0)
#define GLOBALPARAM(name, vals) do { static GlobalShaderParam param( #name ); param.set(vals); } while(0)
#define GLOBALPARAMF(name, ...) do { static GlobalShaderParam param( #name ); param.setf(__VA_ARGS__); } while(0)
#define GLOBALPARAMI(name, ...) do { static GlobalShaderParam param( #name ); param.seti(__VA_ARGS__); } while(0)
#define GLOBALPARAMV(name, vals, num) do { static GlobalShaderParam param( #name ); param.setv(vals, num); } while(0)

#define SETSHADER(name, ...) \
    do { \
        static Shader *name##shader = NULL; \
        if(!name##shader) name##shader = lookupshaderbyname(#name); \
        name##shader->set(__VA_ARGS__); \
    } while(0)
#define SETVARIANT(name, ...) \
    do { \
        static Shader *name##shader = NULL; \
        if(!name##shader) name##shader = lookupshaderbyname(#name); \
        name##shader->setvariant(__VA_ARGS__); \
    } while(0)

extern Shader *nullshader, *hudshader, *hudnotextureshader, *textureshader, *notextureshader, *nocolorshader, *foggedshader, *foggednotextureshader, *stdworldshader;
extern SharedVar<int> reservevpparams, maxvsuniforms, maxfsuniforms;

extern Shader *lookupshaderbyname(const char *name);
extern Shader *useshaderbyname(const char *name);
extern Shader *generateshader(const char *name, const char *cmd, ...);
extern void resetslotshader();
extern void setslotshader(Slot &s);
extern void linkslotshader(Slot &s, bool load = true);
extern void linkvslotshader(VSlot &s, bool load = true);
extern void linkslotshaders();
extern const char *getshaderparamname(const char *name, bool insert = true);

#define MAXDYNLIGHTS 5
#define DYNLIGHTBITS 6
#define DYNLIGHTMASK ((1<<DYNLIGHTBITS)-1)

#define MAXBLURRADIUS 7

extern void setupblurkernel(int radius, float sigma, float *weights, float *offsets);
extern void setblurshader(int pass, int size, int radius, float *weights, float *offsets);

// TODO
extern Slot dummyslot;
extern VSlot dummyvslot;
