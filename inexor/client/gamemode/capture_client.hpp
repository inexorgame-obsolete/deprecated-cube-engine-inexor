#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/capture_common.hpp"
#include "inexor/client/gamemode/gamemode_client.hpp"

namespace game {

struct captureclientmode : clientmode, capturemode_common
{
    static const int AMMOHEIGHT = 5;

    void respawned(fpsent *d)
    {
    }

    void replenishammo()
    {
        if(!m_capture || m_regencapture) return;
        loopv(bases)
        {
            baseinfo &b = bases[i];
            if(b.valid() && insidebase(b, player1->feetpos()) && player1->hasmaxammo(b.ammotype-1+I_SHELLS)) return;
        }
        addmsg(N_REPAMMO, "rc", player1);
    }

    void receiveammo(fpsent *d, int type)
    {
        type += I_SHELLS-1;
        if(type<I_SHELLS || type>I_CARTRIDGES) return;
        entities::repammo(d, type, d==player1);
        int icon = itemstats[type-I_SHELLS].icon;
        if(icon >= 0) particle_icon(d->abovehead(), icon%4, icon/4, PART_HUD_ICON_GREY, 2000, 0xFFFFFF, 2.0f, -8);
    }

    void checkitems(fpsent *d);

    void rendertether(fpsent *d)
    {
        int oldbase = d->lastbase;
        d->lastbase = -1;
        vec pos(d->o.x, d->o.y, d->o.z + (d->aboveeye - d->eyeheight)/2);
        if(d->state==CS_ALIVE)
        {
            loopv(bases)
            {
                baseinfo &b = bases[i];
                if(!b.valid() || !insidebase(b, d->feetpos()) || (strcmp(b.owner, d->team) && strcmp(b.enemy, d->team))) continue;
                if(d->lastbase < 0 && (lookupmaterial(d->feetpos())&MATF_CLIP) == MAT_GAMECLIP) break;
                particle_flare(pos, vec(b.ammopos.x, b.ammopos.y, b.ammopos.z - AMMOHEIGHT - 4.4f), 0, PART_LIGHTNING, strcmp(d->team, player1->team) ? 0xFF2222 : 0x2222FF, 1.0f);
                if(oldbase < 0)
                {
                    particle_fireball(pos, 4.8f, PART_EXPLOSION, 250, strcmp(d->team, player1->team) ? 0x802020 : 0x2020FF, 4.8f);
                    particle_splash(PART_SPARK, 50, 250, pos, strcmp(d->team, player1->team) ? 0x802020 : 0x2020FF, 0.24f);
                }
                d->lastbase = i;
            }
        }
        if(d->lastbase < 0 && oldbase >= 0)
        {
            particle_fireball(pos, 4.8f, PART_EXPLOSION, 250, strcmp(d->team, player1->team) ? 0x802020 : 0x2020FF, 4.8f);
            particle_splash(PART_SPARK, 50, 250, pos, strcmp(d->team, player1->team) ? 0x802020 : 0x2020FF, 0.24f);
        }
    }

    void preload()
    {
        static const char * const basemodels[3] ={"game/base/neutral", "game/base/red", "game/base/blue"};
        loopi(3) preloadmodel(basemodels[i]);
        inexor::sound::preloadsound(S_V_BASECAP);
        inexor::sound::preloadsound(S_V_BASELOST);
    }

    void rendergame();

    void drawblips(fpsent *d, float blipsize, int fw, int fh, int type, bool skipenemy = false);

    int respawnwait(fpsent *d)
    {
        if(m_regencapture) return -1;
        return max(0, RESPAWNSECS-(lastmillis-d->lastpain)/1000);
    }

    int clipconsole(int w, int h)
    {
        return (h*(1 + 1 + 10))/(4*10);
    }

    void drawhud(fpsent *d, int w, int h);

    void setup()
    {
        resetbases();
        loopv(entities::ents)
        {
            extentity *e = entities::ents[i];
            if(e->type!=BASE) continue;
            baseinfo &b = bases.add();
            b.o = e->o;
            b.ammopos = b.o;
            abovemodel(b.ammopos, "game/base/neutral");
            b.ammopos.z += AMMOHEIGHT-2;
            b.ammotype = e->attr1;
            defformatstring(alias, "base_%d", e->attr2);
            const char *name = getalias(alias);
            copystring(b.name, name);
            b.light = e->light;
        }
    }

