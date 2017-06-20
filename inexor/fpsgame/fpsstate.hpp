#pragma once


#include "inexor/shared/cube_loops.hpp"
#include "inexor/shared/ents.hpp"
#include "inexor/fpsgame/weapon.hpp"
#include "inexor/gamemode/gamemode.hpp"
#include "inexor/util/random.hpp"

#include <algorithm>


enum { AI_NONE = 0, AI_BOT, AI_MAX };
#define isaitype(a) (a >= 0 && a <= AI_MAX-1)

/// First person state. TODO: change name
/// inherited by fpsent and server clients
struct fpsstate
{
    int health, maxhealth;
    int armour, armourtype;
    int quadmillis;
    int gunselect, gunwait;
    int ammo[NUMGUNS];
    int aitype, skill;
    int backupweapon; //no ammo - weapon
    int bombradius;
    int bombdelay;

    fpsstate() : maxhealth(100), aitype(AI_NONE), skill(0), backupweapon(GUN_FIST) {}

    /// set initial ammo
    void baseammo(int gun, int k = 2, int scale = 1)
    {
        ammo[gun] = (itemstats[gun-GUN_SG].add*k)/scale;
    }

    /// add ammo
    void addammo(int gun, int k = 1, int scale = 1)
    {
        const itemstat &is = itemstats[gun-GUN_SG];
        ammo[gun] = std::min(ammo[gun] + (is.add*k)/scale, is.max);
    }

    /// ammo limitation reached/exceeded?
    bool hasmaxammo(int type)
    {
        const itemstat &is = itemstats[type-I_SHELLS];
        return ammo[type-I_SHELLS+GUN_SG]>=is.max;
    }

    /// check if I can pick up this item depending on the radius
    bool canpickup(int type)
    {
        if(type<I_SHELLS || type>I_QUAD) return false;
        const itemstat &is = itemstats[type-I_SHELLS];
        switch(type)
        {
            case I_BOOST: return maxhealth<is.max;
            case I_HEALTH: return health<maxhealth;
            case I_GREENARMOUR:
                // (100h/100g only absorbs 200 damage)
                if(armourtype==A_YELLOW && armour>=100) return false;
            case I_YELLOWARMOUR: return !armourtype || armour<is.max;
            case I_QUAD: return quadmillis<is.max;
            case I_BOMBRADIUS:
                return bombradius<is.max;
                break;
            case I_BOMBDELAY:
                return bombdelay<is.max;
                break;
            default: return ammo[is.info]<is.max;
        }
    }

    /// pick up this item
    void pickup(int type)
    {
        if(type<I_SHELLS || type>I_QUAD) return;
        const itemstat &is = itemstats[type-I_SHELLS];
        switch(type)
        {
            case I_BOOST:
                maxhealth = std::min(maxhealth+is.add, is.max);
            case I_HEALTH: // boost also adds to health
                health = std::min(health+is.add, maxhealth);
                break;
            case I_GREENARMOUR:
            case I_YELLOWARMOUR:
                armour = std::min(armour+is.add, is.max);
                armourtype = is.info;
                break;
            case I_QUAD:
                quadmillis = std::min(quadmillis+is.add, is.max);
                break;
            case I_BOMBRADIUS:
                bombradius = std::min(bombradius+is.add, is.max);
                break;
            case I_BOMBDELAY:
                bombdelay = std::min(bombdelay+is.add, is.max);
                break;
            default:
                ammo[is.info] = std::min(ammo[is.info]+is.add, is.max);
                break;
        }
    }

    /// reset all members when spawning
    void respawn()
    {
        health = maxhealth;
        armour = 0;
        armourtype = A_BLUE;
        quadmillis = 0;
        gunselect = GUN_PISTOL;
        gunwait = 0;
        bombradius = 1;
        bombdelay = 1;
        loopi(NUMGUNS) ammo[i] = 0;
        ammo[backupweapon] = 1;
    }

    /// configure spawn settings (weapons, ammo, health...) depending on game mode
    void spawnstate(int gamemode)
    {
        if(m_demo)
        {
            gunselect = GUN_FIST;
            backupweapon = GUN_FIST;
        } else if(m_insta)
        {
            armour = 0;
            health = 1;
            gunselect = GUN_RIFLE;
            ammo[GUN_RIFLE] = 100;
            backupweapon = GUN_FIST;
        } else if(m_regencapture)
        {
            armourtype = A_BLUE;
            armour = 25;
            gunselect = GUN_PISTOL;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
            backupweapon = GUN_FIST;
        } else if(m_tactics)
        {
            armourtype = A_GREEN;
            armour = 100;
            ammo[GUN_PISTOL] = 40;
            backupweapon = GUN_FIST;
            int spawngun1 = inexor::util::random::rnd(5)+1, spawngun2;
            gunselect = spawngun1;
            baseammo(spawngun1, m_noitems ? 2 : 1);
            do spawngun2 = inexor::util::random::rnd(5)+1; while(spawngun1==spawngun2);
            baseammo(spawngun2, m_noitems ? 2 : 1);
            if(m_noitems) ammo[GUN_GL] += 1;
        } else if(m_efficiency)
        {
            armourtype = A_GREEN;
            armour = 100;
            loopi(5) baseammo(i+1);
            gunselect = GUN_CG;
            ammo[GUN_CG] /= 2;
            backupweapon = GUN_FIST;
        } else if(m_ctf || m_collect)
        {
            armourtype = A_BLUE;
            armour = 50;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
            backupweapon = GUN_FIST;
        } else if(m_bomb)
        {
            health = 1;
            armourtype = A_GREEN;
            armour = 0;
            gunselect = GUN_BOMB;
            backupweapon = GUN_BOMB;
        } else if(m_hideandseek)
        {
            health = 100;
            armour = 0;
            gunselect = GUN_RL;
            ammo[GUN_RL] = 10;
            ammo[GUN_PISTOL] = 0;
            ammo[GUN_GL] = 0;
            backupweapon = GUN_FIST;
        } else
        {
            armourtype = A_BLUE;
            armour = 25;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
            backupweapon = GUN_FIST;
        }
    }

    /// just subtract damage here, we can set death, etc. later in code calling this
    int dodamage(int damage)
    {
        int ad = damage*(armourtype+1)*25/100; // let armour absorb when possible
        if(ad>armour) ad = armour;
        armour -= ad;
        damage -= ad;
        health -= damage;
        return damage;
    }

    /// is there ammo left for this gun
    int hasammo(int gun, int exclude = -1)
    {
        return gun >= 0 && gun <= NUMGUNS && gun != exclude && ammo[gun] > 0;
    }
};
