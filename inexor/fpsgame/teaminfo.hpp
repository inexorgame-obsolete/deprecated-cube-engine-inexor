#pragma once
#include "inexor/fpsgame/fpsent.hpp"

#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/cube_tools.hpp"
#include "inexor/shared/cube_loops.hpp"

#include <string.h>


/// important teamspecific declarations
#define MAXTEAMS 128
#define MAXNAMELEN 15  /// max player name length
#define MAXTEAMLEN 4   /// max team name length
#define MAXTAGLEN 8    /// max player tag length
#define BOTTAG "Bot"   /// all bots share this tag

enum
{
    TEAM_NONE,
    TEAM_OWN,
    TEAM_OPPONENT,
    TEAM_NUM
};

/// const radar blip colors
static const char * const teamblipcolor[TEAM_NUM] =
{
    "_neutral", // = 'gray'
    "_blue",
    "_red"
};

// team handling

#define MAXNAMELEN 15
#define MAXTEAMLEN 4
#define MAXTEAMS 128

/// some team modes allow more than 2 teams
/// allow sorting multiple teams using team scores
struct teamscore
{
    const char *team;
    int score;
    teamscore() {}
    teamscore(const char *s, int n) : team(s), score(n) {}

    // used for quicksort template to compare teams
    static bool compare(const teamscore &x, const teamscore &y)
    {
        if(x.score > y.score) return true;
        if(x.score < y.score) return false;
        return strcmp(x.team, y.team) < 0;
    }
};

/// create hashes to access hashmaps
static inline uint hthash(const teamscore &t) { return hthash(t.team); }

/// compare two teamnames
static inline bool htcmp(const char *key, const teamscore &t) { return htcmp(key, t.team); }

/// scoreboard team block description
struct teaminfo
{
    char team[MAXTEAMLEN+1];
    int frags;
};

/// create hash for hashsts
static inline uint hthash(const teaminfo &t) { return hthash(t.team); }

/// compare two team names
static inline bool htcmp(const char *team, const teaminfo &t) { return !strcmp(team, t.team); }


/// Used only for the scoreboard
struct scoregroup : teamscore
{
    vector<fpsent *> players;

    /// Returns whether this scoregroup is a clan/playing-group, whatever.
    /// @return the shared tag if all tags are the same, otherwise null.
    char *sametag()
    {
        fpsent *prev = nullptr;
        loopv(players)
        {
            fpsent *p = players[i];
            if(!p->tag[0]) return nullptr;
            if(!prev) { prev = p; continue; }
            if(strcmp(p->tag, prev->tag)) return nullptr; //two tags are not matching
        }
        return prev ? prev->tag : nullptr;
    }
};