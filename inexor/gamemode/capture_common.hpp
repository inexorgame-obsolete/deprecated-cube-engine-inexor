#pragma once
#include "inexor/fpsgame/game.hpp"

#include <algorithm>

struct capturemode_common
{
    static const int CAPTURERADIUS = 64;
    static const int CAPTUREHEIGHT = 24;
    static const int OCCUPYBONUS = 1;
    static const int OCCUPYPOINTS = 1;
    static const int OCCUPYENEMYLIMIT = 28;
    static const int OCCUPYNEUTRALLIMIT = 14;
    static const int SCORESECS = 10;
    static const int AMMOSECS = 15;
    static const int REGENSECS = 1;
    static const int REGENHEALTH = 10;
    static const int REGENARMOUR = 10;
    static const int REGENAMMO = 20;
    static const int MAXAMMO = 5;
    static const int REPAMMODIST = 32;
    static const int RESPAWNSECS = 5;
    static const int MAXBASES = 100;

    struct baseinfo
    {
        vec o;
        string owner, enemy;
        vec ammopos;
        string name, info;
        entitylight light;

        int ammogroup, ammotype, ammo, owners, enemies, converted, capturetime;

        baseinfo() { reset(); }

        bool valid() const { return ammotype>0 && ammotype<=I_CARTRIDGES-I_SHELLS+1; }

        void noenemy()
        {
            enemy[0] = '\0';
            enemies = 0;
            converted = 0;
        }

        void reset()
        {
            noenemy();
            owner[0] = '\0';
            capturetime = -1;
            ammogroup = 0;
            ammotype = 0;
            ammo = 0;
            owners = 0;
        }

        bool enter(const char *team)
        {
            if(!strcmp(owner, team))
            {
                owners++;
                return false;
            }
            if(!enemies)
            {
                if(strcmp(enemy, team))
                {
                    converted = 0;
                    copystring(enemy, team);
                }
                enemies++;
                return true;
            } else if(strcmp(enemy, team)) return false;
            else enemies++;
            return false;
        }

        bool steal(const char *team)
        {
            return !enemies && strcmp(owner, team);
        }

        bool leave(const char *team)
        {
            if(!strcmp(owner, team) && owners > 0)
            {
                owners--;
                return false;
            }
            if(strcmp(enemy, team) || enemies <= 0) return false;
            enemies--;
            return !enemies;
        }

        int occupy(const char *team, int units)
        {
            if(strcmp(enemy, team)) return -1;
            converted += units;
            if(units<0)
            {
                if(converted<=0) noenemy();
                return -1;
            } else if(converted<(owner[0] ? int(OCCUPYENEMYLIMIT) : int(OCCUPYNEUTRALLIMIT))) return -1;
            if(owner[0]) { owner[0] = '\0'; converted = 0; copystring(enemy, team); return 0; } else { copystring(owner, team); ammo = 0; capturetime = 0; owners = enemies; noenemy(); return 1; }
        }

        bool addammo(int i)
        {
            if(ammo>=MAXAMMO) return false;
            ammo = std::min(ammo+i, int(MAXAMMO));
            return true;
        }

        bool takeammo(const char *team)
        {
            if(strcmp(owner, team) || ammo<=0) return false;
            ammo--;
            return true;
        }
    };

    vector<baseinfo> bases;

    struct score
    {
        string team;
        int total;
    };

    vector<score> scores;

    int captures = 0;

    void resetbases()
    {
        bases.shrink(0);
        scores.shrink(0);
        captures = 0;
    }

    bool hidefrags() { return true; }

    int getteamscore(const char *team)
    {
        loopv(scores)
        {
            score &cs = scores[i];
            if(!strcmp(cs.team, team)) return cs.total;
        }
        return 0;
    }

    void getteamscores(vector<teamscore> &teamscores)
    {
        loopv(scores) teamscores.add(teamscore(scores[i].team, scores[i].total));
    }

    score &findscore(const char *team)
    {
        loopv(scores)
        {
            score &cs = scores[i];
            if(!strcmp(cs.team, team)) return cs;
        }
        score &cs = scores.add();
        copystring(cs.team, team);
        cs.total = 0;
        return cs;
    }

    void addbase(int ammotype, const vec &o)
    {
        if(bases.length() >= MAXBASES) return;
        baseinfo &b = bases.add();
        b.ammogroup = min(ammotype, 0);
        b.ammotype = ammotype > 0 ? ammotype : rnd(I_GRENADES-I_SHELLS+1)+1;
        b.o = o;

        if(b.ammogroup)
        {
            loopi(bases.length()-1) if(b.ammogroup == bases[i].ammogroup)
            {
                b.ammotype = bases[i].ammotype;
                return;
            }
            int uses[I_GRENADES-I_SHELLS+1];
            memset(uses, 0, sizeof(uses));
            loopi(bases.length()-1) if(bases[i].ammogroup)
            {
                loopj(i) if(bases[j].ammogroup == bases[i].ammogroup) goto nextbase;
                uses[bases[i].ammotype-1]++;
            nextbase:;
            }
            int mintype = 0;
            loopi(I_GRENADES-I_SHELLS+1) if(uses[i] < uses[mintype]) mintype = i;
            int numavail = 0, avail[I_GRENADES-I_SHELLS+1];
            loopi(I_GRENADES-I_SHELLS+1) if(uses[i] == uses[mintype]) avail[numavail++] = i+1;
            b.ammotype = avail[rnd(numavail)];
        }
    }

    void initbase(int i, int ammotype, const char *owner, const char *enemy, int converted, int ammo)
    {
        if(!bases.inrange(i)) return;
        baseinfo &b = bases[i];
        b.ammotype = ammotype;
        copystring(b.owner, owner);
        copystring(b.enemy, enemy);
        b.converted = converted;
        b.ammo = ammo;
    }

    bool hasbases(const char *team)
    {
        loopv(bases)
        {
            baseinfo &b = bases[i];
            if(b.owner[0] && !strcmp(b.owner, team)) return true;
        }
        return false;
    }

    float disttoenemy(baseinfo &b)
    {
        float dist = 1e10f;
        loopv(bases)
        {
            baseinfo &e = bases[i];
            if(e.owner[0] && strcmp(b.owner, e.owner))
                dist = min(dist, b.o.dist(e.o));
        }
        return dist;
    }

    bool insidebase(const baseinfo &b, const vec &o)
    {
        float dx = (b.o.x-o.x), dy = (b.o.y-o.y), dz = (b.o.z-o.z);
        return dx*dx + dy*dy <= CAPTURERADIUS*CAPTURERADIUS && fabs(dz) <= CAPTUREHEIGHT;
    }

};
