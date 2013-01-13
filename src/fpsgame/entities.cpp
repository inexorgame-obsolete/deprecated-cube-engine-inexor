#include "game.h"

namespace entities
{
    using namespace game;

    int extraentinfosize() { return 0; }       // size in bytes of what the 2 methods below read/write... so it can be skipped by other games

    void writeent(entity &e, char *buf)   // write any additional data to disk (except for ET_ ents)
    {
    }

    void readent(entity &e, char *buf, int ver)     // read from disk, and init
    {
        if(ver <= 30) switch(e.type)
        {
            case FLAG:
            case MONSTER:
            case TELEDEST:
            case RESPAWNPOINT:
            case BOX:
            case BARREL:
            case OBSTACLE:
            case PLATFORM:
            case ELEVATOR:
                e.attr1 = (int(e.attr1)+180)%360;
                break;
        }
        if(ver <= 31) switch(e.type)
        {
            case BOX:
            case BARREL:
            case OBSTACLE:
            case PLATFORM:
            case ELEVATOR:
                int yaw = (int(e.attr1)%360 + 360)%360 + 7; 
                e.attr1 = yaw - yaw%15;
                break;
        }
    }

#ifndef STANDALONE
    vector<extentity *> ents;

    vector<extentity *> &getents() { return ents; }

    bool mayattach(extentity &e) { return false; }
    bool attachent(extentity &e, extentity &a) { return false; }

    const char *itemname(int i)
    {
        int t = ents[i]->type;
        if(t>=I_BOMBS && t<=I_BOMBDELAY) {
            return itemstats[P_AMMO_BO+t-I_BOMBS].name;
        } else if (t>=I_SHELLS && t<=I_QUAD) {
            return itemstats[t-I_SHELLS].name;
        } else {
            return NULL;
        }
    }

    int itemicon(int i)
    {
        int t = ents[i]->type;
        if(t>=I_BOMBS && t<=I_BOMBDELAY) {
            return itemstats[P_AMMO_BO+t-I_BOMBS].icon;
        } else if (t>=I_SHELLS && t<=I_QUAD) {
            return itemstats[t-I_SHELLS].icon;
        } else {
            return -1;
        }
    }

    const char *entmdlname(int type)
    {
        static const char *entmdlnames[] =
        {
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            "ammo/shells", "ammo/bullets", "ammo/rockets", "ammo/rrounds", "ammo/grenades", "ammo/cartridges",
            "health", "boost", "armor/green", "armor/yellow", "quad", "teleporter",
            NULL, NULL,
            "carrot",
            NULL, NULL,
            "checkpoint",
            NULL, NULL,
            NULL, NULL,
            NULL,
            "ammo/bombs", "ammo/bombradius", "ammo/bombdelay", NULL, NULL, NULL, NULL, NULL, // bomb
            NULL, //obstacle
            NULL, NULL, NULL, // race
            NULL, NULL, NULL, NULL // physics
        };
        return entmdlnames[type];
    }

    const char *entmodel(const entity &e)
    {
        if(e.type == TELEPORT)
        {
            if(e.attr2 > 0) return mapmodelname(e.attr2);
            if(e.attr2 < 0) return NULL;
        }
        return e.type < MAXENTTYPES ? entmdlname(e.type) : NULL;
    }

    void preloadentities()
    {
        loopi(MAXENTTYPES)
        {
            switch(i)
            {
                case I_SHELLS: case I_BULLETS: case I_ROCKETS: case I_ROUNDS: case I_GRENADES: case I_CARTRIDGES:
                    if(m_noammo) continue;
                    break;
                case I_HEALTH: case I_BOOST: case I_GREENARMOUR: case I_YELLOWARMOUR: case I_QUAD:
                    if(m_noitems) continue;
                    break;
                case CARROT: case RESPAWNPOINT:
                    if(!m_classicsp) continue;
                    break;
                case RACE_START: case RACE_FINISH: case RACE_CHECKPOINT:
                    if(!m_race) continue;
                    break;
                case I_BOMBS: case I_BOMBRADIUS: case I_BOMBDELAY: case I_BOMBRESERVED2: case I_BOMBRESERVED3: case I_BOMBRESERVED4: case I_BOMBRESERVED5: case I_BOMBRESERVED6:
                    if(!m_bomb) continue;
                    break;
            }
            const char *mdl = entmdlname(i);
            if(!mdl) continue;
            preloadmodel(mdl);
        }
        loopv(ents)
        {
            extentity &e = *ents[i];
            switch(e.type)
            {
                case TELEPORT:
                    if(e.attr2 > 0) preloadmodel(mapmodelname(e.attr2));
                case JUMPPAD:
                    if(e.attr4 > 0) preloadmapsound(e.attr4);
                    break;
            }
        }
    }

