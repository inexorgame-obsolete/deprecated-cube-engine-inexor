#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/parse_sharedoption.hpp"

using namespace pugi;
using namespace boost;
using namespace inexor::filesystem;
using namespace std;


namespace inexor { namespace rpc { namespace gluegen {

vector<xml_node> find_class_constructors(const xml_node &class_compound_xml)
{
    vector<xml_node> constructors;

    vector<string> ns(split_by_delimiter(class_compound_xml.child("compoundname").text().as_string(), "::"));
    std::string raw_func_name = ns.back(); // constructor got same name as class

    for(const xml_node section : class_compound_xml.children("sectiondef"))
    {
        if(string(section.attribute("kind").value()) == "public-func")
        {
            for(const xml_node member : section.children("memberdef"))
            {
                if(string(member.attribute("kind").value()) == "function")
                {
                    if(raw_func_name == member.child("name").text().as_string())
                        constructors.push_back(member);
                }
            }
        }
    }
    return constructors;
}

vector<xml_node> find_class_member_vars(const xml_node &class_compound_xml)
{
    vector<xml_node> vars;
    for(const xml_node section : class_compound_xml.children("sectiondef"))
        if(string(section.attribute("kind").value()) == "public-attrib")
            for(const xml_node member : section.children("memberdef"))
                if(string(member.attribute("kind").value()) == "variable")
                    vars.push_back(member);
    return vars;
}

/// Returns a list of (already parsed) XML files which contain the AST of a class which is the child of a specific class.
/// Returns not the 'doxygen' parent but directly the specific 'compounddef'
///
/// Note: Use the return as a rvalue. e.g. `auto matching_file_trees = find_classes_with_parent(...);`
vector<xml_node> find_classes_with_parent(string parentname, const vector<Path> class_xml_filenames)
{
    //the AST looks as follows:
    //- doxygen
    //    compounddef[kind="class"]
    //       compoundname
    //       sectiondef[kind="public-attrib"]
    //           memberdef[kind="variable"]
    //              name
    //              initializer ('= "wert"')
    //       sectiondef[kind="public-func"]
    //           memberdef[kind="function"]
    //              name
    //              param
    //                 type
    //                 declname <-
    //                 defval
    vector<xml_node> matching_file_trees;
    for(auto file : class_xml_filenames)
    {
        xml_document xml;
        if(!xml.load_file(file.make_preferred().c_str(), parse_default|parse_trim_pcdata))
        {
            std::cout << "XML file representing the AST couldn't be parsed: " << file << std::endl;
            break;
        }
        xml_node compound_xml = xml.child("doxygen").child("compounddef"); //[@kind='class' and @language='C++']");


        for(xml_node base_class : compound_xml.children("basecompoundref"))
        {
            if(string(base_class.text().as_string()) == parentname)
            {
                matching_file_trees.push_back(std::move(compound_xml));
                break;
            }
        }
    }
    return matching_file_trees;
}


/// Parse NoSync()|Persistent()|Function([] { echo("hello"); })
vector<ShTreeNode::attached_so> parse_shared_option_strings(string options_list_str)
{
    vector<ShTreeNode::attached_so> options;

    const vector<string> option_strings_vec(split_by_delimiter(options_list_str, "|")); // tokenize

    for(string raw_str : option_strings_vec) // e.g. " NoSync() \n" or Range(0, 3) or Persistent(true)
    {
        trim(raw_str);                       // remove any whitespace around normal chars " NoSync(   ) \n" -> "NoSync(   )"
        ShTreeNode::attached_so option;

        string temp;
        string argsstr = parse_bracket(raw_str, option.name, temp);       // from Range(0, 3) we get "0, 3"
        option.constructor_args = tokenize_arg_list(argsstr);             // "0", " 3"
        for(string &arg : option.constructor_args)                        // "0", "3"
            trim(arg);


        std::cout << "string: " << raw_str << std::endl;
        std::cout << "opt name: " << option.name << std::endl << "args:";
        for(auto i : option.constructor_args)
            std::cout << " " << i;
        std::cout << std::endl;

        options.push_back(option);
    }
    return options;
}

/// @param argsstring is of= ("map", NoSync()|Persistent())          (defaultval, sharedoption|sharedoption|..)
void handle_shared_var(const string type, const string name, string argsstring, std::vector<ShTreeNode> &tree, std::string var_namespace)
{
    remove_surrounding_brackets(argsstring);

    const vector<string> args(tokenize_arg_list(argsstring));
    std::cout << "type: " << type << " name: " << name << " argsstring: " << argsstring << " (num: " << args.size() << ")" << std::endl;

    if(args.size() < 1)
    {
        std::cout << "IGNORING SharedVar " << name << ": no defaultvalue given! (This code should not compile)" << std::endl;
        return; //(the defaultvalue is REQUIRED for SharedVars)
    }
    if(args.size() == 1) // no options
    {
        tree.push_back(ShTreeNode(type, name, var_namespace, args[0], vector<ShTreeNode::attached_so>()));
        return;
    }
    vector<ShTreeNode::attached_so> options = parse_shared_option_strings(args.back());
    tree.push_back(ShTreeNode(type, name, var_namespace, args[0], options));
}

/// Takes xml variable nodes and outputs ShTreeNode sharedvar declarations.
void handle_global_shared_var(const xml_node var_xml, std::vector<ShTreeNode> &tree, std::string var_namespace)
{
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));
    string argsstring = get_complete_xml_text(var_xml.child("argsstring"));
    if(argsstring.empty()) return; // it is just an "extern" declaration

