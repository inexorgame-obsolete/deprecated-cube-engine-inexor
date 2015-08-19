/// string operations on filenames (INCOMPLETE! see e.g. stream.cpp).

#include "inexor/shared/filesystem.h"

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
            nformatstring(output, MAXSTRLEN, "%s/%s%s", dir ? dir : "", basename, extension ? extension : "");
            return output;
        }

        /// Get a media name either relative to the current file or the specific media folder according to type.
        /// @warning not threadsafe! (since makerelpath, parentdir and getcurexecdir are not)
        char *getmedianame(char *output, const char *basename, int type, JSON *j)
        {
            ASSERT(basename != NULL && strlen(basename)>=2);
            if(basename[0] == '/') appendmediadir(output, basename+1, type);
            else if(j && j->currentfile) nformatstring(output, MAXSTRLEN, makerelpath(parentdir(j->currentfile), basename));
            else if(!j) nformatstring(output, MAXSTRLEN, makerelpath(getcurexecdir(), basename));
            else copystring(output, basename, strlen(basename));
            return output;
        }
    }
}
