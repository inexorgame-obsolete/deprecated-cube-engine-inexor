#pragma once

#include "inexor/gluegen/parse_sharedoption.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <string>
#include <vector>


namespace inexor { namespace rpc { namespace gluegen {


struct shared_function
{
    std::string name;
    std::string ns;
    std::vector<attached_option> options;

    /// We can possibly find a lot of function overloads
    struct function_parameter_list
    {
        struct param
        {
            /// We only allow primitive types in the parameter lists.
            /// Any parameter lists containing a parameter which isn't one of these gets discarded.
            /// If no parameter good enough for us is found, we discard the shared_function and warn.
            enum PRIMITIVE_TYPES { P_INVALID, P_INT, P_FLOAT, P_STR } type;
            std::string name;
            std::string default_value;
            inline bool operator!=(const param &b) { return b.name != name || b.type != type;}
        };
        std::vector<param> params;
        std::string declaration;
        /// If this is a clone, this is a copy of a parameter list which had default values.
        bool clone = false;

        inline bool operator==(const function_parameter_list &p_list)
        {
            if(p_list.params.size() != params.size()) return false;
            for(int i = 0; i < params.size(); i++)
                if(params[i] != p_list.params[i]) return false;
            return true;
        }
        bool has_default_params() const;
    };
    std::string get_name_cpp_full();
    std::string get_unique_name();
    std::string get_path();

    /// All overloaded parameter lists.
    std::vector<function_parameter_list> parameter_lists;

    /// Checks whether this parameter_list is already saved in parameter_lists and pushes back if not.
    /// Special case: A has no default params but B has. A and B share the same parameters though -> drop A for B.
    void add_parameter_list(const function_parameter_list &p_list);
};

/// Returns true if this member var is a function marker.
extern bool is_function_marker_node(const pugi::xml_node var_node);

struct ParserContext;

/// Go through the list of shared function marker nodes and pushes in shared_functions.
/// Shared Function markers: in the GlueGen pass we add dummy booleans named like the functions.
extern void analyze_shared_function_markers(ParserContext &data);

/// looks for shared functions and saves them in the global vector of shared_functions
extern void look_for_shared_functions(ParserContext &data);

/// Returns the sharedfunction if this xml piece is of a type function() with the name of that shared_function.
/// (So it is an overload of that function)
/// otherwise returns nullptr!.
extern shared_function *is_shared_function_declaration_node(const pugi::xml_node xml_member_node, ParserContext &data);

/// Found a new declaration -> add a new entry to the instances vector of the shared function definition.
extern void parse_function_declaration(const pugi::xml_node var_xml, shared_function *sf);

/// Checks for any shared function whether it is correct (e.g. has findable declarations).
extern void control_shared_functions(ParserContext &data);

} } } // namespace inexor::rpc::gluegen