    handle_shared_var(type, name, argsstring, tree, var_namespace);
}

/// Get the init list of the constructor of this class.
///
/// @warning returns an empty list in case there was no ":" or "{" in the constructor definition. TODO
string get_class_constructor_init_list(const xml_node &class_compound_xml)
{
    xml_node first_constructor = find_class_constructors(class_compound_xml).front(); // we currently ignore the other ones.
    xml_node loc = first_constructor.child("location");
    string filename = loc.attribute("bodyfile").value();
    size_t startline = loc.attribute("bodystart").as_int();
    size_t endline = loc.attribute("bodyend").as_int();
    if(endline <= startline) endline = startline; // for one line constructors we sometimes have endline == -1

    string str = filecontents_partly(filename, startline, endline);
    // player(int kills) : kills(0), deaths(0) { ... }

    // remove anything before and ":"
    vector<string> split_v = split_by_delimiter(str, ":");
    if(split_v.size() < 2) return ""; // we **ALWAYS** expect a ":" since the SharedVars need an assignment (TODO: subclasses not!)
    str = split_v[1];

    // remove anything after and '{' -> " kills(0), deaths(0) "
    split_v = split_by_delimiter(str, "{");
    if(split_v.size() < 1) return ""; // we **ALWAYS** expect a body.
    str = split_v[0];

    trim(str); // remove leading/trailing whitespace  -> "kills(0), deaths(0)"

    // remove any whitespace
    // tokenize arg list " kills(0)," 
}

void handle_class_shared_var(const xml_node var_xml, vector<ShTreeNode> &tree, string var_namespace, string initlist)
{
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));
    handle_shared_var(type, name, initlist, tree, var_namespace);
}



/// Find all classes derived from "SharedClass" and put them in a vector.
vector<xml_node> find_shared_class_definitions(const vector<Path> &class_xml_filenames)
{
    return find_classes_with_parent("SharedClass", class_xml_filenames);
}

