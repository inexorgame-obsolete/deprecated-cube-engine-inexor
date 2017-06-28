#pragma once
#include "inexor/shared/cube_types.hpp"

/// microtiming header

extern int totalmillis;                 // elapsed wall time since program start (in real milliseconds)
extern int elapsedtime;                 // elapsed wall time since last updatetime() (in real milliseconds)
extern uint totalsecs;  // probably bc the server is longer running there was a need of a bigger range.

// note: virtual game milliseconds is scaled with the gamespeed and effected by a paused game.
extern int curtime;                     // elapsed frame time since last updatetime() (in virtual game milliseconds)
extern int lastmillis;                  // elapsed frame time since program start (in virtual game milliseconds)
extern int gamemillis;                  // elapsed frame time since game start (in virtual game milliseconds)

/// Updates the above global timing variables.
/// @param is_paused if true we won't update any frame times.
/// @param gamespeed there exist wall time and frame time:
///        one is the virtual 'clock' for the game, the other one is scaled (and does not update when paused).
/// @param maxfps in case of limited fps we let this thread sleep for some milliseconds, if 0 everythings unlimited.
/// TODO: encapsulate this into a class to make concurrency easier.
extern void updatetime(bool is_paused, int gamespeed, int max_fps = 0);

/// real time in milliseconds since program start.
extern int time_since_program_start();

/// scale time with gametime: gamespeed default is 100.
/// Hence default return value would be t * 100.
/// @param time in milliseconds.
extern int scaletime(int time, int gamespeed);
