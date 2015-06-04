/// string operations on filenames (INCOMPLETE! see e.g. stream.cpp).

#ifndef I_FILESYSTEM_H
#define I_FILESYSTEM_H

#include "inexor/shared/cube.h"

enum {
    DIR_MEDIA,
    DIR_MAP,
    DIR_TEXTURE,
    DIR_SKYBOX,
    DIR_UI,
    DIR_ICON,
    DIR_NUM
}; /// media path types.

extern SharedVar<char*> mediadir, mapdir, texturedir,
                        skyboxdir, interfacedir, icondir;

namespace inexor
{
    namespace filesystem {
        extern const char *getmediadir(int type);
        extern char *appendmediadir(char *output, const char *basename, int type, const char *extension = NULL);
        extern char *getmedianame(char *output, const char *basename, int type, JSON *j = NULL);
    }
}
#endif // I_FILESYSTEM_H