    void senditems(packetbuf &p)
    {
        putint(p, N_BASES);
        putint(p, bases.length());
        loopv(bases)
        {
            baseinfo &b = bases[i];
            putint(p, b.ammotype);
            putint(p, int(b.o.x*DMF));
            putint(p, int(b.o.y*DMF));
            putint(p, int(b.o.z*DMF));
        }
    }

    void updatebase(int i, const char *owner, const char *enemy, int converted, int ammo);

    void setscore(int base, const char *team, int total)
    {
        findscore(team).total = total;
        if(total>=10000) spdlog::get("gameplay")->info("{0} captured all bases", teamcolor(team, team));
        else if(bases.inrange(base))
        {
            baseinfo &b = bases[base];
            if(!strcmp(b.owner, team))
            {
                defformatstring(msg, "%d", total);
                vec above(b.ammopos);
                above.z += AMMOHEIGHT+1.0f;
                particle_textcopy(above, msg, PART_TEXT, 2000, isteam(team, player1->team) ? 0x6496FF : 0xFF4B19, 4.0f, -8);
            }
        }
    }

    int closesttoenemy(const char *team, bool noattacked = false, bool farthest = false)
    {
        float bestdist = farthest ? -1e10f : 1e10f;
        int best = -1;
        int attackers = INT_MAX, attacked = -1;
        loopv(bases)
        {
            baseinfo &b = bases[i];
            if(!b.owner[0] || strcmp(b.owner, team)) continue;
            if(noattacked && b.enemy[0]) continue;
            float dist = disttoenemy(b);
            if(farthest ? dist > bestdist : dist < bestdist)
            {
                best = i;
                bestdist = dist;
            } else if(b.enemy[0] && b.enemies < attackers)
            {
                attacked = i;
                attackers = b.enemies;
            }
        }
        if(best < 0) return attacked;
        return best;
    }

    int pickteamspawn(const char *team)
    {
        int closest = closesttoenemy(team, true, m_regencapture);
        if(!m_regencapture && closest < 0) closest = closesttoenemy(team, false);
        if(closest < 0) return -1;
        baseinfo &b = bases[closest];

        float bestdist = 1e10f, altdist = 1e10f;
        int best = -1, alt = -1;
        loopv(entities::ents)
        {
            extentity *e = entities::ents[i];
            if(e->type!=PLAYERSTART || e->attr2) continue;
            float dist = e->o.dist(b.o);
            if(dist < bestdist)
            {
                alt = best;
                altdist = bestdist;
                best = i;
                bestdist = dist;
            } else if(dist < altdist)
            {
                alt = i;
                altdist = dist;
            }
        }
        return rnd(2) ? best : alt;
    }

    void pickspawn(fpsent *d)
    {
        findplayerspawn(d, pickteamspawn(d->team));
    }

    bool aicheck(fpsent *d, ai::aistate &b)
    {
        return false;
    }

    void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests)
    {
        vec pos = d->feetpos();
        loopvj(bases)
        {
            baseinfo &f = bases[j];
            if(!f.valid()) continue;
            static vector<int> targets; // build a list of others who are interested in this
            targets.setsize(0);
            ai::checkothers(targets, d, ai::AI_S_DEFEND, ai::AI_T_AFFINITY, j, true);
            fpsent *e = NULL;
            int regen = !m_regencapture || d->health >= 100 ? 0 : 1;
            if(m_regencapture)
            {
                int gun = f.ammotype-1+I_SHELLS;
                if(f.ammo > 0 && !d->hasmaxammo(gun))
                    regen = gun != d->ai->weappref ? 2 : 4;
            }
            loopi(numdynents()) if((e = (fpsent *)iterdynents(i)) && !e->ai && e->state == CS_ALIVE && isteam(d->team, e->team))
            { // try to guess what non ai are doing
                vec ep = e->feetpos();
                if(targets.find(e->clientnum) < 0 && ep.squaredist(f.o) <= (CAPTURERADIUS*CAPTURERADIUS))
                    targets.add(e->clientnum);
            }
            if((regen && f.owner[0] && !strcmp(f.owner, d->team)) || (targets.empty() && (!f.owner[0] || strcmp(f.owner, d->team) || f.enemy[0])))
            {
                ai::interest &n = interests.add();
                n.state = ai::AI_S_DEFEND;
                n.node = ai::closestwaypoint(f.o, ai::SIGHTMIN, false);
                n.target = j;
                n.targtype = ai::AI_T_AFFINITY;
                n.score = pos.squaredist(f.o)/(regen ? float(100*regen) : 1.f);
            }
        }
    }

