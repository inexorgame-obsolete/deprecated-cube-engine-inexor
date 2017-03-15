
#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/parse_sharedfunc.hpp"
#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/ParserContext.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
#include <memory>
#include <iostream>

using namespace pugi;
using namespace std;
using namespace boost::algorithm;

namespace inexor { namespace rpc { namespace gluegen {


/// We use the SharedFunc dummy boolean to find out about the name of the function.
///
/// The sharedoptions are saved in the initilzers list:
/// "<initializer>= function_args_dummy(  )...</initializer>"
/// @return the function name.
/// @param options in this we return the shared options attached to the variable.
string get_shared_func_name_from_dummy(const xml_node var_xml, vector<attached_option> &options)
{
    const string dummy_name = get_complete_xml_text(var_xml.child("name"));
    string initstring = get_complete_xml_text(var_xml.child("initializer"));

    // we receive sth like static bool __function_dummy_<functionname> = function_args_dummy("<functionname>", options)
    if(initstring.empty())
        std::cout << "WARNING: Could not find initializer list of SharedFunc with the dummy " << dummy_name << std::endl;
    string dummy; // not in used
    initstring = parse_bracket(initstring, dummy, dummy);    // TODO better api

    string name;
    parse_shared_var_constructor_argsstring(name, initstring, name, options); // We missuse this function for "<functionname>", options
                                                                              // TODO more generic name.
    return name;
}

/// Parse param from string, e.g. "float param1" or "int param2".
/// needs to be checked (if name is empty)
shared_function::function_parameter_list::param parse_param(string str)
{
    typedef shared_function::function_parameter_list::param::PRIMITIVE_TYPES PRIMITIVE_TYPES;
    shared_function::function_parameter_list::param return_param;

    // input comes e.g. as "const char *name" or "const char* name = \"hello string\""
    // We split the input into 3 or 4 parts: delimiter is any non alphanumeric(or '_') char.
    vector<string> parts = split_in_alphanumeric_parts(str, true);

    bool has_default_value = str.find('=') != string::npos; // TODO does not escape.

    size_t parts_size = parts.size();
    if(parts_size<2 || (has_default_value && parts_size < 3))
    {
        return_param.type = PRIMITIVE_TYPES::P_INVALID;
        return return_param;
    }

    return_param.name = has_default_value ? parts[parts_size-2] : parts[parts_size-1];
    string type_str = has_default_value ? parts[parts_size-3] : parts[parts_size-2];
    if(has_default_value) return_param.default_value = parts[parts_size-1];

    static const unordered_map<string, PRIMITIVE_TYPES> paramtypestr_to_type_mapping ={
        {"int", PRIMITIVE_TYPES::P_INT},
        {"float", PRIMITIVE_TYPES::P_FLOAT},
        {"char", PRIMITIVE_TYPES::P_STR}, // note: the * does not appear in our parts

        {"string", PRIMITIVE_TYPES::P_STR}, // we access it in rpc with a char*, but it got a constructor for it.
        {"std::string", PRIMITIVE_TYPES::P_STR},
        {"Path", PRIMITIVE_TYPES::P_STR},
        {"filesystem::Path", PRIMITIVE_TYPES::P_STR},
        {"inexor::filesystem::Path", PRIMITIVE_TYPES::P_STR}
    };

    auto typemap_finder = paramtypestr_to_type_mapping.find(type_str);
    if(typemap_finder == paramtypestr_to_type_mapping.end())
    {
        return_param.type = PRIMITIVE_TYPES::P_INVALID;
        return return_param;
    }

    return_param.type = typemap_finder->second;
    if(return_param.type == PRIMITIVE_TYPES::P_INT || return_param.type == PRIMITIVE_TYPES::P_FLOAT)
        if(str.find("*") != string::npos || str.find("&") != string::npos) // we do not allow pointers or references on numeric types.
            return_param.type = PRIMITIVE_TYPES::P_INVALID; // TODO: we should switch to whitelisting instead of blacklisting here..

    if(return_param.type == PRIMITIVE_TYPES::P_STR)
        if(type_str == "char" && str.find("const") == string::npos) // we only allow const char, no mutable char arguments
            return_param.type = PRIMITIVE_TYPES::P_INVALID;
    return return_param;
}

/// Parse params from string e.g. "(float param1, const int param2)"
shared_function::function_parameter_list parse_parameter_list(string str, bool &is_valid_param_list)
{
    typedef shared_function::function_parameter_list::param::PRIMITIVE_TYPES PRIMITIVE_TYPES;

    shared_function::function_parameter_list param_list;
    if(str.empty()) { is_valid_param_list = false; return param_list; }
    remove_surrounding_brackets(str);
    if(str.empty()) // we had () before, now we have nothing -> no parameters
    {
        is_valid_param_list = true;
        return param_list;
    }
    vector<string> param_strs = tokenize_arg_list(str);
    for(string &param_str : param_strs)
    {
        auto param = parse_param(param_str);
        if(param.type == PRIMITIVE_TYPES::P_INVALID)
        {
            is_valid_param_list = false;
            return param_list;
        }
        else param_list.params.push_back(std::move(param));
    }
    is_valid_param_list = true;
    return param_list;
}

bool shared_function::function_parameter_list::has_default_params() const
{
    for(auto &param : params)
        if(!param.default_value.empty()) return true;
    return false;
}

/// If we input a p(const char *a, const char *b = hello, const char *c = "world"); this will give us the function param list for p(const char *a);
/// @note check before using this function whether the parameter list has params with default values (otherwise you'll add a total copy of the input).
shared_function::function_parameter_list default_value_shrinked_clone(const shared_function::function_parameter_list &p_list)
{
    for(int i = 0; i < p_list.params.size(); i++)
    {
        auto &param = p_list.params[i];
        if(param.default_value.empty()) continue;
        /// add the new param list with params up until this one.
        shared_function::function_parameter_list param_list_clone;
        for(int k = 0; k < i; k++)
            param_list_clone.params.push_back(p_list.params[k]);
        //param_list_clone.declaration = p_list.declaration;
        param_list_clone.clone = true;
        return param_list_clone;
    }
    return shared_function::function_parameter_list(p_list);
}

void shared_function::add_parameter_list(const function_parameter_list &p_list)
{
    bool haslist = false;
    for(int i = 0; i < parameter_lists.size(); i++)
        if(parameter_lists[i] == p_list)
        {
            if(!parameter_lists[i].has_default_params() && p_list.has_default_params())
            { // Special case: A has no default params but B has
                parameter_lists[i] = p_list;
                parameter_lists.push_back(default_value_shrinked_clone(p_list));
            }
            haslist = true; // in any case: we already got this one, no need to append a new one.
        }
    if(!haslist)
    {
        parameter_lists.push_back(p_list);
        if(p_list.has_default_params()) // Add another parameter lists if we find params with default values.
            parameter_lists.push_back(default_value_shrinked_clone(p_list));
    }
}

/// Adds a (+or several) parameter list(s).
/// Adds none if none primitive types we're used in the parameter list declaration or types
/// we do not know how to default_construct them.
/// In case of params with default values we add several parameter lists for each.
void add_parameter_lists(shared_function &sf, string argsstr, string definition_str)
{
    bool succesfully_parsed = false;
    shared_function::function_parameter_list param_list = parse_parameter_list(argsstr, succesfully_parsed);
    if(!succesfully_parsed) // argsstring wasnt parseable
        return;
    param_list.declaration = definition_str + argsstr;

    sf.add_parameter_list(param_list);
}

bool is_function_marker_node(const xml_node var_node)
{
    if(contains(get_complete_xml_text(var_node.child("name")), "__function_dummy_"))
        return true;
    return false;
}

extern void analyze_shared_function_markers(ParserContext &data)
{
    for(auto &member_xml : data.def_nodes.shared_function_markers)
    {
        shared_function sf;
        sf.name = get_shared_func_name_from_dummy(member_xml, sf.options);

        xml_node compound_def = member_xml.parent().parent(); // first up: sectiondef 2nd: compounddef
        sf.ns = get_namespace_of_namespace_file(compound_def);

        data.shared_functions[sf.ns + "::" + sf.name] = sf;

        if(data.verbose) std::cout << "shared function: " << sf.name << std::endl;
    }
}

// Finds all functions(and variables: TODO) instances with a "definition" entry in the AST containing a known variable marker.
shared_function *is_shared_function_declaration_node(const pugi::xml_node xml_member_node, ParserContext &data)
{
    if(string(xml_member_node.attribute("kind").value()) != "function") return nullptr;

    xml_node compound_def = xml_member_node.parent().parent(); // first up: sectiondef 2nd: compounddef
    string full_name = get_namespace_of_namespace_file(compound_def) + "::" + get_complete_xml_text(xml_member_node.child("name"));

    auto finditr = data.shared_functions.find(full_name);
    return finditr == data.shared_functions.end() ? nullptr : &finditr->second;
}

void parse_function_declaration(const pugi::xml_node var_xml, shared_function *sf)
{
    add_parameter_lists(*sf, get_complete_xml_text(var_xml.child("argsstring")),
                        get_complete_xml_text(var_xml.child("type"))+ " " + get_complete_xml_text(var_xml.child("name")));
}

void control_shared_functions(ParserContext &data)
{
    for(auto it = data.shared_functions.begin(); it != data.shared_functions.end();)
    {
        shared_function &sf = it->second;
        if(sf.parameter_lists.empty())
        {
            std::cout << "WARN: Ignored shared function " << sf.name << " (no valid parameter list found)" << std::endl;
            it = data.shared_functions.erase(it);
        }
        else it++;
    }
}

} } } // namespace inexor::rpc::gluegen

