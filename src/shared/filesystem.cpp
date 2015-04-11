/// string operations on filenames (INCOMPLETE! see e.g. stream.cpp).

#include "filesystem.h"

/// Media paths ///

SVARP(mediadir, "media");
SVARP(mapdir, "media/map");
SVARP(texturedir, "media/texture");
SVARP(skyboxdir, "media/skybox");
SVARP(interfacedir, "media/interface");
SVARP(icondir, "media/interface/icon");

namespace inexor {
    namespace filesystem {

        /// Returns the specific media dir according to type.
        const char *getmediadir(int type)
        {
            switch(type)
            {
            case DIR_MEDIA:     return mediadir;
            case DIR_MAP:       return mapdir;
            case DIR_TEXTURE:   return texturedir;
            case DIR_SKYBOX:    return skyboxdir;
            case DIR_UI:        return interfacedir;
            case DIR_ICON:      return icondir;
            }
            return NULL;
        }

        /// Append the media directory specified by type to the basename.
        char *appendmediadir(char *output, const char *basename, int type, const char *extension)
        {

            //size_t dirlen = strlen(dir);
           // if(dirlen >= 2 && (dir[dirlen - 1] == '/' || dir[dirlen - 1] == '\\')) dir[dirlen - 1] = '\0';

            const char *dir = getmediadir(type);
            formatstring(output)("%s/%s%s", dir ? dir : "", basename, extension ? extension : "");
            return output;
        }

        /// Get a media name either relative to the current file or the specific media folder according to type.
        /// @warning not threadsafe! (since makerelpath, parentdir and getcurexecdir are not)
        char *getmedianame(char *output, const char *basename, int type, JSON *j)
        {
            ASSERT(basename != NULL);
            if(basename[0] == '/') appendmediadir(output, basename, type);
            else if(j) copystring(output, makerelpath(parentdir(j->currentfile), basename));
            else copystring(output, makerelpath(getcurexecdir(), basename));
            return output;
        }
    }
}