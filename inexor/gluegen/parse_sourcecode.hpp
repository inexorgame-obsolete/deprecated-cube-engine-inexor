#pragma once

#include <functional>
#include <string>
#include <sstream>

#include "inexor/gluegen/tree.hpp"

namespace inexor { namespace rpc { namespace gluegen {


/// Find all the Shared Declarations in a (doxygen provided) xml AST representation of the sources.
///
/// At the moment this is any SharedVar declaration.
///
/// @param xml_folder the index-file of the doxygen output (or any else, but we're tailored for the index one)
/// @param tree the vector we put our parsed info into.
/// @return true on success.
extern bool find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree);


/// C++ equivalent of strtok, tokenizes the input string based on the occurences of delimiter.
extern std::vector<std::string> split_by_delimiter(std::string input, std::string delimiter);

/// Join the entrys of a vector|sthelsewithrange into a string, using 'd' as the seperator between the parts.
template<typename SinglePassRange, typename Delim>
inline std::string join_to_str(SinglePassRange r, Delim d)
{
    std::stringstream s;
    bool first = true;
    for(auto &e : r)
    {
        if(first)
            first = false;
        else
            s << d;
        s << e;
    }
    return s.str();
}

} } } // namespace inexor::rpc::gluegen
