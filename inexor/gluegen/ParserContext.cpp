#include "inexor/gluegen/ParserContext.hpp"

#include <boost/algorithm/string.hpp>

#include <iostream>

using namespace std;
using namespace pugi;
using namespace inexor::filesystem;
using namespace boost;

namespace inexor { namespace rpc { namespace gluegen {

void ParserContext::AST_xmls::find_xml_files(Path directory)
{
    // sorting input files:

    list_files(directory, all_xml_file_names, ".xml");
    for(auto &file : all_xml_file_names)
    {

        if(contains(file.filename().string(), "_8cpp.xml") || contains(file.filename().string(), "_8hpp.xml")
           || contains(file.filename().string(), "namespace"))// cpp/hpp files for namespaced contents
        {
            code_xml_file_names.push_back(file);
        } else if(contains(file.stem().string(), "class") || contains(file.stem().string(), "struct")) class_xml_file_names.push_back(file);
    }
}

void ParserContext::AST_xmls::parse_all_xmls()
{
    for(auto &file : class_xml_file_names)
    {
        auto xml = make_unique<xml_document>();
        if(parse_xml_file(file, xml)) class_ast_xmls.push_back(std::move(xml));
    }
    for(auto &file : code_xml_file_names)
    {
        auto xml = make_unique<xml_document>();
        if(parse_xml_file(file, xml)) code_ast_xmls.push_back(std::move(xml));
    }
}

bool ParserContext::AST_xmls::parse_xml_file(Path & file, unique_ptr<xml_document>& xml)
{
    if(!xml->load_file(file.make_preferred().c_str(), parse_default|parse_trim_pcdata))
    {
        std::cout << "XML file representing the AST couldn't be parsed: " << file << std::endl;
        return false;
    }
    return true;
}


} } } // namespace inexor::rpc::gluegen
