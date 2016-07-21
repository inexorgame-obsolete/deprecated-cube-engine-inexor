#pragma once

#include <vector>
#include <string>

#include <boost/filesystem.hpp>

namespace inexor { namespace filesystem {

/// @see boost::filesystem::path
/// We need to rename this class bc otherwise we get clashes with legacy code.
using Path = boost::filesystem::path;

/// Retrieve the contents of a text file.
extern const std::string filecontents(const std::string &filename);

/// Retrieve a list of all files inside a folder (non recursively!).
/// @param ext needs to be either empty or an extension to filter for (only those files get accepted) DOT needed! ".jpg"
extern std::vector<Path> &list_files(Path folder, std::vector<Path> &file_list, Path ext);

} } // ns inexor::filesystem

