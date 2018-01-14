#pragma once

#include "inexor/network/SharedVar.hpp"
#include "inexor/shared/geom.hpp"

// Main menu controlling.

extern SharedVar<int> mainmenu;

extern void clearmainmenu();
extern void g3d_mainmenu();

extern void menuprocess();
extern void addchange(const char *desc, int type);
extern void clearchanges(int type);


extern vec menuinfrontofplayer();
extern int cleargui(int n = 0);

enum
{
    NOT_INITING = 0,
    INIT_LOAD,
    INIT_RESET
};
extern int initing;

enum { CHANGE_GFX = 1<<0, CHANGE_SOUND = 1<<1 };
extern bool initwarning(const char *desc, int level = INIT_RESET, int type = CHANGE_GFX);
