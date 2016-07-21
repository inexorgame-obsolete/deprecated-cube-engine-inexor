#include <iostream>
#include <vector>

#include "inexor/gluegen/pugixml.hpp" // TODO make this global

#include "inexor/filesystem/path.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/tree.hpp"

using namespace pugi;
using namespace inexor::filesystem;


namespace inexor { namespace rpc { namespace gluegen {

Sharedwo x(DefaultValue()|DefaultValue());
bool find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree)
{
    std::vector<Path> all_files;
    list_files(xml_folder, all_files, ".xml");
    for(auto it : all_files)
    {
        std::cout << "file: " << it.filename() << std::endl;
      //  if(it.filename().string().find_last_of("8)
    }

    //xml_document xml;
    //x.zwei = 2;
    //if(!xml.load_file(xml_folder.c_str()))
    //{
    //    std::cout << "XML file representing the AST couldn't be parsed: " << xml_folder << std::endl;
    //    return false;
    //}


    //pugi::xpath_node_set file_xmls = xml.select_nodes("/doxygen/compounddef[@kind='file' and @language='C++']");
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



    return true;
}

} } } // namespace inexor::rpc::gluegen
