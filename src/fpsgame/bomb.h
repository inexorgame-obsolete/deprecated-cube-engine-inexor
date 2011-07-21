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

        // show barrels on minimap
        loopv(movables) {
        	dynent *m = (dynent *) movables[i];
            // conoutf("m->state=%i (%i) m->type=%i (%i)", m->state, CS_ALIVE, m->type, BARREL);
            // if(m->state!=CS_ALIVE || m->type!=BARREL) continue;
        	if(!isbarrelalive((movable *) m)) continue;
            settexture("packages/hud/block_yellow_t.png", 3);
            drawblip(d, x, y, s, m->o, 1);
        }

        // show other players on minimap
        loopv(players) {
            fpsent *p = players[i];
            if(p == player1 || p->state!=CS_ALIVE) continue;
            settexture("packages/hud/blip_red.png", 3);
            drawblip(d, x, y, s, p->o, 2);
        }

        // show fired bombs on minimap
        loopv(bouncers) {
        	bouncer *p = bouncers[i];
        	if(p->bouncetype != BNC_BOMB) continue;
            settexture("packages/hud/blip_blue.png", 3);
            drawblip(d, x, y, s, p->o, p->owner->bombradius);
        }

        if(d->state == CS_ALIVE && !game::intermission) {
            // bomb radius icon
            int x = HICON_X + 3*HICON_STEP + (d->quadmillis ? HICON_SIZE + HICON_SPACE : 0);
            drawicon(HICON_BOMBRADIUS, x, HICON_Y, HICON_SIZE);
            glPushMatrix();
            glScalef(2, 2, 1);
            draw_textf("%d", (x + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, d->bombradius);
            glPopMatrix();
        } else if(d->state == CS_ALIVE) {
            glPushMatrix();
            glScalef(2, 2, 1);
            bool flash = d==player1 && lastspawnattempt>=d->lastpain && lastmillis < lastspawnattempt+100;
            draw_textf("%s%s", (x+s/2)/2-56, (y+s/2)/2-48, flash ? "\f3" : "", "You");
            draw_textf("%s%s", (x+s/2)/2-48, (y+s/2)/2-8, flash ? "\f3" : "", "win");
            glPopMatrix();
        } else if(d->state != CS_ALIVE && !game::intermission) {
            int pw, ph, tw, th, fw, fh;
            text_bounds("  ", pw, ph);
            text_bounds("YOU ARE DEAD", tw, th);
            th = max(th, ph);
            fpsent *f = followingplayer();
            text_bounds(f ? colorname(f) : " ", fw, fh);
            fh = max(fh, ph);
            draw_text("YOU ARE DEAD", w*1800/h - tw - pw, 1650 - th - fh);
            if(f) draw_text(colorname(f), w*1800/h - fw - pw, 1650 - fh);
        }
    }

    void renderhiddenplayers() {
        loopv(players)
        {
        	fpsent *p = players[i];
        	if(p == player1 || p->state!=CS_ALIVE) continue;
            float yaw, pitch;
            vectoyawpitch(vec(p->o).sub(camera1->o), yaw, pitch);
        	// playermodelinfo model = getplayermodelinfo(p);
            const char *modelname = "quadrings"; // "flags/neutral"; // model.redteam;
            /* switch(testteam ? testteam-1 : team) // TODO: teammode
            {
                case 1: modelname = mdl.blueteam; break;
                case 2: modelname = mdl.redteam; break;
            } */
            float angle = 360*lastmillis/1000.0f;
            float alpha = 0.3f + 0.5f*(2*fabs(fmod(lastmillis/1000.0f, 1.0f) - 0.5f));
            entitylight light;
            rendermodel(/* NULL */ &light, modelname, ANIM_MAPMODEL|ANIM_LOOP, // ANIM_ALL|
                    p->feetpos(), angle, pitch,
                    MDL_GHOST | MDL_CULL_VFC | MDL_LIGHT | MDL_CULL_OCCLUDED,
                    NULL /* p */, NULL, /* p->lastaction+ */ /* lastmillis/10.0f */ 0, 0, alpha);
        }
    }

    void rendergame()
    {
    	renderhiddenplayers();
    }


#else

	bool canspawn(clientinfo *ci, bool connecting = false) {
    	if(!m_lms) return true;
    	else if(ci->state.deaths==0) return true; // ci->state.aitype!=AI_NONE &&
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

	void died(clientinfo *target, clientinfo *actor) {
        for(int i=0; i<target->state.ammo[GUN_BOMB]/2; i++) pushentity(I_BOMBS, target->state.o);
        for(int i=0; i<target->state.bombradius/2; i++) pushentity(I_BOMBRADIUS, target->state.o);
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