    void renderentities()
    {
        loopv(ents)
        {
            extentity &e = *ents[i];
            int revs = 10;
            switch(e.type)
            {
                case CARROT:
                case RESPAWNPOINT:
                    if(e.attr2) revs = 1;
                    break;
                case TELEPORT:
                    if(e.attr2 < 0) continue;
                    break;
                default:
                    if(!e.spawned) continue;
                    if(m_bomb) {
                        if(!e.spawned || e.type < I_BOMBS || e.type > I_BOMBDELAY) continue;
                    } else {
                        if(!e.spawned || e.type < I_SHELLS || e.type > I_QUAD) continue;
                    }
            }
            const char *mdlname = entmodel(e);
            if(mdlname)
            {
                vec p = e.o;
                p.z += 1+sinf(lastmillis/100.0+e.o.x+e.o.y)/20;
                rendermodel(&e.light, mdlname, ANIM_MAPMODEL|ANIM_LOOP, p, lastmillis/(float)revs, 0, MDL_SHADOW | MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED);
            }
        }
    }

    void addammo(int type, int &v, bool local)
    {
        int tindex = type-I_SHELLS;
        if(type==I_BOMBS) tindex = 11;
        itemstat &is = itemstats[tindex];
        v += is.add;
        if(v>is.max) v = is.max;
        if(local) msgsound(is.sound);
    }

    void repammo(fpsent *d, int type, bool local)
    {
    	if(type==I_BOMBS) addammo(type, d->ammo[GUN_BOMB], local);
    	else addammo(type, d->ammo[type-I_SHELLS+GUN_SG], local);
    }

    // these two functions are called when the server acknowledges that you really
    // picked up the item (in multiplayer someone may grab it before you).

    void pickupeffects(int n, fpsent *d)
    {
        if(!ents.inrange(n)) return;
        int type = ents[n]->type;
        if (m_bomb && (type<I_BOMBS || type>I_BOMBDELAY)) return;
        else if (!m_bomb && (type<I_SHELLS || type>I_QUAD)) return;
        ents[n]->spawned = false;
        if(!d) return;
        int tindex = type-I_SHELLS;
        if(type>=I_BOMBS) tindex = 11+type-I_BOMBS;
        itemstat &is = itemstats[tindex];
        if(d!=player1 || isthirdperson())
        {
            //particle_text(d->abovehead(), is.name, PART_TEXT, 2000, 0xFFC864, 4.0f, -8);
            // TODO: bomb items switch
            particle_icon(d->abovehead(), is.icon%4, is.icon/4, PART_HUD_ICON_GREY, 2000, 0xFFFFFF, 2.0f, -8);
        }
        playsound(itemstats[type-I_SHELLS].sound, d!=player1 ? &d->o : NULL, NULL, 0, 0, 0, -1, 0, 1500);
        d->pickup(type);
        if(d==player1) switch(type)
        {
            case I_BOOST:
                conoutf(CON_GAMEINFO, "\f2you have a permanent +10 health bonus! (%d)", d->maxhealth);
                playsound(S_V_BOOST, NULL, NULL, 0, 0, 0, -1, 0, 3000);
                break;

            case I_QUAD:
                conoutf(CON_GAMEINFO, "\f2you got the quad!");
                playsound(S_V_QUAD, NULL, NULL, 0, 0, 0, -1, 0, 3000);
                break;

            case I_BOMBRADIUS:
                conoutf(CON_GAMEINFO, "\f2you have a permanent +1 damage radius bonus!");
                playsound(S_V_QUAD, NULL, NULL, 0, 0, -1, 0, 3000); // TODO: other sound
                break;

            case I_BOMBDELAY:
                conoutf(CON_GAMEINFO, "\f2your bombs explodes faster!");
                playsound(S_ITEMHEALTH, NULL, NULL, 0, 0, -1, 0, 3000);
                break;
        }
    }

