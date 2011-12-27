// bomb.h: client and server state for bomb gamemode
#ifndef PARSEMESSAGES

#ifdef SERVMODE

extern void sendspawn(clientinfo *ci);
extern void pausegame(bool val);

struct raceservmode : servmode
#else

VARP(showracetime, 0, 1, 1);
VARP(showracecheckpoints, 0, 1, 1);
VARP(showracelaps, 0, 1, 1);
VARP(showracerank, 0, 1, 1);

struct raceclientmode : clientmode
#endif
{

  struct spawnloc{
    vec o;
    int team, index;
#ifdef SERVMODE
    int cn;
    spawnloc(const vec& o_, int team_, int index_): o(o_), team(team_), index(index_), cn(-1) {}
#endif
  };

#ifdef SERVMODE
    struct raceinfo {
        int cn;
        int timefinished;
        int gotcheckpoints;
        int timepenalties;
        raceinfo(int cn_, int timefinished_, int gotcheckpoints_, int timepenalties_): cn(cn_), timefinished(timefinished_), gotcheckpoints(gotcheckpoints_), timepenalties(timepenalties_) {}
    };
#endif

#ifndef SERVMODE

    int myspawnloc;

    void setup() {
        myspawnloc = -1;
        resetplayers();
    }

    void resetplayers() {
      loopv(players) {
          fpsent *d = players[i];
          d->racelaps = 0;
          d->racecheckpoint = 0;
          d->racetime = 0;
          d->racerank = -1;
      }
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

    void drawhud(fpsent *d, int w, int h) {
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
      if(showminimapobstacles) loopv(movables)
      {
          dynent *m = (dynent *) movables[i];
          if(!isobstaclealive((movable *) m)) continue;
          settexture("packages/hud/block_yellow_t.png", 3);
          drawblip(d, x, y, s, m->o, 1.0f);
      }

      // show other players on minimap
      loopv(players)
      {
          fpsent *p = players[i];
          if(p == player1 || p->state!=CS_ALIVE) continue;
          if(!m_teammode || strcmp(p->team, player1->team) != 0) settexture("packages/hud/blip_red.png", 3);
          else settexture("packages/hud/blip_blue.png", 3);
          drawblip(d, x, y, s, p->o, 2.0f);
      }

    }

    void rendergame() {
    }

    void renderscoreboard(g3d_gui &g, game::scoregroup &sg, int fgcolor, int bgcolor) {
        if (showracerank) {
            g.pushlist();
            g.strut(7);
            g.text("rank", fgcolor);
            loopv(sg.players) {
                fpsent *d = sg.players[i];
                if(d->racerank == -1) {
                    g.textf("%s", 0xFFFFDD, NULL, "start");
                } else {
                    g.textf("%02d", 0xFFFFDD, NULL, d->racerank);
                }
            }
            g.poplist();
        }
        if (showracelaps) {
            g.pushlist();
            g.strut(7);
            g.text("laps", fgcolor);
            loopv(sg.players) {
                fpsent *d = sg.players[i];
                g.textf("%02d", 0xFFFFDD, NULL, d->racelaps);
            }
            g.poplist();
        }
        if (showracecheckpoints) {
            g.pushlist();
            g.strut(7);
            g.text("check", fgcolor);
            loopv(sg.players) {
                fpsent *d = sg.players[i];
                g.textf("%d", 0xFFFFDD, NULL, d->racecheckpoint);
            }
            g.poplist();
        }
        if (showracetime) {
            g.pushlist();
            g.strut(7);
            g.text("time", fgcolor);
            loopv(sg.players) {
                fpsent *d = sg.players[i];
                int secs = max(d->racetime, 0)/1000, mins = secs/60;
                secs %= 60;
                g.textf("%d:%02d", 0xFFFFDD, NULL, mins, secs);
            }
            g.poplist();
        }
    }

    void killed(fpsent *d, fpsent *actor) {
        // conoutf("killed");
        // d->state.racetime = 0;
    }

    void respawned(fpsent *d) {
        // conoutf("respawned");
        // d->racetime = lastmillis;
        // conoutf("racetime: %d lastmillis: %d", d->racetime, lastmillis);
    }

    void pickspawn(fpsent *d) {
      if(d->racelaps > 0 || d->racecheckpoint > 0) {
          if(d->racecheckpoint == 0) pickspawnbyenttype(d, PLAYERSTART);
          else if (d->racecheckpoint > 0) pickspawnbyenttype(d, RACE_CHECKPOINT);
          return;
      }
      if(!entities::ents.inrange(myspawnloc)) return;
      extentity& e = *entities::ents[myspawnloc];
      d->o = e.o;
      d->yaw = e.attr1;
      d->pitch = 0;
      d->roll = 0;
      entinmap(d);
    }

    void pickspawnbyenttype(fpsent *d, int ent_type) {
      loopv(entities::ents){
          extentity& e = *entities::ents[i];
          if(e.type == ent_type && e.attr2 == d->racecheckpoint) {
              // conoutf("pick RACE_START or RACE_CHECKPOINT as spawn point");
              d->o = e.o;
              d->yaw = e.attr1;
              d->pitch = 0;
              d->roll = 0;
              entinmap(d);
          }
      }
    }

    bool hidefrags() {
        return true;
    }

#else

    bool notgotspawnlocations;
    vector<spawnloc*> spawnlocs;
    int sequence, timecounter, countdown;
    int maxcheckpoint;
    int timestarted;
    int lastupdatecheck;
    vector<raceinfo*> raceinfos;
    // int timefinished[];
    // int gotcheckpoints[];
    // int timepenalties[];

#define COUNTDOWNSECONDS 3

    void setup() {
        maxcheckpoint = getmaxcheckpoint();
        sequence = 0;
        countdown = COUNTDOWNSECONDS;
        timecounter = totalmillis;
        lastupdatecheck = totalmillis;
        pausegame(true);
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
        raceinfos.deletecontents();
        initplayers();
    }

    int getmaxcheckpoint() {
        int m = 0;
        loopv(ments) {
            entity& e = ments[i];
            if(e.type == RACE_CHECKPOINT && e.attr2 > m) {
                m = e.attr2;
            }
        }
        // conoutf("MAX CHECKPOINT: %d", m);
        return m;
    }

    bool parsespawnloc(ucharbuf &p, bool commit) {
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
            // sendservmsg("Map load complete (grannies left behind).");
            sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_BOTTOM, "Map load complete (grannies left behind)");
        } else {
          loopv(spawnlocs){
            if(spawnlocs[i]->cn == -1) continue;
            clientinfo* ci = getinfo(spawnlocs[i]->cn);
            if(!ci || ci->state.state==CS_SPECTATOR || ci->state.aitype != AI_NONE || ci->clientmap[0] || ci->mapcrc) continue;
            return;
          }
          sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_BOTTOM, "Map load complete");
          // sendservmsg("Map load complete.");
        }
        sequence = 1;
        timecounter = totalmillis;
        return;

      case 1:
      {
        int remaining = COUNTDOWNSECONDS*1000 - (totalmillis - timecounter);
        if(remaining <= 0){
          sequence = 2;
          sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 2000, E_ZOOM_IN, "S T A R T");
          // sendservmsg("FIGHT!");
          timestarted = totalmillis;
          pausegame(false);
        }
        else if(remaining/1000 != countdown){
          // defformatstring(msg)("-%d...", countdown--);
          // sendservmsg(msg);
          defformatstring(msg)("- %d -", countdown--);
          sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 1500, E_ZOOM_IN, msg);
        }
        break;
      }

      case 2: break;
      }
    }

    void spawned(fpsent *d) {
    }

    void intermission() {
    }

    bool checkfinished() {
        if(interm) return false;
        int allplayersfinished = true;
        loopv(raceinfos) if (raceinfos[i]->timefinished == -1) allplayersfinished = false;
        return allplayersfinished;
    }

    void update() {
        if (totalmillis > lastupdatecheck + 1000) {
            lastupdatecheck = totalmillis;
            if(checkfinished()) forceintermission();
            loopv(clients) {
                clientinfo *ci = clients[i];
                ci->state.racerank = getrank(ci->clientnum);
                sendf(-1, 1, "ri6", N_RACEINFO, ci->clientnum, ci->state.racelaps, ci->state.racecheckpoint, getracetime(ci), ci->state.racerank);
            }
        }
    }

    int getrank(int cn) {
        int rank = 1;
        int timefinished = -1;
        int gotcheckpoints = 0;
        int timepenalties = 0;
        loopv(raceinfos) if(raceinfos[i]->cn == cn) {
            timefinished = raceinfos[i]->timefinished;
            gotcheckpoints = raceinfos[i]->gotcheckpoints;
            timepenalties = raceinfos[i]->timepenalties;
        }
        loopv(raceinfos) if(raceinfos[i]->cn != cn) {
            // conoutf("cn:%d gotcheckpoints:%d", raceinfos[i]->cn, raceinfos[i]->gotcheckpoints);
            if(raceinfos[i]->timefinished > timefinished || raceinfos[i]->gotcheckpoints > gotcheckpoints || (raceinfos[i]->timefinished == timefinished && raceinfos[i]->gotcheckpoints == gotcheckpoints && raceinfos[i]->timepenalties > timepenalties)) rank++;
        }
        return rank;
    }

    int getracetime(clientinfo *ci) {
        loopv(raceinfos) if(raceinfos[i]->cn == ci->clientnum){
            return totalmillis - ci->state.racetime + (raceinfos[i]->timepenalties * 10000);
        }
        return totalmillis - ci->state.racetime;
    }

    void sendfinishannounce(clientinfo *ci) {
        int rank = ci->state.racerank;
        defformatstring(msg)("%d%s", rank, (rank==1 ? "st" : (rank==2 ? "nd" : (rank==3 ? "rd": "th"))));
        sendf(ci->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
    }

    void leavegame(clientinfo *ci, bool disconnecting) {
        loopv(raceinfos) if(raceinfos[i]->cn == ci->clientnum){
            raceinfos[i]->cn = -1;
            raceinfos[i]->timefinished = -2;
        }
        if(!disconnecting) return;
        loopv(spawnlocs) if(spawnlocs[i]->cn == ci->clientnum){
            spawnlocs[i]->cn = -1;
            break;
        }
    }

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

    bool canspawn(clientinfo *ci, bool connecting) {
        loopv(raceinfos) if(raceinfos[i]->cn == ci->clientnum){
            if(raceinfos[i]->timefinished > 0) return false;
        }
        if(notgotspawnlocations) {conoutf("not got spawn locations yet"); return false; }
        int i = 0;
        for(; i < spawnlocs.length(); i++) if(spawnlocs[i]->cn == ci->clientnum) break;
        if(i == spawnlocs.length()) {conoutf("player has got no spawn location"); return false; }
    	  return true;
    }

    void pushentity(int type, vec o) {
    }

    void died(clientinfo *target, clientinfo *actor) {
        loopv(raceinfos) if(raceinfos[i]->cn == target->clientnum){
            raceinfos[i]->timepenalties++;
        }
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam){
    	  return false;
    }

    void cleanup() {
        spawnlocs.deletecontents();
        raceinfos.deletecontents();
    }

    void initplayers() {
        loopv(clients) {
            clientinfo *ci = clients[i];
            ci->state.racelaps = 0;
            ci->state.racecheckpoint = 0;
            ci->state.racerank = -1;
            raceinfos.add(new raceinfo(ci->clientnum, (ci->state.state==CS_SPECTATOR ? -2 : -1), 0, 0));
            sendf(-1, 1, "ri6", N_RACEINFO, ci->clientnum, 0, 0, 0, -1);
        }
    }

#endif

};

