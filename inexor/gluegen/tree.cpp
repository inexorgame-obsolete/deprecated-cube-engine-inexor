
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "inexor/gluegen/tree.hpp"

namespace inexor {
namespace rpc {
namespace gluegen {

using std::unordered_map;
using std::string;
using boost::algorithm::replace_all_copy;
using boost::algorithm::replace_all;


std::vector<optionclass> optionclasses;


/// Maps C++ string type declarations to the numeric type.
/// SharedVar<float> -> float
const std::unordered_map<std::string, ShTreeNode::type_t> ShTreeNode::type_cpp_template_to_numeric ={
    {"SharedVar<char*>", ShTreeNode::t_cstring},
    {"SharedVar<float>", ShTreeNode::t_float},
    {"SharedVar<int>", ShTreeNode::t_int}
};

ShTreeNode::ShTreeNode(const std::string &full_cpp_type_dcl, const std::string &full_cpp_name, const std::vector<shared_option_arg> &so_constructor_arguments)
                          : name_cpp_full(full_cpp_name), shared_options(so_constructor_arguments)
{
    std::string type_templ_short(full_cpp_type_dcl);
    replace_all(type_templ_short, " ", "");
    type_numeric = type_cpp_template_to_numeric.at(type_templ_short);
}


const char * ShTreeNode::get_type_cpp_full()
{
    return type_lookup[type_numeric].type_cpp_full;
}

const char * ShTreeNode::get_type_cpp_primitive()
{
    return type_lookup[type_numeric].type_cpp_primitive;
}

const char * ShTreeNode::get_type_protobuf()
{
    return type_lookup[type_numeric].type_protobuf;
}


std::string ShTreeNode::get_name_cpp_full()
{
    return name_cpp_full;
}

std::string ShTreeNode::get_name_unique()
{
    return replace_all_copy(get_path(), "/", "_");
}

std::string ShTreeNode::get_path()
{
    if(path.empty())
    {
        path = replace_all_copy(name_cpp_full, "::", "/");
        replace_all(path, "/inexor/", "/");
    }
    return path;
}

}
}
}

