#pragma once
#include "inexor/fpsgame/game.hpp"

namespace entities {

/// Returns whether the ammo entity gets spawned at mapstart.
inline bool delayspawn(int type)
{
    switch(type)
    {
        case I_GREENARMOUR:
        case I_YELLOWARMOUR:
        case I_BOOST:
        case I_QUAD:
            return true;
    }
    return false;
}
} // ns entities
