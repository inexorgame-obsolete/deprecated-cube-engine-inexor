#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/hideandseek_common.hpp"
#include "inexor/client/gamemode/gamemode_client.hpp"

namespace game {

extern SharedVar<int> showminimapobstacles;

struct hideandseekclientmode : clientmode, hideandseekmode
{
    static constexpr int STARTINVISIBLESECS = 30;

    void setup() {}

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, float size_factor);

    void drawhud(fpsent *d, int w, int h);

    bool isinvisible(fpsent *d);

    void rendergame()
    {
    }

    void renderscoreboard(g3d_gui &g, scoregroup &sg, int fgcolor, int bgcolor)
    {
        /*
        if (showhideandseekrole) {
        g.pushlist();
        g.strut(4);
        g.text("rank", fgcolor);
        loopv(sg.players) {
        fpsent *d = sg.players[i];
        g.textf("%s", 0xFFFFDD, NULL, "");
        }
        g.poplist();
        }
        */
    }

    void killed(fpsent *d, fpsent *actor)
    {
    }

    void respawned(fpsent *d)
    {
    }

    void pickspawn(fpsent *d)
    {
        findplayerspawn(player1); // TODO: Is this correct??
    }

    bool hidefrags()
    {
        return true;
    }

    bool parse_network_message(int type, ucharbuf &p) override
    {
        switch(type)
        {
            /*
            case N_RACEINFO:
            {
              int rcn = getint(p);
              return true;
            }
            */
            default: break;
        }
        return false;
    }
};

extern hideandseekclientmode hideandseekmode;


} // ns game