    // these functions are called when the client touches the item

    void teleporteffects(fpsent *d, int tp, int td, bool local)
    {
        if(ents.inrange(tp) && ents[tp]->type == TELEPORT)
        {
            extentity &e = *ents[tp];
            if(e.attr4 >= 0) 
            {
                int snd = S_TELEPORT, flags = 0;
                if(e.attr4 > 0) { snd = e.attr4; flags = SND_MAP; }
                if(d == player1) playsound(snd, NULL, NULL, flags);
                else
                {
                    playsound(snd, &e.o, NULL, flags);
                    if(ents.inrange(td) && ents[td]->type == TELEDEST) playsound(snd, &ents[td]->o, NULL, flags);
                }
            }
        }
        if(local && d->clientnum >= 0)
        {
            sendposition(d);
            packetbuf p(32, ENET_PACKET_FLAG_RELIABLE);
            putint(p, N_TELEPORT);
            putint(p, d->clientnum);
            putint(p, tp);
            putint(p, td);
            sendclientpacket(p.finalize(), 0);
            flushclient();
        }
    }

    void jumppadeffects(fpsent *d, int jp, bool local)
    {
        if(ents.inrange(jp) && ents[jp]->type == JUMPPAD)
        {
            extentity &e = *ents[jp];
            if(e.attr4 >= 0)
            {
                int snd = S_JUMPPAD, flags = 0;
                if(e.attr4 > 0) { snd = e.attr4; flags = SND_MAP; }
                if(d == player1) playsound(snd, NULL, NULL, flags);
                else playsound(snd, &e.o, NULL, flags);
            }
        }
        if(local && d->clientnum >= 0)
        {
            sendposition(d);
            packetbuf p(16, ENET_PACKET_FLAG_RELIABLE);
            putint(p, N_JUMPPAD);
            putint(p, d->clientnum);
            putint(p, jp);
            sendclientpacket(p.finalize(), 0);
            flushclient();
        }
    }

    void teleport(int n, fpsent *d)     // also used by monsters
    {
        int e = -1, tag = ents[n]->attr1, beenhere = -1;
        for(;;)
        {
            e = findentity(TELEDEST, e+1);
            if(e==beenhere || e<0) { conoutf(CON_WARN, "no teleport destination for tag %d", tag); return; }
            if(beenhere<0) beenhere = e;
            if(ents[e]->attr2==tag)
            {
                teleporteffects(d, n, e, true);
                d->o = ents[e]->o;
                d->yaw = ents[e]->attr1;
                if(ents[e]->attr3 > 0)
                {
                    vec dir;
                    vecfromyawpitch(d->yaw, 0, 1, 0, dir);
                    float speed = d->vel.magnitude2();
                    d->vel.x = dir.x*speed;
                    d->vel.y = dir.y*speed;
                }
                else d->vel = vec(0, 0, 0);
                entinmap(d);
                updatedynentcache(d);
                ai::inferwaypoints(d, ents[n]->o, ents[e]->o, 16.f);
                break;
            }
        }
    }

