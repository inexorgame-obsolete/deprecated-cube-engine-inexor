/// string operations on filenames (INCOMPLETE! see e.g. stream.cpp).

#include "inexor/shared/cube.hpp"
#include "inexor/filesystem/mediadirs.hpp"
#include "inexor/util.hpp"

/// Media paths ///

SVARP(mapdir, "map");
SVARP(texturedir, "texture");
SVARP(skyboxdir, "skybox");
SVARP(interfacedir, "interface");
SVARP(icondir, "interface/icon");
SVARP(sounddir, "sound");
SVARP(musicdir, "music");

using namespace inexor::util;

namespace inexor {
    namespace filesystem {

        /// Returns the specific media dir according to type.
        const char *getmediadir(int type)
        {
            switch(type)
            {
            case DIR_MAP:       return *mapdir;
            case DIR_TEXTURE:   return *texturedir;
            case DIR_SKYBOX:    return *skyboxdir;
            case DIR_UI:        return *interfacedir;
            case DIR_ICON:      return *icondir;
            case DIR_SOUND:     return *sounddir;
            case DIR_MUSIC:     return *musicdir;
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
        void getmedianame(std::string &output, const char *basename, int type)
        {
            ASSERT(basename != NULL && strlen(basename)>=2);

            if(basename[0] == '/') appendmediadir(output, basename+1, type);
            else
            {
                const char *execdir = getcurexecdir();
                if(execdir) output = fmt << execdir << "/" << basename;
                else output = fmt << basename;
            }
        }

        char *getmedianame(char *output, size_t outputlen, const char *basename, int type)
        {
            ASSERT(output != NULL);
            std::string s;
            getmedianame(s, basename, type);
            copystring(output, s.c_str(), outputlen);
            return output;
        }
    }
}
