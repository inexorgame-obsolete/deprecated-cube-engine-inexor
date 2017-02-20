#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/parse_sharedoption.hpp"
#include "inexor/gluegen/parse_sharedfunc.hpp"

using namespace pugi;
using namespace boost;
using namespace inexor::filesystem;
using namespace std;


namespace inexor { namespace rpc { namespace gluegen {

bool verbose = true;

/// Global Singleton class containing all xml files (and filenames)
///
/// The .xml files contain doxygen generated ASTs (Abstract Syntax Trees)
struct AST_xmls_context
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
    void find_xml_files(Path directory)
    {
        // sorting input files:

        list_files(directory, all_xml_file_names, ".xml");
        for(auto &file : all_xml_file_names)
        {
            
            if(contains(file.filename().string(), "_8cpp.xml") || contains(file.filename().string(), "_8hpp.xml")
               || contains(file.filename().string(), "namespace"))// cpp/hpp files for namespaced contents
            {
                code_xml_file_names.push_back(file);
            }
            else if(contains(file.stem().string(), "class") || contains(file.stem().string(), "struct")) class_xml_file_names.push_back(file);
        }
    }

    /// Parse all xml files of all_xml_file_names and load the parsed ASTs into code_ast_xmls and class_ast_xmls.
    /// @note find_xml_files needs to be executed beforehand.
    void parse_all_xmls()
    {
        for(auto &file : class_xml_file_names)
        {
            auto xml = make_unique<xml_document>();
            if(parse_xml_file(file, xml)) class_ast_xmls.push_back(std::move(xml));
        }
        for(auto &file : code_xml_file_names)
        {
            auto xml = make_unique<xml_document>();
            if(parse_xml_file(file, xml)) code_ast_xmls.push_back(std::move(xml));
        }
    }

