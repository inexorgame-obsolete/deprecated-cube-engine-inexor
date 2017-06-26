#pragma once
#include "inexor/shared/cube_vector.hpp"


// game mode specific code

/// basic game mode bitmask "FLAGS"
/// (NOT game modes but attributes of game modes)
enum
{
    M_TEAM       = 1<<0,   /// game mode contains teams
    M_NOITEMS    = 1<<1,   /// game mode has no items
    M_NOAMMO     = 1<<2,   /// game mode has no ammo?
    M_INSTA      = 1<<3,   /// game mode has an instagib modifier
    M_EFFICIENCY = 1<<4,   /// game mode has an efficiency modifier
    M_TACTICS    = 1<<5,   /// game mode offers random spawn weapons (see tactics mode)
    M_CAPTURE    = 1<<6,   /// game mode is about capturing bases
    M_REGEN      = 1<<7,   /// game mode is about capturing supply bases (see regencapture mode)
    M_CTF        = 1<<8,   /// game mode is about capturing a flag
    M_PROTECT    = 1<<9,   /// game mode is about protecting a flag
    M_HOLD       = 1<<10,  /// game mode is about holding a flag (for 20 seconds)
    M_OVERTIME   = 1<<11,  /// game mode has longer matches
    M_EDIT       = 1<<12,  /// game mode allows cooperative editing (coopedit)
    M_DEMO       = 1<<13,  /// game mode is a demo playback
    // old: M_LOCAL      = 1<<14,  /// game mode is played in singleplayer only (locally)
    M_LOBBY      = 1<<15,  /// game mode does not imply certain (good vs evil) grouped gameplay but also allows to built lobbys (pseudoteams working against each other)
    M_DMSP       = 1<<16,  /// death match single player
    M_CLASSICSP  = 1<<17,  /// classic singleplayer
    M_SLOWMO     = 1<<18,  /// game mode is played in slow motion
    M_COLLECT    = 1<<19,  /// game mode is about collecting skulls

    M_LMS        = 1<<20,  /// last man standing
    M_BOMB       = 1<<21,  /// bomberman
    M_TIMEFORWARD= 1<<22,  /// time counts onward (instead of from full time to zero)
    M_OBSTACLES  = 1<<23,  /// game mode has obstacles which can be destroyed dynamically
    M_HIDEANDSEEK= 1<<24
};


/// structure for game mode description
static struct gamemodeinfo
{
    const char *name; /// game mode's name
    int flags;        /// a bitmask container (see flags above)
} gamemodes[] =
{
    {"demo", M_DEMO},
    {"ffa", M_LOBBY},
    {"coop edit", M_EDIT},
    {"teamplay", M_TEAM},
    {"instagib", M_NOITEMS | M_INSTA},
    {"insta team", M_NOITEMS | M_INSTA | M_TEAM},
    {"efficiency", M_NOITEMS | M_EFFICIENCY},
    {"effic team", M_NOITEMS | M_EFFICIENCY | M_TEAM},
    {"tactics", M_NOITEMS | M_TACTICS},
    {"tac team", M_NOITEMS | M_TACTICS | M_TEAM},
    {"capture", M_NOAMMO | M_TACTICS | M_CAPTURE | M_TEAM},
    {"regen capture", M_NOITEMS | M_CAPTURE | M_REGEN | M_TEAM},
    {"ctf", M_CTF | M_TEAM},
    {"insta ctf", M_NOITEMS | M_INSTA | M_CTF | M_TEAM},
    {"protect", M_CTF | M_PROTECT | M_TEAM},
    {"insta protect", M_NOITEMS | M_INSTA | M_CTF | M_PROTECT | M_TEAM},
    {"hold", M_CTF | M_HOLD | M_TEAM},
    {"insta hold", M_NOITEMS | M_INSTA | M_CTF | M_HOLD | M_TEAM},
    {"effic ctf", M_NOITEMS | M_EFFICIENCY | M_CTF | M_TEAM},
    {"effic protect", M_NOITEMS | M_EFFICIENCY | M_CTF | M_PROTECT | M_TEAM},
    {"effic hold", M_NOITEMS | M_EFFICIENCY | M_CTF | M_HOLD | M_TEAM},
    {"collect", M_COLLECT | M_TEAM},
    {"insta collect", M_NOITEMS | M_INSTA | M_COLLECT | M_TEAM},
    {"effic collect", M_NOITEMS | M_EFFICIENCY | M_COLLECT | M_TEAM},
    {"bomberman", M_LMS | M_BOMB | M_OBSTACLES},
    {"bomberman team", M_LMS | M_BOMB | M_TEAM | M_OBSTACLES},
    {"hideandseek"}
};

