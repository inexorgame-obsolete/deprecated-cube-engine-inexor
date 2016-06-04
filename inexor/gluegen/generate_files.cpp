#include <algorithm>
#include <fstream>
#include <functional>
#include <tuple>
#include <iostream>

#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <kainjow/mustache.hpp>

#include "inexor/gluegen/generate_files.hpp"
#include "inexor/gluegen/fill_templatedata.hpp"

namespace inexor {
namespace rpc {
namespace gluegen {

void render_proto_file(const std::string &out_path, const std::string &template_path, std::vector<ShTreeNode> &tree, TemplateData &tmpldata)
{

    std::ifstream template_file(template_path);;
    std::string template_file_contents(std::istreambuf_iterator<char>(template_file), {});

    MustacheTemplate tmpl{template_file_contents.c_str()};
    std::ofstream sink{out_path, std::ofstream::trunc};
    tmpl.render(tmpldata, [&sink](const std::string& str) {
        sink << str;
    });


    // TODO: put basic file to std::string functionality in filesystem/ e.g. based on
    // http://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
}

void render_cpp_tree_header(const std::string &out_path, const std::string &template_path, std::vector<ShTreeNode> &tree, TemplateData &tmpldata)
{
    std::ifstream template_file(template_path);;
    std::string template_file_contents(std::istreambuf_iterator<char>(template_file), {});

    MustacheTemplate tmpl{template_file_contents.c_str()};
    std::ofstream sink{out_path, std::ofstream::trunc};
    tmpl.render(tmpldata, [&sink](const std::string& str) {
        sink << str;
    });


}


}
}
}
