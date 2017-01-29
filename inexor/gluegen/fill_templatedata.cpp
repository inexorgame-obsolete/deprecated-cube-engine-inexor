#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/fill_templatedata.hpp"
#include "inexor/gluegen/tree.hpp"

#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
#include <unordered_set>

using namespace inexor::rpc::gluegen;
using namespace std;


void add_rendered_template_hybrids(const so_class_definition &opt, TemplateData &variable, const TemplateData constructor_args_data)
{
    for(auto member : opt.const_char_members)
    {
        TemplateData template_hybrid_rendered{TemplateData::Type::Object};
        MustacheTemplate tmpl{member.default_value};             // the default value of the const char member acts as template.
        template_hybrid_rendered["s"] = tmpl.render(constructor_args_data); // gets rendered using the data from the constructor args
        variable[member.name] << template_hybrid_rendered; // and the rendered string is templatedata for the variable (key = <name> from "const char *<name>"

        //std::cout << "rendered " << template_hybrid.name << " : " << template_hybrid_rendered["s"].stringValue() << std::endl;
    }
}

void add_generic_templatedata_default_values(TemplateData &variable, ShTreeNode node)
{
    for(auto reg_option : so_class_definitions)
    {
        so_class_definition &opt = reg_option.second;
        if(!opt.constructor_has_default_values) continue;
        for(auto arg : opt.constructor_args)
        {
            MustacheTemplate tmpl{arg.default_value};
            variable[arg.name] = tmpl.render(variable); // add templatedata for this
        }
    }
}

/// Add templatedata for this shared variable coming from shared options.
void add_generic_templatedata(TemplateData &variable, ShTreeNode node)
{
    // renders: 1. fill data: 
    //             - take node constructor args, compare it with so_class_definition names [done]
    //             - create TemplateData instance for every constructor param
    //            1b. default values
    //              - if so_class_definition has default values add default value TemplateData
    //              - 2 cases for default values: values or templates (special: char * get rendered nontheless)
    //          2. render templates optionclass.templatehybrids().templatestr; templatehybrid { name, templatestr } with passed TemplateData
    //             add rendered templates to passed TemplateData

    // sharedvar-list
    //    <template_hybrid_name>-list
    //       sharedoptioninstance1 // e.g. NoSync()
    //       sharedoptioninstance2 // e.g. Persistent()
    //       sharedoptioninstance3 // e.g. Range(0, 3)


    // add template data from constructor arguments:

    TemplateData constructor_args_data = variable;

    add_generic_templatedata_default_values(constructor_args_data, node);
    for(auto node_option : node.attached_options) // a node option is one instance of a sharedoption attached to a node (a SharedVar or SharedClass)
    {
        auto find_in_declarations = so_class_definitions.find(node_option.name);
        if(find_in_declarations == so_class_definitions.end()) continue; // this argument is not corresponding with the name of a sharedoption.
        std::cout << "node: " << node.get_name_cpp_full() << " option: " << node_option.name << std::endl;

        const so_class_definition &opt = find_in_declarations->second;
        // if(opt.constructor_args.size() >= node_option.constructor_args.size()) throw exception("");

        for(size_t i = 0; i < node_option.constructor_args.size(); i++) // loop instance constructor args, take names from defintion of the constructor args.
        {
            if(i >= opt.constructor_args.size()) break; // more arguments used for the instance than the declaration allows.
            constructor_args_data[opt.constructor_args[i].name] = node_option.constructor_args[i];
        }
    }

    // render template_hybrids and add them to the templatedata of the variable:

    // add empty lists to the variable key=the name
    for(auto opt : so_class_definitions)
        for(auto member : opt.second.const_char_members)
            variable[member.name] = TemplateData(TemplateData::Type::List);

    unordered_set<string> rendered_th_names;
    // render th's occuring in the constructor
    for(auto node_option : node.attached_options)
    {
        auto find_in_definitions = so_class_definitions.find(node_option.name);
        if(find_in_definitions == so_class_definitions.end()) continue;
        add_rendered_template_hybrids(find_in_definitions->second, variable, constructor_args_data);
        rendered_th_names.emplace(find_in_definitions->second.name);
    }

    // render th's which have default values and havent been rendered before.
    for(auto reg_option : so_class_definitions)
    {
        so_class_definition &opt = reg_option.second;
        auto find_in_instances = rendered_th_names.find(opt.name);
        if(find_in_instances == rendered_th_names.end() && opt.constructor_has_default_values)
            add_rendered_template_hybrids(opt, variable, constructor_args_data);
    }
}
/// Adds the entries namespace_sep_{open|close} to the templatedata given.
/// open is e.g. "namespace inexor { namespace rendering {" close is "} }"
void add_namespace_seps_templatedata(TemplateData &templdata, string ns_str)
{
    vector<string> ns(split_by_delimiter(ns_str, "::"));

    TemplateData namespace_sep_open{TemplateData::LambdaType{
        [ns](const string&)
    {
        std::stringstream ss;
        for(auto &tok : ns)
        {
            if(tok.empty())continue;
            ss << "namespace ";
            ss << tok;
            ss << " { ";
        }
        return ss.str();
    }}};

    TemplateData namespace_sep_close{TemplateData::LambdaType{
        [ns](const std::string&)
    {
        std::stringstream ss;
        for(auto &tok : ns)
        {
            if(tok.empty())continue;
            ss << " }";
        }
        return ss.str();
    }}};

    templdata.set("namespace_sep_open", namespace_sep_open);
    templdata.set("namespace_sep_close", namespace_sep_close);
}

