#include <fstream>

#include <kainjow/mustache.hpp>

#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/generate_files.hpp"
#include "inexor/gluegen/fill_templatedata.hpp"

using namespace inexor::filesystem;

namespace inexor {
namespace rpc {
namespace gluegen {

void render_proto_file(const std::string &out_path, const std::string &template_path, std::vector<ShTreeNode> &tree, TemplateData &tmpldata)
{
    const std::string template_file_contents(filecontents(template_path));

    MustacheTemplate tmpl{template_file_contents.c_str()};
    std::ofstream sink{out_path, std::ofstream::trunc};
    tmpl.render(tmpldata, [&sink](const std::string& str) {
        sink << str;
    });
}

void render_cpp_tree_data(const std::string &out_path, const std::string &template_path, std::vector<ShTreeNode> &tree, TemplateData &tmpldata)
{
    const std::string template_file_contents(filecontents(template_path));

    MustacheTemplate tmpl{template_file_contents.c_str()};
    std::ofstream sink{out_path, std::ofstream::trunc};
    tmpl.render(tmpldata, [&sink](const std::string& str) {
        sink << str;
    });
}


}
}
}
