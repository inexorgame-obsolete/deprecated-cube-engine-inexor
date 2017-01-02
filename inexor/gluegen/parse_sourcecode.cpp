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

/// Takes xml variable nodes and outputs ShTreeNode sharedvar declarations.
void handle_shared_var(const xml_node var_xml, std::vector<ShTreeNode> &tree, std::string var_namespace)
{
    //was tue ich: "(" << +char_-')' << ',' << char_-'|'oder'('+klammer-')'
    // return content parse_bracket(string)
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));
    string argsstring = get_complete_xml_text(var_xml.child("argsstring"));
    if(argsstring.empty()) return; // it is just an "extern" declaration

    remove_surrounding_brackets(argsstring);

    const vector<string> args(tokenize_arg_list(argsstring)); // argsstring = ("map", NoSync()|Persistent())          (defaultval, sharedoption|sharedoption|..)


    std::cout << "type: " << type << " name: " << name << " argsstring: " << argsstring << " (num: " << args.size() << ")" << std::endl;
    if(args.size() <= 1) // no sharedoptions given (its not allowed to have only shared options as constructor args)
    {
        tree.push_back(ShTreeNode(type, name, var_namespace, vector<ShTreeNode::attached_so>()));
        return;
    }

    const vector<string> shared_option_strings(split_by_delimiter(boost::erase_all_copy(args.back(), " "), "|"));// remove "any" whitespace and tokenize

    vector<ShTreeNode::attached_so> shared_options;
    for(string raw_str : shared_option_strings) // e.g. NoSync() or Range(0, 3) or Persistent(true)
    {
        ShTreeNode::attached_so option;
        std::string temp;

        string constructor_argsstr = parse_bracket(raw_str, option.name, temp);
        option.constructor_args = tokenize_arg_list(constructor_argsstr);


        std::cout << "string: " << raw_str << std::endl;
        std::cout << "opt name: " << option.name << std::endl << "args:";
        for(auto i : option.constructor_args)
            std::cout << " " << i;
        std::cout << std::endl;
        shared_options.push_back(option);
    }
    tree.push_back(ShTreeNode(type, name, var_namespace, shared_options));
}

bool find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree)
{
    //sorting input files:
    std::vector<Path> all_xmls;
    std::vector<Path> code_xmls;
    std::vector<Path> class_xmls;

    list_files(xml_folder, all_xmls, ".xml");
    for(auto file : all_xmls)
    {
        if(contains(file.filename().string(), "_8cpp.xml") || contains(file.filename().string(), "_8hpp.xml") // cpp files for non-namespace declarations
            || contains(file.filename().string(), "namespace")) //
            code_xmls.push_back(file);
        if(contains(file.stem().string(), "class") || contains(file.stem().string(), "struct")) class_xmls.push_back(file);
    }
    vector<xml_node> SharedOption_ASTS = find_classes_with_parent("SharedOption", class_xmls);
    for(auto so_xml_file : SharedOption_ASTS)
        handle_shared_option(so_xml_file);

    // parsing cpp-file xmls for shared declarations.
    //
    // doxygens AST in cpp files xml is mainly:
    // doxygen
    //   compound
    //     section("func")
    //       member
    //       member..
    //     section("var")
    //     section("define")..
    for(auto file : code_xmls)
    {
        //std::cout << "processing file: " << file.make_preferred() << std::endl;

        xml_document xml;
        if(!xml.load_file(file.make_preferred().c_str(), parse_default|parse_trim_pcdata))
        {
            std::cout << "XML file representing the AST couldn't be parsed: " << file << std::endl;
            continue;
        }

        xml_node compound_xml = xml.child("doxygen").child("compounddef"); //[@kind='file' and @language='C++']");

        bool isnamespacefile = string(compound_xml.attribute("kind").value()) == "namespace";
        std::string ns = isnamespacefile ? compound_xml.child("compoundname").text().as_string() : "";
        for(auto section : compound_xml.children("sectiondef"))
        {
            if(string(section.attribute("kind").value()) == "var"
               || string(section.attribute("kind").value()) == "func") // sometimes accessing constructors gets mistakenly recognized as function
            {
                for(auto member : section.children("memberdef"))
                {
                    if(contains(get_complete_xml_text(member.child("definition")), "SharedVar"))
                        handle_shared_var(member, tree, ns);
                }
            }
        }
    }
    return true;
}

} } } // namespace inexor::rpc::gluegen
