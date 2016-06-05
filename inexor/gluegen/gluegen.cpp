#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/range.hpp>
#include <boost/algorithm/string/regex.hpp>

#include <clang/Tooling/CommonOptionsParser.h>

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
        << "\n\n  (2) " << ex << " --out-proto FILE --out-header FILE --template-proto FILE --template-header FILE --namespace NAMESPACE \"CLANG_OPTIONS\" --parse-file FILE"
        << "\n\n  (3) " << ex << " --out-proto FILE --out-header FILE --template-proto FILE --template-header FILE --namespace NAMESPACE \"CLANG_OPTIONS\" --parse-file FILE1 --parse-file FILE2 --parse-file FILE3"
        << "\n\n  (4) " << ex << " --out-proto FILE --out-header FILE --template-proto FILE --template-header FILE --namespace NAMESPACE \"CLANG_OPTIONS\" --parse-file FILE1 FILE2 FILE3"
        << "\n\n\nDESCRIPTION"
        << "\n  (1) Show this help page"
        << "\n  (2) Generate the glue code. Note the quotes around the compile-options list."
        << "\n      CLANG_OPTIONS are the clang compile flags and definitions we need to parse/\"compile\" the given input files with. Add them as usual."
        << "\n      Note: Options are order independent, so the position of the arguments do not matter (not even for the clang compile flags and definitions)."
        << "\n  (3) Generate the glue code, but specify multiple input files"
        << "\n  (4) Same as example 3 but different input syntax for --parse-file."
        << "\n\n\n" << params << "\n";
}


int main(int argc, const char **argv) {

    // Declare our variables

    po::variables_map cli_config;
    po::options_description params("PARAMETERS");
    params.add_options()
        ("help", "Print this help message")
        ("namespace", po::value<string>(), "The namespace to use in the generated protocol file and c++ source files. (use C++ :: notation)")
        ("out-proto", po::value<string>(), "The .proto file to write the protocol description to.")
        ("out-header", po::value<string>(), "The header `.hpp` file the c++ tree adapter code should be generated in")
        ("template-proto", po::value<string>(), "The mustache template which gets used to render(generate) the .proto file")
        ("template-header", po::value<string>(), "The mustache template which gets used to render(generate) the '.hpp' header file")
        ("parse-file", po::value<std::vector<string>>(), "The source file to scan for Inexor shared variables");

    std::string exec{argv[0]};

    vector<string> args(argv+1, argv+argc);

    vector<string> further_compile_options; // we pass through everything unrecognized to libclang.

    try {
        po::parsed_options parsed = po::command_line_parser(args).options(params).allow_unregistered().run();
        further_compile_options = po::collect_unrecognized(parsed.options, po::include_positional);
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

    if(c("help") || !c("namespace") || !c("out-proto") || !c("out-header") || !c("parse-file") 
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
    const vector<string> &input_files = cli_config["parse-file"].as<vector<string>>();

    // Filter out any sourcefiles having no *VAR*( inside.
    std::vector<string> sources;
    for(const string file_name : input_files)
    {
        const std::string file_contents(filecontents(file_name));

        if(boost::regex_search(file_contents, boost::regex("[A-Z]?VAR[A-Z]?[A-Z]?\\("))) sources.push_back(file_name);
    }

    // Read the list of variables

    ShTree tree;

    struct {
        ShTree &tree;
        void shared_var(string cpp_type, string cpp_var, string tree_path) {
            tree.emplace_back(cpp_type, std::move(cpp_var), std::move(tree_path));
        }
    } visitor{tree};

    find_shared_decls(further_compile_options, sources, visitor);

    TemplateData templdata = fill_templatedata(tree, ns_str);

    // Write the protoc file
    render_proto_file(proto_file, proto_template, tree, templdata);

    // Write cpp files
    render_cpp_tree_header(hpp_file, hpp_template, tree, templdata);

    return 0;
}
