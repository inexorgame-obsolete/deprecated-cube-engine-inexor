
#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/parse_sourcecode.hpp"
#include "inexor/gluegen/parse_sharedfunc.hpp"
#include "inexor/gluegen/tree.hpp"

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
#include <iostream>

using namespace pugi;
using namespace std;
using namespace boost::algorithm;

namespace inexor { namespace rpc { namespace gluegen {


/// Allocates and parses a new shared
shared_class_definition *new_shared_class_definition(xml_node &compound_xml)
{
    shared_class_definition *def = new shared_class_definition();

    def->refid = compound_xml.attribute("id").value();
    string full_name =  get_complete_xml_text(compound_xml.child("compoundname")); // including the namespace e.g. inexor::rendering::screen

    vector<string> ns_and_name(split_by_delimiter(full_name, "::"));

    def->class_name = ns_and_name.back();
    ns_and_name.pop_back();
    def->definition_namespace = join(ns_and_name, "::");
    def->containing_header = compound_xml.child("location").attribute("file").value();

    if(contains(def->containing_header, ".c"))
    {
        std::cerr << "ERROR: SharedClasses can only be defined in cleanly include-able **header**-files"
            << std::endl << "Class in question is " << full_name << std::endl;
    }

    const unordered_map<string, string> init_list_map = get_class_initialized_member_map(compound_xml);

    // If there is an entry SharedClass(...) in the constructor initializer list, then we treat ... as SharedOptions
    auto class_options_itr = init_list_map.find("SharedClass");
    if(class_options_itr != init_list_map.end())
        def->attached_options = parse_attached_options_string(class_options_itr->second);

    for(xml_node &var_xml : find_class_member_vars(compound_xml))
    {
        string type = get_complete_xml_text(var_xml.child("type"));
        if(!contains(type, "SharedVar")) continue; // TODO recursive logic

        parse_sharedvar_of_class(var_xml, def->definition_namespace, def->class_name, init_list_map, def->nodes);
    }
    return def;
}

void shared_class_definition::make_all_children_node_class_var()
{
    for(ShTreeNode *child : nodes)
    {
        child->node_type = ShTreeNode::NODE_CLASS_VAR;
        child->set_all_childrens_type(ShTreeNode::NODE_CLASS_VAR);
    }
}

void parse_shared_class_definitions(ParserContext &data)
{
    for(xml_node &compound_xml : data.def_nodes.shared_classes)
    {
        shared_class_definition *s = new_shared_class_definition(compound_xml);
        data.shared_class_definitions[s->refid] = s;
    }

    for(auto it : data.shared_class_definitions)
        it.second->make_all_children_node_class_var();
}

bool is_shared_class_definition_node(const pugi::xml_node class_xml_compound_node)
{
    for(xml_node &base_class : class_xml_compound_node.children("basecompoundref"))
    {
        string baseclassname = base_class.text().as_string();
        if(baseclassname == "SharedClass")
            return true;
    }
    return false;
}

shared_class_definition *is_shared_class_instance_node(const pugi::xml_node xml_member_node, ParserContext &data)
{
    vector<string> all_childs_refids = get_values_of_childs_attribute(xml_member_node.child("type"), "refid");

    if(all_childs_refids.empty()) return nullptr;
    // a template can have many refids, the first is the outer case (SharedList<SharedClass, SharedClassB> name)
    auto finditr = data.shared_class_definitions.find(all_childs_refids.front());
    return finditr == data.shared_class_definitions.end() ? nullptr : finditr->second;
}


void parse_class_instance(const xml_node var_xml, std::string var_namespace, shared_class_definition *class_definition, ParserContext &data)
{
    const string type = get_complete_xml_text(var_xml.child("type"));
    const string name = get_complete_xml_text(var_xml.child("name"));

    //if(argsstring.empty()) return; // it is just an "extern" declaration
    // the constructor of SharedClasses are not containing sharedoptions (or should we?)
    // TODO: do class instances get here for extern declarations?

    vector<attached_option> options = class_definition->attached_options; // = parse_attached_options_string(args.back()); TODO
    ShTreeNode *class_node = new ShTreeNode(type, name, var_namespace, class_definition, options);
    class_definition->instances.push_back(class_node);

    for(ShTreeNode *child : class_definition->nodes)
    {
        // TODO sollte rekursiv sein wenn type = child
        ShTreeNode *childclone = new ShTreeNode(child);
        childclone->parent = class_node;
        class_node->children.push_back(childclone);
    }
    class_node->set_all_childrens_parent_entry(); // DOPPELT GEMOPPELT?

    // In case we have a template child, we link the definition of it into the class.
    vector<string> all_childs_refids = get_values_of_childs_attribute(var_xml.child("type"), "refid");
    if(all_childs_refids.size() >= 2)
    {
        // a template can have many refids, TODO: we only recognize the first one atm, not all template args.
        auto finditr = data.shared_class_definitions.find(all_childs_refids[1]);
        if(finditr != data.shared_class_definitions.end())
            class_node->template_type_definition = finditr->second;
    }
}

} } } // namespace inexor::rpc::gluegen
