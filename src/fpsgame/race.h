// bomb.h: client and server state for bomb gamemode
#ifndef PARSEMESSAGES

#ifdef SERVMODE

extern void sendspawn(clientinfo *ci);
extern void pausegame(bool val);

struct raceservmode : servmode
#else

VARP(showracetime, 0, 1, 1);

struct raceclientmode : clientmode
#endif
{

#ifndef SERVMODE

    void setup() {
    }

    void drawhud(fpsent *d, int w, int h) {
    }

    void rendergame() {
    }

    void renderscoreboard(g3d_gui &g, game::scoregroup &sg, int fgcolor, int bgcolor) {
        if (showracetime) {
            g.pushlist();
            g.strut(7);
            g.text("racetime", fgcolor);
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
                    int secs = d->racetime/1000, mins = secs/60;
                    secs %= 60;
                    g.textf("%d:%02d", 0xFFFFDD, NULL, mins, secs);
                }
            }
            g.poplist();
        }
    }

    void killed(fpsent *d, fpsent *actor) {
        // d->state.racetime = 0;
    }

    void respawned(fpsent *d) {
        d->racetime = lastmillis;
        conoutf("racetime: %d lastmillis: %d", d->racetime, lastmillis);
    }

    void gameconnect(fpsent *d) {
    }

    void pickspawn(fpsent *d) {
        findplayerspawn(d);
    }

    bool hidefrags() {
        return true;
    }

#else

    void setup() {
//        loopv(clients) {
//            timecounter = totalmillis;
//        }
    }

    void spawned(fpsent *d) {
        d->racetime = lastmillis;
        conoutf("racetime: %d lastmillis: %d", d->racetime, lastmillis);
    }

    void intermission() {
        loopv(clients) {
            clientinfo *ci = clients[i];
            conoutf("I racetime old: %d", ci->state.racetime);
            ci->state.racetime = max(lastmillis - ci->state.racetime, 0);
            conoutf("I racetime: %d lastmillis: %d", ci->state.racetime, lastmillis);
        }
    }


    void update() {
//        loopv(clients) {
//            clients[i]->state.racetime = lastmillis;
//        }
    }

    void leavegame(clientinfo *ci, bool disconnecting) {
    }

    bool canspawn(clientinfo *ci, bool connecting) {
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
    }

#endif

};

#ifndef SERVMODE
extern raceclientmode racemode;
#endif

#elif SERVMODE

case N_FINISH:
{
  conoutf("N_FINISH SERVMODE");
  if(smode==&racemode) {
      forceintermission();
  }
  break;
}


#endif
