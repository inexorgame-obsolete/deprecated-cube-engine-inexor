#pragma once

#include "inexor/fpsgame/fpsstate.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/network/legacy/administration.hpp"
#include "inexor/engine/sound.hpp"
#include "inexor/fpsgame/weapon.hpp"
#include "inexor/fpsgame/ai.hpp"


// mostly players can be described with this
struct fpsent : dynent, fpsstate
{
    int weight;                         // affects the effectiveness of hitpush
    int clientnum, privilege, lastupdate, plag, ping;
    int lifesequence;                   // sequence id for each respawn, used in damage test
    int respawned, suicided;
    int lastpain;
    int lastaction, lastattackgun;
    bool attacking;
    int attacksound, attackchan, idlesound, idlechan;
    int lasttaunt;
    int lastpickup, lastpickupmillis, lastbase, lastrepammo, flagpickup, tokens;
    vec lastcollect;
    int frags, flags, deaths, teamkills, totaldamage, totalshots;
    editinfo *edit;
    float deltayaw, deltapitch, deltaroll, newyaw, newpitch, newroll;
    int smoothmillis;

    string name, tag, team, info;
    int playermodel;
    int fov;                            // field of view

    ai::aiinfo *ai;
    int ownernum, lastnode;

    vec muzzle;

    fpsent() : weight(100), clientnum(-1), privilege(PRIV_NONE), lastupdate(0), plag(0), ping(0), lifesequence(0), respawned(-1), suicided(-1), lastpain(0), attacksound(-1), attackchan(-1), idlesound(-1), idlechan(-1),
        frags(0), flags(0), deaths(0), teamkills(0), totaldamage(0), totalshots(0), edit(NULL), smoothmillis(-1), playermodel(-1), fov(100), ai(NULL), ownernum(-1), muzzle(-1, -1, -1)
    {
        name[0] = team[0] = tag[0] = info[0] = 0;
        respawn();
    }
    ~fpsent()
    {
        freeeditinfo(edit);
        if(attackchan >= 0) inexor::sound::stopsound(attacksound, attackchan);
        if(idlechan >= 0) inexor::sound::stopsound(idlesound, idlechan);
        if(ai) delete ai;
    }

    /// apply push event to object's velocity vector
    void hitpush(int damage, const vec &dir, fpsent *actor, int gun)
    {
        vec push(dir);
        push.mul((actor==this && guns[gun].exprad ? EXP_SELFPUSH : 1.0f)*guns[gun].hitpush*damage/weight);
        vel.add(push);
    }

    /// @see stopsound
    void stopattacksound()
    {
        if(attackchan >= 0) inexor::sound::stopsound(attacksound, attackchan, 250);
        attacksound = attackchan = -1;
    }

    /// @see stopsound
    void stopidlesound()
    {
        if(idlechan >= 0) inexor::sound::stopsound(idlesound, idlechan, 100);
        idlesound = idlechan = -1;
    }

    /// respawn item
    void respawn()
    {
        dynent::reset();
        fpsstate::respawn();
        respawned = suicided = -1;
        lastaction = 0;
        lastattackgun = gunselect;
        attacking = false;
        lasttaunt = 0;
        lastpickup = -1;
        lastpickupmillis = 0;
        lastbase = lastrepammo = -1;
        flagpickup = 0;
        tokens = 0;
        lastcollect = vec(-1e10f, -1e10f, -1e10f);
        stopattacksound();
        lastnode = -1;
    }
};
