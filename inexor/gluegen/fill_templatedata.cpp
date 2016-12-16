
#include <vector>
#include <string>
#include <unordered_set>

#include "inexor/gluegen/parse_sourcecode.hpp" // only bc of some string formatting/splitting functions, remove as refractored
#include "inexor/gluegen/fill_templatedata.hpp"
#include "inexor/gluegen/tree.hpp"

using namespace inexor::rpc::gluegen;
using namespace std;



// class xy : SharedOption {
// const char *<name> = <template>;
// };
// -> key==<name>, value==<template>


void add_rendered_template_hybrids(const optionclass &opt, TemplateData &variable, const TemplateData constructor_args_data)
{
    for(auto template_hybrid : opt.template_hybrids)
    {
        TemplateData template_hybrid_rendered{TemplateData::Type::Object};
        MustacheTemplate tmpl{template_hybrid.default_value};
        template_hybrid_rendered["s"] = tmpl.render(constructor_args_data);
        variable[template_hybrid.name] << template_hybrid_rendered;

        //std::cout << "rendered " << template_hybrid.name << " : " << template_hybrid_rendered["s"].stringValue() << std::endl;
    }
}

void add_generic_templatedata_default_values(TemplateData &variable, ShTreeNode node)
{
    for(auto reg_option : optionclasses)
    {
        optionclass &opt = reg_option.second;
        if(!opt.hasdefaultvals) continue;
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
    //             - take node constructor args, compare it with optionclass names [done]
    //             - create TemplateData instanz for every constructor param
    //            1b. default values
    //              - if optionclass has default values add default value TemplateData
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
    for(auto node_option : node.shared_options)
    {
        auto find_in_definitions = optionclasses.find(node_option.class_name);
        if(find_in_definitions == optionclasses.end()) continue;
        std::cout << "node: " << node.get_name_cpp_full() << " option: " << node_option.class_name << std::endl;

        const optionclass &opt = find_in_definitions->second;

        for(size_t i = 0; i < node_option.constructor_args.size(); i++) // loop instance constructor args, take names from defintion of the constructor args.
        {
            if(i >= opt.constructor_args.size()) break; // should never happen
            constructor_args_data[opt.constructor_args[i].name] = node_option.constructor_args[i];
        }
    }

    // render template_hybrids and add them to the templatedata of the variable:

    // add empty lists to the variable key=th name
    for(auto opt : optionclasses)
        for(auto template_hybrid : opt.second.template_hybrids)
            variable[template_hybrid.name] = TemplateData(TemplateData::Type::List);

    unordered_set<string> rendered_th_names;
    // render th's occuring in the constructor
    for(auto node_option : node.shared_options)
    {
        auto find_in_definitions = optionclasses.find(node_option.class_name);
        if(find_in_definitions == optionclasses.end()) continue;
        add_rendered_template_hybrids(find_in_definitions->second, variable, constructor_args_data);
        rendered_th_names.emplace(find_in_definitions->second.name);
    }

    // render th's which have default values and havent been rendered before.
    for(auto reg_option : optionclasses)
    {
        optionclass &opt = reg_option.second;
        auto find_in_instances = rendered_th_names.find(opt.name);
        if(find_in_instances == rendered_th_names.end() && opt.hasdefaultvals)
            add_rendered_template_hybrids(opt, variable, constructor_args_data);
    }
}

TemplateData fill_templatedata(vector<ShTreeNode> &tree, const string &ns)
{
    TemplateData tmpldata{TemplateData::Type::Object};

    tmpldata.set("file_comment", "// This file gets generated!\n"
                 "// Do not modify it directly but its corresponding template file instead!");

    // namespace string -> protobuf syntax: replace :: with .
    vector<string> ns_list(split_by_delimiter(ns, "::"));
    const string &proto_pkg = join_to_str(ns_list, '.');
    tmpldata.set("package", proto_pkg);
    tmpldata.set("namespace", ns);

    TemplateData sharedvars{TemplateData::Type::List};
    int index = 1;
    for(auto node : tree)
    {
        TemplateData curvariable{TemplateData::Type::Object};
        curvariable.set("type_protobuf", node.get_type_protobuf());
        curvariable.set("type_cpp_primitive", node.get_type_cpp_primitive());
        curvariable.set("type_numeric", std::to_string(node.get_type_numeric()));
        curvariable.set("index", std::to_string(index++));
        curvariable.set("name_unique", node.get_name_unique());
        curvariable.set("path", node.get_path());
        curvariable.set("name_cpp_full", node.get_name_cpp_full());
        curvariable.set("name_cpp_short", node.get_name_cpp_short());

        vector<string> ns(split_by_delimiter(node.get_namespace(), "::"));

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

        curvariable.set("namespace_sep_open", namespace_sep_open);
        curvariable.set("namespace_sep_close", namespace_sep_close);

        add_generic_templatedata(curvariable, node);

        sharedvars << curvariable;
    }
    tmpldata.set("shared_vars", sharedvars);

    return tmpldata;
}

