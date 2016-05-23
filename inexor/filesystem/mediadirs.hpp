/// string operations on filenames (INCOMPLETE! see e.g. stream.cpp).

#ifndef I_FILESYSTEM_H
#define I_FILESYSTEM_H

#include "inexor/rpc/SharedTree.hpp"
#include <boost/filesystem.hpp>
#include <string>

enum {
    DIR_MAP,
    DIR_TEXTURE,
    DIR_SKYBOX,
    DIR_UI,
    DIR_ICON,
    DIR_SOUND,
    DIR_MUSIC,
    DIR_NUM
}; /// media path types.

extern SharedVar<char*> mapdir, texturedir, skyboxdir, interfacedir, icondir, sounddir, musicdir;

namespace inexor {
namespace filesystem {

/// @see boost::filesystem::path
/// We need to rename this class bc otherwise we get clashes with legacy code.
using Path = boost::filesystem::path;

/// Returns the media-dir string of specific type.
extern const char *getmediadir(int type);

/// Append the media directory specified by type to the basename.
/// Slashes get corrected as well and will be in the platforms prefered form.
extern Path getmediapath(const std::string &basename, int type);
extern const char *getmediapath(char *output, int outputlen, const std::string &basename, int type);
extern std::string &getmediapath(std::string &output, const std::string basename, int type);


} // namespace filesystem
} // namespace inexor
#endif // I_FILESYSTEM_H
