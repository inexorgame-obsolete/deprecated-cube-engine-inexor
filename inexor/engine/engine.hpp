#pragma once

#include "inexor/engine/world.hpp"

#include "inexor/network/SharedTree.hpp"

#ifndef STANDALONE

#include "inexor/engine/octree.hpp"
#include "inexor/engine/material.hpp"
#include "inexor/engine/lightmap.hpp"
#include "inexor/engine/shader.hpp"
#include "inexor/engine/frame.hpp"
#include "inexor/engine/octa.hpp"
#include "inexor/texture/texture.hpp"
#include "inexor/model/model.hpp"

#include "inexor/engine/depthfx.hpp"

#include "inexor/util/InexorException.hpp"


#include "inexor/engine/material.hpp"
extern dynent *player;
extern physent *camera1;                // special ent that acts as camera, same object as player1 in FPS mode

extern SharedVar<int> worldscale, worldsize;
extern SharedVar<int> mapversion;
extern vector<ushort> texmru;
extern int xtraverts, xtravertsva;
extern const ivec cubecoords[8];
extern const ivec facecoords[6][4];
extern const uchar fv[6][4];
extern const uchar fvmasks[64];
extern const uchar faceedgesidx[6][4];

extern SDL_Window *sdl_window;


extern SharedVar<int> zpass, glowpass;

extern vector<int> entgroup;

// octaedit + slots TODO: merge into slots.cpp

extern void compacteditvslots();
extern void compactmruvslots();

// ents
extern char *entname(entity &e);
extern bool haveselent();
extern undoblock *copyundoents(undoblock *u);
extern void pasteundoent(int idx, const entity &ue);
extern void pasteundoents(undoblock *u);

// renderva
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

// console
extern void processkey(int code, bool isdown);
extern void processtextinput(const char *str, int len);
extern int rendercommand(int x, int y, int w);
extern int renderconsole(int w, int h, int abovehud);
extern void resetcomplete();
extern void complete(char *s, int maxlen, const char *cmdprefix, bool backwards);
const char *getkeyname(int code);
extern const char *addreleaseaction(char *s);
extern void writebinds(stream *f);
extern void writecompletions(stream *f);

// main
extern SharedVar<int> numcpus;

// extern bool grabinput, minimized;

// extern void pushevent(const SDL_Event &e);
// extern bool interceptkey(int sym);
#include "inexor/engine/renderbackground.hpp"

extern void getfps(int &fps, int &bestdiff, int &worstdiff);
extern void swapbuffers(bool overlay = true);

#include "inexor/engine/glare.hpp"
#include "inexor/engine/octarender.hpp"
#include "inexor/engine/water.hpp"
#include "inexor/engine/world.hpp"
#include "inexor/engine/renderparticles.hpp"
#include "inexor/engine/rendergl.hpp"
#include "inexor/engine/grass.hpp"
#endif
