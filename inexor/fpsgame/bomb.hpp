// bomb.h: client and server state for bomb gamemode
#ifndef PARSEMESSAGES

//#include <signal.h>

#ifdef SERVMODE


extern void sendspawn(clientinfo *ci);

struct bombservmode : servmode
#else

VARP(showbombs, 0, 1, 1);
VARP(showbombradius, 0, 1, 1);
VARP(showbombdelay, 0, 1, 1);
VARP(showminimapobstacles, 0, 1, 1);

struct bombclientmode : clientmode
#endif
{

    struct spawnloc {
    	vec o;
    	int team, index;
#ifdef SERVMODE
    	int cn;
    	spawnloc(const vec& o_, int team_, int index_): o(o_), team(team_), index(index_), cn(-1) {}
#endif
    };

#ifndef SERVMODE

	int myspawnloc;

	void setup(){
		myspawnloc = -1;
	}

	void senditems(packetbuf &p){
		vector<spawnloc> v;
		loopv(entities::ents){
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
		loopv(v){
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
        glTexCoord2f(tx,     ty);     glVertex2f(x,    y);
        glTexCoord2f(tx+tsz, ty);     glVertex2f(x+sz, y);
        glTexCoord2f(tx,     ty+tsz); glVertex2f(x,    y+sz);
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
            dynent *m = (dynent *) movables[i];
            if(!isobstaclealive((movable *) m)) continue;
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

    void renderscoreboard(g3d_gui &g, game::scoregroup &sg, int fgcolor, int bgcolor)
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

    void pickspawn(fpsent *d){
    	if(!entities::ents.inrange(myspawnloc)) return;
    	extentity& e = *entities::ents[myspawnloc];
    	d->o = e.o;
    	d->yaw = e.attr1;
    	d->pitch = 0;
    	d->roll = 0;
    	entinmap(d);
    }

#else

    bool notgotspawnlocations;
    vector<spawnloc*> spawnlocs;
    int sequence, timecounter, countdown;

#define COUNTDOWNSECONDS 3

    void setup(){
    	sequence = 0;
    	countdown = COUNTDOWNSECONDS;
    	timecounter = totalmillis;
    	forcepaused(true);
    	notgotspawnlocations = true;
    	spawnlocs.deletecontents();
    	if(!notgotitems){
    		loopv(ments){
    			if(ments[i].type != PLAYERSTART) continue;
    			entity& e = ments[i];
    			spawnlocs.add(new spawnloc(e.o, e.attr2, i));
    		}
    		notgotspawnlocations = false;
    		sendspawnlocs();
    	}
    }

    bool parsespawnloc(ucharbuf &p, bool commit)
    {
    	int numsploc = getint(p);
    	loopi(numsploc){
    		vec o;
    		loopk(3) o[k] = max(getint(p)/DMF, 0.0f);
    		int team = getint(p), index = getint(p);
    		if(p.overread()) break;
        	if(m_teammode ? team < 1 || team > 2 : team) return false;
    		if(commit && notgotspawnlocations) spawnlocs.add(new spawnloc(o, team, index));
    	}
    	if(commit && notgotspawnlocations){
    		notgotspawnlocations = false;
    		sendspawnlocs(true);
    	}
    	return true;
    }

    void updatelimbo(){
    	if(notgotspawnlocations) return;
    	switch(sequence){
    	case 0:
    		if(totalmillis - timecounter >= 10000) {
            sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_BOTTOM, "Map load complete (grannies left behind)");
    		} else {
    			loopv(spawnlocs){
    				if(spawnlocs[i]->cn == -1) continue;
    				clientinfo* ci = getinfo(spawnlocs[i]->cn);
    				if(!ci || ci->state.state==CS_SPECTATOR || ci->state.aitype != AI_NONE || ci->clientmap[0] || ci->mapcrc) continue;
    				return;
    			}
          sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_BOTTOM, "Map load complete");
    		}
    		sequence = 1;
    		timecounter = totalmillis;
    		return;

    	case 1:
    	{
    		int remaining = COUNTDOWNSECONDS*1000 - (totalmillis - timecounter);
    		if(remaining <= 0){
    			sequence = 2;
          sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 2000, E_ZOOM_IN, "F I G H T");
    			forcepaused(false);
    		}
    		else if(remaining/1000 != countdown){
          defformatstring(msg, "- %d -", countdown--);
          sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 2000, E_ZOOM_IN, msg);
    		}
    		break;
    	}

    	case 2: break;
    	}
    }

    void leavegame(clientinfo *ci, bool disconnecting){
    	if(!disconnecting) return;
    	loopv(spawnlocs) if(spawnlocs[i]->cn == ci->clientnum){
    		spawnlocs[i]->cn = -1;
    		break;
    	}
    }

