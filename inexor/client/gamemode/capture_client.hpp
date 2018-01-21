#pragma once
#include <algorithm>                                   // for max

#include "inexor/client/gamemode/gamemode_client.hpp"  // for clientmode
#include "inexor/fpsgame/ai.hpp"                       // for ::AI_S_DEFEND
#include "inexor/fpsgame/fpsent.hpp"                   // for fpsent
#include "inexor/gamemode/capture_common.hpp"          // for capturemode_co...
#include "inexor/gamemode/gamemode.hpp"                // for m_regencapture
#include "inexor/network/legacy/buffer_types.hpp"      // for packetbuf (ptr...
#include "inexor/physics/physics.hpp"                  // for findplayerspawn
#include "inexor/shared/cube_vector.hpp"               // for vector
#include "inexor/shared/tools.hpp"                     // for max
#include "inexor/util/legacy_time.hpp"                 // for lastmillis

namespace game {

struct captureclientmode : clientmode, capturemode_common
{
    static const int AMMOHEIGHT = 5;

    void respawned(fpsent *d) override
    {
    }

    void replenishammo();

    void receiveammo(fpsent *d, int type);

    void checkitems(fpsent *d) override;

    void rendertether(fpsent *d);

    void preload() override;

    void rendergame() override;

    void drawblips(fpsent *d, float blipsize, int fw, int fh, int type, bool skipenemy = false);

    int respawnwait(fpsent *d) override
    {
        if(m_regencapture) return -1;
        return max(0, RESPAWNSECS-(lastmillis-d->lastpain)/1000);
    }

    int clipconsole(int w, int h) override
    {
        return (h*(1 + 1 + 10))/(4*10);
    }

    void drawhud(fpsent *d, int w, int h) override;

    void setup() override;

    void senditems(packetbuf &p) override;

    void updatebase(int i, const char *owner, const char *enemy, int converted, int ammo);

    void setscore(int base, const char *team, int total);

    int closesttoenemy(const char *team, bool noattacked = false, bool farthest = false);

    int pickteamspawn(const char *team);

    void pickspawn(fpsent *d) override
    {
        findplayerspawn(d, pickteamspawn(d->team));
    }

    bool aicheck(fpsent *d, ai::aistate &b) override
    {
        return false;
    }

    void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests) override;

    bool aidefend(fpsent *d, ai::aistate &b) override;

    bool aipursue(fpsent *d, ai::aistate &b) override
    {
        b.type = ai::AI_S_DEFEND;
        return aidefend(d, b);
    }

    bool parse_network_message(int type, ucharbuf &p) override;
};

extern captureclientmode capturemode;

} // ns game
