#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/sound/sound.hpp"
#include "inexor/gamemode/collect_common.hpp"
#include "inexor/client/gamemode/gamemode_client.hpp"

namespace game {

struct collectclientmode : clientmode, collectmode_common
{
    static const int TOKENHEIGHT = 5;

    token &droptoken(int id, const vec &o, int team, int droptime);

    void preload();

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, float size = 0.05f);

    void drawbaseblip(fpsent *d, float x, float y, float s, int i);

    int clipconsole(int w, int h)
    {
        return (h*(1 + 1 + 10))/(4*10);
    }

    void drawhud(fpsent *d, int w, int h);

    void rendergame();

    void setup();

    void senditems(packetbuf &p);

    vec movetoken(const vec &o, int yaw);

    void parsetokens(ucharbuf &p, bool commit);

    void baseexplosion(int i, int team, const vec &loc);

    void baseeffect(int i, int team, const vec &from, const vec &to, bool showfrom = true, bool showto = true);

    void expiretoken(int id);

    void taketoken(fpsent *d, int id, int total);

    token *droptoken(fpsent *d, int id, const vec &o, int team, int yaw, int n);

    void stealtoken(fpsent *d, int id, const vec &o, int team, int yaw, int n, int basenum, int enemyteam, int score);

    void deposittokens(fpsent *d, int basenum, int deposited, int team, int score, int flags);

    void checkitems(fpsent *d);

    int respawnwait(fpsent *d)
    {
        return max(0, RESPAWNSECS-(lastmillis-d->lastpain)/1000);
    }

    void pickspawn(fpsent *d)
    {
        findplayerspawn(d, -1, collectteambase(d->team));
    }

    bool aicheck(fpsent *d, ai::aistate &b) override;

    void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests) override;

    bool aipursue(fpsent *d, ai::aistate &b) override;

    bool parse_network_message(int type, ucharbuf &p) override;
};

} // ns game