    bool parse_xml_file(Path &file, unique_ptr<xml_document> &xml)
    {
        if(!xml->load_file(file.make_preferred().c_str(), parse_default|parse_trim_pcdata))
        {
            std::cout << "XML file representing the AST couldn't be parsed: " << file << std::endl;
            return false;
        }
        return true;
    }
} xmls;

vector<xml_node> find_class_constructors(const xml_node &class_compound_xml)
{
    vector<xml_node> constructors;

    vector<string> ns(split_by_delimiter(class_compound_xml.child("compoundname").text().as_string(), "::"));
    string raw_func_name = ns.back(); // constructor got same name as class

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
vector<xml_node> find_classes_with_parent(string parentname)
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
    vector<xml_node> matching_compound_xmls;
    for(auto &xml: xmls.class_ast_xmls)
    { 
        xml_node compound_xml = xml->child("doxygen").child("compounddef"); //[@kind='class' and @language='C++']");

        for(xml_node &base_class : compound_xml.children("basecompoundref"))
        {
            string baseclassname = base_class.text().as_string();
            if(baseclassname == parentname)
            {
                auto compoundname = compound_xml.child("compoundname");
                matching_compound_xmls.push_back(compound_xml);
                break;
            }
        }
    }
    return matching_compound_xmls;
}

/// Get the init list of the constructor of this class.
///
/// @warning returns an empty list in case there was no ":" or "{" in the constructor definition. TODO
string get_class_constructor_init_list(const xml_node &class_compound_xml)
{
    auto constructor_vector = find_class_constructors(class_compound_xml);
    if(constructor_vector.empty()) return "";

    const xml_node first_constructor = constructor_vector.front(); // we currently ignore the other ones.
    const xml_node loc = first_constructor.child("location");

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
    split_v = split_by_delimiter(str, "{"); // TODO { technically forbidden in the initializer list
    if(split_v.size() < 1) return "";
    str = split_v[0];

    trim(str); // remove leading/trailing whitespace  -> "kills(0), deaths(0)"
    return str;
}

/// Splits the initializer list of the constructor ( ": x(0), y(0) {" into a map.
/// Key = member name, second string = arguments of the members constructor (e.g. {"x", "0"}, {"y", "0"})
unordered_map<string, string> get_class_initialized_member_map(const xml_node &class_compound_xml)
{
    unordered_map<string, string> initialized_member_map;
    string complete_init_list = get_class_constructor_init_list(class_compound_xml);

    if(complete_init_list.empty()) return unordered_map<string, string>();

    // tokenize arg list " kills(0),", " deaths(0), "
    vector<string> tokens = tokenize_arg_list(complete_init_list);
    for(string &token : tokens)
    {
        trim(token);
        string var_name, dummy;
        string argsstring = parse_bracket(token, var_name, dummy);
        trim(argsstring);
        initialized_member_map[var_name] = argsstring;
    }
    return initialized_member_map;
}

/// Parse NoSync()|Persistent()|Function([] { echo("hello"); })
vector<attached_option> parse_shared_option_strings(string options_list_str)
{
    vector<attached_option> options;

    const vector<string> option_strings_vec(split_by_delimiter(options_list_str, "|")); // tokenize

    for(string raw_str : option_strings_vec) // e.g. " NoSync() \n" or Range(0, 3) or Persistent(true)
    {
        trim(raw_str);                       // remove any whitespace around normal chars " NoSync(   ) \n" -> "NoSync(   )"
        attached_option option;

        string temp;
        string argsstr = parse_bracket(raw_str, option.name, temp);       // from Range(0, 3) we get "0, 3"
        option.constructor_args = tokenize_arg_list(argsstr);             // "0", " 3"
        for(string &arg : option.constructor_args)                        // "0", "3"
            trim(arg);


        if(verbose)
        {
            std::cout << "string: " << raw_str << std::endl;
            std::cout << "opt name: " << option.name << std::endl << "args:";
            for(auto &i : option.constructor_args)
                std::cout << " " << i;
            std::cout << std::endl;
        }

        options.push_back(option);
    }
    return options;
}

/// Given the parameter list of a constructor, we set default_value and options plus we return the tokenized arg list.
///
/// @param argsstring is formed like ("map", NoSync()|Persistent())       so its (defaultval, sharedoption|sharedoption|..)
/// @param default_value will be set to the first param (in this example "map")
/// @param options the sharedoptions given (the second argument of the constructor-string) will be parsed using parse_shared_option_strings().
/// @warning throws if no default_value is given!
const vector<string> parse_shared_var_constructor_argsstring(string name, string argsstring, string &default_value, vector<attached_option> &options)
{
    remove_surrounding_brackets(argsstring);
    const vector<string> args(tokenize_arg_list(argsstring));

    if(args.empty())
    {
        std::cout << "IGNORING SharedVar " << name << ": no defaultvalue given! (This code should not compile)" << std::endl;
        throw(std::runtime_error("SharedVar constructor parameters missing!")); //(the defaultvalue is REQUIRED for SharedVars)
    }

    // use the thing after the first bracket as default_value, if there is nothing
    string dummy;
    string backup = parse_bracket(args[0], dummy, default_value);
    if(default_value.empty()) default_value = std::move(backup);
    trim(default_value);
    trim_floating_point_number_mark(default_value);
    remove_surrounding_quotes(default_value); // We need to statically type the default value, so there will always be " " around the def_value already in the message.

    if(args.size() > 1) options = parse_shared_option_strings(args.back());
    return args;
}

/// Takes xml variable nodes and outputs ShTreeNode sharedvar declarations.
void parse_global_shared_var(const xml_node var_xml, string var_namespace, vector<ShTreeNode *> &tree)
{
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));
    string argsstring = get_complete_xml_text(var_xml.child("argsstring"));

    if(argsstring.empty()) return; // it is just an "extern" declaration

    vector<attached_option> options;
    string default_value;
    const vector<string>  args = parse_shared_var_constructor_argsstring(name, argsstring, default_value, options);

