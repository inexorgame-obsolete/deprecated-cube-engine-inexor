#pragma once
#include "inexor/fpsgame/game.hpp"
#include "inexor/gamemode/collect_common.hpp"
#include "inexor/gamemode/gamemode_server.hpp"

namespace server {

struct collectservermode : servmode, collectmode_common
{
    token &droptoken(const vec &o, int yaw, int team, int droptime, int dropper)
    {
        token &t = collectmode_common::droptoken(o, team, droptime);
        if(++nexttoken < 0) nexttoken = 1;
        t.id = nexttoken;
        t.dropper = dropper;
        t.yaw = yaw;
        return t;
    }
    bool notgotbases = false;

    void reset(bool empty)
    {
        resetbases();
        notgotbases = !empty;
    }

    void cleanup()
    {
        reset(false);
    }

    void setup()
    {
        reset(false);
        if(notgotitems || ments.empty()) return;
        loopv(ments)
        {
            entity &e = ments[i];
            if(e.type != FLAG || e.attr2 < 1 || e.attr2 > 2) continue;
            if(!addbase(bases.length(), e.o, e.attr2)) break;
        }
        notgotbases = false;
    }

    void newmap()
    {
        reset(true);
    }

#if 0
    void losetokens(clientinfo *ci)
    {
        if(notgotbases || ci->state.tokens <= 0) return;
        sendf(-1, 1, "ri2", N_LOSETOKENS, ci->clientnum);
        ci->state.tokens = 0;
    }
#endif

    void droptokens(clientinfo *ci, bool penalty = false)
    {
        if(notgotbases) return;
        int team = collectteambase(ci->team), totalenemy = penalty ? 0 : ci->state.tokens, totalfriendly = 1, expired = 0;
        packetbuf p(300, ENET_PACKET_FLAG_RELIABLE);
        loopvrev(tokens)
        {
            token &t = tokens[i];
            if(t.dropper == ci->clientnum && (t.team == team ? ++totalfriendly > TOKENLIMIT : ++totalenemy > TOKENLIMIT))
            {
                if(!expired) putint(p, N_EXPIRETOKENS);
                expired++;
                putint(p, t.id);
                tokens.removeunordered(i);
            }
        }
        if(expired) putint(p, -1);
        putint(p, N_DROPTOKENS);
        putint(p, ci->clientnum);
        putint(p, int(ci->state.o.x*DMF));
        putint(p, int(ci->state.o.y*DMF));
        putint(p, int(ci->state.o.z*DMF));
        int numdrops = 1 + (penalty ? 0 : ci->state.tokens), yaw = rnd(360);
        loopi(numdrops)
        {
            token &t = droptoken(ci->state.o, yaw + (i*360)/numdrops, !i ? team : -team, lastmillis, ci->clientnum);
            putint(p, t.id);
            putint(p, t.team);
            putint(p, t.yaw);
        }
        putint(p, -1);
        sendpacket(-1, 1, p.finalize());
        ci->state.tokens = 0;
    }

    void leavegame(clientinfo *ci, bool disconnecting = false)
    {
        ci->state.tokens = 0;
        if(disconnecting)
        {
            int team = collectteambase(ci->team), totalfriendly = 0, totalenemy = 0;
            loopvrev(tokens)
            {
                token &t = tokens[i];
                if(t.dropper == ci->clientnum) t.dropper = INT_MIN; else if(t.dropper > INT_MIN) continue;
                if(t.team == team ? ++totalfriendly > UNOWNEDTOKENLIMIT : ++totalenemy > UNOWNEDTOKENLIMIT)
                {
                    packetbuf p(300, ENET_PACKET_FLAG_RELIABLE);
                    putint(p, N_EXPIRETOKENS);
                    putint(p, t.id);
                    tokens.removeunordered(i);
                    while(--i >= 0)
                    {
                        token &t = tokens[i];
                        if(t.dropper == ci->clientnum) t.dropper = INT_MIN; else if(t.dropper > INT_MIN) continue;
                        if(t.team == team ? ++totalfriendly > UNOWNEDTOKENLIMIT : ++totalenemy > UNOWNEDTOKENLIMIT)
                        {
                            putint(p, t.id);
                            tokens.removeunordered(i);
                        }
                    }
                    putint(p, -1);
                    sendpacket(-1, 1, p.finalize());
                }
            }
        }
    }

    void died(clientinfo *ci, clientinfo *actor)
    {
        droptokens(ci, !actor || isteam(actor->team, ci->team));
    }

    bool canspawn(clientinfo *ci, bool connecting)
    {
        return connecting || !ci->state.lastdeath || gamemillis+curtime-ci->state.lastdeath >= RESPAWNSECS*1000;
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
        return collectteambase(newteam) > 0;
    }