#ifndef SERVMODE
extern raceclientmode racemode;
#endif

#elif SERVMODE

#define RACELAPS 3
case N_RACEFINISH:
{
  if(smode==&racemode && cq) {
      loopv(racemode.raceinfos) if(racemode.raceinfos[i]->cn == cq->clientnum && cq->state.racecheckpoint == racemode.maxcheckpoint) {
          cq->state.racecheckpoint = 0;
          cq->state.racelaps++;
          cq->state.racerank = racemode.getrank(cq->clientnum);
          sendf(-1, 1, "ri6", N_RACEINFO, cq->clientnum, cq->state.racelaps, cq->state.racecheckpoint, racemode.getracetime(cq), cq->state.racerank);
          // conoutf("racelabs:%d RACELAPS:%d timefinished:%d", cq->state.racelaps, RACELAPS, racemode.raceinfos[i]->timefinished);
          if (cq->state.racelaps >= RACELAPS) {
              racemode.raceinfos[i]->timefinished = totalmillis;
              racemode.sendfinishannounce(cq);
              cq->state.state = CS_DEAD;
              sendf(-1, 1, "ri4", N_DIED, cq->clientnum, cq->clientnum, cq->state.frags);
          } else {
              defformatstring(msg)("%d %s REMAINING", RACELAPS - cq->state.racelaps, RACELAPS - cq->state.racelaps != 1 ? "LAPS" : "LAP");
              sendf(cq->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 1500, E_ZOOM_IN, msg);
          }
      }
  }
  break;
}