    void trypickup(int n, fpsent *d)
    {
        switch(ents[n]->type)
        {
            default:
                if(d->canpickup(ents[n]->type))
                {
                    addmsg(N_ITEMPICKUP, "rci", d, n);
                    ents[n]->spawned = false; // even if someone else gets it first
                }
                break;

            case RACE_FINISH:
                if (m_race) {
                    addmsg(N_RACEFINISH, "rc", d);
                }
                d->lastpickup = ents[n]->type;
                d->lastpickupindex = n;
                d->lastpickupmillis = lastmillis;
                break;

            case RACE_START:
                if (m_race) {
                    addmsg(N_RACESTART, "rc", d);
                }
                d->lastpickup = ents[n]->type;
                d->lastpickupindex = n;
                d->lastpickupmillis = lastmillis;
                break;

            case RACE_CHECKPOINT:
                if (m_race) {
                    addmsg(N_RACECHECKPOINT, "rci", d, ents[n]->attr2);
                }
                d->lastpickup = ents[n]->type;
                d->lastpickupindex = n;
                d->lastpickupmillis = lastmillis;
                break;

            case TELEPORT:
            {
                if(d->lastpickup==ents[n]->type && lastmillis-d->lastpickupmillis<500) break;
                if(ents[n]->attr3 > 0)
                {
                    defformatstring(hookname)("can_teleport_%d", ents[n]->attr3);
                    if(identexists(hookname) && !execute(hookname)) break;
                }
                d->lastpickup = ents[n]->type;
                d->lastpickupindex = n;
                d->lastpickupmillis = lastmillis;
                teleport(n, d);
                break;
            }

            case RESPAWNPOINT:
                if(d!=player1) break;
                if(n==respawnent) break;
                respawnent = n;
                conoutf(CON_GAMEINFO, "\f2respawn point set!");
                playsound(S_V_RESPAWNPOINT);
                break;

            case JUMPPAD:
            {
                if(d->lastpickup==ents[n]->type && lastmillis-d->lastpickupmillis<300) break;
                d->lastpickup = ents[n]->type;
                d->lastpickupindex = n;
                d->lastpickupmillis = lastmillis;
                jumppadeffects(d, n, true);
                vec v((int)(char)ents[n]->attr3*10.0f, (int)(char)ents[n]->attr2*10.0f, ents[n]->attr1*12.5f);
                if(d->ai) d->ai->becareful = true;
                d->falling = vec(0, 0, 0);
                d->physstate = PHYS_FALL;
                d->timeinair = 1;
                d->vel = v;
                break;
            }

        }
    }

    void checkitems(fpsent *d)
    {
        if(d->state!=CS_ALIVE) return;
        vec o = d->feetpos();
        loopv(ents)
        {
            extentity &e = *ents[i];
            if(e.type==NOTUSED) continue;
            if(!e.spawned && e.type!=TELEPORT && e.type!=JUMPPAD && e.type!=RESPAWNPOINT && (m_race && e.type!=RACE_START && e.type!=RACE_FINISH && e.type!=RACE_CHECKPOINT) ) continue;
            float dist = e.o.dist(o);
            if(dist<(e.type==TELEPORT ? 16 : 12)) trypickup(i, d);
        }
    }

    void checkphysics(fpsent *d)
    {
        float p_gravity = 0.0f;
        float p_friction_land = 0.0f;
        float p_jumpvel = 0.0f;
        float p_playerspeed = 0.0f;
        loopv(ents) {
            extentity &e = *ents[i];
            if(e.type < P_GRAVITY || e.type > P_SPEED) continue;
            float dist = camera1->o.dist(e.o);
            if(dist < e.attr2) {
                /*
                float addval = ((float) e.attr3) / ((dist*dist)/100); // physics influence depends on distance
                e.attr3 < 0 ? addval = max((float) e.attr3, addval) : min((float) e.attr3, addval);
                */
                float addval = (float) e.attr3;
                switch(e.type) {
                    case P_GRAVITY:
                        p_gravity += addval;
                        // conoutf("+ attr1:%d attr2:%d attr3:%d p_gravity:%1.2f", e.attr1, e.attr2, e.attr3, p_gravity);
                        break;
                    case P_FRICTION:
                        p_friction_land += addval;
                        break;
                    case P_JUMP:
                        p_jumpvel += addval;
                        break;
                    case P_SPEED:
                        p_playerspeed += addval;
                        break;
                    default:
                        break;
                }
            }
        }
        d->p_gravity = p_gravity;
        d->p_friction_land = p_friction_land;
        d->p_jumpvel = p_jumpvel;
        d->p_playerspeed = p_playerspeed;
        // conoutf("physics manipulation: gravity:%1.2f friction:%1.2f jump:%1.2f speed:%1.2f", d->p_gravity, d->p_friction_land, d->p_jumpvel, d->p_playerspeed);
    }

    void checkquad(int time, fpsent *d)
    {
        if(d->quadmillis && (d->quadmillis -= time)<=0)
        {
            d->quadmillis = 0;
            playsound(S_PUPOUT, d==player1 ? NULL : &d->o);
            if(d==player1) conoutf(CON_GAMEINFO, "\f2quad damage is over");
        }
    }

