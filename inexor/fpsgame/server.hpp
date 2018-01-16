#pragma once

#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/cube_hash.hpp"
#include "inexor/fpsgame/teaminfo.hpp"
#include "inexor/network/legacy/buffer_types.hpp"

namespace server
{
    extern int gamespeed;

    extern void serverinit();
    extern void clientdisconnect(int n);
    extern int clientconnect(int n, uint ip);
    extern bool allowbroadcast(int n);
    extern void parsepacket(int sender, int chan, packetbuf &p);
    extern bool sendpackets(bool force = false);
    extern void serverinforeply(ucharbuf &req, ucharbuf &p);
    extern void serverupdate();
    extern bool servercompatible(char *name, char *sdec, char *map, int ping, const vector<int> &attr, int np);
    extern bool ispaused();
    extern hashset<teaminfo> teaminfos;
}
