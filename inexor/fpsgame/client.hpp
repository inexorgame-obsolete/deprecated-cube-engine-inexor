#pragma once

#include "inexor/fpsgame/fpsent.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/command.hpp"
#include "inexor/network/legacy/buffer_types.hpp"
#include "inexor/io/legacy/stream.hpp"
#include "inexor/texture/slot.hpp"
#include "inexor/engine/octree.hpp"

namespace game {

extern bool connected, demoplayback;
extern string servinfo;
extern vector<uchar> messages;

extern int parseplayer(const char *arg);
extern void ignore(int cn);
extern void unignore(int cn);
extern bool isignored(int cn);
extern bool addmsg(int type, const char *fmt = nullptr, ...);
extern void switchname(const char *name, const char *tag);
extern void switchteam(const char *name);
extern void switchplayermodel(int playermodel);
extern void sendmapinfo();
extern void stopdemo();
extern void changemap(const char *name, int mode);
extern void forceintermission();
extern void c2sinfo(bool force = false);
extern void sendposition(fpsent *d, bool reliable = false);


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
extern void broadcastfov(int fov);
extern void edittrigger(const selinfo &sel, int op, int arg1 = 0, int arg2 = 0, int arg3 = 0, const VSlot *vs = nullptr);
extern void vartrigger(ident *id);
extern void newmap(int size);
}
