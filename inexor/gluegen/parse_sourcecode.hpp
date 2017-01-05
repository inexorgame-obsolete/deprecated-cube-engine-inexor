#pragma once

#include "inexor/gluegen/tree.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <functional>
#include <string>
#include <sstream>
#include <vector>


namespace inexor { namespace rpc { namespace gluegen {


/// Find all the Shared Declarations in a (doxygen provided) xml AST representation of the sources.
///
/// At the moment this is any SharedVar declaration.
///
/// @param xml_folder the index-file of the doxygen output (or any else, but we're tailored for the index one)
/// @param tree the vector we put our parsed info into.
/// @return true on success.
extern void find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree);


/// Finds in the compound xml node the constructors of this class.xml.
std::vector<pugi::xml_node> find_class_constructors(const pugi::xml_node &class_compound_xml);

/// Finds in the AST xml all nodes containing public variables.
///
/// The path is "sectiondef(kind==public-attrib)/memberdef(kind==variable)"
std::vector<pugi::xml_node> find_class_member_vars(const pugi::xml_node &class_compound_xml);

} } } // namespace inexor::rpc::gluegen
