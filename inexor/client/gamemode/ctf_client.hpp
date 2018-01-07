#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/ctf_common.hpp"
#include "inexor/client/gamemode/gamemode_client.hpp"

namespace game {

struct ctfclientmode : clientmode, ctfmode
{
    bool addflag(int i, const vec &o, int team, int vistime = -1000);

    void ownflag(int i, fpsent *owner, int owntime);

    void returnflag(int i, int vistime = -1000);

    void preload() override;

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, bool flagblip);

    void drawblip(fpsent *d, float x, float y, float s, int i, bool flagblip);

    int clipconsole(int w, int h) override
    {
        return (h*(1 + 1 + 10))/(4*10);
    }

    void drawhud(fpsent *d, int w, int h) override;

    void removeplayer(fpsent *d) override;

    vec interpflagpos(flag &f, float &angle);

    vec interpflagpos(flag &f) { float angle; return interpflagpos(f, angle); }

    void rendergame() override;

    void setup() override;

    void senditems(packetbuf &p) override;

    void parseflags(ucharbuf &p, bool commit);

    void trydropflag();

    const char *teamcolorflag(flag &f);

    void dropflag(int i, const vec &o, float yaw, int droptime);

    void dropflag(fpsent *d, int i, int version, const vec &droploc);

    void flagexplosion(int i, int team, const vec &loc);

    void flageffect(int i, int team, const vec &from, const vec &to);

    void returnflag(fpsent *d, int i, int version);

    void spawnflag(flag &f);

    void resetflag(int i, int version, int spawnindex, int team, int score);

    void scoreflag(fpsent *d, int relay, int relayversion, int goal, int goalversion, int goalspawn, int team, int score, int dflags, int time);

    void takeflag(fpsent *d, int i, int version);

    void invisflag(int i, int invis);

    void checkitems(fpsent *d) override;

    void respawned(fpsent *d) override;

    int respawnwait(fpsent *d) override;

    bool pickholdspawn(fpsent *d);

    void pickspawn(fpsent *d) override;

    bool aihomerun(fpsent *d, ai::aistate &b);

    bool aicheck(fpsent *d, ai::aistate &b) override;

    void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests) override;

    bool aidefend(fpsent *d, ai::aistate &b) override;

    bool aipursue(fpsent *d, ai::aistate &b) override;

    bool parse_network_message(int type, ucharbuf &p) override;
};

extern ctfclientmode ctfmode;


} // ns game
