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

