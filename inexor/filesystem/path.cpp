
#include <fstream>
#include <vector>
#include "inexor/filesystem/path.hpp"

namespace bfs = boost::filesystem;

namespace inexor { namespace filesystem {

// TODO: put into filesystem/
// taken from http://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
const std::string filecontents(const std::string &filename)
{
    std::ifstream file_stream(filename);
    std::string ret;
    char buffer[4096];
    while(file_stream.read(buffer, sizeof(buffer)))
        ret.append(buffer, sizeof(buffer));
    ret.append(buffer, file_stream.gcount());
    return ret;
}

std::vector<Path> &list_files(Path folder, std::vector<Path> &file_list, Path ext)
{
    if(!bfs::exists(folder) || !bfs::is_directory(folder)) return file_list;
    boost::system::error_code err;
    using Iterator = bfs::directory_iterator;
    Iterator iter_end;          // boost fs is a fucked up API it seems.

    for(Iterator iter(folder, err); iter != iter_end; ++iter)
    {
        Path file = iter->path();
        if(bfs::is_regular_file(file) && (ext.empty() || file.extension() == ext)) file_list.push_back(file);
    }
    return file_list;
}

} } // ns inexor::filesystem
