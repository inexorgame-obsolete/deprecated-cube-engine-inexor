#pragma once
#include "inexor/fpsgame/teaminfo.hpp"
#include "inexor/fpsgame/fpsent.hpp"
#include "inexor/fpsgame/entities.hpp"

namespace game {

extern SharedVar<float> minimapalpha;
extern float calcradarscale();
extern void drawminimap(fpsent *d, float x, float y, float s);
extern void setradartex();
extern void drawradar(float x, float y, float s);
extern void drawteammates(fpsent *d, float x, float y, float s);
extern void setbliptex(int team, const char *type = "");

struct clientmode
{
    virtual ~clientmode() {}

    virtual void preload() {}
    virtual int clipconsole(int w, int h) { return 0; }
    virtual void drawhud(fpsent *d, int w, int h) {}
    virtual bool isinvisible(fpsent *d) { return false; }
    virtual void rendergame() {}
    virtual void respawned(fpsent *d) {}
    virtual void setup() {}
    virtual void checkitems(fpsent *d) {}
    virtual int respawnwait(fpsent *d) { return 0; }
    virtual void pickspawn(fpsent *d) { findplayerspawn(d); }
    virtual void senditems(packetbuf &p) {}
    virtual void addplayer(fpsent *d) {}
    virtual void removeplayer(fpsent *d) {}
    virtual void gameover() {}
    virtual bool hidefrags() { return false; }
    virtual int getteamscore(const char *team) { return 0; }
    virtual void getteamscores(vector<teamscore> &scores) {}
    virtual void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests) {}
    virtual bool aicheck(fpsent *d, ai::aistate &b) { return false; }
    virtual bool aidefend(fpsent *d, ai::aistate &b) { return false; }
    virtual bool aipursue(fpsent *d, ai::aistate &b) { return false; }
    virtual void killed(fpsent *d, fpsent *actor) {}
    virtual void gameconnect(fpsent *d) {}
    virtual void renderscoreboard(g3d_gui &g, scoregroup &sg, int fgcolor, int bgcolor) {}
    /// Parse game mode specific network messages.
    /// @return true if message got handled.
    virtual bool parse_network_message(int type, ucharbuf &p) = 0;
};

extern clientmode *cmode;
extern void setclientmode();

} // ns game
