#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/engine/sound.hpp"
#include "inexor/network/legacy/buffer_types.hpp"

#define ctfteamflag(s) (!strcmp(s, "good") ? 1 : (!strcmp(s, "evil") ? 2 : 0))
#define ctfflagteam(i) (i==1 ? "good" : (i==2 ? "evil" : NULL))

struct flag
{
    int id, version, spawnindex;
    vec droploc, spawnloc;
    int team, droptime, owntime;

    int dropcount, dropper;

    /// time when the flagrun was initiated
    int runstart;

    fpsent *owner; // TODO this is the only hard dependency to client specific code in the gamemode code!
    int owner_id;

    float dropangle, spawnangle;
    entitylight light;
    vec interploc;
    float interpangle;
    int interptime;
    int vistime, invistime; // one is used by the server, the other one by the client..

    flag() : id(-1) { reset(); }

    void reset()
    {
        version = 0;
        spawnindex = -1;
        droploc = spawnloc = vec(0, 0, 0);
        team = 0;
        droptime = owntime = 0;

        dropcount = 0;
        owner_id = dropper = -1;
        invistime = owntime = runstart = 0;
        //if(id >= 0) loopv(players) players[i]->flagpickup &= ~(1<<id);
        owner = NULL;
        dropangle = spawnangle = 0;
        interploc = vec(0, 0, 0);
        interpangle = 0;
        interptime = 0;
        vistime = -1000;
    }

    vec pos() const
    {
        if(owner) return vec(owner->o).sub(owner->eyeheight);
        if(droptime) return droploc;
        return spawnloc;
    }

};

struct ctfmode
{
    static const int BASERADIUS = 64;
    static const int BASEHEIGHT = 24;
    static const int MAXFLAGS = 20;
    static const int FLAGRADIUS = 16;
    static const int FLAGLIMIT = 10;
    static const int MAXHOLDSPAWNS = 100;
    static const int HOLDSECS = 20;
    static const int HOLDFLAGS = 1;
    static const int RESPAWNSECS = 5;



    struct holdspawn
    {
        vec o;
        entitylight light;
    };

    vector<holdspawn> holdspawns;
    vector<flag> flags;
    int scores[2];

    void resetflags()
    {
        holdspawns.shrink(0);
        flags.shrink(0);
        loopk(2) scores[k] = 0;
    }

    bool addflag(int i, const vec &o, int team)
    {
        if(i<0 || i>=MAXFLAGS) return false;
        while(flags.length()<=i) flags.add();
        flag &f = flags[i];
        f.id = i;
        f.reset();
        f.team = team;
        f.spawnloc = o;
        return true;
    }

    bool addholdspawn(const vec &o)
    {
        if(holdspawns.length() >= MAXHOLDSPAWNS) return false;
        holdspawn &h = holdspawns.add();
        h.o = o;
        return true;
    }

    int totalscore(int team)
    {
        return team >= 1 && team <= 2 ? scores[team-1] : 0;
    }

    int setscore(int team, int score)
    {
        if(team >= 1 && team <= 2) return scores[team-1] = score;
        return 0;
    }

    int addscore(int team, int score)
    {
        if(team >= 1 && team <= 2) return scores[team-1] += score;
        return 0;
    }

    bool hidefrags() { return true; }

    int getteamscore(const char *team)
    {
        return totalscore(ctfteamflag(team));
    }

    void getteamscores(vector<teamscore> &tscores)
    {
        loopk(2) if(scores[k]) tscores.add(teamscore(ctfflagteam(k+1), scores[k]));
    }

    bool insidebase(const flag &f, const vec &o)
    {
        float dx = (f.spawnloc.x-o.x), dy = (f.spawnloc.y-o.y), dz = (f.spawnloc.z-o.z);
        return dx*dx + dy*dy <= BASERADIUS*BASERADIUS && fabs(dz) <= BASEHEIGHT;
    }
};

