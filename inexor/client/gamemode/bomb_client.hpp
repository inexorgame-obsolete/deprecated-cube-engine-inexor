#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/bomb_common.hpp"
#include "inexor/client/gamemode/gamemode_client.hpp"

namespace game {

struct bombclientmode : clientmode, bombmode
{
    int myspawnloc;

    void setup()
    {
        myspawnloc = -1;
    }

    void senditems(packetbuf &p);

    void drawicon(int icon, float x, float y, float sz) //todo merge with other items
    {
        int bicon = icon - HICON_BOMBRADIUS;
        bind_bomb_items_texture();
        glBegin(GL_TRIANGLE_STRIP);
        float tsz = 0.25f, tx = tsz*(bicon%4), ty = tsz*(bicon/4);
        glTexCoord2f(tx, ty);     glVertex2f(x, y);
        glTexCoord2f(tx+tsz, ty);     glVertex2f(x+sz, y);
        glTexCoord2f(tx, ty+tsz); glVertex2f(x, y+sz);
        glTexCoord2f(tx+tsz, ty+tsz); glVertex2f(x+sz, y+sz);
        glEnd();
    }

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

    void drawhud(fpsent *d, int w, int h);

    void renderplayersposindicator()
    {
        loopv(players)
        {
            fpsent *p = players[i];
            if(p == player1 || p->state!=CS_ALIVE) continue;
            float yaw, pitch;
            vectoyawpitch(vec(p->o).sub(camera1->o), yaw, pitch);
            const char *modelname = m_teammode ? (strcmp(p->team, player1->team) == 0 ? "bomb/posindicator/blue" : "bomb/posindicator/red") : "bomb/posindicator/green";
            float angle = 360*lastmillis/1000.0f;
            float alpha = 0.3f + 0.5f*(2*fabs(fmod(lastmillis/1000.0f, 1.0f) - 0.5f));
            entitylight light;
            rendermodel(&light, modelname, ANIM_MAPMODEL|ANIM_LOOP,
                        p->feetpos(), angle, pitch,
                        MDL_GHOST | MDL_CULL_VFC | MDL_LIGHT | MDL_CULL_OCCLUDED,
                        NULL, NULL, 0, 0, alpha);
        }
    }

    void rendergame()
    {
        renderplayersposindicator();
    }

    void renderscoreboard(g3d_gui &g, scoregroup &sg, int fgcolor, int bgcolor);

    void killed(fpsent *d, fpsent *actor)
    {
        d->state = CS_SPECTATOR;
        if(d!=player1) return;
        following = actor->clientnum;
        player1->yaw = actor->yaw;
        player1->pitch = actor->pitch;
        player1->o = actor->o;
        player1->resetinterp();
    }

    void gameconnect(fpsent *d)
    {
        d->deaths++;
        d->state = CS_SPECTATOR;
    }

    void pickspawn(fpsent *d)
    {
        if(!entities::ents.inrange(myspawnloc)) return;
        extentity& e = *entities::ents[myspawnloc];
        d->o = e.o;
        d->yaw = e.attr1;
        d->pitch = 0;
        d->roll = 0;
        entinmap(d);
    }

    bool parse_network_message(int type, ucharbuf &p) override
    {
        switch(type)
        {
            case N_SPAWNLOC:
            {
                myspawnloc = getint(p);
                return true;
            }
        }
        return false;
    }
};

extern bombclientmode bombmode;


} // ns game
