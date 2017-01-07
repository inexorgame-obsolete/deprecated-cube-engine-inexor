#pragma once
#include <vector>
#include <string>

#include <pugiconfig.hpp>
#include <pugixml.hpp>

namespace inexor { namespace rpc { namespace gluegen {

/// This function workarounds doxygens faulty xml which contains '= whateverisbehind' as initializer (totally raw, no c++11 support it seems)
extern void remove_leading_assign_sign(std::string &str);

/// If first char of string is matching, remove the first and the last one of the string (no matter what the last one is).
/// @warning does not do leading/trailing whitespace skimming.
extern void remove_surrounding_char(std::string &str, const char first_cha);

/// @warning requires data has no whitespace before or after the quotes.
extern void remove_surrounding_quotes(std::string &str);

/// @warning requires data has no whitespace before or after the brackets, see remove_surrounding_char.
extern void remove_surrounding_brackets(std::string &str);


/// C++ equivalent of strtok, tokenizes the input string based on the occurences of delimiter.
extern std::vector<std::string> split_by_delimiter(std::string input, std::string delimiter);

/// Splits e.g. 'something, some(dadadalu,da), "ich,,,skwo"' into 3 strings "something", "some(dadadalu,da)" and ""ich,,,skwo""
/// split_by_delimiter with ',' as delimiter wouldnt handle (,) correctly.
///
extern std::vector<std::string> tokenize_arg_list(std::string input);

/// Splits a "something(totally(but pretty much ) stupid)great" into "something" "totally(but pretty much ) stupid" and "great".
/// Its greedy meaning that the first full bracket will be matched to the result, everything else goes into after_bracket.
extern std::string parse_bracket(std::string input, std::string &before_bracket, std::string &after_bracket);


/// Text can have subfields with more text + siblings text, usually you want all of them concatenated.
std::string get_complete_xml_text(const pugi::xml_node parent, bool recursive = true);

} } } // namespace inexor::rpc::gluegen
