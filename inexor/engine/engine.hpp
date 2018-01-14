#pragma once

#include "inexor/shared/cube.hpp"
#include "inexor/engine/world.hpp"

#include "inexor/network/SharedTree.hpp"

#ifndef STANDALONE

#include "inexor/engine/octree.hpp"
#include "inexor/engine/lightmap.hpp"
#include "inexor/engine/shader.hpp"
#include "inexor/texture/texture.hpp"
#include "inexor/model/model.hpp"

#include "inexor/util/InexorException.hpp"


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
extern bool inbetweenframes, renderedframe;

extern SDL_Window *sdl_window;

namespace inexor {
namespace rendering {
namespace screen {
    extern int screenw, screenh;
}
}
}

extern SharedVar<int> zpass, glowpass;

extern vector<int> entgroup;

// shader

extern void loadshaders();
extern void renderpostfx();

// octaedit + slots TODO: merge into slots.cpp

extern void compacteditvslots();
extern void compactmruvslots();

// rendergl
extern bool hasVAO, hasFBO, hasAFBO, hasDS, hasTF, hasTRG, hasTSW, hasS3TC, hasFXT1, hasAF, hasFBB, hasUBO, hasMBR;
extern int hasstencil;
extern SharedVar<int> glversion, glslversion;

enum { DRAWTEX_NONE = 0, DRAWTEX_ENVMAP, DRAWTEX_MINIMAP, DRAWTEX_MODELPREVIEW };

extern SharedVar<float> forceaspect;
extern float curfov, fovy, aspect;
extern int drawtex;
extern bool renderedgame;
extern const matrix4 viewmatrix;
extern matrix4 cammatrix, projmatrix, camprojmatrix, invcammatrix, invcamprojmatrix;
extern bvec fogcolor;
extern vec curfogcolor;
extern SharedVar<int> fog;
extern float curfogstart, curfogend;

extern void gl_checkextensions();
extern void gl_init(int depth, int fsaa);
extern void gl_resize();
extern void cef_resize(int width, int height);
extern void cleangl();
extern void rendergame(bool mainpass = false);
extern void invalidatepostfx();
extern void gl_drawframe();
extern void gl_drawmainmenu();
extern void gl_drawhud();
extern void drawminimap();
extern void drawtextures();
extern void enablepolygonoffset(GLenum type);
extern void disablepolygonoffset(GLenum type);
extern void calcspherescissor(const vec &center, float size, float &sx1, float &sy1, float &sx2, float &sy2);
extern int pushscissor(float sx1, float sy1, float sx2, float sy2);
extern void popscissor();
extern void recomputecamera();
extern void screenquad();
extern void screenquad(float sw, float sh);
extern void screenquadflipped(float sw, float sh);
extern void screenquad(float sw, float sh, float sw2, float sh2);
extern void screenquadoffset(float x, float y, float w, float h);
extern void screenquadoffset(float x, float y, float w, float h, float x2, float y2, float w2, float h2);
extern void hudquad(float x, float y, float w, float h, float tx = 0, float ty = 0, float tw = 1, float th = 1);
extern void setfogcolor(const vec &v);
extern void zerofogcolor();
extern void resetfogcolor();
extern void setfogdist(float start, float end);
extern void clearfogdist();
extern void resetfogdist();
extern void writecrosshairs(stream *f);

namespace modelpreview
{
    extern void start(int x, int y, int w, int h, bool background = true);
    extern void end();
}

// renderextras
extern void render3dbox(vec &o, float tofloor, float toceil, float xradius, float yradius = 0);

// ents
extern char *entname(entity &e);
extern bool haveselent();
extern undoblock *copyundoents(undoblock *u);
extern void pasteundoent(int idx, const entity &ue);
extern void pasteundoents(undoblock *u);

// octarender
extern vector<tjoint> tjoints;
extern vector<vtxarray *> varoot, valist;

