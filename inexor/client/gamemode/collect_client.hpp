#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/engine/sound.hpp"
#include "inexor/gamemode/collect_common.hpp"
#include "inexor/client/gamemode/gamemode_client.hpp"

namespace game {

struct collectclientmode : clientmode, collectmode_common
{
    static const int TOKENHEIGHT = 5;

    token &droptoken(int id, const vec &o, int team, int droptime)
    {
        token &t = collectmode_common::droptoken(o, team, droptime);
        t.id = id;
        return t;
    }

    void preload()
    {
        preloadmodel("game/base/red");
        preloadmodel("game/base/blue");
        preloadmodel("game/skull/red");
        preloadmodel("game/skull/blue");
        static const int sounds[] ={S_FLAGDROP, S_FLAGSCORE, S_FLAGFAIL};
        loopi(sizeof(sounds)/sizeof(sounds[0])) inexor::sound::preloadsound(sounds[i]);
    }

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, float size = 0.05f)
    {
        float scale = calcradarscale();
        vec dir = d->o;
        dir.sub(pos).div(scale);
        float xoffset = -size,
            yoffset = -size,
            dist = dir.magnitude2(), maxdist = 1 - 0.05f - 0.05f;
        if(dist >= maxdist) dir.mul(maxdist/dist);
        dir.rotate_around_z(-camera1->yaw*RAD);
        drawradar(x + s*0.5f*(1.0f + dir.x + xoffset), y + s*0.5f*(1.0f + dir.y + yoffset), size*s);
    }

    void drawbaseblip(fpsent *d, float x, float y, float s, int i)
    {
        base &b = bases[i];
        setbliptex(b.team==collectteambase(player1->team) ? TEAM_OWN : TEAM_OPPONENT);
        drawblip(d, x, y, s, b.o);
    }

    int clipconsole(int w, int h)
    {
        return (h*(1 + 1 + 10))/(4*10);
    }

