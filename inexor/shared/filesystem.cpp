/// string operations on filenames (INCOMPLETE! see e.g. stream.cpp).

#include "inexor/shared/filesystem.h"
#include "inexor/util/util.h"

/// Media paths ///

SVARP(mediadir, "media");
SVARP(mapdir, "media/map");
SVARP(texturedir, "media/texture");
SVARP(skyboxdir, "media/skybox");
SVARP(interfacedir, "media/interface");
SVARP(icondir, "media/interface/icon");

using namespace inexor::util;

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
        const char *appendmediadir(std::string &output, const char *basename, int type, const char *extension)
        {

            //size_t dirlen = strlen(dir);
           // if(dirlen >= 2 && (dir[dirlen - 1] == '/' || dir[dirlen - 1] == '\\')) dir[dirlen - 1] = '\0';

            const char *dir = getmediadir(type);
            output = fmt << (dir ? dir : "") << (dir ? "/" : "") << basename << (extension ? extension : "");
            return output.c_str();
        }

        const char *appendmediadir(char *output, size_t outputlen, const char *basename, int type, const char *extension)
        {
            ASSERT(output != NULL);
            std::string s;
            appendmediadir(s, basename, type, extension);
            copystring(output, s.c_str(), outputlen);
            return s.c_str();
        }

        /// Get a media name either relative to the current file or the specific media folder according to type.
        /// @warning not threadsafe! (since makerelpath, parentdir and getcurexecdir are not)
        void getmedianame(std::string &output, const char *basename, int type, JSON *j)
        {
            ASSERT(basename != NULL && strlen(basename)>=2);

            if(basename[0] == '/') appendmediadir(output, basename+1, type);
            else if(j && j->currentfile) output = fmt << parentdir(j->currentfile) << "/" << basename;
            else
            {
                const char *execdir = getcurexecdir();
                if(!j && execdir) output = fmt << execdir << "/" << basename;
                else output = fmt << basename;
            }
        }

        char *getmedianame(char *output, size_t outputlen, const char *basename, int type, JSON *j)
        {
            ASSERT(output != NULL);
            std::string s;
            getmedianame(s, basename, type, j);
            copystring(output, s.c_str(), outputlen);
            return output;
        }
    }
}
