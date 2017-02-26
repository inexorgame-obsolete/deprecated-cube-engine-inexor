#pragma once

#include <string>

#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/fill_templatedata.hpp"

namespace inexor {
namespace rpc {
namespace gluegen {

extern void render_proto_file(const std::string &out_path, const std::string &template_path, TemplateData &tmpldata);
extern void render_cpp_tree_data(const std::string &out_path, const std::string &template_path, TemplateData &tmpldata);
}
}
}