    bool aidefend(fpsent *d, ai::aistate &b)
    {
        if(!bases.inrange(b.target)) return false;
        baseinfo &f = bases[b.target];
        if(!f.valid()) return false;
        bool regen = !m_regencapture || d->health >= 100 ? false : true;
        if(!regen && m_regencapture)
        {
            int gun = f.ammotype-1+I_SHELLS;
            if(f.ammo > 0 && !d->hasmaxammo(gun))
                regen = true;
        }
        int walk = 0;
        if(!regen && !f.enemy[0] && f.owner[0] && !strcmp(f.owner, d->team))
        {
            static vector<int> targets; // build a list of others who are interested in this
            targets.setsize(0);
            ai::checkothers(targets, d, ai::AI_S_DEFEND, ai::AI_T_AFFINITY, b.target, true);
            fpsent *e = NULL;
            loopi(numdynents()) if((e = (fpsent *)iterdynents(i)) && !e->ai && e->state == CS_ALIVE && isteam(d->team, e->team))
            { // try to guess what non ai are doing
                vec ep = e->feetpos();
                if(targets.find(e->clientnum) < 0 && (ep.squaredist(f.o) <= (CAPTURERADIUS*CAPTURERADIUS*4)))
                    targets.add(e->clientnum);
            }
            if(!targets.empty())
            {
                if(lastmillis-b.millis >= (201-d->skill)*33)
                {
                    d->ai->trywipe = true; // re-evaluate so as not to herd
                    return true;
                } else walk = 2;
            } else walk = 1;
            b.millis = lastmillis;
        }
        return ai::defend(d, b, f.o, float(CAPTURERADIUS), float(CAPTURERADIUS*(2+(walk*2))), walk); // less wander than ctf
    }

    bool aipursue(fpsent *d, ai::aistate &b)
    {
        b.type = ai::AI_S_DEFEND;
        return aidefend(d, b);
    }

    bool parse_network_message(int type, ucharbuf &p) override
    {
        static char text[MAXTRANS];
        switch(type)
        {
            case N_BASEINFO:
            {
                int base = getint(p);
                string owner, enemy;
                getstring(text, p);
                copystring(owner, text);
                getstring(text, p);
                copystring(enemy, text);
                int converted = getint(p), ammo = getint(p);
                if(m_capture) updatebase(base, owner, enemy, converted, ammo);
                return true;
            }

            case N_BASEREGEN:
            {
                int rcn = getint(p), health = getint(p), armour = getint(p), ammotype = getint(p), ammo = getint(p);
                fpsent *regen = rcn==player1->clientnum ? player1 : getclient(rcn);
                if(regen && m_capture)
                {
                    regen->health = health;
                    regen->armourtype = A_GREEN;
                    regen->armour = armour;
                    if(ammotype>=GUN_SG && ammotype<=GUN_PISTOL) regen->ammo[ammotype] = ammo;
                }
                return true;
            }

            case N_BASES:
            {
                int numbases = getint(p);
                loopi(numbases)
                {
                    int ammotype = getint(p);
                    string owner, enemy;
                    getstring(text, p);
                    copystring(owner, text);
                    getstring(text, p);
                    copystring(enemy, text);
                    int converted = getint(p), ammo = getint(p);
                    initbase(i, ammotype, owner, enemy, converted, ammo);
                }
                return true;
            }
            case N_BASESCORE:
            {
                int base = getint(p);
                getstring(text, p);
                int total = getint(p);
                if(m_capture) setscore(base, text, total);
                return true;
            }

            case N_REPAMMO:
            {
                int rcn = getint(p), ammotype = getint(p);
                fpsent *r = rcn==player1->clientnum ? player1 : getclient(rcn);
                if(r && m_capture) receiveammo(r, ammotype);
                return true;
            }
        }
        return false;
    }
};

extern captureclientmode capturemode;

} // ns game
