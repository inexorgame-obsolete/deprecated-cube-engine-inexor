#pragma once

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace inexor { namespace rpc { namespace gluegen {

struct name_defaultvalue_tupel
{
    std::string name;
    std::string default_value;
};
typedef std::vector<name_defaultvalue_tupel> name_defaultvalue_vector;

/// A declaration of a class with a "SharedOption" parent class.
///
/// To make our glue generation more flexible we invented Shared Option classes,
/// which contain info about how to render stuff and which are used in the C++ Tree API.
///
/// class xy : SharedOption {
///     xy(T <paramname> = <paramdefvalue>, S <param2name> = <param2defvalue>, ......) {}
///     const char *<membername> = <membertemplate>;
/// };
struct option_definition
{
    /// The name of the class.
    std::string name;

    /// Whether or not the constructor has default values is important for subsequent
    bool constructor_has_default_values = false;

    /// All constructor arguments: name first, defaultvalue second.
    /// since its an ordered map we have the positions of the arguments.
    // we dont have type deduction!
    name_defaultvalue_vector constructor_args;

    /// "const char *" members are template "partials" (see mustache docs) for our shared declarations.
    /// 
    /// They may contain template data entries previously available or those named the same as the constructor parameters.
    name_defaultvalue_vector const_char_members;

    option_definition() {}
    option_definition(std::string &&class_name) : name(class_name) {}
};


/// A SharedOption instance **used** when instancing a variable or class.
/// (used inside the constructor: "SharedVar<int> xy(0, NoSync()|Persistent(true))").
/// For classes it currently only works for the whole definition of it!
/// The SharedClass(..) entry in the shared classes constructor initializer list can contain those options.
/// (e.g. "ClassName() : SharedClass(GameServerOnly(true)|FastLine(true)), membervar1(0), membervar2(0)... { }")
/// TODO: Note that we forbid non-default-constructable shared classes. (or delete it explicitly somehow)
/// -> option_name = "Persistent" constructor_args.push_back("true").
struct attached_option
{
    /// The sharedoptions name.
    std::string name;
    /// The constructor args for the sharedoption instance.
    std::vector<std::string> constructor_args;
};

/// Parses " NoSync()|Persistent()|Function([] { echo("hello"); })   "
extern std::vector<attached_option> parse_attached_options_string(std::string options_list_str, bool verbose = false);

struct ParserContext;

/// Parse all option_definition xml nodes and save it to our option_definitions map.
extern void analyze_shared_options(ParserContext &data);

/// Returns true if this compound xml node has as parent the SharedOption base class.
extern bool is_option_class_node(const pugi::xml_node class_xml_compound_node);



} } } // namespace inexor::rpc::gluegen
