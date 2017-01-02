#pragma once

#include <pugiconfig.hpp>
#include <pugixml.hpp>

namespace inexor { namespace rpc { namespace gluegen {

extern void handle_shared_option(const pugi::xml_node &compound_xml);

} } } // namespace inexor::rpc::gluegen