    void drawhud(fpsent *d, int w, int h)
    {
        if(d->state == CS_ALIVE && d->tokens > 0)
        {
            int x = HICON_X + 3*HICON_STEP + (d->quadmillis ? HICON_SIZE + HICON_SPACE : 0);
            pushhudmatrix();
            hudmatrix.scale(2, 2, 1);
            flushhudmatrix();
            draw_textf("%d", (x + HICON_SIZE + HICON_SPACE)/2, HICON_TEXTY/2, d->tokens);
            pophudmatrix();
            drawicon(HICON_TOKEN, x, HICON_Y);
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
        loopv(bases)
        {
            base &b = bases[i];
            if(!collectbaseteam(b.team)) continue;
            drawbaseblip(d, x, y, s, i);
        }

        loopv(players)
        {
            fpsent *o = players[i];
            if(o != d && o->state == CS_ALIVE && o->tokens > 0 && !isteam(o->team, d->team))
            { //todo fix eventually
                setbliptex(TEAM_OPPONENT, "_skull");
                drawblip(d, x, y, s, o->o, 0.07f);
            }
        }
        drawteammates(d, x, y, s);
        if(d->state == CS_DEAD)
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

    void rendergame()
    {
        int team = collectteambase(player1->team);
        vec theight(0, 0, 0);
        abovemodel(theight, "game/skull/red");
        loopv(bases)
        {
            base &b = bases[i];
            const char *basename = b.team==team ? "game/base/blue" : "game/base/red";
            rendermodel(&b.light, basename, ANIM_MAPMODEL|ANIM_LOOP, b.o, 0, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_OCCLUDED);
            float fradius = 1.0f, fheight = 0.5f;
            regular_particle_flame(PART_FLAME, vec(b.tokenpos.x, b.tokenpos.y, b.tokenpos.z - 4.5f), fradius, fheight, b.team==team ? 0x2020FF : 0x802020, 3, 2.0f);
            vec tokenpos(b.tokenpos);
            tokenpos.z -= theight.z/2 + sinf(lastmillis/100.0f)/20;
            float alpha = player1->state == CS_ALIVE && player1->tokens <= 0 && lastmillis < b.laststeal + STEALTOKENTIME ? 0.5f : 1.0f;
            rendermodel(&b.light, b.team==team ? "game/skull/blue" : "game/skull/red", ANIM_MAPMODEL|ANIM_LOOP, tokenpos, lastmillis/10.0f, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_OCCLUDED, NULL, NULL, 0, 0, alpha);
            formatstring(b.info, "%d", totalscore(b.team));
            vec above(b.tokenpos);
            above.z += TOKENHEIGHT;
            if(b.info[0]) particle_text(above, b.info, PART_TEXT, 1, b.team==team ? 0x6496FF : 0xFF4B19, 2.0f);
        }
        loopv(tokens)
        {
            token &t = tokens[i];
            vec p = t.o;
            p.z += 1+sinf(lastmillis/100.0+t.o.x+t.o.y)/20;
            rendermodel(&t.light, t.team == team || (t.team < 0 && -t.team != team) ? "game/skull/blue" : "game/skull/red", ANIM_MAPMODEL|ANIM_LOOP, p, lastmillis/10.0f, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED);
        }
        fpsent *exclude = isthirdperson() ? NULL : hudplayer();
        loopv(players)
        {
            fpsent *d = players[i];
            if(d->state != CS_ALIVE || d->tokens <= 0 || d == exclude) continue;
            vec pos = d->abovehead().add(vec(0, 0, 1));
            entitylight light;
            lightreaching(pos, light.color, light.dir, true);
            int dteam = collectteambase(d->team);
            loopj(d->tokens)
            {
                rendermodel(&light, dteam != team ? "game/skull/blue" : "game/skull/red", ANIM_MAPMODEL|ANIM_LOOP, pos, d->yaw+90, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED);
                pos.z += TOKENHEIGHT + 1;
            }
        }
    }

    void setup()
    {
        resetbases();
        vector<extentity *> radarents;
        loopv(entities::ents)
        {
            extentity *e = entities::ents[i];
            if(e->type!=FLAG) continue;
            if(e->attr2<1 || e->attr2>2) continue;
            int index = bases.length();
            if(!addbase(index, e->o, e->attr2)) continue;
            base &b = bases[index];
            b.tokenpos = b.o;
            abovemodel(b.tokenpos, "game/base/blue");
            b.tokenpos.z += TOKENHEIGHT-2;
            b.light = e->light;
        }
    }

    void senditems(packetbuf &p)
    {
        putint(p, N_INITTOKENS);
        putint(p, bases.length());
        loopv(bases)
        {
            base &b = bases[i];
            putint(p, b.team);
            loopk(3) putint(p, int(b.o[k]*DMF));
        }
    }

    vec movetoken(const vec &o, int yaw)
    {
        static struct dropent : physent
        {
            dropent()
            {
                type = ENT_BOUNCE;
            }
        } d;
        d.o = o;
        d.o.z += 4;
        d.radius = d.xradius = d.yradius = 4;
        d.eyeheight = d.aboveeye = 4;
        vecfromyawpitch(yaw, 0, 1, 0, d.vel);
        d.o.add(vec(d.vel).mul(4));
        movecamera(&d, d.vel, TOKENDIST-4, 1);
        if(!droptofloor(d.o, 4, 4)) return vec(-1, -1, -1);
        return d.o;
    }

    void parsetokens(ucharbuf &p, bool commit)
    {
        loopk(2)
        {
            int score = getint(p);
            if(commit) scores[k] = score;
        }
        int numtokens = getint(p);
        loopi(numtokens)
        {
            int id = getint(p), team = getint(p), yaw = getint(p);
            vec o;
            loopk(3) o[k] = getint(p)/DMF;
            if(p.overread()) break;
            o = movetoken(o, yaw);
            if(o.z >= 0) droptoken(id, o, team, lastmillis);
        }
        for(;;)
        {
            int cn = getint(p);
            if(cn < 0) break;
            int tokens = getint(p);
            if(p.overread()) break;
            fpsent *d = cn == player1->clientnum ? player1 : newclient(cn);
            if(d) d->tokens = tokens;
        }
    }

    void baseexplosion(int i, int team, const vec &loc)
    {
        int fcolor;
        vec color;
        if(team==collectteambase(player1->team)) { fcolor = 0x2020FF; color = vec(0.25f, 0.25f, 1); } else { fcolor = 0x802020; color = vec(1, 0.25f, 0.25f); }
        particle_fireball(loc, 30, PART_EXPLOSION, -1, fcolor, 4.8f);
        adddynlight(loc, 35, color, 900, 100);
        particle_splash(PART_SPARK, 150, 300, loc, fcolor, 0.24f);
    }

    void baseeffect(int i, int team, const vec &from, const vec &to, bool showfrom = true, bool showto = true)
    {
        if(showfrom) baseexplosion(i, team, from);
        if(from==to) return;
        if(showto) baseexplosion(i, team, to);
        particle_flare(from, to, 600, PART_LIGHTNING, team==collectteambase(player1->team) ? 0x2222FF : 0xFF2222, 1.0f);
    }

    void expiretoken(int id)
    {
        token *t = findtoken(id);
        if(!t) return;
        inexor::sound::playsound(S_ITEMAMMO, &t->o);
        removetoken(id);
    }

    void taketoken(fpsent *d, int id, int total)
    {
        int team = collectteambase(d->team);
        token *t = findtoken(id);
        if(t)
        {
            inexor::sound::playsound(t->team == team || (t->team < 0 && -t->team != team) ? S_ITEMAMMO : S_ITEMHEALTH, d!=player1 ? &d->o : NULL);
            removetoken(id);
        }
        d->tokens = total;
    }

    token *droptoken(fpsent *d, int id, const vec &o, int team, int yaw, int n)
    {
        vec pos = movetoken(o, yaw);
        if(pos.z < 0) return NULL;
        token &t = droptoken(id, pos, team, lastmillis);
        lightreaching(vec(t.o).add(vec(0, 0, TOKENHEIGHT)), t.light.color, t.light.dir, true);
        if(!n) inexor::sound::playsound(S_ITEMSPAWN, d ? &d->o : &pos);
        if(d)
        {
            if(!n)
            {
                particle_fireball(d->o, 4.8f, PART_EXPLOSION, 500, team==collectteambase(player1->team) ? 0x2020FF : 0x802020, 4.8f);
                particle_splash(PART_SPARK, 50, 250, d->o, team==collectteambase(player1->team) ? 0x2020FF : 0x802020, 0.24f);
            }
            particle_flare(d->o, vec(t.o.x, t.o.y, t.o.z + 0.5f*(TOKENHEIGHT + 1)), 500, PART_LIGHTNING, team==collectteambase(player1->team) ? 0x2222FF : 0xFF2222, 1.0f);
        }
        return &t;
    }

    void stealtoken(fpsent *d, int id, const vec &o, int team, int yaw, int n, int basenum, int enemyteam, int score)
    {
        if(!n) setscore(enemyteam, score);
        token *t = droptoken(NULL, id, o, team, yaw, n);
        if(bases.inrange(basenum))
        {
            base &b = bases[basenum];
            if(!n)
            {
                b.laststeal = lastmillis;
                spdlog::get("gameplay")->info("{0} stole a skull from {1}", teamcolorname(d), teamcolor("your team", collectbaseteam(enemyteam), "the enemy team"));
                inexor::sound::playsound(S_FLAGDROP, &b.tokenpos);
            }
            if(t) particle_flare(b.tokenpos, vec(t->o.x, t->o.y, t->o.z + 0.5f*(TOKENHEIGHT + 1)), 500, PART_LIGHTNING, team==collectteambase(player1->team) ? 0x2222FF : 0xFF2222, 1.0f);
        }
    }

    void deposittokens(fpsent *d, int basenum, int deposited, int team, int score, int flags)
    {
        if(bases.inrange(basenum))
        {
            base &b = bases[basenum];
            b.laststeal = lastmillis;
            //inexor::sound::playsound(S_FLAGSCORE, d != player1 ? &b.tokenpos : NULL);
            int n = 0;
            loopv(bases)
            {
                base &h = bases[i];
                if(h.team == team) baseeffect(i, team, h.tokenpos, b.tokenpos, !n++);
            }
        }
        d->tokens = 0;
        d->flags = flags;
        setscore(team, score);

        spdlog::get("gameplay")->info("{0} collected {1} {2} for {3}", teamcolorname(d), deposited, (deposited==1 ? "skull" : "skulls"), teamcolor("your team", collectbaseteam(team), "the enemy team"));
        inexor::sound::playsound(team==collectteambase(player1->team) ? S_FLAGSCORE : S_FLAGFAIL);

        if(score >= SCORELIMIT) spdlog::get("gameplay")->info("{0} collected {1} skulls", teamcolor("your team", collectbaseteam(team), "the enemy team"), score);
    }

    void checkitems(fpsent *d)
    {
        if(d->state!=CS_ALIVE) return;
        vec o = d->feetpos();
        if(d->tokens > 0 || o != d->lastcollect)
        {
            int team = collectteambase(d->team);
            loopv(bases)
            {
                base &b = bases[i];
                if(!collectbaseteam(b.team) || b.team == team) continue;
                if(insidebase(b, o) && (d->tokens > 0 || !insidebase(b, d->lastcollect)))
                {
                    addmsg(N_DEPOSITTOKENS, "rci", d, i);
                    d->tokens = 0;
                }
            }
        }
        if(d->tokens < TOKENLIMIT) loopv(tokens)
        {
            token &t = tokens[i];
            if(o.dist(t.o) < TOKENRADIUS && d->lastcollect.dist(t.o) >= TOKENRADIUS && (lookupmaterial(o)&MATF_CLIP) != MAT_GAMECLIP && (lookupmaterial(t.o)&MATF_CLIP) != MAT_GAMECLIP)
                addmsg(N_TAKETOKEN, "rci", d, t.id);
        }
        d->lastcollect = o;
    }

    int respawnwait(fpsent *d)
    {
        return max(0, RESPAWNSECS-(lastmillis-d->lastpain)/1000);
    }

    void pickspawn(fpsent *d)
    {
        findplayerspawn(d, -1, collectteambase(d->team));
    }

    bool aicheck(fpsent *d, ai::aistate &b)
    {
        if(ai::badhealth(d)) return false;
        int team = collectteambase(d->team), best = -1;
        float bestdist = 1e16f;
        if(d->tokens > 0)
        {
            loopv(bases)
            {
                base &b = bases[i];
                if(b.team == team) continue;
                float dist = d->o.dist(b.o);
                if(best < 0 || dist < bestdist) { best = i; bestdist = dist; }
            }
            if(best < 0 || !ai::makeroute(d, b, bases[best].o)) return false;
            d->ai->switchstate(b, ai::AI_S_PURSUE, ai::AI_T_AFFINITY, -(best+1));
        } else
        {
            loopv(tokens)
            {
                token &t = tokens[i];
                float dist = d->o.dist(t.o)/(t.team != team && (t.team > 0 || -t.team == team) ? 10.0f : 1.0f);
                if(best < 0 || dist < bestdist) { best = i; bestdist = dist; }
            }
            if(best < 0 || !ai::makeroute(d, b, tokens[best].o)) return false;
            d->ai->switchstate(b, ai::AI_S_PURSUE, ai::AI_T_AFFINITY, tokens[best].id);
        }
        return true;
    }

    void aifind(fpsent *d, ai::aistate &b, vector<ai::interest> &interests)
    {
        vec pos = d->feetpos();
        int team = collectteambase(d->team);
        if(d->tokens > 0)
        {
            loopv(bases)
            {
                base &b = bases[i];
                if(b.team == team) continue;
                ai::interest &n = interests.add();
                n.state = ai::AI_S_PURSUE;
                n.node = ai::closestwaypoint(b.o, ai::SIGHTMIN, true);
                n.target = -(i+1);
                n.targtype = ai::AI_T_AFFINITY;
                n.score = pos.squaredist(b.o)/(d->tokens > 2 ? 1e3f : 1e2f);
            }
        }
        if(d->tokens < TOKENLIMIT) loopv(tokens)
        {
            token &t = tokens[i];
            ai::interest &n = interests.add();
            n.state = ai::AI_S_PURSUE;
            n.node = ai::closestwaypoint(t.o, ai::SIGHTMIN, true);
            n.target = t.id;
            n.targtype = ai::AI_T_AFFINITY;
            n.score = pos.squaredist(t.o)/(t.team != team && (t.team > 0 || -t.team == team) ? 10.0f : 1.0f);
        }
    }

    bool aipursue(fpsent *d, ai::aistate &b)
    {
        if(b.target < 0)
        {
            if(d->tokens <= 0 || !bases.inrange(-(b.target+1))) return false;
            base &g = bases[-(b.target+1)];
            if(g.team == collectteambase(d->team)) return false;
            return ai::makeroute(d, b, g.o);
        } else if(b.target > 0)
        {
            token *t = findtoken(b.target);
            if(t) return ai::makeroute(d, b, t->o);
        }
        return false;
    }

    bool parse_network_message(int type, ucharbuf &p) override
    {
        switch(type)
        {
            case N_INITTOKENS:
                parsetokens(p, m_collect);
                return true;

            case N_TAKETOKEN:
            {
                int ocn = getint(p), id = getint(p), total = getint(p);
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                if(o && m_collect) taketoken(o, id, total);
                return true;
            }

            case N_EXPIRETOKENS:
                for(;;)
                {
                    int id = getint(p);
                    if(p.overread() || id < 0) return true;
                    if(m_collect) expiretoken(id);
                }
                return true;

            case N_DROPTOKENS:
            {
                int ocn = getint(p);
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                vec droploc;
                loopk(3) droploc[k] = getint(p)/DMF;
                for(int n = 0;; n++)
                {
                    int id = getint(p);
                    if(id < 0) return true;
                    int team = getint(p), yaw = getint(p);
                    if(p.overread()) return true;
                    if(o && m_collect) droptoken(o, id, droploc, team, yaw, n);
                }
                return true;
            }

            case N_STEALTOKENS:
            {
                int ocn = getint(p), team = getint(p), basenum = getint(p), enemyteam = getint(p), score = getint(p);
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                vec droploc;
                loopk(3) droploc[k] = getint(p)/DMF;
                for(int n = 0;; n++)
                {
                    int id = getint(p);
                    if(id < 0) return true;
                    int yaw = getint(p);
                    if(p.overread()) return true;
                    if(o && m_collect) stealtoken(o, id, droploc, team, yaw, n, basenum, enemyteam, score);
                }
                return true;
            }

            case N_DEPOSITTOKENS:
            {
                int ocn = getint(p), base = getint(p), deposited = getint(p), team = getint(p), score = getint(p), flags = getint(p);
                fpsent *o = ocn==player1->clientnum ? player1 : newclient(ocn);
                if(o && m_collect) deposittokens(o, base, deposited, team, score, flags);
                return true;
            }
        }
        return false;
    }
};

} // ns game
