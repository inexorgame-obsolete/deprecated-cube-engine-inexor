#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>

#include <pugixml/pugiconfig.hpp>
#include <pugixml/pugixml.hpp>

#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/tree.hpp"

using namespace pugi;
using namespace boost;
using namespace inexor::filesystem;
using namespace std;


namespace inexor { namespace rpc { namespace gluegen {

// Move to utils
// TODO add fast hash table algorithms to utils
// TODO add fast std::string replacement to utils
// TODO add useful string formatter to utils
// merge log stuff into one file in utils
vector<string> split_by_delimiter(string input, string delimiter)
{
    vector<string> out;
    size_t last = 0; size_t next = 0;
    while((next = input.find(delimiter, last)) != string::npos)
    {
        out.push_back(input.substr(last, next-last));
        last = next + delimiter.size();
    }
    out.push_back(input.substr(last));
    return std::move(out);
}

/// This function workarounds doxygens faulty xml which contains '= whateverisbehind' as initializer (totally raw, no c++11 support it seems)
void remove_leading_assign_sign(string &str)
{
    if(str.empty()) return;
    if(str.front() == '=')
        str.erase(0, 1);
}
void remove_leading_whitespace(string &input)
{
    if(input.empty()) return;
    for(int i = 0; i < input.size(); i++)
        if(input[i] != ' ' && input[i] != '\t')
        {
            if(i) input = input.substr(i);
            return;
        }
}

/// If first char of string is matching, remove the first and the last one of the string (no matter what the last one is).
/// @warning does not do leading/trailing whitespace skimming.
void remove_surrounding_char(std::string &str, const char first_cha)
{
    if(str.empty()) return;
    if(str.front() == first_cha)
    {
        str.erase(0, 1);
        str.erase(str.size() - 1);
    }
}

/// @warning requires data has no whitespace before or after the quotes.
void remove_quotes(std::string &str)
{
    remove_surrounding_char(str, '"');
}

/// @warning requires data has no whitespace before or after the brackets, see remove_surrounding_char.
void remove_surrounding_brackets(std::string &str)
{
    remove_surrounding_char(str, '(');
}


/// Splits a "something(totally(but pretty much ) stupid)great" into "something" "totally(but pretty much ) stupid" and "great".
// Yes we could do this with boost::spirit or with some recursive grammar but oh well we dont need that atm.
string parse_bracket(string input, string &before_bracket, string &after_bracket)
{
    size_t len = input.size();

    int brackets_counter = 0;
    bool found_brackets = false;
    size_t first_bracket_pos = 0;
    size_t closing_bracket_pos = len-1;

    for(size_t i = 0; i < len; i++)
    {
        if(input[i] == '"')
            do {
                i++;
                if(i >= len) break;
            } while(input[i] != '"'); //skip brackets inside ""
        if(input[i] == '(')
        {
            if(!brackets_counter) first_bracket_pos = i;
            brackets_counter++;
        }
        else if(input[i] == ')')
        {
            brackets_counter--;
            if(brackets_counter == 0)
            {
                closing_bracket_pos = i;
                found_brackets = true;
                break;
            }
            else if(brackets_counter < 0) break;
        }
    }
    if(!found_brackets) return input;

    before_bracket = input.substr(0, first_bracket_pos);
    string content = input.substr(first_bracket_pos+1, closing_bracket_pos-first_bracket_pos-1);
    after_bracket = input.substr(closing_bracket_pos);
    return content;
}

/// Splits e.g. 'something, some(dadadalu,da), "ich,,,skwo"' into 3 strings "something", "some(dadadalu,da)" and ""ich,,,skwo""
// Yes we could do this with boost::spirit or with some recursive grammar but oh well we dont need that atm.
vector<string> tokenize_arg_list(string input)
{
    vector<string> tokens;

    int brackets_counter = 0;
    size_t last_token_end_pos = 0;

    size_t len = input.size();

    for(size_t i = 0; i < len; i++)
    {
        if(input[i] == '"') while(i < len && input[i] != '"') i++; //skip stuff inside "".
        if(!brackets_counter && input[i] == ',')
        {
            tokens.push_back(input.substr(last_token_end_pos, i-last_token_end_pos));
            last_token_end_pos = min(i+1, len); // +1 skipping the char itself
        }
        else if(input[i] == '(') brackets_counter++;
        else if(input[i] == ')') brackets_counter--;
    }
    tokens.push_back(input.substr(last_token_end_pos));

    return std::move(tokens);
}

/// Text can have subfields with more text + siblings text, usually you want all of them concatenated.
string get_complete_xml_text(const xml_node parent, bool recursive = true)
{
    string text;
    for(pugi::xml_node child : parent.children())
    {
        if(child.type() == pugi::node_pcdata)
            text += child.value();
        else if(recursive && child.children().begin() != child.children().end()) // our child has children
            text += get_complete_xml_text(child, true);
    }
    return text;
}

/// Finds in the compound xml node the constructors of this class.xml.
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

/// This function searches constructors of the found shared_options (derived) class and saves its args to our optionclass instance.
/// 
/// We require to have all constructor arguments named the same.
/// We furthermore require to have default values for either all or no constructor arguments.
/// + all default_values across all constructors need to be the same.
/// Error if those requirements aren't met.
void handle_so_constructors(optionclass &opt, const xml_node &compound_xml)
{
    vector<xml_node> constructors = find_class_constructors(compound_xml);

    // The first constructor fills the argument list, the following just control whether their lists are equal.
    const xml_node first_constructor = constructors.front();
    for(const xml_node param : first_constructor.children("param"))
    {
        optionclass::arg arg;
        arg.name = param.child("declname").text().as_string();
        arg.default_value = get_complete_xml_text(param.child("defval"));
        if(!arg.default_value.empty()) opt.hasdefaultvals = true;
        std::cout << "arg.name: " << arg.name << std::endl;
        if(opt.hasdefaultvals)
        {
            arg.default_value = parse_bracket(arg.default_value, string(), string()); //fu_cast<float>("{{index}}") -> "{{index}}"
            remove_quotes(arg.default_value);
            // TODO need escaping!
        }
        opt.constructor_args.push_back(arg);
    }


    // Error checking: TODO Enable
    //if(opt.hasdefaultvals)
    //    for(auto arg : opt.constructor_args)
    //        if(arg.default_value.empty()) throw std::exception("option classes must have default values for either no or all constructor arguments!");

    // control equalness of follow up constructors.
    //for(const xml_node constru : constructors)
    //{
    //    vector<string> arg_names;
    //    int i = 0;
    //    for(const xml_node param : first_constructor.children("param")) // compare mit paramname der gleichen nummer
    //    {
    //        if(opt.constructor_args[i].name.compare(param.child("declname").text().get()))
    //            throw std::exception("option class constructor argument names must be equal for different constructor types");
    //        i++;
    //    }
    //}
}

/// Finds in the compound xml node the constructors of this class.xml.
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

void handle_so_template_hybrids(optionclass &opt, const xml_node &compound_xml)
{
    for(auto var_xml : find_class_member_vars(compound_xml))
    {
        optionclass::arg templ_hy;
        templ_hy.name = var_xml.child("name").text().as_string();
        templ_hy.default_value = get_complete_xml_text(var_xml.child("initializer"));
        remove_leading_assign_sign(templ_hy.default_value);
        remove_leading_whitespace(templ_hy.default_value);
        remove_quotes(templ_hy.default_value);
        opt.template_hybrids.push_back(templ_hy);
    }
    optionclasses[opt.name] = opt;

    for(auto templ_hy : opt.template_hybrids)

        std::cout << "[Template Hybrids inside " << opt.name << "] " << templ_hy.name << " = " << templ_hy.default_value << std::endl;

}

/// This function saves an optionclass instanz to our optionclasses vector.
/// 
/// We require to have all constructor arguments named the same.
/// We furthermore require to have default values for either all or no constructor arguments.
/// + all default_values across all constructors need to be the same.
/// Error if those requirements aren't met.
void handle_shared_option(const xml_node &compound_xml)
{
    optionclass opt(compound_xml.child("compoundname").text().as_string());
    std::cout << "OptionClass found: " << opt.name << std::endl;

    handle_so_constructors(opt, compound_xml);
    handle_so_template_hybrids(opt, compound_xml);
}

void find_options_classes(const std::vector<Path> class_xml_files)
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
    for(auto file : class_xml_files)
    {
        xml_document xml;
        if(!xml.load_file(file.make_preferred().c_str(), parse_default|parse_trim_pcdata))
        {
            std::cout << "XML file representing the AST couldn't be parsed: " << file << std::endl;
            return;
        }
        xml_node compound_xml = xml.child("doxygen").child("compounddef"); //[@kind='class' and @language='C++']");


        for(xml_node base_class : compound_xml.children("basecompoundref"))
        {
            if(string(base_class.text().as_string()) == "SharedOption")
                handle_shared_option(compound_xml);
        }
    }
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
    if(args.size() < 2) // no sharedoptions given (its not allowed to have only shared options as constructor args)
    {
        tree.push_back(ShTreeNode(type, name, var_namespace, vector<ShTreeNode::shared_option_arg>()));
        return;
    }

    const vector<string> shared_option_strings(split_by_delimiter(boost::erase_all_copy(args.back(), " "), "|"));// remove "any" whitespace and tokenize

    vector<ShTreeNode::shared_option_arg> shared_options;
    for(string raw_str : shared_option_strings) // e.g. NoSync() or Range(0, 3) or Persistent(true)
    {
        ShTreeNode::shared_option_arg option;

        string constructor_argsstr = parse_bracket(raw_str, option.class_name, string());
        option.constructor_args = tokenize_arg_list(constructor_argsstr);


        std::cout << "string: " << raw_str << std::endl;
        std::cout << "opt name: " << option.class_name << std::endl << "args:";
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
    find_options_classes(class_xmls);

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