#define bombteamname(s) (!strcmp(s, "good") ? 1 : (!strcmp(s, "evil") ? 2 : 0))

    void sendspawnlocs(bool resuscitate = false){
    	vector<clientinfo*> activepl;
    	loopv(clients){
    		clientinfo* ci = clients[i];
    		if(ci->state.state == CS_SPECTATOR) continue;
    		activepl.add(ci);
    	}
    	vector<spawnloc*> pool[3];
    	loopv(spawnlocs) pool[spawnlocs[i]->team].add(spawnlocs[i]);
    	loopi(3) pool[i].shuffle();
    	for(int i = 0; i < activepl.length(); i++){
    		vector<spawnloc*>& tpool = pool[m_teammode ? bombteamname(activepl[i]->team) : 0];
    		if(tpool.length()){
    			tpool[0]->cn = activepl[i]->clientnum;
    			sendf(tpool[0]->cn, 1, "ri2", N_SPAWNLOC, tpool[0]->index);
    			if(resuscitate) sendspawn(activepl[i]);
    			tpool.removeunordered(0);
    		}
    	}
    }

    bool gamerunning() {
      for (int cn = 0; cn < clients.length(); cn++)
          if(clients[cn]->state.deaths > 0) return true;
      return false;
    }

    bool canspawn(clientinfo *ci, bool connecting) {
    	if(!m_lms) return true;
    	if(gamerunning()) { spdlog::get("global")->info("game is running"); return false; }
    	if(notgotspawnlocations) { spdlog::get("global")->info("not got spawn locations yet"); return false; }
    	int i = 0;
    	for(; i < spawnlocs.length(); i++) if(spawnlocs[i]->cn == ci->clientnum) break;
    	if(i == spawnlocs.length()) { spdlog::get("global")->info("player has got no spawn location"); return false; }
        if(ci->state.deaths==0) { spdlog::get("global")->info("player has no deaths"); return true; } // ci->state.aitype!=AI_NONE &&
    	sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1250, E_ZOOM_IN, "You cannot respawn this round");
    	return false;
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
        ivec io(o.mul(DMF));
        sendf(-1, 1, "ri6", N_ITEMPUSH, id, type, io.x-120+rnd(240), io.y-120+rnd(240), io.z + rnd(2)*180);
    }

    void died(clientinfo *target, clientinfo *actor)
    {
        int leftitems = 0;
        for(int i=0; i<target->state.ammo[GUN_BOMB]/2; i++) { pushentity(I_BOMBS, target->state.o); leftitems++; }
        for(int i=0; i<target->state.bombradius/2; i++) { pushentity(I_BOMBRADIUS, target->state.o); leftitems++; }
        for(int i=0; i<target->state.bombdelay/3; i++) { pushentity(I_BOMBDELAY, target->state.o); leftitems++; }
        if (leftitems > 0) {
            defformatstring(msg, "%s died and left %d %s!", target->name, leftitems, leftitems > 1 ? "items" : "item");
            sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1250, E_ZOOM_OUT, msg);
        } else {
            defformatstring(msg, "%s died!", target->name);
            sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1250, E_ZOOM_OUT, msg);
        }
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam){
    	return m_teammode && bombteamname(newteam) > 0;
    }

    void cleanup(){
    	spawnlocs.deletecontents();
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

case N_SPAWNLOC:
{
	if(smode==&bombmode)
		if(!bombmode.parsespawnloc(p, (ci->state.state!=CS_SPECTATOR || ci->privilege || ci->local) && !strcmp(ci->clientmap, smapname)))
			disconnect_client(sender, DISC_MSGERR);
	break;
}

#else

case N_SPAWNLOC:
{
	bombmode.myspawnloc = getint(p);
	break;
}

#endif
