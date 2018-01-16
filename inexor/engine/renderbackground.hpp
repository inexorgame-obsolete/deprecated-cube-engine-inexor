#pragma once

#include "inexor/texture/texture.hpp"

extern float loadprogress;

/// render background texture for the mainmenu and the loading screen.
extern void renderbackground(const char *caption = nullptr, Texture *mapshot = nullptr,
                             const char *mapname = nullptr, const char *mapinfo = nullptr, bool restore = false, bool force = false);

/// render progress bar and map screenshot
extern void renderprogress(float bar, const char *text, GLuint tex = 0, bool background = false);

