#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include <boost/program_options.hpp>

#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/generate_files.hpp"
#include "inexor/gluegen/fill_templatedata.hpp"


using namespace inexor::rpc::gluegen;
namespace po = boost::program_options;
using std::string;
using std::vector;

void usage(const std::string &ex, const po::options_description &params) {
    std::cerr
        << "Inexor gluegen       Generates the glue code for the tree API."
        << "\n\nEXAMPLES"
        << "\n\n  (1) " << ex << " --help"
        << "\n\n  (2) " << ex << " --out-proto FILE --out-header FILE --template-proto FILE --template-header FILE --namespace NAMESPACE --XML-AST-folder PATH"
        << "\n\n\nDESCRIPTION"
        << "\n  (1) Show this help page"
        << "\n  (2) Generate the glue code."
        << "\n      Note: Options are order independent, so the position of the arguments do not matter."
        << "\n\n\n" << params << "\n";
}


/// Our generation of glue code works in 3 steps:
///   1) use doxygen to parse the source and spit out the AST in a XML
///   2) use find any Shared Declarations in this AST (parsing the XML)
///   3) use the gathered data to render the templates
int main(int argc, const char **argv)
{
    // Parse and handle command line arguments

    po::variables_map cli_config;
    po::options_description params("PARAMETERS");
    params.add_options()
        ("help", "Print this help message")
        ("namespace", po::value<string>(), "The namespace to use in the generated protocol file and c++ source files. (use C++ :: notation)")
        ("out-proto", po::value<string>(), "The .proto file to write the protocol description to.")
        ("out-header", po::value<string>(), "The header `.hpp` file the c++ tree adapter code should be generated in")
        ("template-proto", po::value<string>(), "The mustache template which gets used to render(generate) the .proto file")
        ("template-header", po::value<string>(), "The mustache template which gets used to render(generate) the '.hpp' header file")
        ("XML-AST-folder", po::value<string>(), "The folder containing the doxygen xml (AST) output. We scan those for Shared Declarations");

    std::string exec{argv[0]};

    vector<string> args(argv+1, argv+argc);
    std::cout << "Used command line options: \n";
    for(auto arg : args) std::cout << arg << "\n";

    try {
        po::parsed_options parsed = po::command_line_parser(args).options(params).run();
        po::store(parsed, cli_config);
        po::notify(cli_config);
    } 
    catch(po::error &e) {
        std::cerr << "Failed to parse the options: " << e.what() << "\n\n";
        usage(exec, params);
        return 1;
    }

    auto c = [&cli_config](const std::string &s)
    {
        return cli_config.count(s);
    };

    if(c("help") || !c("namespace") || !c("out-proto") || !c("out-header") || !c("XML-AST-folder") 
                 || !c("template-proto") || !c("template-header"))
    {
        usage(exec, params);
        return 0;
    }

    const string &ns_str = cli_config["namespace"].as<string>();
    const string &proto_file = cli_config["out-proto"].as<string>();
    const string &hpp_file = cli_config["out-header"].as<string>();
    const string &hpp_template = cli_config["template-header"].as<string>();
    const string &proto_template = cli_config["template-proto"].as<string>();
    const string &xml_AST_file = cli_config["XML-AST-folder"].as<string>();

    // Read the list of variables

    std::vector<ShTreeNode> tree;

    find_shared_decls(xml_AST_file, tree); // fill the tree vector

    TemplateData templdata = fill_templatedata(tree, ns_str);

    // Write the protoc file
    render_proto_file(proto_file, proto_template, tree, templdata);

    // Write cpp files
    render_cpp_tree_header(hpp_file, hpp_template, tree, templdata);

    return 0;
}
