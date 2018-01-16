#pragma once

#include "inexor/engine/particles.hpp"

struct fireballrenderer : listrenderer
{
    fireballrenderer(const char *texname)
        : listrenderer(texname, 0, PT_FIREBALL|PT_GLARE|PT_SHADER)
    {}

    void startrender() override;

    void endrender() override;

    void cleanup() override;

    int finddepthfxranges(void **owners, float *ranges, int numranges, int maxranges, vec &bbmin, vec &bbmax);

    void seedemitter(particleemitter &pe, const vec &o, const vec &d, int fade, float size, int gravity) override;

    void renderpart(listparticle *p, const vec &o, const vec &d, int blend, int ts) override;
};
extern fireballrenderer bluefireballs;
extern fireballrenderer fireballs;

