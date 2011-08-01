// bomb.h: client and server state for bomb gamemode
#ifndef PARSEMESSAGES

#ifdef SERVMODE
struct bombservmode : servmode
#else
struct bombclientmode : clientmode
#endif
{

#ifndef SERVMODE
    void drawicon(int icon, float x, float y, float sz)
    {
        int bicon = icon - HICON_BOMBRADIUS;
        settexture("packages/hud/bomb_items.png");
        glBegin(GL_TRIANGLE_STRIP);
        float tsz = 0.25f, tx = tsz*(bicon%4), ty = tsz*(bicon/4);
        glTexCoord2f(tx,     ty);     glVertex2f(x,    y);
        glTexCoord2f(tx+tsz, ty);     glVertex2f(x+sz, y);
        glTexCoord2f(tx,     ty+tsz); glVertex2f(x,    y+sz);
        glTexCoord2f(tx+tsz, ty+tsz); glVertex2f(x+sz, y+sz);
        glEnd();
    }

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, int size_factor)
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
        settexture("packages/hud/radar.png", 3);
        drawradar(x - roffset, y - roffset, rsize);

        // show obstacles on minimap
        loopv(movables)
        {
            dynent *m = (dynent *) movables[i];
            // conoutf("m->state=%i (%i) m->type=%i (%i)", m->state, CS_ALIVE, m->type, BARREL);
            // if(m->state!=CS_ALIVE || m->type!=BARREL) continue;
            if(!isobstaclealive((movable *) m)) continue;
            settexture("packages/hud/block_yellow_t.png", 3);
            drawblip(d, x, y, s, m->o, 1);
        }

        // show other players on minimap
        loopv(players)
        {
            fpsent *p = players[i];
            if(p == player1 || p->state!=CS_ALIVE) continue;
            if(!m_teammode || strcmp(p->team, player1->team) != 0) settexture("packages/hud/blip_red.png", 3);
            else settexture("packages/hud/blip_blue.png", 3);
            drawblip(d, x, y, s, p->o, 2);
        }

        // show fired bombs on minimap
        loopv(bouncers)
        {
            bouncer *p = bouncers[i];
            if(p->bouncetype != BNC_BOMB) continue;
            settexture("packages/hud/blip_bomb_orange.png", 3);
            drawblip(d, x, y, s, p->o, p->owner->bombradius * 2); // TODO: sin function to make it swing // TODO: geschwindigkeit der schwingung abhängig von bombdelay
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
            draw_textf("%f", (x2 + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, 5.5f-(d->bombdelay*0.5f));
            glPopMatrix();
        }

        if(player1->state == CS_ALIVE  && game::intermission)
        {
            int pw, ph, tw, th;
            text_bounds("  ", pw, ph);
            text_bounds("YOU WIN", tw, th);
            th = max(th, ph);
            draw_text("YOU WIN", w*1800/h - tw - pw, 1650 - th);
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

    void renderplayersposindicator() {
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

    void killed(fpsent *d, fpsent *actor)
    {
        d->state = CS_SPECTATOR;
        if(d!=player1) return;
        conoutf("killed!");
        following = actor->clientnum;
        player1->yaw = actor->yaw;
        player1->pitch = actor->pitch;
        player1->o = actor->o;
        player1->resetinterp();
    }

    void gameconnect(fpsent *d)
    {
        conoutf("gameconnect");
        d->deaths++;
        d->state = CS_SPECTATOR;
    }

    void pickspawn(fpsent *d) {
        const vector<extentity *> &ents = entities::getents();
        vector<extentity *> playerstarts;
        vector<fpsent *> pl;
        loopv(ents)
        {
            extentity &e = *ents[i];
            if(e.type==ET_PLAYERSTART && e.attr2 <= 0) playerstarts.add(&e);
        }
	
		// mapc says: This function fails if there are no playerstarts...
		if (playerstarts.length() <= 0) {
			findplayerspawn(d);
			return;
		}
	
        // conoutf("got %i playerstarts", playerstarts.length());
        int found=0;
        int next=0;
        while(found<players.length())
        {
            loopv(players)
            {
                fpsent *p = players[i];
                if(p->clientnum == next)
                {
                    pl.add(p);
                    found++;
                }
            }
            next++;
        }
        // conoutf("got %i players", pl.length());
        /*
        if(m_teammode)
        {

        }
        else
        {
        */
            loopv(pl)
            {
                fpsent *p = pl[i];
                // conoutf("placing player %i (cn=%i) on playerstart %i", i, pl[i]->clientnum, i%playerstarts.length());
                if(p!=d) continue;
                extentity &e = *playerstarts[i%playerstarts.length()];
                d->o = e.o;
                d->yaw = e.attr1;
                d->pitch = 0;
                d->roll = 0;
                entinmap(d);
                break;
            }
        /* } */
    }

#else

    bool gamerunning() {
      for (int cn = 0; cn < clients.length(); cn++)
          if(clients[cn]->state.deaths > 0) return true;
      return false;
    }

    bool canspawn(clientinfo *ci, bool connecting = false) {
    	if(!m_lms) return true;
    	else if(gamerunning()) {conoutf("game is running"); return false; }
    	else if(ci->state.deaths==0) {conoutf("player has no deaths"); return true; } // ci->state.aitype!=AI_NONE &&
    	else return false;
    }

    void pushentity(int type, vec o) {
    	entity &e = ments.add();
    	e.o = o;
    	e.type = type;
        server_entity se = { NOTUSED, 0, false };
        while(sents.length()<=ments.length()+1) sents.add(se);
        int id = sents.length()-1;
        sents[id].type = ments[id].type;
        sents[id].spawned = true;
        conoutf("ments.length=%i sents.length=%i", ments.length(), sents.length());
        ivec io(o.mul(DMF));
        conoutf("SEND N_ITEMPUSH: id=%i type=%i pos x=%i y=%i z=%i", id, type, io.x-120+rnd(240), io.y-120+rnd(240), io.z + rnd(2)*120);
        sendf(-1, 1, "ri6", N_ITEMPUSH, id, type, io.x-120+rnd(240), io.y-120+rnd(240), io.z + rnd(2)*180);
    }

    void died(clientinfo *target, clientinfo *actor)
    {
        for(int i=0; i<target->state.ammo[GUN_BOMB]/2; i++) pushentity(I_BOMBS, target->state.o);
        for(int i=0; i<target->state.bombradius/2; i++) pushentity(I_BOMBRADIUS, target->state.o);
        for(int i=0; i<target->state.bombdelay/3; i++) pushentity(I_BOMBDELAY, target->state.o);
    }

#endif

};

#ifndef SERVMODE
extern bombclientmode bombmode;
#endif

#elif SERVMODE
/*
case N_KILLMOVABLE:
{
    int id = getint(p);
    // if(m_bomb) bombmode.kill(flag, version, spawnindex, team, score);
    break;
}
*/

#endif
