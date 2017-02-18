#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/parse_sharedoption.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace pugi;
using namespace boost;

namespace inexor { namespace rpc { namespace gluegen {

unordered_map<string, option_definition> option_definitions;

/// This function searches constructors of the sharedoptions class in the AST, looks up the args of the constructor and saves those in opt.
///
/// @param opt the class (derived from a common base class called SharedOption) in parsed form.
/// We require to have all constructor arguments named the same.
/// We furthermore require to have default values for either all or no constructor arguments.
/// + all default_values across all constructors need to be the same.
/// Error if those requirements aren't met.
name_defaultvalue_vector find_so_constructors_args(option_definition &opt, const xml_node &compound_xml)
{
    name_defaultvalue_vector constructor_args;

    auto constructor_vector = find_class_constructors(compound_xml);
    if(constructor_vector.empty()) return name_defaultvalue_vector();

    // The first constructor fills the argument list, the following just control whether their lists are equal.
    const xml_node first_constructor = constructor_vector.front();

    for(const xml_node param : first_constructor.children("param"))
    {
        name_defaultvalue_tupel arg;
        arg.name = get_complete_xml_text(param.child("declname"));
        arg.default_value = get_complete_xml_text(param.child("defval"));
        std::cout << "arg.name: " << arg.name << std::endl;

        if(!arg.default_value.empty())
        {
            opt.constructor_has_default_values = true;
            std::string temp;
            arg.default_value = parse_bracket(arg.default_value, temp, temp); // fu_cast<float>( "{{index}}\n{{name}}" ) -> "{{index}}\n{{name}}"
            trim(arg.default_value);                                          // remove whitespace around "{{index}}\n{{name}}"
            remove_surrounding_quotes(arg.default_value);                     // -> {{index}}'\''n'{{name}}
            unescape(arg.default_value);                                      // replace "\\n" with newline char.
        }
        constructor_args.push_back(arg);
    }
    return constructor_args;

    // TODO Error checking:
    // * check qualness of constructor argument names of the different constructors
    // * allow only: all constructor arguments or no constructor args have default values!
    //    * (we dont want control individually whether constructor param have default values, since
    //       that may require us to match different constructors when parsing the instances. that would be too complex)
}

name_defaultvalue_vector find_options_class_const_char_members(option_definition &opt, const xml_node &compound_xml)
{
    name_defaultvalue_vector const_char_members;

    for(auto var_xml : find_class_member_vars(compound_xml))
    {
        if(!contains(get_complete_xml_text(var_xml.child("type")), "char")) continue;

        name_defaultvalue_tupel var;
        var.name = get_complete_xml_text(var_xml.child("name"));
        var.default_value = get_complete_xml_text(var_xml.child("initializer"));
        remove_leading_assign_sign(var.default_value);
        trim(var.default_value); //remove whitespace
        remove_surrounding_quotes(var.default_value);
        const_char_members.push_back(var);
    }

    return const_char_members;
}

/// This function saves a option_definition (a class declaration which is derived from SharedOption) to our option_definitions vector.
/// 
/// We require to have all constructor arguments named the same.
/// We furthermore require to have default values for either all or no constructor arguments.
/// + all default_values across all constructors need to be the same.
/// Error if those requirements aren't met.
void handle_shared_option(const xml_node &compound_xml)
{
    option_definition opt(get_complete_xml_text(compound_xml.child("compoundname")));
    std::cout << "SharedOption-derived class definition found: " << opt.name << std::endl;

    opt.constructor_args = find_so_constructors_args(opt, compound_xml);
    opt.const_char_members = find_options_class_const_char_members(opt, compound_xml);

    option_definitions[opt.name] = opt;

    for(auto member : opt.const_char_members)
        std::cout << "['const char *'-members of " << opt.name << "] " << member.name << " = " << member.default_value << std::endl;
}

} } } // namespace inexor::rpc::gluegen
