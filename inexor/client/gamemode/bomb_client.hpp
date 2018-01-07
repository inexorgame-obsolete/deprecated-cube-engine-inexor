#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/bomb_common.hpp"
#include "inexor/client/gamemode/gamemode_client.hpp"

namespace game {

struct bombclientmode : clientmode, bombmode
{
    int myspawnloc;

    void setup() override
    {
        myspawnloc = -1;
    }

    void senditems(packetbuf &p) override;

    void drawicon(int icon, float x, float y, float sz);

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, float size_factor);

    void drawhud(fpsent *d, int w, int h) override;

    void renderplayersposindicator();

    void rendergame() override
    {
        renderplayersposindicator();
    }

    void renderscoreboard(g3d_gui &g, scoregroup &sg, int fgcolor, int bgcolor) override;

    void killed(fpsent *d, fpsent *actor) override;

    void gameconnect(fpsent *d) override
    {
        d->deaths++;
        d->state = CS_SPECTATOR;
    }

    void pickspawn(fpsent *d) override;

    bool parse_network_message(int type, ucharbuf &p) override;
};

extern bombclientmode bombmode;


} // ns game
