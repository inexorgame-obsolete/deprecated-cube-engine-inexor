
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "inexor/gluegen/tree.hpp"
#include "tree.hpp"

namespace inexor {
namespace rpc {
namespace gluegen {

using std::unordered_map;
using std::string;
using boost::algorithm::replace_all_copy;
using boost::algorithm::replace_all;


unordered_map<string, so_class_definition> so_class_definitions;


/// Maps C++ string type declarations to the numeric type.
/// SharedVar<float> -> float
const std::unordered_map<std::string, ShTreeNode::type_t> ShTreeNode::type_cpp_template_to_numeric = {
    {"SharedVar<char*>", ShTreeNode::t_cstring},
    {"SharedVar<float>", ShTreeNode::t_float},
    {"SharedVar<int>", ShTreeNode::t_int}
};


ShTreeNode::ShTreeNode(const std::string &full_cpp_type, const std::string &cpp_name, const std::string &var_namespace_,
                       const std::string &default_val, std::vector<attached_so> &so_constructor_arguments)
                          : name_cpp_short(cpp_name), var_namespace(var_namespace_), full_type(full_cpp_type),
                            default_value(default_val), attached_options(so_constructor_arguments)
{
    std::string type_templ_short(full_cpp_type);
    replace_all(type_templ_short, " ", "");
    type_numeric = type_cpp_template_to_numeric.at(type_templ_short);
    node_type = NODE_GLOBAL_VAR;
}

ShTreeNode::ShTreeNode(const std::string &full_cpp_type, const std::string &cpp_name, const std::string &var_namespace_,
                       shared_class_definition class_definition_, std::vector<attached_so>& so_constructor_arguments)
                            : name_cpp_short(cpp_name), var_namespace(var_namespace_), full_type(full_cpp_type),
                              class_definition(class_definition_), attached_options(so_constructor_arguments)
{
    node_type = NODE_CLASS_SINGLETON;
    type_numeric = t_none;
}

ShTreeNode::ShTreeNode(const ShTreeNode *old)
    : name_cpp_short(old->name_cpp_short), var_namespace(old->var_namespace), full_type(old->full_type),
    class_definition(old->class_definition), attached_options(old->attached_options), // TODO attached options should differ
    node_type(old->node_type), type_numeric(old->type_numeric), default_value(old->default_value)
{
    // alloc new children
    for(ShTreeNode *child : old->children)
    {
        children.push_back(new ShTreeNode(child));
        children.back()->parent = this;
    }
}

void ShTreeNode::set_node_parent(ShTreeNode *parent)
{
    this->parent = parent;
    node_type = NODE_CLASS_VAR;
}

void ShTreeNode::set_all_childrens_parent_entry(bool recursively)
{
    for(ShTreeNode *child : children)
    {
        child->set_node_parent(this);
        if(recursively) child->set_all_childrens_parent_entry(true);
    }
}

const char *ShTreeNode::get_type_cpp_full()
{
    if(node_type==NODE_CLASS_SINGLETON) return nullptr;
    return full_type.c_str();
}

const char *ShTreeNode::get_type_cpp_primitive()
{
    if(node_type==NODE_CLASS_SINGLETON) return nullptr;
    return type_lookup[type_numeric].type_cpp_primitive;
}

const char * ShTreeNode::get_type_protobuf()
{
    if(node_type==NODE_CLASS_SINGLETON) return get_name_unique().c_str();

    return type_lookup[type_numeric].type_protobuf;
}

int ShTreeNode::get_type_numeric()
{
    return type_numeric;
}

const std::string ShTreeNode::get_default_value()
const {
    return default_value;
}


std::string ShTreeNode::get_name_cpp_full()
{
    if(node_type==NODE_CLASS_VAR)
    {
        assert(parent != nullptr);
        return parent->get_name_cpp_full() + "." + name_cpp_short;
    }
    return var_namespace + (var_namespace.empty() ? "" : "::") + name_cpp_short;
}

std::string ShTreeNode::get_first_parent_name()
{
    if(!parent) return "";
    ShTreeNode *cur_par;
    for(cur_par = parent; cur_par!=nullptr; cur_par = cur_par->parent); // go to the uppermost
    return cur_par->get_name_cpp_short();
}

std::string ShTreeNode::get_name_cpp_short()
{
    return name_cpp_short;
}

std::string ShTreeNode::get_name_unique()
{
    return replace_all_copy(get_path(), "/", "_");
}

std::string ShTreeNode::get_namespace()
{
    return var_namespace;
}

std::string ShTreeNode::get_path()
{
    if(path.empty())
    {
        path = "/" + replace_all_copy(get_name_cpp_full(), "::", "/");
        replace_all(path, ".", "/");
        replace_all(path, "/inexor/", "/");
    }
    return path;
}

}
}
}

