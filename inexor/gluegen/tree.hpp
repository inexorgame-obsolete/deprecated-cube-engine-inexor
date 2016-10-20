#pragma once

#include <string>
#include <vector>
#include <list>
#include <unordered_map>

namespace inexor {
namespace rpc {
namespace gluegen {

/// To make our glue generation more flexible we invented Shared Option classes,
/// which contain info about how to render stuff and which are used in the C++ Tree API.
struct optionclass
{
    std::string name;
    bool hasdefaultvals = false;

    /// All constructor arguments: name first, defaultvalue second.
    // we dont have type deduction!
    struct arg
    {
        std::string name;
        std::string default_value;
    };
    std::vector<arg> constructor_args;

    /// "const char *" members are template data for our shared declarations,
    /// but also they get rendered with the previously available info about that shared declaration.
    std::vector<arg> template_hybrids;

    optionclass() {}
    optionclass(std::string &&class_name) : name(class_name) {}
};
/// name, optionclass instance
extern std::unordered_map<std::string, optionclass> optionclasses;

class ShTreeNode {
public:
    /// The canonical name (including ::) of the c++ variable.
    /// e.g. "::inexor::rendering::screen::width"
    std::string get_name_cpp_full();

    /// The c++ variable name excluding any namespaces.
    /// e.g. "width"
    std::string get_name_cpp_short();

    /// Name with prepended namespace, connected with underspaces.
    /// e.g. "_inexor_rendering_screen_width"
    std::string get_name_unique();

    /// The C++ namespace of the variable.
    /// e.g. inexor::rendering::screen.
    std::string get_namespace();

    /// Path of the variable inside the tree.
    /// Atm we use only the namespace, e.g. inexor/rendering/screen/.
    std::string get_path();

    /// The full type literal of the c++ type including SharedVar.
    /// e.g. "SharedVar<char*>"
    const char *get_type_cpp_full();

    /// The c++ type literal of wrapped c++ primitive type ("char*"/"int"/"float").
    const char *get_type_cpp_primitive();

    /// The protocol buffers type for this node
    const char *get_type_protobuf();

    /// The ambigous(protobuf, c++,fullc++wrapped) numeric type.
    int get_type_numeric();

    /// The protocol buffers variable index; 0 if unset
    uint64_t protoc_idx = 0;

    /// A SharedOption used when declaring this variable inside the constructor.
    struct shared_option_arg
    {
        /// The sharedoptions name.
        std::string class_name;
        /// The constructor args for the sharedoption instance.
        std::vector<std::string> constructor_args;
    };

    /// We use this list to handle shared options.
    const std::vector<shared_option_arg> shared_options;

    /// @param full_cpp_type_dcl The literal type declaration (e.g. "SharedVar<int>") from which the type_numeric will be deduced.
    ShTreeNode(const std::string &full_cpp_type_dcl, const std::string &full_cpp_name, const std::string &var_namespace_,
               const std::vector<shared_option_arg> &so_constructor_arguments);

    /// Known SharedVar types
    enum type_t
    {
        t_cstring = 0,
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
    std::string name_cpp_short;
    std::string var_namespace;
    std::string path;
};

}
}
}
