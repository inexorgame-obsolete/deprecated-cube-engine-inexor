#pragma once

#include "inexor/shared/ents.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/io/legacy/stream.hpp"

/// special ent that acts as camera, same object as player1 in FPS mode
extern physent *camera1;
extern vec worldpos, camdir, camright, camup;

extern int xtraverts, xtravertsva;

extern void disablezoom();

extern vec calcavatarpos(const vec &pos, float dist);
extern vec calcmodelpreviewpos(const vec &radius, float &yaw);

extern void damageblend(int n);
extern void damagecompass(int n, const vec &loc);

extern vec minimapcenter, minimapradius, minimapscale;
extern void bindminimap();

extern void bind_items_texture();
extern void bind_bomb_items_texture();

extern matrix4 hudmatrix;
extern void resethudmatrix();
extern void pushhudmatrix();
extern void flushhudmatrix(bool flushparams = true);
extern void pophudmatrix(bool flush = true, bool flushparams = true);
extern void pushhudscale(float sx, float sy = 0);
extern void pushhudtranslate(float tx, float ty, float sx = 0, float sy = 0);

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
