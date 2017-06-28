#pragma once

#include "inexor/server/client_management.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/cube_types.hpp"
#include "inexor/network/SharedTree.hpp"

namespace server
{

struct demofile
{
    string info;
    uchar *data;
    int len;
};

extern vector<demofile> demos;
extern SharedVar<int> maxdemos, maxdemosize;

/// The streams for demo playback or demo recording.
/// set to nullptr if not recording/playing a demo.
extern stream *demorecord, *demoplayback;

/// Whether we want to record a demo next match.
extern bool demonextmatch;


extern void setupdemorecord();
extern void recordpacket(int chan, void *data, int len);
extern void enddemorecord();

extern void setupdemoplayback();
extern void readdemo();
extern void enddemoplayback();

/// Wrapper for either enddemoplayback or enddemorecord, depending on m_demo.
extern void stopdemo();

// demos management:

/// Remove all demos until demo number n or all if n = 0.
extern void cleardemos(int n);

/// Send a list of demos to that client.
extern void listdemos(int cn);

/// Send a specific demo to the client.
/// If client ci is not receiving one yet and num is valid.
/// @param num if 0 send the latest demo.
extern void senddemo(clientinfo *ci, int num);

} // ns server
