#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/range.hpp>
#include <boost/algorithm/string/regex.hpp>

#include <clang/Tooling/CommonOptionsParser.h>

#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/parser_cpp_shared_var.hpp"
#include "inexor/gluegen/generator_protoc.hpp"
#include "inexor/gluegen/generator_cpp_tree_adapter.hpp"

using namespace inexor::rpc::gluegen;
namespace po = boost::program_options;
using std::string;
using std::vector;

template<typename SinglePassRange, typename Delim>
std::string join(SinglePassRange r, Delim d) {
    std::stringstream s;
    bool first = true;
    for (auto &e : r) {
        if (first)
            first = false;
        else
            s << d;
        s << e;
    }
    return s.str();
}

void usage(const std::string &ex, const po::options_description &params) {
    std::cerr
        << "Inexor gluegen       Generates the glue code for the tree API."
        << "\n\nEXAMPLES"
        << "\n  (1) " << ex << " --help"
        << "\n  (2) " << ex << " --out-proto FILE --out-source FILE --out-header FILE --namespace NAMESPACE \"CLANG_OPTIONS\" --parse-file FILE"
        << "\n  (3) " << ex << " --out-proto FILE --out-source FILE --out-header FILE --namespace NAMESPACE \"CLANG_OPTIONS\" --parse-file FILE1 --parse-file FILE2 --parse-file FILE3"
        << "\n  (4) " << ex << " --out-proto FILE --out-source FILE --out-header FILE --namespace NAMESPACE \"CLANG_OPTIONS\" --parse-file FILE1 FILE2 FILE3"
        << "\n\nDESCRIPTION"
        << "\n  (1) Show this help page"
        << "\n  (2) Generate the glue code. Note the quotes around the compile-options list."
        << "\n      CLANG_OPTIONS are the clang compile flags and definitions we need to parse/\"compile\" the given input files with, add them as usual."
        << "\n      Note: Options are order independent, so the position of the arguments do not matter (not even for the clang compile flags and definitions)."
        << "\n  (3) Generate the glue code, but specify multiple input files"
        << "\n  (4) Same as example 3 but different syntax."
        << "\n\n" << params << "\n";
}

// TODO: Boost::find should also provide the std::find
// interface
// TODO: Move this to our own algorithm library?
using std::find;
using boost::find;

int main(int argc, const char **argv) {

    // Declare our variables

    po::variables_map cli_config;
    po::options_description params("PARAMETERS");
    params.add_options()
        ("help", "Print this help message")
        ("namespace", po::value<string>(), "The namespace to use in the generated protocol file and c++ source files. (use C++ :: notation)")
        ("out-proto", po::value<string>(), "The .proto file to write the protocol description to.")
        ("out-header", po::value<string>(), "The header `.hpp` file the c++ tree adapter code should be generated in")
        ("out-source", po::value<string>(), "The source `.cpp` file the c++ tree adapter code should be generated in")
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

    if(c("help") || !c("namespace") || !c("out-proto") || !c("out-header") || !c("out-source") || !c("parse-file"))
    {
        usage(exec, params);
        return 0;
    }

    using boost::regex;
    using boost::split_regex;

    const string &ns_str = cli_config["namespace"].as<string>();
    const string &proto_file = cli_config["out-proto"].as<string>();
    const string &hpp_file = cli_config["out-header"].as<string>();
    const string &cpp_file = cli_config["out-source"].as<string>();
    const vector<string> &input_files = cli_config["parse-file"].as<vector<string>>();

    // namespace string -> protobuf syntax: replace :: with .
    std::vector<string> ns;
    split_regex(ns, ns_str, regex("::"));
    const std::string &proto_pkg = join(ns, '.');

    // Read the list of variables

    ShTree tree;

    struct {
        ShTree &tree;
        void shared_var(string cpp_type, string cpp_var, string tree_path) {
            tree.emplace_back(cpp_type, std::move(cpp_var), std::move(tree_path));
        }
    } visitor{tree};

    find_shared_decls(further_compile_options, input_files, visitor);

    // Write the protoc file
    update_protoc_file(proto_file, tree, proto_pkg);

    // Write cpp files
    update_cpp_tree_server_impl(hpp_file, cpp_file, tree, ns);

    return 0;
}
