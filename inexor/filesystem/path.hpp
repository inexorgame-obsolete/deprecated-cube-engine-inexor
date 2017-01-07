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

/// Load the contents of a file in a specific section.
/// @param start_line the first line we copy.
/// @param end_line the last line we copy to the output string.
/// @note we count from 1 upwards (as you see it in your text-editor)
extern const std::string filecontents_partly(const std::string &filename, size_t start_line, size_t end_line);

/// Retrieve a list of all files inside a folder (non recursively!).
/// @param ext needs to be either empty or an extension to filter for (only those files get accepted) DOT needed! ".jpg"
extern std::vector<Path> &list_files(Path folder, std::vector<Path> &file_list, Path ext);
} } // ns inexor::filesystem

