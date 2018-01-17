#include <SDL_opengl.h>                               // for GLenum, glBindT...
#include <algorithm>                                  // for max, min

#include "inexor/engine/depthfx.hpp"
#include "inexor/engine/explosion.hpp"                // for fireballrenderer
#include "inexor/engine/glemu.hpp"                    // for colorf
#include "inexor/engine/glexts.hpp"                   // for glActiveTexture_
#include "inexor/engine/particles.hpp"                // for parts, partrend...
#include "inexor/engine/rendergl.hpp"                 // for calcspherescissor
#include "inexor/engine/shader.hpp"                   // for LOCALPARAMF
#include "inexor/engine/water.hpp"                    // for refracting, ref...
#include "inexor/shared/command.hpp"                  // for VARP, VAR, VARFP
#include "inexor/shared/cube_loops.hpp"               // for i, loopi, k, loopk
#include "inexor/shared/geom.hpp"                     // for vec, vec::(anon...
#include "inexor/shared/tools.hpp"                    // for max, min

#define MAXDFXRANGES 4

void *depthfxowners[MAXDFXRANGES];
float depthfxranges[MAXDFXRANGES];
int numdepthfxranges = 0;
vec depthfxmin(1e16f, 1e16f, 1e16f), depthfxmax(1e16f, 1e16f, 1e16f);

// eye space depth texture for soft particles, done at low res then blurred to prevent ugly jaggies
VARP(depthfxfpscale, 1, 4096, 65536); //1<<12, 1<<16);
VARP(depthfxscale, 1, 64, 256);       //1<<6, 1<<8);
VARP(depthfxblend, 1, 16, 64);
VARP(depthfxpartblend, 1, 8, 64);
VAR(depthfxmargin, 0, 16, 64);
VAR(depthfxbias, 0, 1, 64);
extern void cleanupdepthfx();
VARFP(fpdepthfx, 0, 0, 1, cleanupdepthfx());
VARP(depthfxemuprecision, 0, 1, 1);
VARFP(depthfxsize, 6, 7, 12, cleanupdepthfx());
VARP(depthfx, 0, 1, 1);
VARP(depthfxparts, 0, 1, 1);
VARP(blurdepthfx, 0, 1, 7);
VARP(blurdepthfxsigma, 1, 50, 200);
VAR(depthfxscissor, 0, 2, 2);
VAR(debugdepthfx, 0, 0, 1);

void finddepthfxranges();

depthfxtexture depthfxtex;

float depthfxtexture::eyedepth(const vec &p) const {
    return max(-cammatrix.transform<vec>(p).z, 0.0f);
}

void depthfxtexture::addscissorvert(const vec &v, float &sx1, float &sy1, float &sx2, float &sy2) {
    vec p = camprojmatrix.perspectivetransform(v);
    sx1 = min(sx1, p.x);
    sy1 = min(sy1, p.y);
    sx2 = max(sx2, p.x);
    sy2 = max(sy2, p.y);
}

bool depthfxtexture::addscissorbox(const vec &center, float size) {
    float sx1, sy1, sx2, sy2;
    calcspherescissor(center, size, sx1, sy1, sx2, sy2);
    return addblurtiles(sx1, sy1, sx2, sy2);
}

bool depthfxtexture::addscissorbox(const vec &bbmin, const vec &bbmax) {
    float sx1 = 1, sy1 = 1, sx2 = -1, sy2 = -1;
    loopi(8)
    {
        vec v(i&1 ? bbmax.x : bbmin.x, i&2 ? bbmax.y : bbmin.y, i&4 ? bbmax.z : bbmin.z);
        addscissorvert(v, sx1, sy1, sx2, sy2);
    }
    return addblurtiles(sx1, sy1, sx2, sy2);
}

const GLenum *depthfxtexture::colorformats() const {
    static const GLenum colorfmts[] = { GL_RG16F, GL_RGB16F, GL_RGBA, GL_RGBA8, GL_RGB, GL_RGB8, GL_FALSE };
    return &colorfmts[fpdepthfx && hasTF ? (hasTRG ? 0 : 1) : 2];
}

bool depthfxtexture::highprecision() const { return colorfmt==GL_RG16F || colorfmt==GL_RGB16F; }

bool depthfxtexture::shouldrender() {
    extern void finddepthfxranges();
    finddepthfxranges();
    return (numdepthfxranges && scissorx1 < scissorx2 && scissory1 < scissory2) || debugdepthfx;
}
bool depthfxtexture::emulatehighprecision() const { return depthfxemuprecision && !blurdepthfx; }