void find_shared_class_trees(const vector<Path> &class_xml_filenames)
{
    vector<shared_class_definition> classes;

    vector<xml_node> class_xmls = find_shared_class_definitions(class_xml_filenames);
    for(xml_node &compound_xml : class_xmls)
    {
        shared_class_definition def;
        string full_name =  get_complete_xml_text(compound_xml.child("compoundname")); // including the namespace e.g. inexor::rendering::screen

        vector<string> ns_and_name(split_by_delimiter(full_name, "::"));

        def.class_name = ns_and_name.back();
        ns_and_name.pop_back();
        def.definition_namespace = ns_and_name;
        def.containing_header = compound_xml.child("location").attribute("file").value();

        const string init_list = get_class_constructor_init_list(compound_xml);
        if(init_list.empty()) continue;
        for(auto var_xml : find_class_member_vars(compound_xml))
        {
            string type = get_complete_xml_text(var_xml.child("type"));
            if(!contains(type, "SharedVar")) continue;
            string name = get_complete_xml_text(var_xml.child("name"));
            std::cout << "!!!!!!!!!!!!name: " << name << " type: " << type << " class:" << def.class_name << std::endl;
        }
    }
}

/// Finds all shared variable in a (parsed) xml file which contain a specific searchphrase.
///
/// @return a list of xml "memberdef" nodes (see comment below) + setting the namespace_of_vars parameter.
/// @param namespace_of_vars will be set to the namespace of the xml document
///       (Doxygen splits source files for us, so all variables in one xml file will be in the same ns.)
vector<xml_node> find_variable_instances(const xml_document &xml, const std::string searchphrase, string &namespace_of_vars)
{
    // parsing cpp-file xmls for SharedVars.
    //
    // doxygens AST in cpp files xml is mainly:
    // doxygen
    //   compound
    //     section("func")
    //       member
    //       member..
    //     section("var")
    //     section("define")..
    vector<xml_node> variable_nodes;
    xml_node compound_xml = xml.child("doxygen").child("compounddef"); //[@kind='file' and @language='C++']");

    bool isnamespacefile = string(compound_xml.attribute("kind").value()) == "namespace";
    namespace_of_vars = isnamespacefile ? get_complete_xml_text(compound_xml.child("compoundname")) : "";

    for(auto section : compound_xml.children("sectiondef"))
    {
        if(string(section.attribute("kind").value()) == "var"
           || string(section.attribute("kind").value()) == "func") // sometimes accessing constructors gets mistakenly recognized as function
        {
            for(auto member : section.children("memberdef"))
            {
                if(contains(get_complete_xml_text(member.child("definition")), searchphrase))
                    variable_nodes.push_back(member);
            }
        }
    }
}

void find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree)
{
    // sorting input files:
    std::vector<Path> all_xml_files;
    std::vector<Path> code_xml_files;
    std::vector<Path> class_xml_files;

    list_files(xml_folder, all_xml_files, ".xml");
    for(auto file : all_xml_files)
    {
        if(contains(file.filename().string(), "_8cpp.xml") || contains(file.filename().string(), "_8hpp.xml") // cpp files for non-namespace declarations
            || contains(file.filename().string(), "namespace")) //
            code_xml_files.push_back(file);
        if(contains(file.stem().string(), "class") || contains(file.stem().string(), "struct")) class_xml_files.push_back(file);
    }

    // save all option class definitions to its global map.
    vector<xml_node> SharedOption_ASTS = find_classes_with_parent("SharedOption", class_xml_files);
    for(auto so_xml_file : SharedOption_ASTS)
        handle_shared_option(so_xml_file);

    // Search for SharedClass definitions
    find_shared_class_trees(class_xml_files);

    // search for shared variable instances.
    for(auto file : class_xml_files)
    {
        //std::cout << "processing file: " << file.make_preferred() << std::endl;

        xml_document xml;
        if(!xml.load_file(file.make_preferred().c_str(), parse_default|parse_trim_pcdata))
        {
            std::cout << "XML file representing the AST couldn't be parsed: " << file << std::endl;
            continue;
        }

        // Search for global SharedVars:
        string ns_of_vars; // all vars in one xml file are in the same ns, thanks doxygen.
        vector<xml_node> global_shared_var_xml_parts = find_variable_instances(xml, "SharedVar", ns_of_vars);
        for(auto xml_part : global_shared_var_xml_parts)
            handle_global_shared_var(xml_part, tree, ns_of_vars);

        //
    }
}

} } } // namespace inexor::rpc::gluegen
