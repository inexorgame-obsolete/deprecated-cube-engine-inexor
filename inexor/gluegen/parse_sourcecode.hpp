#pragma once

#include <functional>
#include <string>
#include <regex>

#include "inexor/gluegen/tree.hpp"

namespace inexor { namespace rpc { namespace gluegen {

class DefaultValue
{
    DefaultValue *next;
public:
    friend DefaultValue& operator|(DefaultValue& first, const DefaultValue& second)
    {
        first.next = second;
        return first;
    }
};


class Sharedwo
{
public:
    Sharedwo(DefaultValue x) {}
    int zwei;
};


/// Find all the Shared Declarations in a (doxygen provided) xml AST representation of the sources.
///
/// At the moment this is any SharedVar declaration.
///
/// @param xml_file the index-file of the doxygen output (or any else, but we're tailored for the index one)
/// @param tree the vector we put our parsed info into.
/// @return true on success.
extern bool find_shared_decls(const std::string xml_file, std::vector<ShTreeNode> &tree);

} } } // namespace inexor::rpc::gluegen
