#pragma once
#include <algorithm>                                   // for max

#include "inexor/client/gamemode/gamemode_client.hpp"  // for clientmode
#include "inexor/fpsgame/fpsent.hpp"                   // for fpsent
#include "inexor/gamemode/collect_common.hpp"          // for collectmode_co...
#include "inexor/network/legacy/buffer_types.hpp"      // for ucharbuf, pack...
#include "inexor/physics/physics.hpp"                  // for findplayerspawn
#include "inexor/shared/cube_vector.hpp"               // for vector
#include "inexor/shared/geom.hpp"                      // for vec
#include "inexor/shared/tools.hpp"                     // for max
#include "inexor/util/legacy_time.hpp"                 // for lastmillis

namespace ai {
struct aistate;
struct interest;
}  // namespace ai

namespace game {

struct collectclientmode : clientmode, collectmode_common
{
    static const int TOKENHEIGHT = 5;

    token &droptoken(int id, const vec &o, int team, int droptime);

    void preload() override;

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, float size = 0.05f);

    void drawbaseblip(fpsent *d, float x, float y, float s, int i);

    int clipconsole(int w, int h) override
    {
        return (h*(1 + 1 + 10))/(4*10);
    }

    void drawhud(fpsent *d, int w, int h) override;

    void rendergame() override;

    void setup() override;

    void senditems(packetbuf &p) override;

    vec movetoken(const vec &o, int yaw);

    void parsetokens(ucharbuf &p, bool commit);

    void baseexplosion(int i, int team, const vec &loc);

    void baseeffect(int i, int team, const vec &from, const vec &to, bool showfrom = true, bool showto = true);

    void expiretoken(int id);

    void taketoken(fpsent *d, int id, int total);

    token *droptoken(fpsent *d, int id, const vec &o, int team, int yaw, int n);

    void stealtoken(fpsent *d, int id, const vec &o, int team, int yaw, int n, int basenum, int enemyteam, int score);

    void deposittokens(fpsent *d, int basenum, int deposited, int team, int score, int flags);

    void checkitems(fpsent *d) override;

    int respawnwait(fpsent *d) override
    {
        return max(0, RESPAWNSECS-(lastmillis-d->lastpain)/1000);
    }

    void pickspawn(fpsent *d) override
    {
        findplayerspawn(d, -1, collectteambase(d->team));
    }

    bool aicheck(fpsent *d, ai::aistate &b) override;

    void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests) override;

    bool aipursue(fpsent *d, ai::aistate &b) override;

    bool parse_network_message(int type, ucharbuf &p) override;
};

} // ns game
