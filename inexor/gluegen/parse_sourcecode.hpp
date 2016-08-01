#pragma once

#include <functional>
#include <string>

#include "inexor/gluegen/tree.hpp"

namespace inexor { namespace rpc { namespace gluegen {

class SharedOption
{
    const SharedOption *next;
public:
    friend SharedOption& operator|(SharedOption& first, const SharedOption& second)
    {
        first.next = &second;
        return first;
    }
};

class Range : public SharedOption
{
public:
    /// Parse Template Data: Constructor arguments are data names, values get assigned in the place the constructor gets accessed.
    /// we need it for every possible 
    Range(int min, int max) { }
    Range(float min, float max) { }

    const char *proto_template = "da";
    const char *cpp_receive_template = "da";
    const char *cpp_send_template = "da";
};

// TODO skip last letter and first one
class CustomPath : public SharedOption
{
public:
    CustomPath(const char *path) { }

    const char *proto_template = "da";
    const char *cpp_receive_template = "da";
    const char *cpp_send_template = "da";
};

/// TODO respect default initializer ispersistent = false
class Persistent : public SharedOption
{
public:
    Persistent(bool ispersistent) { }

    const char *proto_template = "da";
    const char *cpp_receive_template = "da";
    const char *cpp_send_template = "da";
};


class Sharedwo
{
public:
    Sharedwo(SharedOption x) {}
    int zwei;
};


/// Find all the Shared Declarations in a (doxygen provided) xml AST representation of the sources.
///
/// At the moment this is any SharedVar declaration.
///
/// @param xml_folder the index-file of the doxygen output (or any else, but we're tailored for the index one)
/// @param tree the vector we put our parsed info into.
/// @return true on success.
extern bool find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree);

} } } // namespace inexor::rpc::gluegen