    void putitems(packetbuf &p)            // puts items in network stream and also spawns them locally
    {
        putint(p, N_ITEMLIST);
        loopv(ents) {
            if((m_bomb && ents[i]->type>=I_BOMBS && ents[i]->type<=I_BOMBDELAY) || (!m_bomb && ents[i]->type>=I_SHELLS && ents[i]->type<=I_QUAD)) {
                putint(p, i);
                putint(p, ents[i]->type);
            }
            if(!m_noammo && ents[i]->type>=I_HEALTH && ents[i]->type<=I_QUAD) {
                putint(p, i);
                putint(p, ents[i]->type);
            }
        }
        putint(p, -1);
    }

    void resetspawns() { loopv(ents) ents[i]->spawned = false; }

    void spawnitems(bool force)
    {
        if(m_noitems) return;
        loopv(ents) {
            if((m_bomb  && ents[i]->type>=I_BOMBS && ents[i]->type<=I_BOMBDELAY) || (!m_bomb && ents[i]->type>=I_SHELLS && ents[i]->type<=I_QUAD)) {
                ents[i]->spawned = force || m_sp || !server::delayspawn(ents[i]->type);
            }
            if(!m_noammo && ents[i]->type>=I_HEALTH && ents[i]->type<=I_QUAD) {
                ents[i]->spawned = force || m_sp || !server::delayspawn(ents[i]->type);
            }
        }
    }

    void setspawn(int i, bool on) { if(ents.inrange(i)) ents[i]->spawned = on; }

    extentity *newentity() { return new fpsentity(); }
    void deleteentity(extentity *e) { delete (fpsentity *)e; }

    void clearents()
    {
        while(ents.length()) deleteentity(ents.pop());
    }

    enum
    {
        TRIG_COLLIDE    = 1<<0,
        TRIG_TOGGLE     = 1<<1,
        TRIG_ONCE       = 0<<2,
        TRIG_MANY       = 1<<2,
        TRIG_DISAPPEAR  = 1<<3,
        TRIG_AUTO_RESET = 1<<4,
        TRIG_RUMBLE     = 1<<5,
        TRIG_LOCKED     = 1<<6,
        TRIG_ENDSP      = 1<<7
    };

    static const int NUMTRIGGERTYPES = 32;

    static const int triggertypes[NUMTRIGGERTYPES] =
    {
        -1,
        TRIG_ONCE,                    // 1
        TRIG_RUMBLE,                  // 2
        TRIG_TOGGLE,                  // 3
        TRIG_TOGGLE | TRIG_RUMBLE,    // 4
        TRIG_MANY,                    // 5
        TRIG_MANY | TRIG_RUMBLE,      // 6
        TRIG_MANY | TRIG_TOGGLE,      // 7
        TRIG_MANY | TRIG_TOGGLE | TRIG_RUMBLE,    // 8
        TRIG_COLLIDE | TRIG_TOGGLE | TRIG_RUMBLE, // 9
        TRIG_COLLIDE | TRIG_TOGGLE | TRIG_AUTO_RESET | TRIG_RUMBLE, // 10
        TRIG_COLLIDE | TRIG_TOGGLE | TRIG_LOCKED | TRIG_RUMBLE,     // 11
        TRIG_DISAPPEAR,               // 12
        TRIG_DISAPPEAR | TRIG_RUMBLE, // 13
        TRIG_DISAPPEAR | TRIG_COLLIDE | TRIG_LOCKED, // 14
        -1 /* reserved 15 */,
        -1 /* reserved 16 */,
        -1 /* reserved 17 */,
        -1 /* reserved 18 */,
        -1 /* reserved 19 */,
        -1 /* reserved 20 */,
        -1 /* reserved 21 */,
        -1 /* reserved 22 */,
        -1 /* reserved 23 */,
        -1 /* reserved 24 */,
        -1 /* reserved 25 */,
        -1 /* reserved 26 */,
        -1 /* reserved 27 */,
        -1 /* reserved 28 */,
        TRIG_DISAPPEAR | TRIG_RUMBLE | TRIG_ENDSP, // 29
        -1 /* reserved 30 */,
        -1 /* reserved 31 */,
    };

    #define validtrigger(type) (triggertypes[(type) & (NUMTRIGGERTYPES-1)]>=0)
    #define checktriggertype(type, flag) (triggertypes[(type) & (NUMTRIGGERTYPES-1)] & (flag))

