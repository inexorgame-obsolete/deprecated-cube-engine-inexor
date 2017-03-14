#pragma once

#include "inexor/gluegen/parse_sharedoption.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <string>
#include <vector>

namespace inexor { namespace rpc { namespace gluegen {

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

    /// The definition of a class instance can already contain shared options, which will get attached to all instances.
    std::vector<attached_option> attached_options;

    /// All children nodes will get copied here. TODO: this should be a clear structure containing sharedvars and subclasses.
    std::vector<ShTreeNode *> nodes;

    /// All ShTreeNodes instances of this type.
    std::vector<ShTreeNode *> instances;

    /// The namespace + the classes name.
    std::string get_name_cpp_full();

    /// The namespace + the classes name but with _ instead of ::.
    std::string get_name_unique();

    /// Sets the node_type of each children to NODE_CLASS_VAR.
    void make_all_children_node_class_var();
};

struct ParserContext;
extern void parse_shared_class_definitions(ParserContext &data);

/// Returns true if this compound xml node has as parent the SharedOption base class.
extern bool is_shared_class_definition_node(const pugi::xml_node class_xml_compound_node);

/// Returns the definition node if this member node fits one (otherwise returns nullptr!).
extern shared_class_definition *is_shared_class_instance_node(const pugi::xml_node xml_member_node, ParserContext &data);

/// Adds an new entry to the instances vector.
extern void parse_class_instance(const pugi::xml_node var_xml, std::string var_namespace, shared_class_definition *class_definition, ParserContext &data);

} } } // namespace inexor::rpc::gluegen
