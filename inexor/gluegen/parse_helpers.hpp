#pragma once
#include <vector>
#include <string>

#include <pugiconfig.hpp>
#include <pugixml.hpp>

namespace inexor { namespace rpc { namespace gluegen {


/// Replaces input containing escaped chars with their string representation (e.g. "\\n" with the newline character)
/// Currently it supports: \' \" \? \\ \a \b \f \n \r \t \v . Search for Escape codes c++ to get their specific meaning.
extern std::string unescape(std::string &str);

/// Remove the last second last char is a digit (or a dot) and the last one is a 'f'.
///
/// This function removes the 'f' from a string like "0.0f", so it works in protobuf where you don't write floats this way.
/// Only if the first char is a floating point number otherwise the string stays unaltered.
extern void trim_floating_point_number_mark(std::string &str);

/// This function workarounds doxygens faulty xml which contains '= whateverisbehind' as initializer (totally raw, no c++11 support it seems)
extern void remove_leading_assign_sign(std::string &str);

/// If first char of string is matching, remove the first and the last one of the string (no matter what the last one is).
/// @warning does not do leading/trailing whitespace skimming.
extern void remove_surrounding_char(std::string &str, const char first_cha);

/// @warning requires data has no whitespace before or after the quotes.
extern void remove_surrounding_quotes(std::string &str);

/// @warning requires data has no whitespace before or after the brackets, see remove_surrounding_char.
extern void remove_surrounding_brackets(std::string &str);

/// Splits a string into all parts which are only A-Z, 0-9 or _.
/// Any other chars in the input wont appear in the output vector.
extern std::vector<std::string> split_in_alphanumeric_parts(const std::string input, bool respect_quotes);

/// C++ equivalent of strtok, tokenizes the input string based on the occurences of delimiter.
extern std::vector<std::string> split_by_delimiter(const std::string input, const std::string delimiter);

/// Splits e.g. 'something, some(dadadalu,da), "ich,,,skwo"' into 3 strings "something", "some(dadadalu,da)" and ""ich,,,skwo""
/// split_by_delimiter with ',' as delimiter wouldnt handle (,) correctly.
///
extern std::vector<std::string> tokenize_arg_list(const std::string input);

/// Splits a "something(totally(but pretty much ) stupid)great" into "something" "totally(but pretty much ) stupid" and "great".
/// Its greedy meaning that the first full bracket will be matched to the result, everything else goes into after_bracket.
extern std::string parse_bracket(std::string input, std::string &before_bracket, std::string &after_bracket);


/// Text can have subfields with more text + siblings text, usually you want all of them concatenated.
extern std::string get_complete_xml_text(const pugi::xml_node parent, bool recursive = true);

/// Checks whether there is a child with a specific attribute with the same ID as the searchid.
/// @return true if found.
extern bool has_child_with_attribute(const pugi::xml_node &parent, std::string attribute_name, std::string attribute_value);

/// Returns the values of all first class childrens attribute given by name.
/// You check for "refid" and get all first level childs refid.
extern std::vector<std::string> get_values_of_childs_attribute(const pugi::xml_node &parent, std::string attribute_name);

} } } // namespace inexor::rpc::gluegen