case N_RACESTART:
{
  if(smode==&racemode && cq && cq->state.racelaps == 0 && cq->state.racecheckpoint == 0) {
      loopv(racemode.raceinfos) if(racemode.raceinfos[i]->cn == cq->clientnum && racemode.raceinfos[i]->gotcheckpoints == 0) {
          racemode.raceinfos[i]->gotcheckpoints = 1;
          cq->state.racetime = totalmillis;
          cq->state.racerank = racemode.getrank(cq->clientnum);
          sendf(-1, 1, "ri6", N_RACEINFO, cq->clientnum, cq->state.racelaps, cq->state.racecheckpoint, 0, cq->state.racerank);
      }
  }
  break;
}

case N_RACECHECKPOINT:
{
  int checkpoint_no = getint(p);
  if(smode==&racemode && cq && checkpoint_no == cq->state.racecheckpoint+1) {
      loopv(racemode.raceinfos) if(racemode.raceinfos[i]->cn == cq->clientnum) racemode.raceinfos[i]->gotcheckpoints++;
      cq->state.racecheckpoint++;
      cq->state.racerank = racemode.getrank(cq->clientnum);
      sendf(-1, 1, "ri6", N_RACEINFO, cq->clientnum, cq->state.racelaps, cq->state.racecheckpoint, racemode.getracetime(cq), cq->state.racerank);
      defformatstring(msg)("CHECKPOINT %d", cq->state.racecheckpoint);
      sendf(cq->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 400, E_ZOOM_OUT, msg);
  }
  break;
}

#else

case N_RACEINFO:
{
  int rcn = getint(p);
  int lap = getint(p);
  int checkpoint = getint(p);
  int time = getint(p);
  int rank = getint(p);
  // conoutf("N_RACEINFO cn:%d lap:%d checkpoint:%d", rcn, lap, checkpoint, time);
  fpsent *r = rcn==player1->clientnum ? player1 : getclient(rcn);
  if(m_race && r) {
      r->racelaps = lap;
      r->racecheckpoint = checkpoint;
      r->racetime = time;
      r->racerank = rank;
  }
  break;
}

#endif
