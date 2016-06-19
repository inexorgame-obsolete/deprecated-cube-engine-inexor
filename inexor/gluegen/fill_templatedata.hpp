#pragma once

#include <vector>
#include <string>

#include <kainjow/mustache.hpp>

#include "inexor/gluegen/tree.hpp"

using MustacheTemplate = Kainjow::BasicMustache<std::string>;
using TemplateData = MustacheTemplate::Data;

extern TemplateData fill_templatedata(std::vector<inexor::rpc::gluegen::ShTreeNode> &tree, const std::string &ns);
