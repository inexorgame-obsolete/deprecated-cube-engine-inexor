#pragma once

#include "inexor/fpsgame/fpsent.hpp"
#include "inexor/shared/cube_vector.hpp"

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

}
