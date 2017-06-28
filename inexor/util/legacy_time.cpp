#include "inexor/util/legacy_time.hpp"

#include <chrono>
#include <thread>

typedef std::chrono::steady_clock Clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;


int curtime = 0, lastmillis = 1, elapsedtime = 0, totalmillis = 1;
int gamemillis = 0;
uint totalsecs = 0;

int scaletime(int time, int gamespeed)
{
    return time * gamespeed;
}

int time_since_program_start()
{
    static auto const startup_timestamp = Clock::now(); // initialized on first time_since_program_start() only and never touched again.
    return duration_cast<milliseconds>(Clock::now() - startup_timestamp).count();
}

/// Block for a specific time to limit frames per seconds to use resources intelligently.
/// @param elapsed_time time in real milliseconds since last updatetime();
/// @warning We block inaccurately sometimes! You need to check the time again afterwards.
void limitfps(int max_fps, int elapsed_time)
{
    static int fpserror = 0; // rounding errors correction: todo this is still insufficient for small rounding errors.
    int delay = 1000/max_fps - elapsed_time;
    if(delay < 0) fpserror = 0;
    else
    {
        fpserror += 1000%max_fps;
        if(fpserror >= max_fps)
        {
            ++delay;
            fpserror -= max_fps;
        }
        if(delay > 0)
        {
            std::this_thread::sleep_for(milliseconds(delay));
        }
    }
}

void updatetime(bool is_paused, int gamespeed, int max_fps)
{
    int current_wall_millis = time_since_program_start();

    elapsedtime = current_wall_millis - totalmillis; // time between last update and current time
    if(max_fps)
    {
        limitfps(max_fps, elapsedtime);
        elapsedtime = time_since_program_start() - totalmillis; // see limitfps warning
    }

    static int timeerr = 0; // the rounding error introduced by the gamespeed multiplication: e.g. gamespeed 125: (t*125)/100) ?= t.
    int scaledtime = scaletime(elapsedtime, gamespeed) + timeerr;
    curtime = scaledtime/100;
    timeerr = scaledtime%100;
  //  if(!multiplayer(false) && curtime>200) curtime = 200;
    if(is_paused) curtime = 0;
    lastmillis += curtime;

    totalmillis = current_wall_millis;

    static int lastsec = 0;
    if(totalmillis - lastsec >= 1000)
    {
        int cursecs = (totalmillis - lastsec) / 1000;
        totalsecs += cursecs;
        lastsec += cursecs * 1000;
    }
}