    static inline void setuptriggerflags(fpsentity &e)
    {
        e.flags = extentity::F_ANIM;
        if(checktriggertype(e.attr3, TRIG_COLLIDE|TRIG_DISAPPEAR)) e.flags |= extentity::F_NOSHADOW;
        if(!checktriggertype(e.attr3, TRIG_COLLIDE)) e.flags |= extentity::F_NOCOLLIDE;
        switch(e.triggerstate)
        {
            case TRIGGERING:
                if(checktriggertype(e.attr3, TRIG_COLLIDE) && lastmillis-e.lasttrigger >= 500) e.flags |= extentity::F_NOCOLLIDE;
                break;
            case TRIGGERED:
                if(checktriggertype(e.attr3, TRIG_COLLIDE)) e.flags |= extentity::F_NOCOLLIDE;
                break;
            case TRIGGER_DISAPPEARED:
                e.flags |= extentity::F_NOVIS | extentity::F_NOCOLLIDE;
                break;
        }
    }

    void resettriggers()
    {
        loopv(ents)
        {
            fpsentity &e = *(fpsentity *)ents[i];
            if(e.type != ET_MAPMODEL || !validtrigger(e.attr3)) continue;
            e.triggerstate = TRIGGER_RESET;
            e.lasttrigger = 0;
            setuptriggerflags(e);
        }
    }

    void unlocktriggers(int tag, int oldstate = TRIGGER_RESET, int newstate = TRIGGERING)
    {
        loopv(ents)
        {
            fpsentity &e = *(fpsentity *)ents[i];
            if(e.type != ET_MAPMODEL || !validtrigger(e.attr3)) continue;
            if(e.attr4 == tag && e.triggerstate == oldstate && checktriggertype(e.attr3, TRIG_LOCKED))
            {
                if(newstate == TRIGGER_RESETTING && checktriggertype(e.attr3, TRIG_COLLIDE) && overlapsdynent(e.o, 20)) continue;
                e.triggerstate = newstate;
                e.lasttrigger = lastmillis;
                if(checktriggertype(e.attr3, TRIG_RUMBLE)) playsound(S_RUMBLE, &e.o);
            }
        }
    }

    ICOMMAND(trigger, "ii", (int *tag, int *state),
    {
        if(*state) unlocktriggers(*tag);
        else unlocktriggers(*tag, TRIGGERED, TRIGGER_RESETTING);
    });

    VAR(triggerstate, -1, 0, 1);

    void doleveltrigger(int trigger, int state)
    {
        defformatstring(aliasname)("level_trigger_%d", trigger);
        if(identexists(aliasname))
        {
            triggerstate = state;
            execute(aliasname);
        }
    }

