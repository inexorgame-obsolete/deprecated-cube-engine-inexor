#pragma once
#include <SDL_opengl.h>                  // for GL_SAMPLES_PASSED

#include "inexor/engine/glexts.hpp"      // for glBeginQuery_, glEndQuery_
#include "inexor/engine/octree.hpp"      // for occludequery, vtxarray (ptr ...
#include "inexor/network/SharedVar.hpp"  // for SharedVar
#include "inexor/shared/geom.hpp"        // for ivec (ptr only), vec

extern vtxarray *visibleva, *reflectedva;

extern void visiblecubes(bool cull = true);
extern void setvfcP(float z = -1, const vec &bbmin = vec(-1, -1, -1), const vec &bbmax = vec(1, 1, 1));
extern void savevfcP();
extern void restorevfcP();
extern void rendergeom(float causticspass = 0, bool fogpass = false);
extern void renderalphageom(bool fogpass = false);
extern void rendermapmodels();
extern void renderreflectedgeom(bool causticspass = false, bool fogpass = false);
extern void renderreflectedmapmodels();
extern void renderoutline();
extern bool rendersky(bool explicitonly = false);

/// Resets the set of slots that an error has been reported for.
extern void resetinvalidtextslots();

extern bool isfoggedsphere(float rad, const vec &cv);
extern int isvisiblesphere(float rad, const vec &cv);
extern bool bboccluded(const ivec &bo, const ivec &br);
extern occludequery *newquery(void *owner);
extern bool checkquery(occludequery *query, bool nowait = false);
extern void resetqueries();
extern int getnumqueries();
extern void startbb(bool mask = true);
extern void endbb(bool mask = true);
extern void drawbb(const ivec &bo, const ivec &br);

extern SharedVar<int> oqfrags;

#define startquery(query) do { glBeginQuery_(GL_SAMPLES_PASSED, ((occludequery *)(query))->id); } while(0)
#define endquery(query) do { glEndQuery_(GL_SAMPLES_PASSED); } while(0)
