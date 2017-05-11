#pragma once

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
