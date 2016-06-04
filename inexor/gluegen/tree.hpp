#pragma once

#include <string>
#include <regex>
#include <utility>
#include <unordered_map>

#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "inexor/util/InexorException.hpp"

namespace inexor {
namespace rpc {
namespace gluegen {

class ShTreeNode {
public:

    /// Known C++ SharedVar types
    enum cpp_type_t {
        t_cstring = 0,
        t_float,
        t_int
    };

    static const std::string protoc_types[3];

    /// Maps C++ string type declarations to the numeric,
    /// unambiguity types above
    static const std::unordered_map<std::string, cpp_type_t> type_parsers;

    /// The numeric types above to their protocol buffers
    /// equivalents
    //static const std::unordered_map<cpp_type_t, std::string> protoc_types;

    /// The canonical name (including ::) of the inexor c++ variable
    std::string cpp_var;

    /// Path of the variable inside the tree
    std::string path;

    /// name with prepended namespace, connected with underspaces.
    std::string unique_name;

    /// The type literal of the c++ type
    std::string type_lit;

    /// C++ type of the variable
    cpp_type_t type;

    /// The protocol buffers type for this node
    std::string protoc_lit;

    /// The protocol buffers variable index; 0 if unset
    uint64_t protoc_idx = 0;

    /// @param type_decl The literal type declaration (e.g.
    ///     "int" or "char *") from which the correct index
    ///     for type will be deduced
    ShTreeNode(const std::string &type_decl
        , const std::string &cpp_var, const std::string &path)
        : cpp_var{cpp_var}, path{path} {
        _init_mangled_path();
        _init_type(type_decl);
    }

    /// @param type_decl The literal type declaration (e.g.
    ///     "int" or "char *") from which the correct index
    ///     for type will be deduced
    ShTreeNode(const std::string &type_decl
        , std::string &&cpp_var, std::string &&path)
        : cpp_var{ std::move(cpp_var) }, path{ std::move(path) } {
        _init_mangled_path();
        _init_type(type_decl);
    }

private:
    void _init_mangled_path() {
        using boost::algorithm::replace_all_copy;
        unique_name = replace_all_copy(path, "/", "_");
    }

    void _init_type(const std::string &type_decl) {
        type = type_parsers.at(type_decl);
        type_lit = type_decl;
        protoc_lit = protoc_types[type];
    }
};

typedef std::vector<ShTreeNode> ShTree;

}
}
}
