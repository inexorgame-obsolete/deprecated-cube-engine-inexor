#pragma once

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <vector>
#include <string>

#include "inexor/gluegen/parse_sharedfunc.hpp"
#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/parse_sharedoption.hpp"
#include "inexor/gluegen/tree.hpp"

namespace inexor { namespace rpc { namespace gluegen {


/// All intermediate steps of the parser + config.
/// The final parse result is in the tree.hpp
struct ParserContext
{
    /// Class containing all xml files (and filenames)
    ///
    /// The .xml files contain doxygen generated ASTs (Abstract Syntax Trees)
    struct AST_xmls
    {
        typedef inexor::filesystem::Path Path;
        typedef pugi::xml_document xml_document;

        std::vector<Path> all_xml_file_names;
        std::vector<Path> code_xml_file_names;
        std::vector<Path> class_xml_file_names;

        // We want to parse the files only once:

        //vector<xml_document> all_ast_xmls; // we dont need all parsed
        std::vector<std::unique_ptr<xml_document>> code_ast_xmls;
        std::vector<std::unique_ptr<xml_document>> class_ast_xmls;

        /// Find all xml files (with a name we're interested in) in a given directory.
        /// all_xml_file_names, code_xml_file_names and class_xml_file_names will contain the entries afterwards.
        void find_xml_files(Path directory);

        /// Parse all xml files of all_xml_file_names and load the parsed ASTs into code_ast_xmls and class_ast_xmls.
        /// @note find_xml_files needs to be executed beforehand.
        void parse_all_xmls();

        bool parse_xml_file(Path &file, std::unique_ptr<xml_document> &xml);

    } xmls;

    /// Switch to turn on extensive messages of what has been parsed.
    bool verbose = false;

    /// Our first pass through the AST just filters out nodes with names/types/.. where interested in.
    struct definition_nodes
    {
        /// Class XML files of Options which can be attached to nodes.
        /// each is the compound part of the AST.
        std::vector<pugi::xml_node> options;
        std::vector<pugi::xml_node> shared_classes;

        /// These are actually not definitions but real variables used to mark functions, but this happens in the same
        /// pass as we look for definitions.
        /// This is a member part of the AST.
        std::vector<pugi::xml_node> shared_function_markers;
    } def_nodes;


    ///// after the definition nodes get parsed they land in there:

    /// options definitions need to get parsed before anything else, since you look for them when parsing the vars/functions/classes..
    std::unordered_map<std::string, option_definition> option_definitions;

    /// The key of this map is the complete function name (including the namespace).
    std::unordered_map<std::string, shared_function> shared_functions;

    /// Those shared_class_definitions also reference the instances (so they get filled in two steps)
    /// @note you need to allocate yourself, we're freeing for you in the destructor. TODO this is bad design.
    /// The key of this map is the refid of the class.
    std::unordered_map<std::string, shared_class_definition *> shared_class_definitions;


    ///// and finally every instances land in here:

    /// @note you need to allocate yourself, we're freeing for you in the destructor. TODO this is bad design.
    std::vector<ShTreeNode *> instances;

    ~ParserContext()
    {
        for(auto &s : shared_class_definitions)
            delete(s.second);
        for(ShTreeNode *i : instances)
            delete(i);
    }
};


} } } // namespace inexor::rpc::gluegen