extern ushort encodenormal(const vec &n);
extern vec decodenormal(ushort norm);
extern void guessnormals(const vec *pos, int numverts, vec *normals);
extern void reduceslope(ivec &n);
extern void findtjoints();
extern void octarender();
extern void allchanged(bool load = false);
extern void clearvas(cube *c);
extern void destroyva(vtxarray *va, bool reparent = true);
extern bool readva(vtxarray *va, ushort *&edata, vertex *&vdata);
extern void updatevabb(vtxarray *va, bool force = false);
extern void updatevabbs(bool force = false);

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

// water
extern int refracting, refractfog;
extern bool reflecting, fading, fogging;
extern float reflectz;
extern SharedVar<int> reflectdist, vertwater, waterrefract, waterreflect, waterfade, caustics, waterfallrefract;

#define GETMATIDXVAR(name, var, type) \
    type get##name##var(int mat) \
    { \
        switch(mat&MATF_INDEX) \
        { \
            default: case 0: return name##var; \
            case 1: return name##2##var; \
            case 2: return name##3##var; \
            case 3: return name##4##var; \
        } \
    }

extern const bvec &getwatercolor(int mat);
extern const bvec &getwaterfallcolor(int mat);
extern int getwaterfog(int mat);
extern const bvec &getlavacolor(int mat);
extern int getlavafog(int mat);
extern const bvec &getglasscolor(int mat);

extern void cleanreflections();
extern void queryreflections();
extern void drawreflections();
extern void renderwater();
extern void renderlava(const materialsurface &m, Texture *tex, float scale);
extern void loadcaustics(bool force = false);
extern void preloadwatershaders(bool force = false);

// glare
extern bool glaring;

extern void drawglaretex();
extern void addglare();

// depthfx
extern bool depthfxing;

extern void drawdepthfxtex();

// serverbrowser
extern bool resolverwait(const char *name, ENetAddress *address);

// client
// TODO: own file client/network.hpp
extern void connectserv(const char *servername, int port, const char *serverpassword, const char *mapwish = nullptr, int modewish = -1);
extern void abortconnect();
extern void clientkeepalive();

// command
extern hashnameset<ident> idents;
extern int identflags;

extern void clearoverrides();
extern void writecfg(const char *name = nullptr);
extern void loadhistory();
extern void writehistory();

extern void checksleep(int millis);
extern void clearsleep(bool clearoverrides = true);

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

extern float loadprogress;
extern void renderbackground(const char *caption = nullptr, Texture *mapshot = nullptr, const char *mapname = nullptr, const char *mapinfo = nullptr, bool restore = false, bool force = false);
extern void renderprogress(float bar, const char *text, GLuint tex = 0, bool background = false);

extern void getfps(int &fps, int &bestdiff, int &worstdiff);
extern void swapbuffers(bool overlay = true);
extern int getclockmillis();
extern const char *gettimestr(const char *format = "%d_%b_%y_%H.%M.%S", bool forcelowercase = false);

enum { KR_CONSOLE = 1<<0, KR_GUI = 1<<1, KR_EDITMODE = 1<<2 };

// extern void keyrepeat(bool on, int mask = ~0);

enum { TI_CONSOLE = 1<<0, TI_GUI = 1<<1 };

// extern void textinput(bool on, int mask = ~0);

// world

extern vector<int> outsideents;

extern void entcancel();
extern void entitiesinoctanodes();
extern void attachentities();
extern void freeoctaentities(cube &c);
extern bool pointinsel(const selinfo &sel, const vec &o);

extern void resetmap();
extern void startmap(const char *name);

// renderparticles
extern void particleinit();
extern void clearparticles();
extern void clearparticleemitters();
extern void seedparticles();
extern void updateparticles();
extern void renderparticles(bool mainpass = false);
extern bool printparticles(extentity &e, char *buf, int len);
extern void regularshape(int type, int radius, int color, int dir, int num, int fade, const vec &p, float size, int gravity, int vel = 200, const vec* modfrom=nullptr, const vec* modto=nullptr); // bomberman

// grass
extern void generategrass();
extern void rendergrass();
extern void cleanupgrass();

/// Exception that should be thrown if GL related functionality failed.
IEXCEPTION(GLException, "OpenGL related functionality failed");

#endif

