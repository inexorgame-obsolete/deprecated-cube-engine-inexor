#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/ctf_common.hpp"
#include "inexor/gamemode/gamemode_client.hpp"

namespace game {

struct ctfclientmode : clientmode, ctfmode
{
    bool addflag(int i, const vec &o, int team, int vistime = -1000)
    {
        if(!ctfmode::addflag(i, o, team)) return false;
        flag &f = flags[i];
        f.vistime = vistime;
        if(f.id >= 0) loopv(players) players[i]->flagpickup &= ~(1<<f.id);
        return true;
    }

    void ownflag(int i, fpsent *owner, int owntime)
    {
        flag &f = flags[i];
        f.owner_id = owner->clientnum;
        f.owner = owner;
        f.owntime = owntime;
        loopv(players) players[i]->flagpickup &= ~(1<<f.id);
        if(!f.vistime) f.vistime = owntime;
    }

    void returnflag(int i, int vistime = -1000)
    {
        flag &f = flags[i];
        f.droptime = 0;
        loopv(players) players[i]->flagpickup &= ~(1<<f.id);
        f.vistime = vistime;
        f.owner = NULL;
        f.owner_id = -1;
    }

    void preload()
    {
        if(m_hold) preloadmodel("game/flag/neutral");
        else
        {
            preloadmodel("game/flag/red");
            preloadmodel("game/flag/blue");
        }
        static const int sounds[] ={S_FLAGPICKUP, S_FLAGDROP, S_FLAGRETURN, S_FLAGSCORE, S_FLAGRESET, S_FLAGFAIL};
        loopi(sizeof(sounds)/sizeof(sounds[0])) inexor::sound::preloadsound(sounds[i]);
    }

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, bool flagblip)
    {
        float scale = calcradarscale();
        vec dir = d->o;
        dir.sub(pos).div(scale);
        float size = flagblip ? 0.1f : 0.05f,
            xoffset = flagblip ? -2*(3/32.0f)*size : -size,
            yoffset = flagblip ? -2*(1 - 3/32.0f)*size : -size,
            dist = dir.magnitude2(), maxdist = 1 - 0.05f - 0.05f;
        if(dist >= maxdist) dir.mul(maxdist/dist);
        dir.rotate_around_z(-camera1->yaw*RAD);
        drawradar(x + s*0.5f*(1.0f + dir.x + xoffset), y + s*0.5f*(1.0f + dir.y + yoffset), size*s);
    }

    void drawblip(fpsent *d, float x, float y, float s, int i, bool flagblip)
    {
        flag &f = flags[i];
        int blip = TEAM_NONE;
        if(m_hold && f.owner && (flagblip || lastmillis%1000 >= 500)) blip = ctfteamflag(f.owner->team) == ctfteamflag(player1->team) ? TEAM_OWN : TEAM_OPPONENT;
        else if(!m_hold) blip = f.team == ctfteamflag(player1->team) ? TEAM_OWN : TEAM_OPPONENT;
        setbliptex(blip, flagblip ? "_flag" : "");

        drawblip(d, x, y, s, flagblip ? (f.owner ? f.owner->o : (f.droptime ? f.droploc : f.spawnloc)) : f.spawnloc, flagblip);
    }

    int clipconsole(int w, int h)
    {
        return (h*(1 + 1 + 10))/(4*10);
    }