    if(verbose) std::cout << "type: " << type << " name: " << name << " argsstring: " << argsstring << " (num: " << args.size() << ")" << std::endl;

    tree.push_back(new ShTreeNode(type, name, var_namespace, default_value, options));
}

void parse_sharedvar_of_class(const xml_node var_xml, string var_namespace, string class_name,
                              const unordered_map<string, string> &class_constructor_init_map, vector<ShTreeNode *> &tree)
{
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));

    // The argsstring (containing the shared options) is in the initilizer list of the constructor of the class, so we look it up.
    auto argsstring_itr = class_constructor_init_map.find(name);
    if(argsstring_itr == class_constructor_init_map.end())
    {
        std::cout << "SharedClass has Sharedvar member, which is missing in the constructors initializer list. (Class: "
            << class_name << ", Variable: " << name << ")" << std::endl;
        return;
    }

    vector<attached_option> options;
    string default_value;
    const vector<string>  args = parse_shared_var_constructor_argsstring(name, argsstring_itr->second, default_value, options);

    if(verbose) std::cout << "Class member -- class: " << class_name << " type: "<< type << " name: " << name << " argsstring: " << argsstring_itr->second << " (num: " << args.size() << ")" << std::endl;

    tree.push_back(new ShTreeNode(type, name, var_namespace, default_value, options));
}

void parse_single_class_instance(const xml_node var_xml, std::string var_namespace, shared_class_definition *class_definition, vector<ShTreeNode *> &tree)
{
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));

    //if(argsstring.empty()) return; // it is just an "extern" declaration
    // the constructor of SharedClasses are not containing sharedoptions (or should we?)
    // TODO: do class instances get here for extern declarations?

    vector<attached_option> options = class_definition->attached_options; // = parse_shared_option_strings(args.back()); TODO
    ShTreeNode *class_node = new ShTreeNode(type, name, var_namespace, class_definition, options);
    class_definition->instances.push_back(class_node);

    for(ShTreeNode *child : class_definition->nodes)
    {
        // TODO sollte rekursiv sein wenn type = child
        class_node->children.push_back(new ShTreeNode(child));
        class_node->children.back()->parent = class_node;
    }
    class_node->set_all_childrens_parent_entry();

    // In case we have a template child, we link the definition of it into the class.
    vector<string> &all_childs_refids = get_values_of_childs_attribute(var_xml.child("type"), "refid");
    if(all_childs_refids.size() >= 2)
    {
        for(shared_class_definition *d : shared_class_definitions)
            if(all_childs_refids[1] == d->refid) // a template can have many refids, the first is the outer case.
                class_node->template_type_definition = d;
    }

    tree.push_back(class_node);
}

// TODO all nodes are const<-
// all loops should be refs

/// Find all classes derived from "SharedClass" and put them in a vector.
vector<xml_node> find_shared_class_definitions()
{
    return find_classes_with_parent("SharedClass");
}

vector<shared_class_definition *> find_shared_class_trees()
{
    vector<shared_class_definition *> classes;

    vector<xml_node> class_xmls = find_shared_class_definitions();
    for(xml_node &compound_xml : class_xmls)
    {
        shared_class_definition *def = new shared_class_definition();
        def->refid = compound_xml.attribute("id").value();
        string full_name =  get_complete_xml_text(compound_xml.child("compoundname")); // including the namespace e.g. inexor::rendering::screen

        vector<string> ns_and_name(split_by_delimiter(full_name, "::"));

        def->class_name = ns_and_name.back();
        ns_and_name.pop_back();
        def->definition_namespace = join(ns_and_name, "::");
        def->containing_header = compound_xml.child("location").attribute("file").value();

        if(contains(def->containing_header, ".c"))
        {
            std::cerr << "ERROR: SharedClasses can only be defined in cleanly include-able **header**-files"
                << std::endl << "Class in question is " << full_name << std::endl;
        }

        const unordered_map<string, string> init_list_map = get_class_initialized_member_map(compound_xml);

        // If there is an entry SharedClass(...) in the constructor initializer list, then we treat ... as SharedOptions
        auto class_options_itr = init_list_map.find("SharedClass");
        if(class_options_itr != init_list_map.end())
            def->attached_options = parse_shared_option_strings(class_options_itr->second);

        for(xml_node &var_xml : find_class_member_vars(compound_xml))
        {
            string type = get_complete_xml_text(var_xml.child("type"));
            if(!contains(type, "SharedVar")) continue; // TODO recursive logic

            parse_sharedvar_of_class(var_xml, def->definition_namespace, def->class_name, init_list_map, def->nodes);
        }
        classes.push_back(def);
    }
    return classes;
}

