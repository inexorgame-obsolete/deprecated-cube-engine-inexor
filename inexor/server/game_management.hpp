#pragma once

#include "inexor/server/client_management.hpp"

namespace server
{
/// Whether this game is currently paused.
extern bool gamepaused;

extern void pausegame(bool val, clientinfo *ci = nullptr);
}

