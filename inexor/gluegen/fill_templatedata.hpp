#pragma once

#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/ParserContext.hpp"

#include <kainjow/mustache.hpp>

#include <vector>
#include <string>

namespace inexor { namespace rpc { namespace gluegen {

using MustacheTemplate = Kainjow::BasicMustache<std::string>;
using TemplateData = MustacheTemplate::Data;

extern TemplateData fill_templatedata(ParserContext &data, const std::string &ns);

} } } // namespace inexor::rpc::gluegen