bool depthfxtexture::dorender()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    depthfxing = true;
    refracting = -1;

    extern void renderdepthobstacles(const vec &bbmin, const vec &bbmax, float scale, float *ranges, int numranges);
    float scale = depthfxscale;
    float *ranges = depthfxranges;
    int numranges = numdepthfxranges;
    if(highprecision())
    {
        scale = depthfxfpscale;
        ranges = nullptr;
        numranges = 0;
    }
    else if(emulatehighprecision())
    {
        scale = depthfxfpscale;
        ranges = nullptr;
        numranges = -3;
    }
    renderdepthobstacles(depthfxmin, depthfxmax, scale, ranges, numranges);

    refracting = 0;
    depthfxing = false;

    return numdepthfxranges > 0;
}

void depthfxtexture::dodebug(int w, int h)
{
    if(numdepthfxranges > 0)
    {
        gle::colorf(0, 1, 0);
        debugscissor(w, h, true);
        gle::colorf(0, 0, 1);
        debugblurtiles(w, h, true);
        gle::colorf(1, 1, 1);
    }
}

void finddepthfxranges()
{
    depthfxmin = vec(1e16f, 1e16f, 1e16f);
    depthfxmax = vec(0, 0, 0);
    numdepthfxranges = fireballs.finddepthfxranges(depthfxowners, depthfxranges, 0, MAXDFXRANGES, depthfxmin, depthfxmax);
    numdepthfxranges = bluefireballs.finddepthfxranges(depthfxowners, depthfxranges, numdepthfxranges, MAXDFXRANGES, depthfxmin, depthfxmax);
    loopk(3)
    {
        depthfxmin[k] -= depthfxmargin;
        depthfxmax[k] += depthfxmargin;
    }
    if(depthfxparts)
    {
        loopi(sizeof(parts)/sizeof(parts[0]))
        {
            partrenderer *p = parts[i];
            if(p->type&PT_SOFT && p->adddepthfx(depthfxmin, depthfxmax))
            {
                if(!numdepthfxranges)
                {
                    numdepthfxranges = 1;
                    depthfxowners[0] = nullptr;
                    depthfxranges[0] = 0;
                }
            }
        }
    }
    if(depthfxscissor<2 && numdepthfxranges>0) depthfxtex.addscissorbox(depthfxmin, depthfxmax);
}

void cleanupdepthfx()
{
    depthfxtex.cleanup(true);
}

void viewdepthfxtex()
{
    if(!depthfx) return;
    depthfxtex.debug();
}

bool depthfxing = false;

bool binddepthfxtex()
{
    if(!reflecting && !refracting && depthfx && depthfxtex.rendertex && numdepthfxranges>0)        
    {
        glActiveTexture_(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, depthfxtex.rendertex);
        glActiveTexture_(GL_TEXTURE0);
        return true;
    }
    return false;
}

void binddepthfxparams(float blend, float minblend, bool allow, void *owner)
{
    if(!reflecting && !refracting && depthfx && depthfxtex.rendertex && numdepthfxranges>0)
    {
        float scale = 0, offset = -1, texscale = 0;
        if(!depthfxtex.highprecision())
        {
            float select[4] = { 0, 0, 0, 0 };
            if(!depthfxtex.emulatehighprecision())
            {
                loopi(numdepthfxranges) if(depthfxowners[i]==owner)
                {
                    select[i] = float(depthfxscale)/blend;
                    scale = 1.0f/blend;
                    offset = -float(depthfxranges[i] - depthfxbias)/blend;
                    break;
                }
            }
            else if(allow)
            {
                select[0] = float(depthfxfpscale)/blend;
                select[1] = select[0]/256;
                select[2] = select[1]/256;
                scale = 1.0f/blend;
                offset = 0;
            }
            LOCALPARAMF(depthfxselect, select[0], select[1], select[2], select[3]);
        }
        else if(allow)
        {
            scale = 1.0f/blend;
            offset = 0;
            texscale = float(depthfxfpscale)/blend;
        }
        LOCALPARAMF(depthfxparams, scale, offset, texscale, minblend);
    }
}

void drawdepthfxtex()
{
    if(!depthfx) return;

    depthfxtex.render(1<<depthfxsize, 1<<depthfxsize, blurdepthfx, blurdepthfxsigma/100.0f);
}


