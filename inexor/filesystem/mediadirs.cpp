/// string operations on filenames (INCOMPLETE! see e.g. stream.cpp).

#include "inexor/shared/cube.hpp"
#include "inexor/filesystem/mediadirs.hpp"
#include "inexor/util.hpp"

SVARP(mapdir, "map");
SVARP(texturedir, "texture");
SVARP(skyboxdir, "skybox");
SVARP(interfacedir, "interface");
SVARP(icondir, "interface/icon");
SVARP(radardir, "interface/radar");
SVARP(sounddir, "sound");
SVARP(musicdir, "music");

using namespace inexor::util;
using namespace boost::filesystem;

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
    case DIR_RADAR:      return *radardir;
    case DIR_SOUND:     return *sounddir;
    case DIR_MUSIC:     return *musicdir;
    }
    return NULL;
}

Path getmediapath(const std::string &basename, int type)
{
    std::string output;
    const char *dir = getmediadir(type);
    output = fmt << (dir ? dir : "") << (dir ? "/" : "") << basename;
    return Path(std::move(output)).make_preferred();
}

std::string &getmediapath(std::string &output, const std::string basename, int type)
{
    output = getmediapath(basename, type).string();
    return output;
}

const char *getmediapath(char *output, int outputlen, const std::string &basename, int type)
{
    std::string tmp;
    std::size_t length = getmediapath(tmp, basename, type).copy(output, outputlen);
    output[length] = '\0';
    return output;
}

} // namespace filesystem
} // namespace inexor
