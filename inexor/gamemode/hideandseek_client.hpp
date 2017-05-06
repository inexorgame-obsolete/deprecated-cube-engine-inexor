#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/hideandseek_common.hpp"
#include "inexor/gamemode/gamemode_client.hpp"


#define ishider(ci) (strcmp(ci->team, TEAM_HIDE) == 0 && ci->state != CS_SPECTATOR ? true : false)
#define isseeker(ci) (strcmp(ci->team, TEAM_SEEK) == 0 && ci->state != CS_SPECTATOR ? true : false)

namespace game {

struct hideandseekclientmode : clientmode, hideandseekmode
{
    static constexpr int STARTINVISIBLESECS = 30;

    void setup() {}

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, float size_factor)
    {
        float scale = calcradarscale();
        vec dir = d->o;
        dir.sub(pos).div(scale);
        float size = 0.03f * size_factor,
            xoffset = -size,
            yoffset = -size,
            dist = dir.magnitude2(), maxdist = 1 - 0.05f - 0.05f;
        if(dist >= maxdist) dir.mul(maxdist/dist);
        dir.rotate_around_z(-camera1->yaw*RAD);
        drawradar(x + s*0.5f*(1.0f + dir.x + xoffset), y + s*0.5f*(1.0f + dir.y + yoffset), size*s);
    }

    void drawhud(fpsent *d, int w, int h)
    {
        if(!ishider(d)) return;

        // minimap
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        int s = 1800/4, x = 1800*w/h - s - s/10, y = s/10;
        glColor4f(1, 1, 1, minimapalpha);
        if(minimapalpha >= 1) glDisable(GL_BLEND);
        bindminimap();
        drawminimap(d, x, y, s);
        if(minimapalpha >= 1) glEnable(GL_BLEND);
        glColor3f(1, 1, 1);
        float margin = 0.04f, roffset = s*margin, rsize = s + 2*roffset;
        setradartex();
        drawradar(x - roffset, y - roffset, rsize);
        // show obstacles on minimap
        defformatstring(blip, "%s/blip_block.png", *radardir);
        if(showminimapobstacles) loopv(movables)
        {
            dynent *m = (dynent *)movables[i];
            if(!isobstaclealive((movable *)m)) continue;

            settexture(blip, 3);
            drawblip(d, x, y, s, m->o, 1.0f);
        }
        // show other players on minimap
        loopv(players)
        {
            fpsent *o = players[i];
            if(o != d && o->state == CS_ALIVE && !ishider(o))
            {
                setbliptex(TEAM_OPPONENT);
                drawblip(d, x, y, s, o->o, 2.0f);
            }
        }
    }

    bool isinvisible(fpsent *d)
    {
        if(ishider(d) && (totalmillis-maptime < STARTINVISIBLESECS*1000 || ishider(player1))) return true;
        return false;
    }

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
