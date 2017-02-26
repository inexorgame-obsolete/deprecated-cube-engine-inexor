#pragma once

#include "inexor/gluegen/ParserContext.hpp"
#include "inexor/gluegen/tree.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <memory>


namespace inexor { namespace rpc { namespace gluegen {

/// Find all the Shared Declarations in a (doxygen provided) xml AST representation of the sources.
///
/// At the moment these are SharedVars, SharedClasses and SharedFunctions.
///
/// @param xml_folder the index-file of the doxygen output (or any else, but we're tailored for the index one)
/// @param data the struct we put our parsed info into.
extern void find_shared_decls(const std::string xml_folder, ParserContext &data);


/// Finds in the compound xml node the constructors of this class.xml.
extern std::vector<pugi::xml_node> find_class_constructors(const pugi::xml_node &class_compound_xml);

/// Splits the initializer list of the constructor ( ": x(0), y(0) {" into a map.
/// Key = member name, second string = arguments of the members constructor (e.g. {"x", "0"}, {"y", "0"})
extern std::unordered_map<std::string, std::string> get_class_initialized_member_map(const pugi::xml_node &class_compound_xml);

/// Finds in the AST xml all nodes containing public variables.
///
/// The path is "sectiondef(kind==public-attrib)/memberdef(kind==variable)"
extern std::vector<pugi::xml_node> find_class_member_vars(const pugi::xml_node &class_compound_xml);

/// Given the parameter list of a constructor, we set default_value and options plus we return the tokenized arg list.
///
/// @param argsstring is formed like ("map", NoSync()|Persistent())       so its (defaultval, sharedoption|sharedoption|..)
/// @param default_value will be set to the first param (in this example "map")
/// @param options the sharedoptions given (the second argument of the constructor-string) will be parsed using parse_attached_options_string().
/// @warning throws if no default_value is given!
extern const std::vector<std::string> parse_shared_var_constructor_argsstring(std::string name, std::string argsstring, std::string &default_value, std::vector<attached_option> &options);

/// This returns the namespace of a given compound xml node (if its not a class definition xml file).
/// Doxygen has dedicated files for any namespaced variables.
std::string get_namespace_of_namespace_file(const pugi::xml_node compound_xml);

extern void parse_sharedvar_of_class(const pugi::xml_node var_xml, std::string var_namespace, std::string class_name,
                              const std::unordered_map<std::string, std::string> &class_constructor_init_map, std::vector<ShTreeNode *> &tree);

} } } // namespace inexor::rpc::gluegen