    void drawhud(fpsent *d, int w, int h)
    {
        if(d->state == CS_ALIVE)
        {
            loopv(flags) if(flags[i].owner_id == d->clientnum)
            {
                int x = HICON_X + 3*HICON_STEP + (d->quadmillis ? HICON_SIZE + HICON_SPACE : 0);
                drawicon(m_hold ? HICON_NEUTRAL_FLAG : (flags[i].team==ctfteamflag(player1->team) ? HICON_BLUE_FLAG : HICON_RED_FLAG), x, HICON_Y);
                if(m_hold)
                {
                    pushhudmatrix();
                    hudmatrix.scale(2, 2, 1);
                    flushhudmatrix();
                    draw_textf("%d", (x + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, max(HOLDSECS - (lastmillis - flags[i].owntime)/1000, 0));
                    pophudmatrix();
                }
                break;
            }
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        int s = 1800/4, x = 1800*w/h - s - s/10, y = s/10;
        gle::colorf(1, 1, 1, minimapalpha);
        if(minimapalpha >= 1) glDisable(GL_BLEND);
        bindminimap();
        drawminimap(d, x, y, s);
        if(minimapalpha >= 1) glEnable(GL_BLEND);
        gle::colorf(1, 1, 1);
        float margin = 0.04f, roffset = s*margin, rsize = s + 2*roffset;
        setradartex();
        drawradar(x - roffset, y - roffset, rsize);

        if(m_hold)  //possible flag spawns
        {
            setbliptex(TEAM_NONE);
            loopv(holdspawns) drawblip(d, x, y, s, holdspawns[i].o, false);
        }
        loopv(flags)
        {
            flag &f = flags[i];
            if(m_hold ? f.spawnindex < 0 : !ctfflagteam(f.team)) continue;
            if(!m_hold) drawblip(d, x, y, s, i, false);
            if(f.owner_id >= 0)
            {
                if(!m_hold && lastmillis%1000 >= 500) continue;
            } else if(f.droptime && (f.droploc.x < 0 || lastmillis%300 >= 150)) continue;
            drawblip(d, x, y, s, i, true);
        }
        drawteammates(d, x, y, s);
        if(d->state == CS_DEAD && (m_efficiency || !m_protect))
        {
            int wait = respawnwait(d);
            if(wait>=0)
            {
                pushhudmatrix();
                hudmatrix.scale(2, 2, 1);
                flushhudmatrix();
                bool flash = wait>0 && d==player1 && lastspawnattempt>=d->lastpain && lastmillis < lastspawnattempt+100;
                draw_textf("%s%d", (x+s/2)/2-(wait>=10 ? 28 : 16), (y+s/2)/2-32, flash ? COL_RED : "", wait);
                pophudmatrix();
            }
        }
    }

    void removeplayer(fpsent *d)
    {
        loopv(flags) if(flags[i].owner_id == d->clientnum)
        {
            flag &f = flags[i];
            f.interploc.x = -1;
            f.interptime = 0;
            dropflag(i, f.owner->o, f.owner->yaw, 1);
        }
    }

    vec interpflagpos(flag &f, float &angle)
    {
        vec pos = f.owner ? vec(f.owner->abovehead()).add(vec(0, 0, 1)) : (f.droptime ? f.droploc : f.spawnloc);
        if(f.owner) angle = f.owner->yaw;
        else if(m_hold)
        {
            float yaw, pitch;
            vectoyawpitch(vec(pos).sub(camera1->o), yaw, pitch);
            angle = yaw + 180;
        } else angle = f.droptime ? f.dropangle : f.spawnangle;
        if(pos.x < 0) return pos;
        if(f.interptime && f.interploc.x >= 0)
        {
            float t = min((lastmillis - f.interptime)/500.0f, 1.0f);
            pos.lerp(f.interploc, pos, t);
            angle += (1-t)*(f.interpangle - angle);
        }
        return pos;
    }

    vec interpflagpos(flag &f) { float angle; return interpflagpos(f, angle); }

    void rendergame()
    {
        loopv(flags)
        {
            flag &f = flags[i];
            if(!f.owner && f.droptime && f.droploc.x < 0) continue;
            if(m_hold && f.spawnindex < 0) continue;
            const char *flagname = m_hold && (!f.owner || lastmillis%1000 < 500) ? "game/flag/neutral" : (m_hold ? ctfteamflag(f.owner->team) : f.team)==ctfteamflag(player1->team) ? "game/flag/blue" : "game/flag/red";
            float angle;
            vec pos = interpflagpos(f, angle);
            if(m_hold)
                rendermodel(!f.droptime && !f.owner ? &f.light : NULL, flagname, ANIM_MAPMODEL|ANIM_LOOP,
                            pos, angle, 0,
                            MDL_GHOST | MDL_CULL_VFC | (f.droptime || f.owner ? MDL_LIGHT : 0),
                            NULL, NULL, 0, 0, 0.5f + 0.5f*(2*fabs(fmod(lastmillis/1000.0f, 1.0f) - 0.5f)));
            rendermodel(!f.droptime && !f.owner ? &f.light : NULL, flagname, ANIM_MAPMODEL|ANIM_LOOP,
                        pos, angle, 0,
                        MDL_DYNSHADOW | MDL_CULL_VFC | MDL_CULL_OCCLUDED | (f.droptime || f.owner ? MDL_LIGHT : 0),
                        NULL, NULL, 0, 0, 0.3f + (f.vistime ? 0.7f*min((lastmillis - f.vistime)/1000.0f, 1.0f) : 0.0f));

            if(m_protect && canaddparticles() && f.owner && insidebase(f, f.owner->feetpos()))
            {
                particle_flare(pos, f.spawnloc, 0, PART_LIGHTNING, strcmp(f.owner->team, player1->team) ? 0xFF2222 : 0x2222FF, 1.0f);
                if(!flags.inrange(f.owner->lastbase))
                {
                    particle_fireball(pos, 4.8f, PART_EXPLOSION, 250, strcmp(f.owner->team, player1->team) ? 0x802020 : 0x2020FF, 4.8f);
                    particle_splash(PART_SPARK, 50, 250, pos, strcmp(f.owner->team, player1->team) ? 0x802020 : 0x2020FF, 0.24f);
                }
                f.owner->lastbase = i;
            }
        }
        if(m_protect && canaddparticles()) loopv(players)
        {
            fpsent *d = players[i];
            if(!flags.inrange(d->lastbase)) continue;
            flag &f = flags[d->lastbase];
            if(f.owner_id == d->clientnum && insidebase(f, d->feetpos())) continue;
            d->lastbase = -1;
            float angle;
            vec pos = interpflagpos(f, angle);
            particle_fireball(pos, 4.8f, PART_EXPLOSION, 250, strcmp(d->team, player1->team) ? 0x802020 : 0x2020FF, 4.8f);
            particle_splash(PART_SPARK, 50, 250, pos, strcmp(d->team, player1->team) ? 0x802020 : 0x2020FF, 0.24f);
        }
    }

    void setup()
    {
        resetflags();
        if(m_hold)
        {
            loopv(entities::ents)
            {
                extentity *e = entities::ents[i];
                if(e->type!=BASE) continue;
                if(!addholdspawn(e->o)) continue;
                holdspawns.last().light = e->light;
            }
            if(holdspawns.length()) while(flags.length() < HOLDFLAGS) addflag(flags.length(), vec(0, 0, 0), 0, -1000);
        } else
        {
            loopv(entities::ents)
            {
                extentity *e = entities::ents[i];
                if(e->type!=FLAG) continue;
                if(e->attr2<1 || e->attr2>2) continue;
                int index = flags.length();
                if(!addflag(index, e->o, e->attr2, m_protect ? 0 : -1000)) continue;
                flags[index].spawnangle = e->attr1;
                flags[index].light = e->light;
            }
        }
    }

    void senditems(packetbuf &p)
    {
        putint(p, N_INITFLAGS);
        if(m_hold)
        {
            putint(p, holdspawns.length());
            loopv(holdspawns)
            {
                holdspawn &h = holdspawns[i];
                putint(p, -1);
                loopk(3) putint(p, int(h.o[k]*DMF));
            }
        } else
        {
            putint(p, flags.length());
            loopv(flags)
            {
                flag &f = flags[i];
                putint(p, f.team);
                loopk(3) putint(p, int(f.spawnloc[k]*DMF));
            }
        }
    }

    void parseflags(ucharbuf &p, bool commit)
    {
        loopk(2)
        {
            int score = getint(p);
            if(commit) scores[k] = score;
        }
        int numflags = getint(p);
        loopi(numflags)
        {
            int version = getint(p), spawn = getint(p), owner = getint(p), invis = getint(p), dropped = 0;
            vec droploc(0, 0, 0);
            if(owner<0)
            {
                dropped = getint(p);
                if(dropped) loopk(3) droploc[k] = getint(p)/DMF;
            }
            if(p.overread()) break;
            if(commit && flags.inrange(i))
            {
                flag &f = flags[i];
                f.version = version;
                f.spawnindex = spawn;
                if(m_hold) spawnflag(f);
                if(owner>=0 && owner==player1->clientnum)
                {
                    f.owner = player1;
                    f.owner_id = player1->clientnum;
                }
                else if(owner>=0)
                {
                    fpsent *n = newclient(owner);
                    f.owner = n;
                    f.owner_id = n->clientnum;
                }
                else
                {
                    f.owner_id = -1;
                    f.owner = nullptr;
                }
                f.droptime = dropped;
                f.droploc = dropped ? droploc : f.spawnloc;
                f.vistime = invis>0 ? 0 : -1000;
                f.interptime = 0;

                if(dropped)
                {
                    f.droploc.z += 4;
                    if(!droptofloor(f.droploc, 4, 0)) f.droploc = vec(-1, -1, -1);
                }
            }
        }
    }

    void trydropflag()
    {
        if(!m_ctf) return;
        loopv(flags) if(flags[i].owner_id == player1->clientnum)
        {
            addmsg(N_TRYDROPFLAG, "rc", player1);
            return;
        }
    }

    const char *teamcolorflag(flag &f)
    {
        return m_hold ? "the flag" : teamcolor("your flag", ctfflagteam(f.team), "the enemy flag");
    }

    void dropflag(int i, const vec &o, float yaw, int droptime)
    {
        flag &f = flags[i];
        f.droploc = o;
        f.droptime = droptime;
        loopv(players) players[i]->flagpickup &= ~(1<<f.id);
        f.owner = NULL;
        f.dropangle = yaw;
        if(!f.vistime) f.vistime = droptime;
    }

    void dropflag(fpsent *d, int i, int version, const vec &droploc)
    {
        if(!flags.inrange(i)) return;
        flag &f = flags[i];
        f.version = version;
        f.interploc = interpflagpos(f, f.interpangle);
        f.interptime = lastmillis;
        dropflag(i, droploc, d->yaw, 1);
        f.droploc.z += 4;
        d->flagpickup |= 1<<f.id;
        if(!droptofloor(f.droploc, 4, 0))
        {
            f.droploc = vec(-1, -1, -1);
            f.interptime = 0;
        }
        spdlog::get("gameplay")->info("{0} dropped {1}", teamcolorname(d), teamcolorflag(f));
        inexor::sound::playsound(S_FLAGDROP);
    }

    void flagexplosion(int i, int team, const vec &loc)
    {
        int fcolor;
        vec color;
        if(!team) { fcolor = 0xFF8080; color = vec(1, 0.75f, 0.5f); } else if(team==ctfteamflag(player1->team)) { fcolor = 0x2020FF; color = vec(0.25f, 0.25f, 1); } else { fcolor = 0x802020; color = vec(1, 0.25f, 0.25f); }
        particle_fireball(loc, 30, PART_EXPLOSION, -1, fcolor, 4.8f);
        adddynlight(loc, 35, color, 900, 100);
        particle_splash(PART_SPARK, 150, 300, loc, fcolor, 0.24f);
    }

    void flageffect(int i, int team, const vec &from, const vec &to)
    {
        vec fromexp(from), toexp(to);
        if(from.x >= 0)
        {
            fromexp.z += 8;
            flagexplosion(i, team, fromexp);
        }
        if(from==to) return;
        if(to.x >= 0)
        {
            toexp.z += 8;
            flagexplosion(i, team, toexp);
        }
        if(from.x >= 0 && to.x >= 0)
            particle_flare(fromexp, toexp, 600, PART_LIGHTNING, !team ? 0xFFC0A0 : (team==ctfteamflag(player1->team) ? 0x2222FF : 0xFF2222), 1.0f);
    }

    void returnflag(fpsent *d, int i, int version)
    {
        if(!flags.inrange(i)) return;
        flag &f = flags[i];
        f.version = version;
        flageffect(i, f.team, interpflagpos(f), f.spawnloc);
        f.interptime = 0;
        returnflag(i);
        if(m_protect && d->feetpos().dist(f.spawnloc) < FLAGRADIUS) d->flagpickup |= 1<<f.id;
        spdlog::get("gameplay")->info("{0} returned {1}", teamcolorname(d), teamcolorflag(f));
        inexor::sound::playsound(S_FLAGRETURN);
    }

    void spawnflag(flag &f)
    {
        if(!holdspawns.inrange(f.spawnindex)) return;
        holdspawn &h = holdspawns[f.spawnindex];
        f.spawnloc = h.o;
        f.light = h.light;
    }

    void resetflag(int i, int version, int spawnindex, int team, int score)
    {
        setscore(team, score);
        if(!flags.inrange(i)) return;
        flag &f = flags[i];
        f.version = version;
        bool shouldeffect = !m_hold || f.spawnindex >= 0;
        f.spawnindex = spawnindex;
        if(m_hold) spawnflag(f);
        if(shouldeffect) flageffect(i, m_hold ? 0 : team, interpflagpos(f), f.spawnloc);
        f.interptime = 0;
        returnflag(i, m_protect ? 0 : -1000);
        if(shouldeffect)
        {
            spdlog::get("gameplay")->info("{0} reset", teamcolorflag(f));
            inexor::sound::playsound(S_FLAGRESET);
        }
    }

    void scoreflag(fpsent *d, int relay, int relayversion, int goal, int goalversion, int goalspawn, int team, int score, int dflags, int time)
    {
        setscore(team, score);
        if(flags.inrange(goal))
        {
            flag &f = flags[goal];
            f.version = goalversion;
            f.spawnindex = goalspawn;
            if(m_hold) spawnflag(f);
            if(relay >= 0)
            {
                flags[relay].version = relayversion;
                flageffect(goal, team, f.spawnloc, flags[relay].spawnloc);
            } else flageffect(goal, team, interpflagpos(f), f.spawnloc);
            f.interptime = 0;
            returnflag(relay >= 0 ? relay : goal, m_protect ? 0 : -1000);
            d->flagpickup &= ~(1<<f.id);
            if(d->feetpos().dist(f.spawnloc) < FLAGRADIUS) d->flagpickup |= 1<<f.id;
        }
        if(d!=player1)
        {
            defformatstring(ds, "%d", score);
            particle_textcopy(d->abovehead(), ds, PART_TEXT, 2000, 0x32FF64, 4.0f, -8);
        }
        d->flags = dflags;
        if(time) spdlog::get("gameplay")->info("{} scored for {} (in {:.1f} seconds)", teamcolorname(d), teamcolor("your team", ctfflagteam(team), "the enemy team"), (float(time)/10.0f));
        else spdlog::get("gameplay")->info("{0} scored for {1}", teamcolorname(d), teamcolor("your team", ctfflagteam(team), "the enemy team"));
        inexor::sound::playsound(team==ctfteamflag(player1->team) ? S_FLAGSCORE : S_FLAGFAIL);

        if(score >= FLAGLIMIT) spdlog::get("gameplay")->info("{0} captured {1} flags", teamcolor("your team", ctfflagteam(team), "the enemy team"), score);
    }

    void takeflag(fpsent *d, int i, int version)
    {
        if(!flags.inrange(i)) return;
        flag &f = flags[i];
        f.version = version;
        f.interploc = interpflagpos(f, f.interpangle);
        f.interptime = lastmillis;
        if(m_hold) spdlog::get("gameplay")->info("{0} picked up the flag for {1}", teamcolorname(d), teamcolor("your team", d->team, "the enemy team"));
        else if(m_protect || f.droptime) spdlog::get("gameplay")->info("{0} picked up {1}", teamcolorname(d), teamcolorflag(f));
        else spdlog::get("gameplay")->info("{0} stole {1}", teamcolorname(d), teamcolorflag(f));
        ownflag(i, d, lastmillis);
        inexor::sound::playsound(S_FLAGPICKUP);
    }

    void invisflag(int i, int invis)
    {
        if(!flags.inrange(i)) return;
        flag &f = flags[i];
        if(invis>0) f.vistime = 0;
        else if(!f.vistime) f.vistime = lastmillis;
    }

    void checkitems(fpsent *d)
    {
        if(d->state!=CS_ALIVE) return;
        vec o = d->feetpos();
        loopv(flags)
        {
            flag &f = flags[i];
            if((m_hold ? f.spawnindex < 0 : !ctfflagteam(f.team)) || f.owner || (f.droptime && f.droploc.x<0)) continue;
            const vec &loc = f.droptime ? f.droploc : f.spawnloc;
            if(o.dist(loc) < FLAGRADIUS)
            {
                if(d->flagpickup&(1<<f.id)) continue;
                if(m_hold || ((lookupmaterial(o)&MATF_CLIP) != MAT_GAMECLIP && (lookupmaterial(loc)&MATF_CLIP) != MAT_GAMECLIP))
                    addmsg(N_TAKEFLAG, "rcii", d, i, f.version);
                d->flagpickup |= 1<<f.id;
            } else d->flagpickup &= ~(1<<f.id);
        }
    }

    void respawned(fpsent *d)
    {
        vec o = d->feetpos();
        d->flagpickup = 0;
        loopv(flags)
        {
            flag &f = flags[i];
            if((m_hold ? f.spawnindex < 0 : !ctfflagteam(f.team)) || f.owner || (f.droptime && f.droploc.x<0)) continue;
            if(o.dist(f.droptime ? f.droploc : f.spawnloc) < FLAGRADIUS) d->flagpickup |= 1<<f.id;
        }
    }

    int respawnwait(fpsent *d)
    {
        return m_efficiency || !m_protect ? max(0, RESPAWNSECS-(lastmillis-d->lastpain)/1000) : 0;
    }

    bool pickholdspawn(fpsent *d)
    {
        vector<extentity *> spawns;
        loopv(flags)
        {
            flag &f = flags[i];
            if(f.spawnindex < 0 || (!f.owner && (!f.droptime || f.droploc.x < 0))) continue;
            const vec &goal = f.owner ? f.owner->o : f.droploc;
            extentity *flagspawns[7];
            int numflagspawns = 0;
            memset(flagspawns, 0, sizeof(flagspawns));
            loopvj(entities::ents)
            {
                extentity *e = entities::ents[j];
                if(e->type != PLAYERSTART || e->attr2 != 0) continue;
                float dist = e->o.dist(goal);
                loopk(numflagspawns)
                {
                    float sdist = flagspawns[k]->o.dist(goal);
                    if(dist >= sdist) continue;
                    swap(e, flagspawns[k]);
                    dist = sdist;
                }
                if(numflagspawns < int(sizeof(flagspawns)/sizeof(flagspawns[0]))) flagspawns[numflagspawns++] = e;
            }
            loopk(numflagspawns) spawns.add(flagspawns[k]);
        }
        if(spawns.empty()) return false;
        int pick = rnd(spawns.length());
        d->pitch = 0;
        d->roll = 0;
        loopv(spawns)
        {
            int attempt = (pick + i)%spawns.length();
            d->o = spawns[attempt]->o;
            d->yaw = spawns[attempt]->attr1;
            if(entinmap(d, true)) return true;
        }
        return false;
    }

    void pickspawn(fpsent *d)
    {
        if(!m_hold || !pickholdspawn(d))
            findplayerspawn(d, -1, m_hold ? 0 : ctfteamflag(d->team));
    }

    bool aihomerun(fpsent *d, ai::aistate &b)
    {
        if(m_protect || m_hold)
        {
            static vector<ai::interest> interests;
            loopk(2)
            {
                interests.setsize(0);
                ai::assist(d, b, interests, k != 0);
                if(ai::parseinterests(d, b, interests, false, true)) return true;
            }
        } else
        {
            vec pos = d->feetpos();
            loopk(2)
            {
                int goal = -1;
                loopv(flags)
                {
                    flag &g = flags[i];
                    if(g.team == ctfteamflag(d->team) && (k || (!g.owner && !g.droptime)) &&
                        (!flags.inrange(goal) || g.pos().squaredist(pos) < flags[goal].pos().squaredist(pos)))
                    {
                        goal = i;
                    }
                }
                if(flags.inrange(goal) && ai::makeroute(d, b, flags[goal].pos()))
                {
                    d->ai->switchstate(b, ai::AI_S_PURSUE, ai::AI_T_AFFINITY, goal);
                    return true;
                }
            }
        }
        if(b.type == ai::AI_S_INTEREST && b.targtype == ai::AI_T_NODE) return true; // we already did this..
        if(randomnode(d, b, ai::SIGHTMIN, 1e16f))
        {
            d->ai->switchstate(b, ai::AI_S_INTEREST, ai::AI_T_NODE, d->ai->route[0]);
            return true;
        }
        return false;
    }

    bool aicheck(fpsent *d, ai::aistate &b)
    {
        static vector<int> takenflags;
        takenflags.setsize(0);
        loopv(flags)
        {
            flag &g = flags[i];
            if(g.owner_id == d->clientnum) return aihomerun(d, b);
            else if(g.team == ctfteamflag(d->team) && ((g.owner && g.team != ctfteamflag(g.owner->team)) || g.droptime))
                takenflags.add(i);
        }
        if(!ai::badhealth(d) && !takenflags.empty())
        {
            int flag = takenflags.length() > 2 ? rnd(takenflags.length()) : 0;
            d->ai->switchstate(b, ai::AI_S_PURSUE, ai::AI_T_AFFINITY, takenflags[flag]);
            return true;
        }
        return false;
    }

    void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests)
    {
        vec pos = d->feetpos();
        loopvj(flags)
        {
            flag &f = flags[j];
            if((!m_protect && !m_hold) || f.owner_id != d->clientnum)
            {
                static vector<int> targets; // build a list of others who are interested in this
                targets.setsize(0);
                bool home = !m_hold && f.team == ctfteamflag(d->team);
                ai::checkothers(targets, d, home ? ai::AI_S_DEFEND : ai::AI_S_PURSUE, ai::AI_T_AFFINITY, j, true);
                fpsent *e = NULL;
                loopi(numdynents()) if((e = (fpsent *)iterdynents(i)) && !e->ai && e->state == CS_ALIVE && isteam(d->team, e->team))
                { // try to guess what non ai are doing
                    vec ep = e->feetpos();
                    if(targets.find(e->clientnum) < 0 && (ep.squaredist(f.pos()) <= (FLAGRADIUS*FLAGRADIUS*4) || f.owner_id == e->clientnum))
                        targets.add(e->clientnum);
                }
                if(home)
                {
                    bool guard = false;
                    if((f.owner && f.team != ctfteamflag(f.owner->team)) || f.droptime || targets.empty()) guard = true;
                    else if(d->hasammo(d->ai->weappref))
                    { // see if we can relieve someone who only has a piece of crap
                        fpsent *t;
                        loopvk(targets) if((t = getclient(targets[k])))
                        {
                            if((t->ai && !t->hasammo(t->ai->weappref)) || (!t->ai && (t->gunselect == GUN_FIST || t->gunselect == GUN_PISTOL)))
                            {
                                guard = true;
                                break;
                            }
                        }
                    }
                    if(guard)
                    { // defend the flag
                        ai::interest &n = interests.add();
                        n.state = ai::AI_S_DEFEND;
                        n.node = ai::closestwaypoint(f.pos(), ai::SIGHTMIN, true);
                        n.target = j;
                        n.targtype = ai::AI_T_AFFINITY;
                        n.score = pos.squaredist(f.pos())/100.f;
                    }
                } else
                {
                    if(targets.empty())
                    { // attack the flag
                        ai::interest &n = interests.add();
                        n.state = ai::AI_S_PURSUE;
                        n.node = ai::closestwaypoint(f.pos(), ai::SIGHTMIN, true);
                        n.target = j;
                        n.targtype = ai::AI_T_AFFINITY;
                        n.score = pos.squaredist(f.pos());
                    } else
                    { // help by defending the attacker
                        fpsent *t;
                        loopvk(targets) if((t = getclient(targets[k])))
                        {
                            ai::interest &n = interests.add();
                            n.state = ai::AI_S_DEFEND;
                            n.node = t->lastnode;
                            n.target = t->clientnum;
                            n.targtype = ai::AI_T_PLAYER;
                            n.score = d->o.squaredist(t->o);
                        }
                    }
                }
            }
        }
    }

    bool aidefend(fpsent *d, ai::aistate &b)
    {
        loopv(flags)
        {
            flag &g = flags[i];
            if(g.owner_id == d->clientnum) return aihomerun(d, b);
        }
        if(flags.inrange(b.target))
        {
            flag &f = flags[b.target];
            if(f.droptime) return ai::makeroute(d, b, f.pos());
            if(f.owner) return ai::violence(d, b, f.owner, 4);
            int walk = 0;
            if(lastmillis-b.millis >= (201-d->skill)*33)
            {
                static vector<int> targets; // build a list of others who are interested in this
                targets.setsize(0);
                ai::checkothers(targets, d, ai::AI_S_DEFEND, ai::AI_T_AFFINITY, b.target, true);
                fpsent *e = NULL;
                loopi(numdynents()) if((e = (fpsent *)iterdynents(i)) && !e->ai && e->state == CS_ALIVE && isteam(d->team, e->team))
                { // try to guess what non ai are doing
                    vec ep = e->feetpos();
                    if(targets.find(e->clientnum) < 0 && (ep.squaredist(f.pos()) <= (FLAGRADIUS*FLAGRADIUS*4) || f.owner_id == e->clientnum))
                        targets.add(e->clientnum);
                }
                if(!targets.empty())
                {
                    d->ai->trywipe = true; // re-evaluate so as not to herd
                    return true;
                } else
                {
                    walk = 2;
                    b.millis = lastmillis;
                }
            }
            vec pos = d->feetpos();
            float mindist = float(FLAGRADIUS*FLAGRADIUS*8);
            loopv(flags)
            { // get out of the way of the returnee!
                flag &g = flags[i];
                if(pos.squaredist(g.pos()) <= mindist)
                {
                    if(!m_protect && !m_hold && g.owner && !strcmp(g.owner->team, d->team)) walk = 1;
                    if(g.droptime && ai::makeroute(d, b, g.pos())) return true;
                }
            }
            return ai::defend(d, b, f.pos(), float(FLAGRADIUS*2), float(FLAGRADIUS*(2+(walk*2))), walk);
        }
        return false;
    }

    bool aipursue(fpsent *d, ai::aistate &b)
    {
        if(flags.inrange(b.target))
        {
            flag &f = flags[b.target];
            if(f.owner_id == d->clientnum) return aihomerun(d, b);
            if(!m_hold && f.team == ctfteamflag(d->team))
            {
                if(f.droptime) return ai::makeroute(d, b, f.pos());
                if(f.owner) return ai::violence(d, b, f.owner, 4);
                loopv(flags)
                {
                    flag &g = flags[i];
                    if(g.owner_id == d->clientnum) return ai::makeroute(d, b, f.pos());
                }
            } else
            {
                if(f.owner) return ai::violence(d, b, f.owner, 4);
                return ai::makeroute(d, b, f.pos());
            }
        }
        return false;
    }

    bool parse_network_message(int type, ucharbuf &p) override
    {
        switch(type)
        {
            case N_INITFLAGS:
            {
                parseflags(p, m_ctf);
                return true;
            }

            case N_DROPFLAG:
            {
                int ocn = getint(p), flag = getint(p), version = getint(p);
                vec droploc;
                loopk(3) droploc[k] = getint(p)/DMF;
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                if(o && m_ctf) dropflag(o, flag, version, droploc);
                return true;
            }

            case N_SCOREFLAG:
            {
                int ocn = getint(p), relayflag = getint(p), relayversion = getint(p), goalflag = getint(p), goalversion = getint(p), goalspawn = getint(p), team = getint(p), score = getint(p), oflags = getint(p), flagruntime = getint(p);
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                if(o && m_ctf) scoreflag(o, relayflag, relayversion, goalflag, goalversion, goalspawn, team, score, oflags, flagruntime);
                return true;
            }

            case N_RETURNFLAG:
            {
                int ocn = getint(p), flag = getint(p), version = getint(p);
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                if(o && m_ctf) returnflag(o, flag, version);
                return true;
            }

            case N_TAKEFLAG:
            {
                int ocn = getint(p), flag = getint(p), version = getint(p);
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                if(o && m_ctf) takeflag(o, flag, version);
                return true;
            }

            case N_RESETFLAG:
            {
                int flag = getint(p), version = getint(p), spawnindex = getint(p), team = getint(p), score = getint(p);
                if(m_ctf) resetflag(flag, version, spawnindex, team, score);
                return true;
            }

            case N_INVISFLAG:
            {
                int flag = getint(p), invis = getint(p);
                if(m_ctf) invisflag(flag, invis);
                return true;
            }
        }
        return false;
    }
};

extern ctfclientmode ctfmode;
ICOMMAND(dropflag, "", (), {ctfmode.trydropflag();});

} // ns game