    void checktriggers()
    {
        if(player1->state != CS_ALIVE) return;
        vec o = player1->feetpos();
        loopv(ents)
        {
            fpsentity &e = *(fpsentity *)ents[i];
            if(e.type != ET_MAPMODEL || !validtrigger(e.attr3)) continue;
            switch(e.triggerstate)
            {
                case TRIGGERING:
                case TRIGGER_RESETTING:
                    if(lastmillis-e.lasttrigger>=1000)
                    {
                        if(e.attr4)
                        {
                            if(e.triggerstate == TRIGGERING) unlocktriggers(e.attr4);
                            else unlocktriggers(e.attr4, TRIGGERED, TRIGGER_RESETTING);
                        }
                        if(checktriggertype(e.attr3, TRIG_DISAPPEAR)) e.triggerstate = TRIGGER_DISAPPEARED;
                        else if(e.triggerstate==TRIGGERING && checktriggertype(e.attr3, TRIG_TOGGLE)) e.triggerstate = TRIGGERED;
                        else e.triggerstate = TRIGGER_RESET;
                    }
                    setuptriggerflags(e);
                    break;
                case TRIGGER_RESET:
                    if(e.lasttrigger)
                    {
                        if(checktriggertype(e.attr3, TRIG_AUTO_RESET|TRIG_MANY|TRIG_LOCKED) && e.o.dist(o)-player1->radius>=(checktriggertype(e.attr3, TRIG_COLLIDE) ? 20 : 12))
                            e.lasttrigger = 0;
                        break;
                    }
                    else if(e.o.dist(o)-player1->radius>=(checktriggertype(e.attr3, TRIG_COLLIDE) ? 20 : 12)) break;
                    else if(checktriggertype(e.attr3, TRIG_LOCKED))
                    {
                        if(!e.attr4) break;
                        doleveltrigger(e.attr4, -1);
                        e.lasttrigger = lastmillis;
                        break;
                    }
                    e.triggerstate = TRIGGERING;
                    e.lasttrigger = lastmillis;
                    setuptriggerflags(e);
                    if(checktriggertype(e.attr3, TRIG_RUMBLE)) playsound(S_RUMBLE, &e.o);
                    if(checktriggertype(e.attr3, TRIG_ENDSP)) endsp(false);
                    if(e.attr4) doleveltrigger(e.attr4, 1);
                    break;
                case TRIGGERED:
                    if(e.o.dist(o)-player1->radius<(checktriggertype(e.attr3, TRIG_COLLIDE) ? 20 : 12))
                    {
                        if(e.lasttrigger) break;
                    }
                    else if(checktriggertype(e.attr3, TRIG_AUTO_RESET))
                    {
                        if(lastmillis-e.lasttrigger<6000) break;
                    }
                    else if(checktriggertype(e.attr3, TRIG_MANY))
                    {
                        e.lasttrigger = 0;
                        break;
                    }
                    else break;
                    if(checktriggertype(e.attr3, TRIG_COLLIDE) && overlapsdynent(e.o, 20)) break;
                    e.triggerstate = TRIGGER_RESETTING;
                    e.lasttrigger = lastmillis;
                    setuptriggerflags(e);
                    if(checktriggertype(e.attr3, TRIG_RUMBLE)) playsound(S_RUMBLE, &e.o);
                    if(checktriggertype(e.attr3, TRIG_ENDSP)) endsp(false);
                    if(e.attr4) doleveltrigger(e.attr4, 0);
                    break;
            }
        }
    }

    void animatemapmodel(const extentity &e, int &anim, int &basetime)
    {
        const fpsentity &f = (const fpsentity &)e;
        if(validtrigger(f.attr3)) switch(f.triggerstate)
        {
            case TRIGGER_RESET: anim = ANIM_TRIGGER|ANIM_START; break;
            case TRIGGERING: anim = ANIM_TRIGGER; basetime = f.lasttrigger; break;
            case TRIGGERED: anim = ANIM_TRIGGER|ANIM_END; break;
            case TRIGGER_RESETTING: anim = ANIM_TRIGGER|ANIM_REVERSE; basetime = f.lasttrigger; break;
        }
    }

    void fixentity(extentity &e)
    {
        switch(e.type)
        {
            case FLAG:
            case BOX:
            case BARREL:
            case OBSTACLE:
            case PLATFORM:
            case ELEVATOR:
                e.attr5 = e.attr4;
                e.attr4 = e.attr3;
            case TELEDEST:
            case P_GRAVITY:
            case P_FRICTION:
            case P_JUMP:
            case P_SPEED:
                e.attr3 = e.attr2;
            case MONSTER:
            case RACE_START:
            case RACE_FINISH:
            case RACE_CHECKPOINT:
                e.attr2 = e.attr1;
            case RESPAWNPOINT:
                e.attr1 = (int)player1->yaw;
                break;
        }
    }

