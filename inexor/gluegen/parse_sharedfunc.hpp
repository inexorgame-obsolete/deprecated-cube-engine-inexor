#pragma once

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <string>
#include <vector>


namespace inexor { namespace rpc { namespace gluegen {

/// looks for shared functions and saves them in the global vector of shared_functions
extern void look_for_shared_functions(std::vector<std::unique_ptr<pugi::xml_document>> &code_ast_xmls);
} } } // namespace inexor::rpc::gluegen
