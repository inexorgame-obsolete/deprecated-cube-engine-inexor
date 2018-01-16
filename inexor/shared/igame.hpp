// the interface the engine uses to run the gameplay module
#pragma once
#include "inexor/shared/command.hpp"
#include "inexor/fpsgame/config.hpp"
#include "inexor/fpsgame/entities.hpp"

namespace game
{
    extern int gamespeed, paused;

    extern void gamedisconnect(bool cleanup);
    extern void parsepacketclient(int chan, packetbuf &p);
    extern void connectattempt(const char *mapwish, int modewish, const char *password);
    extern void connectfail();
    extern void gameconnect();
    extern bool allowedittoggle();
    extern void edittoggled(bool on);
    extern void writeclientinfo(stream *f);
    extern void toserver(char *text);
    extern void changemap(const char *name);
    extern void forceedit(const char *name);
    extern bool ispaused();
    extern bool allowmouselook();
    // view
    extern void broadcastfov(int fov);
    extern int getfollowingfov();


    extern void updateworld();
    extern void initclient();
    extern void physicstrigger(physent *d, bool local, int floorlevel, int waterlevel, int material = 0);
    extern void bounced(physent *d, const vec &surface);
    extern void edittrigger(const selinfo &sel, int op, int arg1 = 0, int arg2 = 0, int arg3 = 0, const VSlot *vs = nullptr);
    extern void vartrigger(ident *id);
    extern void dynentcollide(physent *d, physent *o, const vec &dir);
    extern bool weaponcollide(physent *d, const vec &dir);
    extern const char *getclientmap();
	extern const char *getclientmode();
    extern const char *getmapinfo();
    extern void resetgamestate();
    extern void suicide(physent *d);
    extern void newmap(int size);
    extern void startmap(const char *name);
    extern void preload();
    extern float abovegameplayhud(int w, int h);
    extern void gameplayhud(int w, int h);
    extern bool canjump();
    extern bool allowmove(physent *d);
    extern void doattack(bool on);
    extern dynent *iterdynents(int i);
    extern int numdynents();
    extern void writegamedata(vector<char> &extras);
    extern void readgamedata(vector<char> &extras);
    extern int clipconsole(int w, int h);
    extern const char *defaultcrosshair(int index);
    extern int selectcrosshair(vec &color);
    extern void lighteffects(dynent *d, vec &color, vec &dir);
    extern void setupcamera();
    extern bool detachcamera();
    extern bool collidecamera();
    extern void adddynlights();
    extern void particletrack(physent *owner, vec &o, vec &d);
    extern void dynlighttrack(physent *owner, vec &o, vec &hud);
    extern bool needminimap();
}

