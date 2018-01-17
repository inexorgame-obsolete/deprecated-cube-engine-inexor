#pragma once

#include "inexor/network/SharedVar.hpp"   // for SharedVar
#include "inexor/shared/cube_types.hpp"   // for string
#include "inexor/shared/cube_vector.hpp"  // for vector

struct dynent;
struct fpsent;
struct physent;
struct vec;

namespace game
{
    // fps
    extern int nextmode;
    extern string clientmap;
    extern bool intermission;
    extern int maptime, maprealtime, maplimit;
    extern fpsent *player1;
    extern vector<fpsent *> players, clients;
    extern int lastspawnattempt;
    extern int lasthit;
    extern int respawnent;
    extern int following;
    extern SharedVar<int> smoothmove, smoothdist;

    extern bool clientoption(const char *arg);
    extern fpsent *getclient(int cn);
    extern fpsent *newclient(int cn);
    extern const char *colorname(fpsent *d, const char *name = nullptr, const char *prefix = "", const char *alt = nullptr);
    extern const char *teamcolorname(fpsent *d, const char *alt = "you");
    extern const char *teamcolor(const char *name, bool sameteam, const char *alt = nullptr);
    extern const char *teamcolor(const char *name, const char *team, const char *alt = nullptr);
    extern fpsent *pointatplayer();
    extern fpsent *hudplayer();
    extern fpsent *followingplayer();
    extern void stopfollowing();
    extern void clientdisconnected(int cn, bool notify = true);
    extern void clearclients(bool notify = true);
    extern void startgame();
    extern void spawnplayer(fpsent *);
    extern void deathstate(fpsent *d, bool restore = false);
    extern void damaged(int damage, fpsent *d, fpsent *actor, bool local = true);
    extern void killed(fpsent *d, fpsent *actor);
    extern void timeupdate(int timeremain);
    extern void msgsound(int n, physent *d = nullptr);
    extern void drawicon(int icon, float x, float y, float sz = 120);

    extern int getfollowingfov();
    extern void updateworld();
    extern void initclient();
    extern void physicstrigger(physent *d, bool local, int floorlevel, int waterlevel, int material = 0);
    extern void dynentcollide(physent *d, physent *o, const vec &dir);
    extern const char *getclientmap();
    extern const char *getclientmode();
    extern void resetgamestate();
    extern void suicide(physent *d);
    extern void startmap(const char *name);
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
    extern bool needminimap();
}