vector<xml_node> find_variable_instances(unique_ptr<xml_document> &xml, const string searchphrase, string &namespace_of_vars, bool checkid)
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
    xml_node compound_xml = xml->child("doxygen").child("compounddef"); //[@kind='file' and @language='C++']");

    bool isnamespacefile = string(compound_xml.attribute("kind").value()) == "namespace";
    namespace_of_vars = isnamespacefile ? get_complete_xml_text(compound_xml.child("compoundname")) : "";

    for(auto section : compound_xml.children("sectiondef"))
    {
        if(string(section.attribute("kind").value()) == "var"
           || string(section.attribute("kind").value()) == "func") // sometimes accessing constructors gets mistakenly recognized as function
        {
            for(auto member : section.children("memberdef"))
            {
             //   if(string(member.attribute("static").value()) == "yes") continue; // This is a global variable, we need to access from another file. (COMMENTED bc sharedfunctions get marked with static bools)
                if((!checkid && contains(get_complete_xml_text(member.child("definition")), searchphrase)))
                    variable_nodes.push_back(member);
                else
                {
                    vector<string> all_childs_refids = get_values_of_childs_attribute(member.child("type"), "refid");
                    if(!all_childs_refids.empty() && all_childs_refids.front() == searchphrase) // a template can have many refids, the first is the outer case.
                        variable_nodes.push_back(member);
                }
            }
        }
    }
    return variable_nodes;
}

void find_shared_decls(const string xml_folder, std::vector<ShTreeNode *> &tree)
{
  try {
    // sorting input files:
    xmls.find_xml_files(xml_folder);
    xmls.parse_all_xmls();

    // save all option class definitions to its global map.
    vector<xml_node> so_compound_xmls = find_classes_with_parent("SharedOption");
    for(auto &compound_xml : so_compound_xmls)
        handle_shared_option(compound_xml);

    auto &shared_functions_cp = shared_functions;
    look_for_shared_functions(xmls.code_ast_xmls);

    // Search for SharedClass definitions
    shared_class_definitions = find_shared_class_trees();


    // search for the **instances** of the shared vars/classes.
    for(auto &xml : xmls.code_ast_xmls)
    {
        // Search for global SharedVars:
        string ns_of_vars; // all vars in one xml file are in the same ns, thanks doxygen.
        vector<xml_node> global_shared_var_xml_parts = find_variable_instances(xml, "SharedVar", ns_of_vars);
        for(auto xml_part : global_shared_var_xml_parts)
            parse_global_shared_var(xml_part, ns_of_vars, tree);


        // search for class instances
        for(auto shared_class_def : shared_class_definitions)
        {
            vector<xml_node> global_shared_var_xml_parts = find_variable_instances(xml, shared_class_def->refid, ns_of_vars, true);
            for(auto xml_part : global_shared_var_xml_parts)
                // if(has_child_with_attribute(xml_part.child("type"), "refid", searchphrase))) we should better check for the SharedList id
                    parse_single_class_instance(xml_part, ns_of_vars, shared_class_def, tree);
        }
    }
  }  catch(std::exception &e)
  {
      std::cerr << "Exception thrown running gluegen:" << e.what() << std::endl;
  }
}

} } } // namespace inexor::rpc::gluegen
