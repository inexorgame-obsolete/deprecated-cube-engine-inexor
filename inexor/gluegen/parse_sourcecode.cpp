#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/ParserContext.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/parse_sharedoption.hpp"
#include "inexor/gluegen/parse_sharedfunc.hpp"

#include <boost/algorithm/string.hpp>

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>


using namespace pugi;
using namespace boost;
using namespace inexor::filesystem;
using namespace std;


namespace inexor { namespace rpc { namespace gluegen {

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

/// Given the parameter list of a constructor, we set default_value and options plus we return the tokenized arg list.
///
/// @param argsstring is formed like ("map", NoSync()|Persistent())       so its (defaultval, sharedoption|sharedoption|..)
/// @param default_value will be set to the first param (in this example "map")
/// @param options the sharedoptions given (the second argument of the constructor-string) will be parsed using parse_attached_options_string().
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

    if(args.size() > 1) options = parse_attached_options_string(args.back());
    return args;
}

/// Takes xml variable nodes and **allocates** a ShTreeNode sharedvar declaration and pushes it to the tree.
void parse_global_shared_var(const xml_node var_xml, string var_namespace, vector<ShTreeNode *> &tree)
{
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));
    string argsstring = get_complete_xml_text(var_xml.child("argsstring"));

    if(argsstring.empty()) return; // it is just an "extern" declaration

    vector<attached_option> options;
    string default_value;
    const vector<string>  args = parse_shared_var_constructor_argsstring(name, argsstring, default_value, options);

    //if(verbose) std::cout << "type: " << type << " name: " << name << " argsstring: " << argsstring << " (num: " << args.size() << ")" << std::endl;

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

    //if(verbose) std::cout << "Class member -- class: " << class_name << " type: "<< type << " name: " << name << " argsstring: " << argsstring_itr->second << " (num: " << args.size() << ")" << std::endl;

    tree.push_back(new ShTreeNode(type, name, var_namespace, default_value, options));
}

/// Returns true if this node is of type "SharedVar" (with template).
bool is_SharedVar(const xml_node member_xml)
{
    return contains(get_complete_xml_text(member_xml.child("type")), "SharedVar<");
}

string get_namespace_of_namespace_file(const xml_node compound_xml)
{
    bool isnamespacefile = string(compound_xml.attribute("kind").value()) == "namespace";
    return isnamespacefile ? get_complete_xml_text(compound_xml.child("compoundname")) : "";
}

/// Executes a functor for any variable in the tree.
void for_each_variable(unique_ptr<xml_document> &xml, std::function<void(const xml_node)> functor)
{
    // doxygens AST in cpp files xml is mainly:
    // doxygen
    //   compound
    //     section("func")
    //       member
    //       member..
    //     section("var")
    //     section("define")..
    xml_node compound_xml = xml->child("doxygen").child("compounddef"); //[@kind='file' and @language='C++']");

    for(auto section : compound_xml.children("sectiondef"))
    {
        if(string(section.attribute("kind").value()) == "var"
           || string(section.attribute("kind").value()) == "func") // sometimes accessing constructors gets mistakenly recognized as function
        {
            for(auto member : section.children("memberdef"))
                functor(member);
        }
    }
}

/// Find all variables in the AST which meet our (generic) requirements (the check_functor).
/// @param check_functor a generic check function which returns true if the given member xml node is one we're looking for.
vector<xml_node> find_variable_instances(unique_ptr<xml_document> &xml, std::function<bool(const xml_node)> check_functor)
{
    vector<xml_node> variable_nodes;
    for_each_variable(xml, [&variable_nodes, check_functor](xml_node member) {
        if(check_functor(member))  variable_nodes.push_back(member);
    });
    return variable_nodes;
}

/// Look through the AST (in this case the xmls of classes) for derivates of SharedOption and SharedClass and push them to their dedicated vectors.
void traverse_class_definition_AST(ParserContext &data)
{
    for(auto &xml: data.xmls.class_ast_xmls)
    {
        xml_node compound_xml = xml->child("doxygen").child("compounddef"); //[@kind='class' and @language='C++']");

        if(is_option_class_node(compound_xml))
            data.def_nodes.options.push_back(compound_xml);

        if(is_shared_class_definition_node(compound_xml))
            data.def_nodes.shared_classes.push_back(compound_xml);
    }
}

void traverse_AST_for_markers(ParserContext &data)
{

    for(auto &xml: data.xmls.code_ast_xmls)
    {
        vector<xml_node> func_markers_file = find_variable_instances(xml, [](const xml_node member_xml) {
               return is_function_marker_node(member_xml);
        });

        // The stdlib can be so ugly by times. this appends the vector.
        data.def_nodes.shared_function_markers.insert(data.def_nodes.shared_function_markers.end(),
                                                      func_markers_file.begin(), func_markers_file.end());
    }
}

/// Look through the AST for any nodes of definitions of sharedoptions and sharedclasses plus
/// (although not directly definition) function markers.

/// e.g. class_with_parent "SharedOption" -> option_definitions_vars
/// e.g. class_with_parent "SharedClass" -> shared_class_definitions
/// special case: marker name "__function_dummy" -> shared_function_markers
void traverse_AST_for_definitions(ParserContext &data)
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

    traverse_class_definition_AST(data);
    traverse_AST_for_markers(data);
}

void analyze_definitions(ParserContext &data)
{
    // This needs to happen first, since the others need this information for parsing.
    analyze_shared_options(data);
    analyze_shared_function_markers(data);
    parse_shared_class_definitions(data);
}

void traverse_AST_for_instances(ParserContext &data)
{
    // search for the **instances** of the shared vars/classes.
    for(auto &xml : data.xmls.code_ast_xmls)
    {
        // all vars in one xml file are in the same ns, thanks doxygen.
        string ns_of_vars = get_namespace_of_namespace_file(xml->child("doxygen").child("compounddef"));

        for_each_variable(xml, [ns_of_vars, &data](xml_node member_xml) {

            // Search for global SharedVars:
            if(is_SharedVar(member_xml))
                parse_global_shared_var(member_xml, ns_of_vars, data.instances);

            // Search for SharedClass instances:
            shared_class_definition *s = is_shared_class_instance_node(member_xml, data);
            if(s) parse_class_instance(member_xml, ns_of_vars, s, data);

            // Search for SharedFunc declarations:
            shared_function *sf = is_shared_function_declaration_node(member_xml, data);
            if(sf) parse_function_declaration(member_xml, sf);
        });
    }
}

void find_shared_decls(const string xml_folder, ParserContext &data)
{
  try {
    // sorting input files:
    data.xmls.find_xml_files(xml_folder);
    data.xmls.parse_all_xmls();

    traverse_AST_for_definitions(data);

    analyze_definitions(data); // input: nodes -> output: parsed definitions

    traverse_AST_for_instances(data);

    control_shared_functions(data);
    // control_instances(data); TODO

  }  catch(std::exception &e)
  {
      std::cerr << "Exception thrown running gluegen:" << e.what() << std::endl;
  }
}

} } } // namespace inexor::rpc::gluegen
