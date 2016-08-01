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
using namespace std;


namespace inexor { namespace rpc { namespace gluegen {

Sharedwo x(Range(0, 2)|CustomPath("inexor/rendering/screen/"));

bool find_shared_decls(const std::string xml_folder, std::vector<ShTreeNode> &tree)
{
    //sorting input files:
    std::vector<Path> all_xmls;
    std::vector<Path> cpp_xmls;
    std::vector<Path> class_xmls;

    list_files(xml_folder, all_xmls, ".xml");
    for(auto file : all_xmls)
    {
        if(contains(file.filename().string(), "_8cpp.xml")) cpp_xmls.push_back(file);
        if(contains(file.stem().string(), "class") || contains(file.stem().string(), "struct")) class_xmls.push_back(file);
    }

    // parsing cpp-file xmls for shared declarations.
    //
    // doxygens AST in cpp files xml is mainly:
    // doxygen
    //   compound
    //     section("func")
    //       member
    //       member..
    //     section("var")
    //     section("define")..
    for(auto file : cpp_xmls)
    {
        std::cout << "processing file: " << file.make_preferred() << std::endl;

        xml_document xml;
        if(!xml.load_file(file.make_preferred().c_str(), parse_default|parse_trim_pcdata))
        {
            std::cout << "XML file representing the AST couldn't be parsed: " << file << std::endl;
            continue;
        }

        xml_node compound_xml = xml.child("doxygen").child("compounddef"); //[@kind='file' and @language='C++']");


        // skip files not including our API definition header.
        bool file_includes_treehpp = false;
        for(xml_node header : compound_xml.children("includes"))
            if(!strcmp(header.text().as_string(), "inexor/rpc/SharedTree.hpp")) file_includes_treehpp = true;
        //if(!file_includes_treehpp)
        //{
        //    std::cout << "skipping xml file: " << file.make_preferred() << " (no sharedtree.hpp include found)" << std::endl;
        //    continue;
        //}

        std::vector<xml_node> sharedvar_nodes;
        for(auto section : compound_xml.children("sectiondef"))
        {
            if(!strncmp(section.attribute("kind").value(), "func", 4))
            {
                for(auto member : section.children("memberdef"))
                {
                    if(strstr(member.child("type").text().as_string(), "SharedVar"))
                        sharedvar_nodes.push_back(member);
                }
            }
        }

        // handle shared variable declarations.
        for(auto var : sharedvar_nodes)
        {
            const char *type = var.child("type").text().as_string();
            const char *name = var.child("name").text().as_string();
            std::cout << "type: " << type << " name: " << name << " argsstring: " << var.child("argsstring").text().as_string() << std::endl;
            tree.push_back(ShTreeNode(type, name));
        }
    }
    return true;
}

} } } // namespace inexor::rpc::gluegen
