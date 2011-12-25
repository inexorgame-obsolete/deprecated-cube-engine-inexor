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


    void drawhud(fpsent *d, int w, int h) {
    }

    void rendergame() {
    }

    void renderscoreboard(g3d_gui &g, game::scoregroup &sg, int fgcolor, int bgcolor) {
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
            if (!intermission) {
                loopv(sg.players) {
                    fpsent *d = sg.players[i];
                    int secs = max(lastmillis - d->racetime, 0)/1000, mins = secs/60;
                    secs %= 60;
                    g.textf("%d:%02d", 0xFFFFDD, NULL, mins, secs);
                }
            } else {
                loopv(sg.players) {
                    fpsent *d = sg.players[i];
                    int secs = (d->racetime - maptime)/1000, mins = secs/60;
                    secs %= 60;
                    g.textf("%d:%02d", 0xFFFFDD, NULL, mins, secs);
                }
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
        d->racetime = lastmillis;
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

#define COUNTDOWNSECONDS 3

    void setup() {
      maxcheckpoint = getmaxcheckpoint();
      sequence = 0;
      countdown = COUNTDOWNSECONDS;
      timecounter = totalmillis;
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
    }

    int getmaxcheckpoint() {
      int m = 0;
      loopv(ments) {
        entity& e = ments[i];
        if(e.type == RACE_CHECKPOINT && e.attr2 > m) {
            m = e.attr2;
        }
      }
      conoutf("MAX CHECKPOINT: %d", m);
      return m;
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
        if(totalmillis - timecounter >= 10000) sendservmsg("Map load complete (grannies left behind).");
        else{
          loopv(spawnlocs){
            if(spawnlocs[i]->cn == -1) continue;
            clientinfo* ci = getinfo(spawnlocs[i]->cn);
            if(!ci || ci->state.state==CS_SPECTATOR || ci->state.aitype != AI_NONE || ci->clientmap[0] || ci->mapcrc) continue;
            return;
          }
          sendservmsg("Map load complete.");
        }
        sequence = 1;
        timecounter = totalmillis;
        return;

      case 1:
      {
        int remaining = COUNTDOWNSECONDS*1000 - (totalmillis - timecounter);
        if(remaining <= 0){
          sequence = 2;
          sendservmsg("FIGHT!");
          pausegame(false);
        }
        else if(remaining/1000 != countdown){
          defformatstring(msg)("-%d...", countdown--);
          sendservmsg(msg);
        }
        break;
      }

      case 2: break;
      }
    }

    void spawned(fpsent *d) {
        d->racetime = lastmillis;
        // d->racecheckpoint = 0;
        // conoutf("racetime: %d lastmillis: %d", d->racetime, lastmillis);
    }

    void intermission() {
        loopv(clients) {
            clientinfo *ci = clients[i];
            conoutf("I racetime old: %d", ci->state.racetime);
            ci->state.racetime = max(lastmillis - ci->state.racetime, 0);
            conoutf("I racetime: %d lastmillis: %d", ci->state.racetime, lastmillis);
            ci->state.racelaps = 0;
            ci->state.racecheckpoint = 0;
        }
    }


    void update() {
//        loopv(clients) {
//            clients[i]->state.racetime = lastmillis;
//        }
    }

    void leavegame(clientinfo *ci, bool disconnecting) {
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
      if(notgotspawnlocations) {conoutf("not got spawn locations yet"); return false; }
      int i = 0;
      for(; i < spawnlocs.length(); i++) if(spawnlocs[i]->cn == ci->clientnum) break;
      if(i == spawnlocs.length()) {conoutf("player has got no spawn location"); return false; }
    	return true;
    }

    void pushentity(int type, vec o) {
    }

    void died(clientinfo *target, clientinfo *actor) {
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam){
    	return false;
    }

    void cleanup() {
      spawnlocs.deletecontents();
      resetplayers();
    }

    void resetplayers() {
      loopv(clients) {
          clientinfo *ci = clients[i];
          ci->state.racelaps = 0;
          ci->state.racecheckpoint = 0;
          sendf(-1, 1, "ri4 ", N_RACEINFO, ci->clientnum, 0, 0);
      }
    }

#endif

};

#ifndef SERVMODE
extern raceclientmode racemode;
#endif

#elif SERVMODE

// #define RACELABS 3
case N_RACEFINISH:
{
  if(smode==&racemode && cq) {
      if (cq->state.racecheckpoint == racemode.maxcheckpoint) {
          cq->state.racecheckpoint = 0;
          cq->state.racelaps++;
          sendf(-1, 1, "ri4 ", N_RACEINFO, cq->clientnum, cq->state.racelaps, cq->state.racecheckpoint);
          if (cq->state.racelaps >= engine::racelaps) {
              forceintermission();
          }
      }
  }
  break;
}

case N_RACESTART:
{
  if(smode==&racemode && cq) {
      // conoutf("N_RACESTART SERVMODE cn:%d", cq->clientnum);
  }
  break;
}

case N_RACECHECKPOINT:
{
  int checkpoint_no = getint(p);
  if(smode==&racemode && cq) {
      // conoutf("N_RACECHECKPOINT SERVMODE cn:%d   checkpoint no:%d   old checkpoint no:%d", cq->clientnum, checkpoint_no, cq->state.racecheckpoint);
      if (checkpoint_no == cq->state.racecheckpoint+1) {
          cq->state.racecheckpoint++;
          // conoutf("SEND: new checkpoint:%d",cq->state.racecheckpoint);
          sendf(-1, 1, "ri4 ", N_RACEINFO, cq->clientnum, cq->state.racelaps, cq->state.racecheckpoint);
      }
  }

//  pickupevent *pickup = new pickupevent;
//  pickup->ent = n;
//  cq->addevent(pickup);
  break;
}

#else

case N_RACEINFO:
{
  int rcn = getint(p);
  int lap = getint(p);
  int checkpoint = getint(p);
  // conoutf("N_RACEINFO cn:%d lap:%d checkpoint:%d", rcn, lap, checkpoint);
  fpsent *r = rcn==player1->clientnum ? player1 : getclient(rcn);
  if(m_race && r) {
      r->racelaps = lap;
      r->racecheckpoint = checkpoint;
  }
  break;
}

#endif
