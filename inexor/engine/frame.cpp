#include "inexor/engine/frame.hpp"
#include "inexor/shared/command.hpp"
#include "inexor/ui/legacy/menus.hpp"
#include "inexor/ui/screen/ScreenManager.hpp"

using inexor::rendering::screen::screen_manager;

/// frames per seconds and timing

/// store the last MAXFPSHISTORY fps rates
#define MAXFPSHISTORY 60
int fpspos = 0, fpshistory[MAXFPSHISTORY];
bool inbetweenframes = false, renderedframe = true;

VAR(menufps, 0, 60, 1000);
VARP(maxfps, 0, 200, 1000);

int get_current_max_fps()
{
    return (mainmenu || screen_manager.minimized) && menufps ? (maxfps ? min(maxfps, menufps) : menufps) : maxfps;
}
/// clear fps history array
void resetfpshistory()
{
    loopi(MAXFPSHISTORY) fpshistory[i] = 1;
    fpspos = 0;
}

/// add current frames per seconds score to fps history array
void updatefpshistory(int millis)
{
    fpshistory[fpspos++] = std::max(1, std::min(1000, millis));
    if(fpspos>=MAXFPSHISTORY) fpspos = 0;
}

/// get average fps, best fps and worst fps (see command fpsrange)
void getfps(int &fps, int &bestdiff, int &worstdiff)
{
    int total = fpshistory[MAXFPSHISTORY-1], best = total, worst = total;
    loopi(MAXFPSHISTORY-1)
    {
        int millis = fpshistory[i];
        total += millis;
        if(millis < best) best = millis;
        if(millis > worst) worst = millis;
    }

    fps = (1000*MAXFPSHISTORY)/total;
    bestdiff = 1000/best-fps;
    worstdiff = fps-1000/worst;
}


/// cubescript: get fps as float
/// @see floatret
void getfps_(int *raw)
{
    if(*raw) floatret(1000.0f/fpshistory[(fpspos+MAXFPSHISTORY-1)%MAXFPSHISTORY]);
    else
    {
        int fps, bestdiff, worstdiff;
        getfps(fps, bestdiff, worstdiff);
        intret(fps);
    }
}
COMMANDN(getfps, getfps_, "i");
