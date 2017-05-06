#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/bomb_common.hpp"
#include "inexor/gamemode/gamemode_client.hpp"

namespace game {
VARP(showbombs, 0, 1, 1);
VARP(showbombradius, 0, 1, 1);
VARP(showbombdelay, 0, 1, 1);
VARP(showminimapobstacles, 0, 1, 1);

struct bombclientmode : clientmode, bombmode
{
    int myspawnloc;

    void setup()
    {
        myspawnloc = -1;
    }

    void senditems(packetbuf &p)
    {
        vector<spawnloc> v;
        loopv(entities::ents)
        {
            extentity& e = *entities::ents[i];
            if(e.type != PLAYERSTART) continue;
            if(m_teammode ? e.attr2 < 1 || e.attr2 > 2 : e.attr2) continue;
            spawnloc temp;
            temp.o = e.o;
            temp.team = e.attr2;
            temp.index = i;
            v.add(temp);
        }
        putint(p, N_SPAWNLOC);
        putint(p, v.length());
        loopv(v)
        {
            spawnloc &sploc = v[i];
            loopk(3) putint(p, int(sploc.o[k]*DMF));
            putint(p, sploc.team);
            putint(p, sploc.index);
        }
    }

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

    void drawhud(fpsent *d, int w, int h)
    {
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
            if(o != d && o->state == CS_ALIVE)
            {
                setbliptex(!m_teammode || !isteam(o->team, player1->team) ? TEAM_OPPONENT : TEAM_OWN);
                drawblip(d, x, y, s, o->o, 2.0f);
            }
        }

        // show fired bombs on minimap
        formatstring(blip, "%s/blip_bomb.png", *radardir);
        loopv(bouncers)
        {
            bouncer *p = bouncers[i];
            if(p->bouncetype != BNC_BOMB) continue;
            settexture(blip, 3);
            drawblip(d, x, y, s, p->o, (p->owner->bombradius * 1.5f + p->owner->bombradius * 1.5f * sin((SDL_GetTicks() / (5.5f-p->owner->bombdelay)) / 75.0f))/1.5f);
        }

        if(d->state == CS_ALIVE && !game::intermission)
        {
            // bomb radius and bomb delay icons
            int x1 = HICON_X + 3*HICON_STEP + (d->quadmillis ? HICON_SIZE + HICON_SPACE : 0);
            int x2 = HICON_X + 4*HICON_STEP + (d->quadmillis ? HICON_SIZE + HICON_SPACE : 0);
            drawicon(HICON_BOMBRADIUS, x1, HICON_Y, HICON_SIZE);
            drawicon(HICON_BOMBDELAY, x2, HICON_Y, HICON_SIZE);
            glPushMatrix();
            glScalef(2, 2, 1);
            draw_textf("%d", (x1 + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, d->bombradius);
            draw_textf("%1.1fs", (x2 + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, 5.5f-(d->bombdelay*0.5f));
            glPopMatrix();
        }

        if(player1->state == CS_ALIVE  && game::intermission)
        {
            int pw, ph, tw, th;
            text_bounds("  ", pw, ph);
            text_bounds(m_teammode ? "YOUR TEAM WINS" : "YOU WIN", tw, th);
            th = max(th, ph);
            draw_text(m_teammode ? "YOUR TEAM WINS" : "YOU WIN", w*1800/h - tw - pw, 1650 - th);
        } else if(player1->state != CS_ALIVE && !game::intermission)
        {
            int pw, ph, tw, th, fw, fh;
            text_bounds("  ", pw, ph);
            if(player1->deaths > 0)
            {
                text_bounds("YOU ARE DEAD", tw, th);
                th = max(th, ph);
                draw_text("YOU ARE DEAD", w*1800/h - tw - pw, 1420 - th);
            }
            text_bounds("PLEASE WAIT UNTIL ROUND ENDS", fw, fh);
            draw_text("PLEASE WAIT UNTIL ROUND ENDS", w*1800/h - fw - pw, 1460 - fh);
        }
    }

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

    void renderscoreboard(g3d_gui &g, scoregroup &sg, int fgcolor, int bgcolor)
    {
        if(showbombs)
        {
            g.pushlist();
            g.strut(7);
            g.text("bombs", fgcolor);
            loopv(sg.players)
            {
                fpsent *d = sg.players[i];
                g.textf("%d", 0xFFFFDD, NULL, d->ammo[GUN_BOMB]);
            }
            g.poplist();
        }
        if(showbombdelay)
        {
            g.pushlist();
            g.strut(7);
            g.text("time", fgcolor);
            loopv(sg.players)
            {
                fpsent *d = sg.players[i];
                g.textf("%1.1fs", 0xFFFFDD, NULL, 5.5f-(d->bombdelay*0.5f));
            }
            g.poplist();
        }
        if(showbombradius)
        {
            g.pushlist();
            g.strut(7);
            g.text("radius", fgcolor);
            loopv(sg.players)
            {
                fpsent *d = sg.players[i];
                g.textf("%d", 0xFFFFDD, NULL, d->bombradius);
            }
            g.poplist();
        }
    }

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