    void changeteam(clientinfo *ci, const char *oldteam, const char *newteam)
    {
    }

    void deposittokens(clientinfo *ci, int basenum)
    {
        if(notgotbases || !bases.inrange(basenum) || ci->state.state!=CS_ALIVE || !ci->team[0]) return;
        base &b = bases[basenum];
        if(!collectbaseteam(b.team)) return;
        int team = collectteambase(ci->team);
        if(b.team==team) return;
        if(ci->state.tokens > 0)
        {
            b.laststeal = gamemillis;
            ci->state.flags += ci->state.tokens;
            int score = addscore(team, ci->state.tokens);
            sendf(-1, 1, "ri7", N_DEPOSITTOKENS, ci->clientnum, basenum, ci->state.tokens, team, score, ci->state.flags);
            ci->state.tokens = 0;
            if(score >= SCORELIMIT) startintermission();
        } else
        {
            if(gamemillis < b.laststeal + STEALTOKENTIME) return;
            if(totalscore(b.team) <= 0) return;
            int stolen = 0;
            loopv(tokens) if(tokens[i].dropper == -1 - basenum) stolen++;
            if(stolen < TOKENLIMIT)
            {
                b.laststeal = gamemillis;
                int score = addscore(b.team, -1);
                token &t = droptoken(b.o, rnd(360), team, lastmillis, -1 - basenum);
                sendf(-1, 1, "ri9i3", N_STEALTOKENS, ci->clientnum, team, basenum, b.team, score, int(t.o.x*DMF), int(t.o.y*DMF), int(t.o.z*DMF), t.id, t.yaw, -1);
            }
        }
    }

    void taketoken(clientinfo *ci, int id)
    {
        if(notgotbases || ci->state.state!=CS_ALIVE || !ci->team[0]) return;
        token *t = findtoken(id);
        if(!t) return;
        int team = collectteambase(ci->team);
        if(t->team != team && (t->team > 0 || -t->team == team) && ci->state.tokens < TOKENLIMIT) ci->state.tokens++;
        sendf(-1, 1, "ri4", N_TAKETOKEN, ci->clientnum, id, ci->state.tokens);
    }

    void update()
    {
        if(gamemillis>=gamelimit || notgotbases) return;
        vector<int> resets;
        loopvrev(tokens)
        {
            token &t = tokens[i];
            if(lastmillis - t.droptime >= EXPIRETOKENTIME)
            {
                resets.add(t.id);
                tokens.removeunordered(i);
            }
        }
        if(resets.length())
            sendf(-1, 1, "rivi", N_EXPIRETOKENS, resets.length(), resets.getbuf(), -1);
    }

    void initclient(clientinfo *ci, packetbuf &p, bool connecting)
    {
        putint(p, N_INITTOKENS);
        loopk(2) putint(p, scores[k]);
        putint(p, tokens.length());
        loopv(tokens)
        {
            token &t = tokens[i];
            putint(p, t.id);
            putint(p, t.team);
            putint(p, t.yaw);
            putint(p, int(t.o.x*DMF));
            putint(p, int(t.o.y*DMF));
            putint(p, int(t.o.z*DMF));
        }
        loopv(clients) if(clients[i]->state.state == CS_ALIVE && clients[i]->state.tokens > 0)
        {
            putint(p, clients[i]->clientnum);
            putint(p, clients[i]->state.tokens);
        }
        putint(p, -1);
    }

    void parsebases(ucharbuf &p, bool commit)
    {
        int numbases = getint(p);
        loopi(numbases)
        {
            int team = getint(p);
            vec o;
            loopk(3) o[k] = max(getint(p)/DMF, 0.0f);
            if(p.overread()) break;
            if(commit && notgotbases)
            {
                addbase(i, o, team);
            }
        }
        if(commit && notgotbases)
        {
            notgotbases = false;
        }
    }

    bool parse_network_message(int type, clientinfo *ci, clientinfo *cq, packetbuf &p) override
    {
        switch(type)
        {
            case N_INITTOKENS:
                parsebases(p, (ci->state.state!=CS_SPECTATOR || ci->privilege || ci->local) && !strcmp(ci->clientmap, smapname));
                return true;

            case N_TAKETOKEN:
            {
                int id = getint(p);
                if((ci->state.state!=CS_SPECTATOR || ci->local || ci->privilege) && cq) taketoken(cq, id);
                return true;
            }

            case N_DEPOSITTOKENS:
            {
                int id = getint(p);
                if((ci->state.state!=CS_SPECTATOR || ci->local || ci->privilege) && cq) deposittokens(cq, id);
                return true;
            }
        }
        return false;
    }
};



} // ns server
