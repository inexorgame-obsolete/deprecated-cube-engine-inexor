
#include <vector>
#include <string>

#include <boost/algorithm/string/regex.hpp>

#include "inexor/gluegen/fill_templatedata.hpp"
#include "inexor/gluegen/tree.hpp"

using namespace inexor::rpc::gluegen;

using std::string;
using std::vector;

/// Join the entrys of a vector|sthelsewithranges into a string, using 'd' as the seperator between the parts.
template<typename SinglePassRange, typename Delim>
string join_to_str(SinglePassRange r, Delim d)
{
    std::stringstream s;
    bool first = true;
    for(auto &e : r)
    {
        if(first)
            first = false;
        else
            s << d;
        s << e;
    }
    return s.str();
}

/// C++ equivalent of strtok, tokenizes the input string based on the occurences of delimiter.
/// @param delimiter is actually a boost::regex, so could be used as such!
/// Note: make this a template if needed.
vector<string> split_by_delimter(string input, string delimiter)
{
    using boost::regex;
    using boost::split_regex;

    vector<string> ns;
    split_regex(ns, input, regex(delimiter));
    return std::move(ns);
}

TemplateData fill_templatedata(vector<ShTreeNode> &tree, const string &ns)
{
    TemplateData tmpldata{TemplateData::Type::Object};

    tmpldata["file_comment"] =  "// This file gets generated!\n"
        "// Do not modify it directly but its corresponding template file instead!";

    // namespace string -> protobuf syntax: replace :: with .
    vector<string> ns_list(split_by_delimter(ns, "::"));
    const string &proto_pkg = join_to_str(ns_list, '.');
    tmpldata["package"] = proto_pkg;
    tmpldata["namespace"] = ns;

    TemplateData sharedvars{TemplateData::Type::List};
    int index = 1;
    for(auto node : tree)
    {
        if(node.unique_name.empty())
        {
            std::cerr << "[WARNING] Missing path for " << node.cpp_var << "\n";
        }

        TemplateData curvariable{TemplateData::Type::Object};
        curvariable["proto_type"] = node.protoc_lit;
        curvariable["cpp_type"] = node.type_lit;
        curvariable["type"] = std::to_string(node.type);
        curvariable["index"] = std::to_string(index++);
        curvariable["unique_name"] = node.unique_name;
        curvariable["path"] = node.path;
        curvariable["cpp_name"] = node.cpp_var;

        vector<string> ns(split_by_delimter(node.cpp_var, "::"));
        curvariable["cpp_raw_name"] = ns.back();

        ns.pop_back(); // remove the raw function name
        TemplateData namespace_sep_open{TemplateData::LambdaType{
            [ns](const string&)
        {
            std::stringstream ss;
            for(auto &tok : ns)
            {
                if(tok.empty())continue;
                ss << "namespace ";
                ss << tok;
                ss << " { ";
            }
            return ss.str();
        }}};

        TemplateData namespace_sep_close{TemplateData::LambdaType{
            [ns](const std::string&)
        {
            std::stringstream ss;
            for(auto &tok : ns)
            {
                if(tok.empty())continue;
                ss << " }";
            }
            return ss.str();
        }}};

        curvariable["namespace_sep_open"] = namespace_sep_open;
        curvariable["namespace_sep_close"] = namespace_sep_close;

        sharedvars << curvariable;
    }
    tmpldata["shared_vars"] = sharedvars;

    return tmpldata;
}

