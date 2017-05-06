#pragma once
#include "inexor/fpsgame/game.hpp"

#define collectteambase(s) (!strcmp(s, "good") ? 1 : (!strcmp(s, "evil") ? 2 : 0))
#define collectbaseteam(i) (i==1 ? "good" : (i==2 ? "evil" : NULL))


struct collectmode_common
{
    static const int BASERADIUS = 16;
    static const int BASEHEIGHT = 16;
    static const int MAXBASES = 20;
    static const int TOKENRADIUS = 16;
    static const int TOKENLIMIT = 5;
    static const int UNOWNEDTOKENLIMIT = 15;
    static const int TOKENDIST = 16;
    static const int SCORELIMIT = 50;
    static const int RESPAWNSECS = 5;
    static const int EXPIRETOKENTIME = 10000;
    static const int STEALTOKENTIME = 5000;



    struct base
    {
        int id, team;
        vec o;
        int laststeal;

        // client only
        vec tokenpos;
        string info;
        entitylight light;

        base() { reset(); }

        void reset()
        {
            o = vec(0, 0, 0);
            team = 0;
            laststeal = 0;
        }
    };

    struct token
    {
        int id, team, droptime;
        vec o;
        int yaw, dropper;
        entitylight light;

        token() { reset(); }

        void reset()
        {
            o = vec(0, 0, 0);
            team = 0;
            dropper = -1;
            droptime = 0;
        }
    };

    vector<base> bases;
    int scores[2];
    vector<token> tokens;
    int nexttoken; // server only

    void resetbases()
    {
        bases.shrink(0);
        tokens.shrink(0);
        loopk(2) scores[k] = 0;
        tokens.shrink(0);
        nexttoken = 0;
    }

    bool addbase(int i, const vec &o, int team)
    {
        if(i<0 || i>=MAXBASES) return false;
        while(bases.length()<=i) bases.add();
        base &b = bases[i];
        b.reset();
        b.id = i;
        b.team = team;
        b.o = o;
        return true;
    }

    token *findtoken(int id)
    {
        loopv(tokens) if(tokens[i].id == id) return &tokens[i];
        return NULL;
    }

    token &droptoken(const vec &o, int team, int droptime)
    {
        token &t = tokens.add();
        t.o = o;
        t.team = team;
        t.droptime = droptime;
        return t;
    }

    bool removetoken(int id)
    {
        loopv(tokens) if(tokens[i].id == id)
        {
            tokens.removeunordered(i);
            return true;
        }
        return false;
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
        return totalscore(collectteambase(team));
    }

    void getteamscores(vector<teamscore> &tscores)
    {
        loopk(2) if(scores[k]) tscores.add(teamscore(collectbaseteam(k+1), scores[k]));
    }

    bool insidebase(const base &b, const vec &o)
    {
        float dx = (b.o.x-o.x), dy = (b.o.y-o.y), dz = (b.o.z-o.z);
        return dx*dx + dy*dy <= BASERADIUS*BASERADIUS && fabs(dz) <= BASEHEIGHT;
    }
};
