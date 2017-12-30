#pragma once

// Potentially visible sets are used to optimize the rendering performance by culling primitives which aren't visible.
// They get precomputed using static geometry.
// So for really dynamic worlds one would probably need a different solution.

#include "inexor/shared/geom.hpp"
#include "inexor/io/legacy/stream.hpp"

extern void clearpvs();
extern bool pvsoccluded(const ivec &bbmin, const ivec &bbmax);
extern bool pvsoccludedsphere(const vec &center, float radius);
extern bool waterpvsoccluded(int height);
extern void setviewcell(const vec &p);
extern void savepvs(stream *f);
extern void loadpvs(stream *f, int numpvs);
extern int getnumviewcells();

static inline bool pvsoccluded(const ivec &bborigin, int size)
{
    return pvsoccluded(bborigin, ivec(bborigin).add(size));
}
