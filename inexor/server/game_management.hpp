#pragma once

namespace server {
struct clientinfo;
}  // namespace server

namespace server
{
/// Whether this game is currently paused.
extern bool gamepaused;

extern void pausegame(bool val, clientinfo *ci = nullptr);
}

