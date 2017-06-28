#include "inexor/client/gamemode/bomb_client.hpp"
#include "inexor/filesystem/mediadirs.hpp"

namespace game {

VARP(showbombs, 0, 1, 1);
VARP(showbombradius, 0, 1, 1);
VARP(showbombdelay, 0, 1, 1);
VARP(showminimapobstacles, 0, 1, 1);

void bombclientmode::drawhud(fpsent *d, int w, int h)
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
    }
    else if(player1->state != CS_ALIVE && !game::intermission)
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

void bombclientmode::senditems(packetbuf &p)
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

void bombclientmode::renderscoreboard(g3d_gui &g, scoregroup &sg, int fgcolor, int bgcolor)
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

}
