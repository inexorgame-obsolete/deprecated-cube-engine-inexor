#pragma once
#include "inexor/util/Logging.hpp"

/// priviledge levels
enum { PRIV_NONE = 0, PRIV_MASTER, PRIV_ADMIN };

inline const char *privname(int type)
{
    switch(type)
    {
        case PRIV_ADMIN: return "admin";
        case PRIV_MASTER: return "master";
        default: return "unknown";
    }
}


/// master mode states: server rights management
enum
{
    MM_START = -1,
    MM_OPEN = 0,   // anyone on this server can claim master
    MM_VETO,       // anyone on this server can vote for maps and join
    MM_LOCKED,     // newly joined players start in spectator mode
    MM_PRIVATE,
    MM_PASSWORD,
};

/// static strings for server description in master server list
static const char * const mastermodenames[] ={"default",   "open",   "veto",   "locked",     "private",    "password"};

/// Gives back the mastermode name based on the index. If index is out of range, gives back the given unknown-string.
inline const char *mastermodename(int n, const char *unknown = "unknown")
{
    return (n>=MM_START && size_t(n-MM_START)<sizeof(mastermodenames)/sizeof(mastermodenames[0])) ? mastermodenames[n-MM_START] : unknown;
}