TemplateData get_shared_var_templatedata(ShTreeNode &node, int index)
{
    TemplateData curvariable{TemplateData::Type::Object};
    curvariable.set("is_global", node.node_type==ShTreeNode::NODE_CLASS_VAR ? TemplateData::Type::False : TemplateData::Type::True);
    curvariable.set("type_protobuf", node.get_type_protobuf());
    curvariable.set("type_cpp_full", node.get_type_cpp_full());
    curvariable.set("type_cpp_primitive", node.get_type_cpp_primitive());
    curvariable.set("type_numeric", std::to_string(node.get_type_numeric()));
    curvariable.set("index", std::to_string(index));
    curvariable.set("name_unique", node.get_name_unique());
    curvariable.set("path", node.get_path());
    curvariable.set("default_value", node.get_default_value());
    curvariable.set("name_cpp_full", node.get_name_cpp_full());
    curvariable.set("name_cpp_short", node.get_name_cpp_short());

    add_namespace_seps_templatedata(curvariable, node.get_namespace());

    add_generic_templatedata(curvariable, node);
    return curvariable;
}

void add_node_templatedata(ShTreeNode &node, int &index, TemplateData &templdata)
{
    switch(node.node_type)
    {
        case ShTreeNode::NODE_GLOBAL_VAR:
        case ShTreeNode::NODE_CLASS_VAR:
        {
            templdata << get_shared_var_templatedata(node, index);
            index++;
            break;
        }
        case ShTreeNode::NODE_CLASS_SINGLETON:
        {
            for(auto child : node.children)
            {
                add_node_templatedata(*child, index, templdata);
            }
            break;
        }
    }
}

TemplateData get_shared_class_templatedata(ShTreeNode &node)
{
    TemplateData curclass{TemplateData::Type::Object};

    shared_class_definition def = node.class_definition;
    add_namespace_seps_templatedata(curclass, node.get_namespace());
    curclass.set("definition_header_file", def.containing_header);

    // TODO: recognize the innerclass case!
    curclass.set("type_parent_cpp_full", def.definition_namespace + "::" + def.class_name);
    curclass.set("name_parent_cpp_short", node.get_name_cpp_short());

    return curclass;
}

TemplateData fill_templatedata(vector<ShTreeNode *> &tree, const string &ns)
{
    TemplateData tmpldata{TemplateData::Type::Object};

    tmpldata.set("file_comment", "// This file gets generated!\n"
                 "// Do not modify it directly but its corresponding template file instead!");

    // namespace string -> protobuf syntax: replace :: with .
    vector<string> ns_list(split_by_delimiter(ns, "::"));
    const string &proto_pkg = boost::join(ns_list, ".");
    tmpldata.set("package", proto_pkg);
    tmpldata.set("namespace", ns);

    TemplateData sharedvars{TemplateData::Type::List};

    // The protocol buffers variable index
    int index = 21;
    for(ShTreeNode *node : tree)
    {
        add_node_templatedata(*node, index, sharedvars);
    }
    tmpldata.set("shared_vars", sharedvars);

    TemplateData sharedclasses{TemplateData::Type::List};

    for(ShTreeNode *node : tree)
    {
        if(node->node_type!=ShTreeNode::NODE_CLASS_SINGLETON) continue;
        sharedclasses << get_shared_class_templatedata(*node);
    }
    tmpldata.set("shared_classes", sharedclasses);

    return tmpldata;
}

