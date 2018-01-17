#pragma once

#include <enet/enet.h>

struct stream;

extern void sendclientpacket(ENetPacket *packet, int chan);
extern void flushclient();
extern void disconnect(bool async = false, bool cleanup = true);
extern bool isconnected(bool attempt = false, bool local = true);
extern const ENetAddress *connectedpeer();
extern bool multiplayer(bool msg = true);
extern void neterr(const char *s, bool disc = true);
extern void gets2c();
extern void notifywelcome();
/// Send a file to all other clients.
extern ENetPacket *send_file(stream *file, const char *format = "", ...);

extern void connectserv(const char *servername, int port, const char *serverpassword, const char *mapwish = nullptr, int modewish = -1);
extern void abortconnect();
extern void clientkeepalive();

extern bool resolverwait(const char *name, ENetAddress *address);
