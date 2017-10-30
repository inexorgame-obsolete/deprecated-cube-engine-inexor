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
/// @param max_fps in case of limited fps we let this thread sleep for some milliseconds, if 0 everythings unlimited.
/// @param elapsed_time time in real milliseconds since last updatetime();
/// @return We block inaccurately sometimes! So we give back the delay in milliseconds.
int limitfps(int max_fps, int elapsed_time)
{
    static int fpserror = 0; // rounding errors correction: todo this is still insufficient for small rounding errors.
    int delay = 1000/max_fps - elapsed_time;
    // we return the real delay: we ask the process to go to sleep for xy milliseconds,
    // but its not guaranteed it really only takes xy milliseconds.
    int real_delay = 0;
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
            int wall_millis_before_sleep = time_since_program_start();
            std::this_thread::sleep_for(milliseconds(delay));
            // the sleep may be of inaccurate duration:
            real_delay = time_since_program_start() - wall_millis_before_sleep;
        }
    }
    return real_delay;
}

void updatetime(bool is_paused, int gamespeed, int max_fps)
{
    int current_wall_millis = time_since_program_start();

    elapsedtime = current_wall_millis - totalmillis; // time between last update and current time
    if(max_fps)
    {
        int delay = limitfps(max_fps, elapsedtime);
        current_wall_millis += delay;
        elapsedtime += delay;
    }

    static int timeerr = 0; // the rounding error introduced by the gamespeed multiplication: e.g. gamespeed 125: (t*125)/100) ?= t.
    int scaledtime = scaletime(elapsedtime, gamespeed) + timeerr;
    curtime = scaledtime/100;
    timeerr = scaledtime%100;

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

