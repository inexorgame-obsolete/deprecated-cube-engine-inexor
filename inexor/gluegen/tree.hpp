#pragma once

#include "inexor/gluegen/parse_sharedclass.hpp"
#include "inexor/gluegen/parse_sharedfunc.hpp"
#include "inexor/gluegen/parse_sharedoption.hpp"

#include <string>
#include <vector>
#include <list>
#include <unordered_map>

namespace inexor {
namespace rpc {
namespace gluegen {

class ShTreeNode {
public:

    /// This node could either be a variable (as member of a class or as global one) or a class.
    /// A class would contain a subtree and passes its options on to it.
    enum NODE_TYPE
    {
        NODE_GLOBAL_VAR,      /// We are a global SharedVar
        NODE_CLASS_SINGLETON, /// We are a global instance of a SharedClass (no pointer)
        NODE_CLASS_VAR        /// We are a variable inside an NODE_CLASS_SINGLETON (so this node is a subnode)
    } node_type;

    /// A pointer to the parent if this node is a NODE_CLASS_VAR.
    /// Otherwise this is a nullptr.
    ShTreeNode *parent = nullptr;

    /// If this is a NODE_CLASS_SINGLETON, this is a subtree containing all SharedVars or instanced subclasses.
    std::vector<ShTreeNode *> children;

    /// The canonical name (including ::) of the c++ variable instance.
    /// If its NODE_GLOBAL_VAR, this is e.g. "::inexor::rendering::num_screens"
    /// If its NODE_CLASS_SINGLETON, this will return the full name of the class instance (e.g. "::inexor::rendering::Screen")
    /// If its NODE_CLASS_VAR, this is e.g. "::inexor::rendering::Screen.width"
    std::string get_name_cpp_full();

    /// If this is a NODE_CLASS_VAR this will return the first parents name
    /// (e.g. Screen)
    std::string get_first_parent_name_short();

    /// If this is a NODE_CLASS_VAR this will return the first parents name + prepended namespace
    /// (e.g. inexor::rendering::Screen)
    std::string get_first_parent_name_full();

    /// The c++ variable name excluding any namespaces.
    /// e.g. "num_screens" or "Screen" or "width"
    std::string get_name_cpp_short();

    /// Name with prepended namespace (and classname), connected with underspaces.
    /// e.g. "_inexor_rendering_num_screens" or "_inexor_rendering_Screen_width"
    std::string get_name_unique();

    /// The C++ namespace of the variable.
    /// e.g. inexor::rendering.
    std::string get_namespace();

    /// Path of the variable inside the tree (including the node name ofc).
    /// e.g. inexor/rendering/num_screens or inexor/rendering/Screen/ or inexor/rendering/Screen/width.
    std::string get_path();

    /// The full type literal of the c++ type including SharedVar.
    /// e.g. "SharedVar<char*>" or "inexor::rendering::Screen" or "SharedVar<int>"
    const char *get_type_cpp_full();

    /// The C++ template type of a SharedVar ("char*"/"int"/"float")
    /// or a SharedClass("Classname<SharedVar<int>>" or "ClassName1<ClassName2>").
    /// @return Gives back anything between '<' and the first ',' of the full_type string
    /// @note For NODE_CLASS_SINGLETON its an edge case to handle sharedlists (SharedList<player> players).
    std::string get_template_type();

    /// The protocol buffers type for this node.
    /// If its NODE_GLOBAL_VAR or NODE_CLASS_VAR, this is string/float/int32
    /// If its NODE_CLASS_SINGLETON, this will return get_name_unique (e.g. "_inexor_rendering_Screen")
    const char *get_type_protobuf();

    /// The ambigous(protobuf, c++,fullc++wrapped) numeric type in case this is a NODE_GLOBAL_VAR or NODE_CLASS_VAR.
    int get_type_numeric();

    /// All SharedVars MUST have a default_value to compile.
    /// In case of a NODE_CLASS_SINGLETON this is empty.
    const std::string get_default_value() const;

