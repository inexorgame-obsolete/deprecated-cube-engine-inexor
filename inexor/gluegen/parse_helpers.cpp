#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <vector>
#include <string>
#include <algorithm>

using namespace pugi;
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

void remove_leading_assign_sign(string &str)
{
    if(str.empty()) return;
    if(str.front() == '=')
        str.erase(0, 1);
}

void remove_surrounding_char(string &str, const char first_cha)
{
    if(str.empty()) return;
    if(str.front() == first_cha)
    {
        str.erase(0, 1);
        str.erase(str.size() - 1);
    }
}

void remove_surrounding_quotes(std::string &str)
{
    remove_surrounding_char(str, '"');
}

void remove_surrounding_brackets(std::string &str)
{
    remove_surrounding_char(str, '(');
}

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
            do
            {
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
string get_complete_xml_text(const xml_node parent, bool recursive)
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

/// Checks recursively whether there is a child with a specific attribute with the same ID as the searchid.
/// @return true if found.
bool has_child_with_attribute(const xml_node &parent, string attribute_name, string attribute_value)
{
    for(pugi::xml_node child : parent.children())
    {
        if(child.attribute(attribute_name.c_str()).value() == attribute_value)
            return true;
        if(has_child_with_attribute(child, attribute_name, attribute_value))
            return true;
    }
    return false;
}

} } } // namespace inexor::rpc::gluegen
