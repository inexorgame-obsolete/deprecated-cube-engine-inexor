#pragma once
#include "inexor/fpsgame/fpsent.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/network/SharedVar.hpp"

namespace game {
struct playermodelinfo
{
    const char *ffa, *blueteam, *redteam, *hudguns,
            *vwep, *quad, *armour[3],
            *ffaicon, *blueicon, *redicon;
    bool ragdoll;
};

extern SharedVar<int> playermodel, teamskins, testteam;

extern void saveragdoll(fpsent *d);
extern void clearragdolls();
extern void moveragdolls();
extern void changedplayermodel();
extern const playermodelinfo &getplayermodelinfo(fpsent *d);
extern int chooserandomplayermodel(int seed);
extern void swayhudgun(int curtime);
extern vec hudgunorigin(int gun, const vec &from, const vec &to, fpsent *d);

extern void rendergame(bool mainpass);
extern void renderavatar();
extern void renderplayerpreview(int model, int team, int weap);
}