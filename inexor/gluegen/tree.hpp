#pragma once

#include <string>
#include <vector>
#include <list>
#include <unordered_map>

namespace inexor {
namespace rpc {
namespace gluegen {

struct name_defaultvalue_tupel
{
    std::string name;
    std::string default_value;
};
typedef std::vector<name_defaultvalue_tupel> name_defaultvalue_vector;

/// A declaration of a class with a "SharedOption" parent class.
///
/// To make our glue generation more flexible we invented Shared Option classes,
/// which contain info about how to render stuff and which are used in the C++ Tree API.
///
/// class xy : SharedOption {
///     xy(T <paramname> = <paramdefvalue>, S <param2name> = <param2defvalue>, ......) {}
///     const char *<membername> = <membertemplate>;
/// };
struct so_class_definition
{
    /// The name of the class.
    std::string name;

    /// Whether or not the constructor has default values is important for subsequent
    bool constructor_has_default_values = false;

    /// All constructor arguments: name first, defaultvalue second.
    /// since its an ordered map we have the positions of the arguments.
    // we dont have type deduction!
    name_defaultvalue_vector constructor_args;

    /// "const char *" members are template "partials" (see mustache docs) for our shared declarations.
    /// 
    /// They may contain template data entries previously available or those named the same as the constructor parameters.
    name_defaultvalue_vector const_char_members;

    so_class_definition() {}
    so_class_definition(std::string &&class_name) : name(class_name) {}
};

extern std::unordered_map<std::string, so_class_definition> so_class_definitions;

class ShTreeNode;

struct shared_class_definition
{
    /// The name of the SharedClass e.g. "Screen".
    std::string class_name;

    /// The reference identification number used by doxygen.
    /// We can search for it and every instance contains this refid somewhere.
    std::string refid;

    /// The namespace of the SharedClass definition e.g. "inexor::metainfo"
    /// @warning this could be some other namespace as the instances one!
    ///          for example you could have a inexor::metainfo::Screen inexor::rendering::screen1;
    std::string definition_namespace;

    /// We REQUIRE the file to be defined in a cleanly includeable headerfile.
    /// (There is no chance of using forward declarations of the class for the synchronisation code.)
    std::string containing_header;

    std::vector<ShTreeNode> nodes;
};

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
    std::vector<ShTreeNode> children;

    /// The canonical name (including ::) of the c++ variable instance.
    /// If its NODE_GLOBAL_VAR, this is e.g. "::inexor::rendering::num_screens"
    /// If its NODE_CLASS_SINGLETON, this will return the full name of the class instance (e.g. "::inexor::rendering::Screen")
    /// If its NODE_CLASS_VAR, this is e.g. "::inexor::rendering::Screen.width"
    std::string get_name_cpp_full();

    /// If this is a NODE_CLASS_VAR this will return the first parents name
    /// (Needed for e.g. declaring an extern)
    std::string get_first_parent_name();

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

    /// The C++ template type of a SharedVar ("char*"/"int"/"float").
    /// @note Works only for NODE_GLOBAL_VAR and NODE_CLASS_VAR (otherwise returns nullptr)
    const char *get_type_cpp_primitive();

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
    shared_class_definition class_definition;

    /// A SharedOption instance used when declaring this variable.
    /// (used inside the constructor: "SharedVar<int> xy(0, NoSync()|Persistent(true))").
    /// -> option_name = "Persistent" constructor_args.push_back("true").
    struct attached_so
    {
        /// The sharedoptions name.
        std::string name;
        /// The constructor args for the sharedoption instance.
        std::vector<std::string> constructor_args;
    };

    /// All options attached when instancing this variable.
    const std::vector<attached_so> attached_options;



    /// @param full_cpp_type_dcl The literal type declaration (e.g. "SharedVar<int>") from which the type_numeric will be deduced.
    ShTreeNode(const std::string &full_cpp_type_dcl, const std::string &full_cpp_name, const std::string &var_namespace_,
               const std::string &default_val, std::vector<attached_so> &so_constructor_arguments, ShTreeNode *parent = nullptr);

    // 2. name of file containing the type declaration shared_class_definition class_instance_type
    /// @param full_cpp_type_dcl The literal type declaration (e.g. "SharedVar<int>" or "inexor::rendering::Screen").
    /// @param full_cpp_name The literal variable name (e.g. "mapmodel_amount").
    /// @param var_namespace_ The namespace of the variable (e.g. "inexor::rendering").
    ShTreeNode(const std::string &full_cpp_type, const std::string &cpp_name, const std::string &var_namespace_,
               shared_class_definition class_definition_, std::vector<attached_so> &so_constructor_arguments);

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
    };// SharedList<ClassName>

    /// We use this function in the descriptor since we save type_numeric but the constructor takes the full cpp type.
    static const std::unordered_map<std::string, ShTreeNode::type_t> type_cpp_template_to_numeric;


    // internal cached of the corresponding retrival function get_xy().
    std::string full_type, name_cpp_short, var_namespace, path, default_value;
};

struct class_node : ShTreeNode
{
  //  shared_class_definition class_definition;
};

struct variable_node : ShTreeNode
{
    // Changes:
    // extern directly not the containing class-instance
};

struct class_member_var : ShTreeNode
{
    // Changes:
    // Use class options. Prepend class path to namespace.
    // Don't iterate var as global var.
    // index begins for every class from 0
    // Don't need full c++ name anymore, but class name for extern.
    // path() is path of class + path of var
    //        path of class: default = namespace + classname, otherwise CustomPath("...")-attribute
    //        path of var: default = variablename, otherwise CustomPath("...")
    //        -> path = namespace + if(isclassmember) classname + (endif) cpp_short_name
};

/// A Class derived from SharedClass gets reflected automagically. This is the (shrinked) AST representation to enable the magic.
//struct shared_class : parsed_class_base
//{
//    std::string class_name_short;
//    std::string class_namespace;
//
//    /// We use this list to handle shared options applied to all SharedVars we contain.
//    const std::vector<shared_option_arg> shared_options;
//
//    const std::vector<class_member_var> member_vars;
//
//    void add_member_var(class_member_var)
//    {
//
//    }
//};

}
}
}
