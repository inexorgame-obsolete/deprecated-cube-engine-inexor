#ifndef _CEF_CONTEXT_BINDINGS_H
#define _CEF_CONTEXT_BINDINGS_H

#include "engine.h"
#include "fpsgame/game.h"

extern void quit();
extern void getfps(int &fps, int &bestdiff, int &worstdiff);

extern int fullscreen;
extern int scr_w;
extern int scr_h;
extern int vsync;

namespace game {
    extern fpsent *player1;
    extern void switchname(const char *name);
}

#endif  // _CEF_CONTEXT_BINDINGS_H
