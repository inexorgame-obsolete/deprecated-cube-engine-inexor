#pragma once

#include "inexor/network/legacy/cube_network.hpp"
#include "inexor/network/legacy/game_types.hpp"


extern ENetPacket *sendf(int cn, int chan, const char *format, ...);
extern void sendpacket(int cn, int chan, ENetPacket *packet, int exclude = -1);
extern ENetPacket *sendfile(int cn, int chan, stream *file, const char *format, ...);

extern void sendservmsg(const char *s);
extern void sendservmsgf(const char *fmt, ...);