// game mode validation and attribute handling

/// macro to determine the amount of available game modes
#define NUMGAMEMODES ((int)(sizeof(gamemodes)/sizeof(gamemodes[0])))

/// validate game mode number (array index)
#define m_valid(mode)          ((mode) >= 0 && (mode) < NUMGAMEMODES)
/// validate game mode number and attribute (to check if this gamemode has items or bases e.g.)
#define m_check(mode, flag)    (m_valid(mode) && gamemodes[(mode)].flags&(flag))
/// validate game mode number and check if game mode does NOT have these attribuges
#define m_checknot(mode, flag) (m_valid(mode) && !(gamemodes[(mode)].flags&(flag)))
/// validate game mode number and check if game mode supports parameter flag bit masks
/// to check if this game mode supports multiple attributes (EFFICIENCY | CTF  e.g.)
#define m_checkall(mode, flag) (m_valid(mode) && (gamemodes[(mode)].flags&(flag)) == (flag))

/// those game mode check macros are built on top of the layer above
#define m_noitems      (m_check(gamemode, M_NOITEMS))
#define m_noammo       (m_check(gamemode, M_NOAMMO|M_NOITEMS))
#define m_insta        (m_check(gamemode, M_INSTA))
#define m_tactics      (m_check(gamemode, M_TACTICS))
#define m_efficiency   (m_check(gamemode, M_EFFICIENCY))
#define m_capture      (m_check(gamemode, M_CAPTURE))
#define m_regencapture (m_checkall(gamemode, M_CAPTURE | M_REGEN))
#define m_ctf          (m_check(gamemode, M_CTF))
#define m_protect      (m_checkall(gamemode, M_CTF | M_PROTECT))
#define m_hold         (m_checkall(gamemode, M_CTF | M_HOLD))
#define m_collect      (m_check(gamemode, M_COLLECT))
#define m_teammode     (m_check(gamemode, M_TEAM))
#define m_overtime     (m_check(gamemode, M_OVERTIME))
#define isteam(a,b)    (m_teammode && strcmp(a, b)==0)

#define m_lms          (m_check(gamemode, M_LMS))
#define m_bomb         (m_check(gamemode, M_BOMB))
#define m_hideandseek  (m_check(gamemode, M_HIDEANDSEEK))

#define m_obstacles    (m_check(gamemode, M_OBSTACLES))
#define m_timeforward  (m_check(gamemode, M_TIMEFORWARD))

#define m_demo         (m_check(gamemode, M_DEMO))
#define m_edit         (m_check(gamemode, M_EDIT))
#define m_lobby        (m_check(gamemode, M_LOBBY))
#define m_timed        (m_checknot(gamemode, M_DEMO|M_EDIT))
#define m_botmode      (m_checknot(gamemode, M_DEMO))

/// shortens a list of mode groups ("[<operator>]<modetype>") into a bitmask.
/// Input may be "?ctf" "!?collect" "*capture" which would do:
///  operator ? adds this to the bitmask (so ctf modes are added)
///  operator !? means AND (so after the second entry got evaluated only modes which are ctf AND collect modes are left)
///  operator * is equivalent to add this if its not edit mode or anything local.
///  operator ! means REVERT (so "?ctf", "!instactf" means all ctf-gamemodes but instactf)
/// Input could also be the gamemode number (e.g. "21", "3") or the gamemode name ("ctf", "collect")
extern int genmodemask(vector<char *> &modes);

/// Returns the name of the gamemode number n.
/// If n does not specify a correct gamemode, it returns the "unknown" string.
extern const char *modename(int n, const char *unknown = "unknown");
