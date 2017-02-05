
#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/parse_sharedfunc.hpp"
#include "inexor/gluegen/tree.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <vector>
#include <string>
#include <memory>
#include <iostream>

using namespace pugi;
using namespace std;

namespace inexor { namespace rpc { namespace gluegen {


/// We use the SharedFunc dummy boolean to find out about the name of the function.
///
/// The sharedoptions are saved in the initilzers list:
/// "<initializer>= function_args_dummy(  )...</initializer>"
/// @return the function name.
/// @param options in this we return the shared options attached to the variable.
string get_shared_func_name_from_dummy(const xml_node var_xml, vector<ShTreeNode::attached_so> &options)
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
    return return_param;
}

/// Parse params from string e.g. "(float param1, const int param2)"
shared_function::function_parameter_list parse_parameter_list(string str, bool &is_valid_param_list)
{
    typedef shared_function::function_parameter_list::param::PRIMITIVE_TYPES PRIMITIVE_TYPES;

    shared_function::function_parameter_list param_list;
    if(str.empty()) { is_valid_param_list = false; return param_list; }
    remove_surrounding_brackets(str);
    vector<string> param_strs = tokenize_arg_list(str);
    for(string &param_str : param_strs)
    {
        param_list.params.push_back(parse_param(param_str));
        if(!param_str.empty() // an empty string inside () means we have no params, but that counts as param list.
           && !param_list.params.back().type != PRIMITIVE_TYPES::P_INVALID)
        {
            is_valid_param_list = false;
            return param_list;
        }
    }
    is_valid_param_list = true;
    return param_list;
}


/// Adds a (+or several) parameter list(s).
/// Adds none if none primitive types we're used in the parameter list declaration or types
/// we do not know how to default_construct them. TODO: Add generic runtime mechanism to do expend these!
/// In case of params with default values we add several parameter lists for each.
void add_parameter_lists(shared_function &sf, string argsstr)
{
    bool succesfully_parsed = false;
    shared_function::function_parameter_list param_list = parse_parameter_list(argsstr, succesfully_parsed);
    if(!succesfully_parsed) // argsstring wasnt parseable
        return;
    sf.parameter_lists.push_back(param_list);

    // Add parameter lists if we find params with default values.
    for(int i = param_list.params.size()-1; i >= 0; i--)
    {
        auto &param = param_list.params[i];
        if(param.default_value.empty()) break;
        /// add the new param list with params up until this one.
        shared_function::function_parameter_list param_list_clone;
        for(int k = 0; k < i; k++)
            param_list_clone.params.push_back(param_list.params[k]);
        sf.parameter_lists.push_back(param_list_clone);
    }
}

/// Its a two pass: first we look for the markers signaling we have a shared function,
/// next we visit any code ASTs again to look up the declarations of these functions.
/// This struct contains the intermediate result from one to the next step.
void look_for_shared_functions(vector<unique_ptr<xml_document>> &code_ast_xmls)
{
    // For the SharedFunctions markers:
    // in the GlueGen pass we add dummy booleans named like the functions.
    for(auto &xml : code_ast_xmls)
    {
        string dummy;
        vector<xml_node> global_shared_func_xml_parts = find_variable_instances(xml, "__function_dummy_", dummy);
        for(auto &func_xml : global_shared_func_xml_parts)
        {
            shared_functions.push_back(shared_function());
            shared_function &sf = shared_functions.back();
            sf.name = get_shared_func_name_from_dummy(func_xml, sf.options);
        }
    }

    // Look for the functions declarations of the functions marked with SharedFunc
    for(auto &xml : code_ast_xmls)
    {
        for(shared_function &sf : shared_functions)
        {
            string declaration_namespace;
            vector<xml_node> func_xmls = find_variable_instances(xml, sf.name, declaration_namespace);
            // TODO rename function
            // TODO: compare declaration namespace with SharedFunc namespace
            for(xml_node &node : func_xmls)
                add_parameter_lists(sf, get_complete_xml_text(node.child("argsstring")));
        }
        // TODO: warn about empty param list;
    }
    for(shared_function &sf : shared_functions)
        if(sf.parameter_lists.empty())
            std::cout << "WARN: Ignored shared function " << sf.name << " (no valid parameter list found)" << std::endl;
}

} } } // namespace inexor::rpc::gluegen

