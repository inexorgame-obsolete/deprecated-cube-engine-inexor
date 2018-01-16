#pragma once

// FPS: Frames per second.

extern bool inbetweenframes, renderedframe;

extern void resetfpshistory();

/// The current fps limit.
extern int get_current_max_fps();

extern void updatefpshistory(int millis);

extern void getfps(int &fps, int &bestdiff, int &worstdiff);
