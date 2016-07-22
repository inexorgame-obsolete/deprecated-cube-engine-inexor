#include <iostream>
#include <set>

#include <boost/algorithm/string.hpp>

#include "inexor/gluegen/pugixml.hpp" // TODO make this global

#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/tree.hpp"

using namespace pugi;
using namespace boost;
using namespace inexor::filesystem;


namespace inexor { namespace rpc { namespace gluegen {

Sharedwo x(DefaultValue()|DefaultValue());
bool find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree)
{
    try {
    std::vector<Path> all_xmls;
    std::vector<Path> cpp_xmls;
    std::vector<Path> class_xmls;

    list_files(xml_folder, all_xmls, ".xml");
    for(auto file : all_xmls)
    {
        //std::cout << "file: " << file.filename() << std::endl;
        if(contains(file.filename().string(), "_8cpp.xml")) cpp_xmls.push_back(file);
        if(contains(file.stem().string(), "class") || contains(file.stem().string(), "struct")) class_xmls.push_back(file);
    }
    //for(auto file : cpp_xmls)
    //{
    //    std::cout << "cpp xmls: " << file.stem() << std::endl;
    //}
    //for(auto file : class_xmls)
    //{
    //    std::cout << "class xmls: " << file.stem() << std::endl;
    //}

    xml_document xml;
    if(!xml.load_file(cpp_xmls.begin()->c_str(), parse_default|parse_trim_pcdata))
    {
        std::cout << "XML file representing the AST couldn't be parsed: " << cpp_xmls.begin()->c_str() << std::endl;
        return false;
    }

    std::cout << cpp_xmls.begin()->filename().string() << std::endl;
    xml_node compound_xml = xml.child("doxygen").child("compounddef"); //[@kind='file' and @language='C++']");
    //for(auto it: compound_xml.attributes())
    //{
    //    std::cout << "comp: " << it.name() << " = " << it.as_string() << std::endl;
    //}
    xml_node *functions_section = nullptr;
    for(auto section : compound_xml.children("sectiondef"))
    {
        std::string attrvalue = section.attribute("kind").value();
        if(!attrvalue.compare("func"))
        {
            functions_section = &section;
            break; // TODO this is required atm since range balbal
        }
    }

    for(auto member : functions_section->children("memberdef"))
    {
        std::cout << "type: " << member.child("type").text().as_string() << std::endl;
        std::cout << "name: " << member.child("name").text().as_string() << std::endl;
        std::cout << "argsstring: " << member.child("argsstring").text().as_string() << std::endl;
    }

    //std::vector<xpath_node> all_variables;
    //for(auto file : file_xmls)
    //{
    //    pugi::xpath_node variablesection = file.node.select_node("sectiondef[@kind='var']");
    //    pugi::xpath_node_set variables = variablesection.node.select_nodes("memberdef[@kind='var']");
    //    for(auto var : variables)
    //    {
    //        if(var.node().child_value("type") == "SharedVar<int>"); // strcmp
    //    }


    //    pugi::xpath_node_set functions = file.node.select_nodes("sectiondef[@kind='func']");
    //}

    //for(xpath_node file : file_xmls)
    //{
    //    bool hasrightinclude = x.zwei;
    //    for(xml_node header : file.node().children("includes"))
    //        if(strcmp(header.text().get(), "inexor/rpc/SharedTree.hpp")) hasrightinclude = true;
    //    if(!hasrightinclude) continue;
    //    xpath_node_set 
    //}

    //std::cout << "Tools:\n";

    //for(pugi::xpath_node_set::const_iterator it = tools.begin(); it != tools.end(); ++it)
    //{
    //    pugi::xpath_node node = *it;
    //    std::cout << node.node().attribute("Filename").value() << "\n";
    //}

    //pugi::xpath_node build_tool = doc.select_node("//Tool[contains(Description, 'build system')]");

    //if(build_tool)
    //    std::cout << "Build tool: " << build_tool.node().attribute("Filename").value() << "\n";


    }
    catch(xpath_exception &e)
    {
        std::cout << "Fatal: XML Parsing Exception thrown (XPATH): " << std::endl
                  << e.what() << std::endl;
    }
    return true;
}

} } } // namespace inexor::rpc::gluegen
