#include <sys/types.h>  // for uint
#include <chrono>       // for milliseconds, duration_cast, operator-, stead...
#include <thread>       // for sleep_for
#include <type_traits>  // for enable_if<>::type

#include "inexor/util/legacy_time.hpp"

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
/*
static int clockrealbase = 0, clockvirtbase = 0;
static void clockreset() 
{ 
	clockrealbase = SDL_GetTicks(); 
	clockvirtbase = totalmillis;
}

int clockerror = 1000000;
int clockfix = 0;

int getclockmillis()
{
    int millis = SDL_GetTicks() - clockrealbase;
    if(clockfix) millis = int(millis*(double(clockerror)/1000000));
    millis += clockvirtbase;
    return std::max(millis, totalmillis);
} */

int time_since_program_start()
{
    static auto const startup_timestamp = Clock::now(); // initialized on first time_since_program_start() only and never touched again.
    return duration_cast<milliseconds>(Clock::now() - startup_timestamp).count();
    //return getclockmillis();
}

/// Block for a specific time to limit frames per seconds to use resources intelligently.
/// @param max_fps in case of limited fps we let this thread sleep for some milliseconds, if 0 everythings unlimited.
/// @param elapsed_time time in real milliseconds since last updatetime();
/// @return We block inaccurately sometimes! So we give back the delay in milliseconds.
void limitfps(int &millis, int curmillis, int fps_limit)
{
    if(!fps_limit) return;
    static int fpserror = 0;
    int delay = 1000/fps_limit - (millis-curmillis);
    if(delay < 0) fpserror = 0;
    else
    {
        fpserror += 1000%fps_limit;
        if(fpserror >= fps_limit)
        {
            ++delay;
            fpserror -= fps_limit;
        }
        if(delay > 0)
        {
            std::this_thread::sleep_for(milliseconds(delay));
            millis += delay;
        }
    }
}

void updatetime(bool is_paused, int gamespeed, int fps_limit)
{
    int current_wall_millis = time_since_program_start();
    limitfps(current_wall_millis, totalmillis, fps_limit);
    elapsedtime = current_wall_millis - totalmillis;

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

