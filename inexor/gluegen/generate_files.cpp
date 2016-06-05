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



// TODO: put into filesystem/
// taken from http://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
const std::string filecontents(const std::string &filename)
{
    std::ifstream file_stream(filename);
    std::string ret;
    char buffer[4096];
    while(file_stream.read(buffer, sizeof(buffer)))
        ret.append(buffer, sizeof(buffer));
    ret.append(buffer, file_stream.gcount());
    return ret;
}

void render_proto_file(const std::string &out_path, const std::string &template_path, std::vector<ShTreeNode> &tree, TemplateData &tmpldata)
{
    const std::string template_file_contents(filecontents(template_path));

    MustacheTemplate tmpl{template_file_contents.c_str()};
    std::ofstream sink{out_path, std::ofstream::trunc};
    tmpl.render(tmpldata, [&sink](const std::string& str) {
        sink << str;
    });
}

void render_cpp_tree_header(const std::string &out_path, const std::string &template_path, std::vector<ShTreeNode> &tree, TemplateData &tmpldata)
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
