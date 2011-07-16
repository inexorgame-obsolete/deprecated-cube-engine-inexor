#ifdef SERVMODE

struct bombservmode : servmode
#else
static int BNC_BOMB = 1;
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

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, bool flagblip, int size_factor)
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

        // show other players on minimap
        loopv(players) {
            fpsent *p = players[i];
            if(p == player1 || p->state!=CS_ALIVE) continue;
            settexture("packages/hud/blip_red.png", 3);
            drawblip(d, x, y, s, p->o, true, 2);
        }

        // show fired bombs on minimap
        loopv(bouncers) {
        	bouncer *p = bouncers[i];
        	if(p->bouncetype != BNC_BOMB) continue;
            settexture("packages/hud/blip_blue.png", 3);
            drawblip(d, x, y, s, p->o, false, p->owner->bombradius);
        }

        // bomb radius icon
        if(d->state == CS_ALIVE)
        {
            int x = HICON_X + 3*HICON_STEP + (d->quadmillis ? HICON_SIZE + HICON_SPACE : 0);
            drawicon(HICON_BOMBRADIUS, x, HICON_Y, HICON_SIZE);
            glPushMatrix();
            glScalef(2, 2, 1);
            draw_textf("%d", (x + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, d->bombradius);
            glPopMatrix();
        }
        else {
            glPushMatrix();
            glScalef(2, 2, 1);
            bool flash = d==player1 && lastspawnattempt>=d->lastpain && lastmillis < lastspawnattempt+100;
            draw_textf("%s%s", (x+s/2)/2-64, (y+s/2)/2-48, flash ? "\f3" : "", "Game");
            draw_textf("%s%s", (x+s/2)/2-48, (y+s/2)/2-8, flash ? "\f3" : "", "over");
            glPopMatrix();
        }

    }

    void renderhiddenplayers() {
        loopv(players)
        {
        	fpsent *p = players[i];
        	if(p == player1 || p->state!=CS_ALIVE) continue;
            float yaw, pitch;
            vectoyawpitch(vec(p->o).sub(camera1->o), yaw, pitch);
            float angle = yaw + 180;
            int flags = MDL_GHOST | MDL_CULL_VFC | MDL_CULL_OCCLUDED;

        	playermodelinfo model = getplayermodelinfo(p);
            const char *modelname = model.redteam;
            /* switch(testteam ? testteam-1 : team) // TODO: teammode
            {
                case 1: modelname = mdl.blueteam; break;
                case 2: modelname = mdl.redteam; break;
            } */
        	rendermodel(NULL, modelname, ANIM_ALL|ANIM_MAPMODEL|ANIM_LOOP, p->feetpos(), yaw, pitch, flags, p, NULL, /* p->lastaction+ */ lastmillis/10.0f, 0, 0.3f);
/*        	rendermodel(NULL, modelname, ANIM_MAPMODEL|ANIM_LOOP,
                    p->pos, angle, 0,
                    MDL_GHOST | MDL_CULL_VFC | (f.droptime || f.owner ? MDL_LIGHT : 0),
                    NULL, NULL, 0, 0, 0.5f + 0.5f*(2*fabs(fmod(lastmillis/1000.0f, 1.0f) - 0.5f)));
*/
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

	void died(clientinfo *target, clientinfo *actor) {
		conoutf("%s died bombs:%i bombradius:%i", target->name, target->state.ammo[GUN_BOMB], target->state.bombradius);

	}

#endif

};

#ifndef SERVMODE
extern bombclientmode bombmode;
#endif
