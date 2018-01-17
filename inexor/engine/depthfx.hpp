#pragma once

#include <SDL_opengl.h>                    // for GLenum

#include "inexor/engine/rendertarget.hpp"  // for rendertarget
#include "inexor/network/SharedVar.hpp"    // for SharedVar
#include "inexor/shared/command.hpp"
#include "inexor/shared/geom.hpp"

struct vec;

extern SharedVar<int> depthfx, depthfxsize, blurdepthfx, depthfxpartblend, depthfxblend, depthfxscale, depthfxbias, depthfxscissor;
extern int numdepthfxranges;
extern bool depthfxing;


struct depthfxtexture : rendertarget
{
    const GLenum *colorformats() const override;

    float eyedepth(const vec &p) const;

    void addscissorvert(const vec &v, float &sx1, float &sy1, float &sx2, float &sy2);

    bool addscissorbox(const vec &center, float size);

    bool addscissorbox(const vec &bbmin, const vec &bbmax);

    bool screenrect() const override { return true; }
    bool filter() const override { return blurdepthfx!=0; }
    bool highprecision() const;
    bool emulatehighprecision() const;

    bool shouldrender() override;

    bool dorender() override;

    void dodebug(int w, int h) override;
};
extern depthfxtexture depthfxtex;
extern bool depthfxing;

extern void cleanupdepthfx();

extern void viewdepthfxtex();

extern bool binddepthfxtex();

extern void binddepthfxparams(float blend, float minblend = 0, bool allow = true, void *owner = nullptr);

extern void drawdepthfxtex();