    /// In case this is a NODE_CLASS_SINGLETON this is a copy of the corresponding class definition.
    shared_class_definition *class_definition = nullptr;

    /// In case this is a NODE_CLASS_SINGLETON and its a template, we link to the shared classes definition of the template arg.
    /// @note This is for handling the edge case of a SharedLists, since there we're interested in the templated arg 
    //        (SharedList<player> players).
    shared_class_definition *template_type_definition = nullptr;

    /// All options attached when instancing this variable.
    const std::vector<attached_option> attached_options;

    /// Tell this NODE_GLOBAL_VAR about its parent, to make it a NODE_CLASS_VAR.
    /// So basically you do this in a subsequent run for all NODE_CLASS_SINGLETONs children.
    void set_node_parent(ShTreeNode *parent);

    /// If this is a NODE_CLASS_SINGLETON we do call set_node_parent for any child.
    /// @warning you need to be sure that this node and all childs are already on the memory place they belong,
    ///          if you're pushing ShTreeNodes to a vector not operating on the heap, make sure you call this function **afterwards**.
    void set_all_childrens_parent_entry(bool recursively = true);   /// If this is a NODE_CLASS_SINGLETON we do call set_node_parent for any child.

    /// Sets the node_type of each children (e.g. to NODE_CLASS_VAR).
    void set_all_childrens_type(NODE_TYPE ntype);

    /// Creates a Node of type NODE_GLOBAL_VAR.
    /// Use set_node_parent to change it to a NODE_CLASS_VAR.
    /// @param full_cpp_type_dcl The literal type declaration (e.g. "SharedVar<int>") from which the type_numeric will be deduced.
    ShTreeNode(const std::string &full_cpp_type_dcl, const std::string &full_cpp_name, const std::string &var_namespace_,
               const std::string &default_val, std::vector<attached_option> &so_constructor_arguments);

    // 2. name of file containing the type declaration shared_class_definition class_instance_type
    /// @param full_cpp_type_dcl The literal type declaration (e.g. "SharedVar<int>" or "inexor::rendering::Screen").
    /// @param full_cpp_name The literal variable name (e.g. "mapmodel_amount").
    /// @param var_namespace_ The namespace of the variable (e.g. "inexor::rendering").
    ShTreeNode(const std::string &full_cpp_type, const std::string &cpp_name, const std::string &var_namespace_,
               shared_class_definition *class_definition_, std::vector<attached_option> &so_constructor_arguments);

    /// Copy constructor, creates a new subtree similar of all childs of the given node.
    /// So this allocates all children again on the heap.
    ShTreeNode(const ShTreeNode *old);

    /// Known SharedVar types
    enum type_t
    {
        t_none = -1, // e.g. a class instance
        t_cstring,
        t_float,
        t_int
    };

private:

    /// The ambigous(protobuf, c++,fullc++wrapped) numeric type.
    type_t type_numeric;

    /// Internal use, so we just store type_numeric and lookup the rest in here.
    /// Static helper class to provide language dependend strings for the different types.
    const struct
    {
        /// The full type literal of the c++ type including SharedVar.
        /// e.g. "SharedVar<char*>"
        const char *type_cpp_full;

        /// The c++ type literal of wrapped c++ primitive type ("char*"/"int"/"float").
        const char *type_cpp_primitive;

        /// The protocol buffers type for this node
        const char *type_protobuf;
    } type_lookup[t_int+1] = {
        {"SharedVar<char*>", "char*", "string"},
        {"SharedVar<float>", "float", "float"},
        {"SharedVar<int>",   "int",   "int32"},
    };

    /// We use this function in the descriptor since we save type_numeric but the constructor takes the full cpp type.
    static const std::unordered_map<std::string, ShTreeNode::type_t> type_cpp_template_to_numeric;


    // internal cached of the corresponding retrival function get_xy().
    std::string full_type, name_cpp_short, var_namespace, path, default_value;
};

}
}
}