    void entradius(extentity &e, bool color)
    {
        int maxcheckpoints = 0;
        switch(e.type)
        {
            case TELEPORT:
                loopv(ents) if(ents[i]->type == TELEDEST && e.attr1==ents[i]->attr2)
                {
                    renderentarrow(e, vec(ents[i]->o).sub(e.o).normalize(), e.o.dist(ents[i]->o));
                    break;
                }
                break;

            case JUMPPAD:
                renderentarrow(e, vec((int)(char)e.attr3*10.0f, (int)(char)e.attr2*10.0f, e.attr1*12.5f).normalize(), 4);
                break;

            case RACE_START:
                loopv(ents) {
                    // successor
                    if(ents[i]->type == RACE_CHECKPOINT && ents[i]->attr2 == 1) {
                        renderentarrow(e, vec(ents[i]->o).sub(e.o).normalize(), e.o.dist(ents[i]->o));
                    }
                    // precessor
                    if(ents[i]->type == RACE_FINISH) {
                        renderentarrow(*ents[i], vec(e.o).sub(ents[i]->o).normalize(), ents[i]->o.dist(e.o));
                    }
                }
                break;

            case RACE_CHECKPOINT:
                loopv(ents) {
                    // successor
                    if(ents[i]->type == RACE_CHECKPOINT && (e.attr2+1) == ents[i]->attr2) {
                        renderentarrow(e, vec(ents[i]->o).sub(e.o).normalize(), e.o.dist(ents[i]->o));
                    }
                    // precessor
                    if(ents[i]->type == RACE_CHECKPOINT && (e.attr2-1) == ents[i]->attr2) {
                        renderentarrow(*ents[i], vec(e.o).sub(ents[i]->o).normalize(), ents[i]->o.dist(e.o));
                    }
                }
                break;

            case RACE_FINISH:
                loopv(ents) if(ents[i]->type == RACE_CHECKPOINT && ents[i]->attr2 > maxcheckpoints) {
                    maxcheckpoints = ents[i]->attr2;
                }
                // successor
                loopv(ents) if(ents[i]->type == RACE_START) {
                    renderentarrow(e, vec(ents[i]->o).sub(e.o).normalize(), e.o.dist(ents[i]->o));
                }
                // precessor
                loopv(ents) if(ents[i]->type == RACE_CHECKPOINT && ents[i]->attr2 == maxcheckpoints) {
                    renderentarrow(*ents[i], vec(e.o).sub(ents[i]->o).normalize(), ents[i]->o.dist(e.o));
                }
                break;

            case P_GRAVITY:
            case P_FRICTION:
            case P_JUMP:
            case P_SPEED:
                renderentsphere(e, e.attr2);
                break;


            case FLAG:
            case MONSTER:
            case TELEDEST:
            case RESPAWNPOINT:
            case BOX:
            case BARREL:
            case OBSTACLE:
            case PLATFORM:
            case ELEVATOR:
            {
                vec dir;
                vecfromyawpitch(e.attr1, 0, 1, 0, dir);
                renderentarrow(e, dir, 4);
                break;
            }
            case MAPMODEL:
                if(validtrigger(e.attr3)) renderentring(e, checktriggertype(e.attr3, TRIG_COLLIDE) ? 20 : 12);
                break;
        }
    }

    bool printent(extentity &e, char *buf)
    {
        return false;
    }

    const char *entnameinfo(entity &e) { return ""; }
    const char *entname(int i)
    {
        static const char *entnames[] =
        {
            "none?", "light", "mapmodel", "playerstart", "envmap", "particles", "sound", "spotlight",
            "shells", "bullets", "rockets", "riflerounds", "grenades", "cartridges",
            "health", "healthboost", "greenarmour", "yellowarmour", "quaddamage",
            "teleport", "teledest",
            "monster", "carrot", "jumppad",
            "base", "respawnpoint",
            "box", "barrel",
            "platform", "elevator",
            "flag",
            "bombs", "bombradius", "bombdelay", "bombreserved2", "bombreserved3", "bombreserved4", "bombreserved5", "bombreserved6",
            "obstacle",
            "start", "finish", "checkpoint",
            "gravity", "friction", "jump", "speed",
            "", "", // two empty strings follows.
        };
        return i>=0 && size_t(i)<sizeof(entnames)/sizeof(entnames[0]) ? entnames[i] : "";
    }

    void editent(int i, bool local)
    {
        extentity &e = *ents[i];
        if(e.type == ET_MAPMODEL && validtrigger(e.attr3))
        {
            fpsentity &f = (fpsentity &)e;
            f.triggerstate = TRIGGER_RESET;
            f.lasttrigger = 0;
            setuptriggerflags(f);
        }
        else e.flags = 0;
        if(local) addmsg(N_EDITENT, "rii3ii5", i, (int)(e.o.x*DMF), (int)(e.o.y*DMF), (int)(e.o.z*DMF), e.type, e.attr1, e.attr2, e.attr3, e.attr4, e.attr5);
    }

    float dropheight(entity &e)
    {
        if(e.type==BASE || e.type==FLAG) return 0.0f;
        return 4.0f;
    }

    bool hasmapmodel(extentity &e)
    {
        if(e.type==MAPMODEL || e.type==BOX || e.type==BARREL || e.type==OBSTACLE) return true;
        return false;
    }
#endif
}

