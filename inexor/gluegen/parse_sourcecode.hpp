#pragma once

#include "inexor/gluegen/tree.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <memory>


namespace inexor { namespace rpc { namespace gluegen {

/// Global singleton switching between verbose or non-verbose output to the console.
extern bool verbose;

/// Find all the Shared Declarations in a (doxygen provided) xml AST representation of the sources.
///
/// At the moment this is any SharedVar declaration.
///
/// @param xml_folder the index-file of the doxygen output (or any else, but we're tailored for the index one)
/// @param tree the vector we put our parsed info into.
/// @return true on success.
extern void find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode *> &tree);


/// Finds in the compound xml node the constructors of this class.xml.
std::vector<pugi::xml_node> find_class_constructors(const pugi::xml_node &class_compound_xml);

/// Finds in the AST xml all nodes containing public variables.
///
/// The path is "sectiondef(kind==public-attrib)/memberdef(kind==variable)"
std::vector<pugi::xml_node> find_class_member_vars(const pugi::xml_node &class_compound_xml);


/// Finds all shared variables or functions in a (parsed) xml file which contain a specific searchphrase.
///
/// @return a list of xml "memberdef" nodes (see comment below) + setting the namespace_of_vars parameter.
/// @param namespace_of_vars will be set to the namespace of the xml document
///       (Doxygen splits source files for us, so all variables in one xml file will be in the same ns.)
/// @param checkid if true the "type"-child (and its childs) are searched for an attribute refid matching the searchphrase,
///        otherwise we check whether the "type"-child contains any text like the searchphrase.
extern std::vector<pugi::xml_node> find_variable_instances(std::unique_ptr<pugi::xml_document> &xml, const std::string searchphrase, std::string &namespace_of_vars, bool checkid = false);

/// Given the parameter list of a constructor, we set default_value and options plus we return the tokenized arg list.
///
/// @param argsstring is formed like ("map", NoSync()|Persistent())       so its (defaultval, sharedoption|sharedoption|..)
/// @param default_value will be set to the first param (in this example "map")
/// @param options the sharedoptions given (the second argument of the constructor-string) will be parsed using parse_shared_option_strings().
/// @warning throws if no default_value is given!
extern const std::vector<std::string> parse_shared_var_constructor_argsstring(std::string name, std::string argsstring, std::string &default_value, std::vector<attached_option> &options);

} } } // namespace inexor::rpc::gluegen
