#include "inexor/gluegen/parse_helpers.hpp"
#include "inexor/gluegen/fill_templatedata.hpp"
#include "inexor/gluegen/tree.hpp"
#include "inexor/gluegen/ParserContext.hpp"

#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

namespace inexor { namespace rpc { namespace gluegen {


void add_rendered_template_hybrids(const option_definition &opt, TemplateData &variable, const TemplateData constructor_args_data)
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

/// A shared option can have default values. All Classes WITHOUT having this option attached will use the options default values then!
void add_options_with_default_values_templatedata(TemplateData &variable, ParserContext &data)
{
    for(auto reg_option : data.option_definitions)
    {
        option_definition &opt = reg_option.second;
        if(!opt.constructor_has_default_values) continue;
        for(auto arg : opt.constructor_args)
        {
            MustacheTemplate tmpl{arg.default_value};
            variable[arg.name] = tmpl.render(variable); // add templatedata for this
        }
    }
}

/// Add templatedata for this shared variable coming from shared options.
void add_options_templatedata(TemplateData &variable, vector<attached_option> attached_options, ParserContext &data)
{
    // renders: 1. fill data: 
    //             - take node constructor args, compare it with option_definition names [done]
    //             - create TemplateData instance for every constructor param
    //            1b. default values
    //              - if option_definition has default values add default value TemplateData
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

    add_options_with_default_values_templatedata(constructor_args_data, data);
    for(auto node_option : attached_options) // a node option is one instance of a sharedoption attached to a node (a SharedVar or SharedClass)
    {
        auto find_in_declarations = data.option_definitions.find(node_option.name);
        if(find_in_declarations == data.option_definitions.end()) continue; // this argument is not corresponding with the name of a sharedoption.
       // std::cout << "node: " << node.get_name_cpp_full() << " option: " << node_option.name << std::endl;

        const option_definition &opt = find_in_declarations->second;
        // if(opt.constructor_args.size() >= node_option.constructor_args.size()) throw exception("");

        for(size_t i = 0; i < node_option.constructor_args.size(); i++) // loop instance constructor args, take names from defintion of the constructor args.
        {
            if(i >= opt.constructor_args.size()) break; // more arguments used for the instance than the declaration allows.
            constructor_args_data[opt.constructor_args[i].name] = node_option.constructor_args[i];
        }
    }

    // render template_hybrids and add them to the templatedata of the variable:

    // add empty lists to the variable key=the name
    for(auto opt : data.option_definitions)
        for(auto member : opt.second.const_char_members)
            variable[member.name] = TemplateData(TemplateData::Type::List);

    unordered_set<string> rendered_th_names;
    // render th's occuring in the constructor
    for(auto node_option : attached_options)
    {
        auto find_in_definitions = data.option_definitions.find(node_option.name);
        if(find_in_definitions == data.option_definitions.end()) continue;
        add_rendered_template_hybrids(find_in_definitions->second, variable, constructor_args_data);
        rendered_th_names.emplace(find_in_definitions->second.name);
    }

    // render th's which have default values and havent been rendered before.
    for(auto reg_option : data.option_definitions)
    {
        option_definition &opt = reg_option.second;
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

/// Index is a very special data entry: every time it gets referenced it gets iterated!
TemplateData::PartialType get_index_incrementer(bool reset = false)
{
    return TemplateData::PartialType([reset]() {
        static int count = 21;
        if(reset) count = 20;
        return to_string(count++);
    });
}

/// @param local_index if this is different from -1 we set "local_index" with it.
///        otherwise we use the tree_event index counter.. @see add_event_index_templatedata
TemplateData get_shared_var_templatedata(ShTreeNode &node, int local_index, ParserContext &data)
{
    TemplateData curvariable{TemplateData::Type::Object};
    // These is a hacky way to distinct between these in pure-data form.. TODO embedd logic in template?
    curvariable.set("is_global", node.node_type==ShTreeNode::NODE_CLASS_VAR ? TemplateData::Type::False : TemplateData::Type::True);
    curvariable.set("is_int", node.get_type_numeric()== node.t_int ? TemplateData::Type::True : TemplateData::Type::False);
    curvariable.set("is_float", node.get_type_numeric()== node.t_float ? TemplateData::Type::True : TemplateData::Type::False);
    curvariable.set("is_string", node.get_type_numeric()== node.t_cstring ? TemplateData::Type::True : TemplateData::Type::False);

    curvariable.set("type_protobuf", node.get_type_protobuf());
    curvariable.set("type_cpp_full", node.get_type_cpp_full());
    curvariable.set("type_cpp_primitive", node.get_template_type());
    curvariable.set("type_numeric", std::to_string(node.get_type_numeric()));
    if(local_index>0) curvariable.set("local_index", std::to_string(local_index));
    curvariable.set("index", get_index_incrementer());
    curvariable.set("name_unique", node.get_name_unique());
    curvariable.set("path", node.get_path());
    curvariable.set("default_value", node.get_default_value());
    curvariable.set("name_cpp_full", node.get_name_cpp_full());
    curvariable.set("name_cpp_short", node.get_name_cpp_short());

    add_namespace_seps_templatedata(curvariable, node.get_namespace());

    add_options_templatedata(curvariable, node.attached_options, data);
    return curvariable;
}

TemplateData get_shared_class_templatedata(shared_class_definition *def, ParserContext &ctx, bool add_instances = true)
{
    TemplateData cur_definition{TemplateData::Type::Object};
    // The class needs to be defined in a cleanly includeable header file.
    cur_definition.set("definition_header_file", def->containing_header);

    // TODO: recognize the innerclass case!
    // The name of the class with leading namespace.
    cur_definition.set("definition_name_cpp", def->get_name_cpp_full());
    cur_definition.set("definition_name_unique", def->get_name_unique());

    add_options_templatedata(cur_definition, def->attached_options, ctx);

    TemplateData all_instances{TemplateData::Type::List};

    if(add_instances) for(ShTreeNode *inst_node : def->instances)
    {
        TemplateData cur_instance{TemplateData::Type::Object};
        add_namespace_seps_templatedata(cur_instance, inst_node->get_namespace());

        // The first parents name, e.g. of inexor::game::player1.weapons.ammo its player1.
        cur_instance.set("name_parent_cpp_short", inst_node->get_name_cpp_short());
        cur_instance.set("name_parent_cpp_full", inst_node->get_name_cpp_full());
        cur_instance.set("instance_name_unique", inst_node->get_name_unique());
        cur_instance.set("path", inst_node->get_path());
        cur_instance.set("index", get_index_incrementer());

        // were doing this for sharedlists, where the first template is relevant.
        if(inst_node->template_type_definition)
        {
            TemplateData dummy_list(TemplateData::Type::List);
            dummy_list << get_shared_class_templatedata(inst_node->template_type_definition, ctx, false);
            cur_instance.set("first_template_type", std::move(dummy_list));
        }

        add_options_templatedata(cur_instance, inst_node->attached_options, ctx);

        all_instances << cur_instance;
    }
    cur_definition.set("instances", all_instances);

    TemplateData members{TemplateData::Type::List};

    int local_index = 2;
    for(ShTreeNode *child : def->nodes)
    {
        members << get_shared_var_templatedata(*child, local_index++, ctx);
    }
    cur_definition.set("members", members);
    return cur_definition;
}

/// list shared_functions 
///   list #parameter_lists}}
///       function_declaration
///       path ?
///       list params: local_index type_protobuf param_name, not_last_param
///   function_name_unique [DONE]
///   function_name_cpp [DONE]
///   namespacesep [DONE]
///        
typedef shared_function::function_parameter_list::param::PRIMITIVE_TYPES PRIMITIVE_TYPES;
TemplateData get_shared_function_templatedata(shared_function &sf)
{
    TemplateData curfunction{TemplateData::Type::Object};

    curfunction.set("function_name_cpp_full", sf.get_name_cpp_full());
    curfunction.set("function_name_unique", sf.get_unique_name());
    curfunction.set("path", sf.get_path());
    add_namespace_seps_templatedata(curfunction, sf.ns);


    TemplateData overloads{TemplateData::Type::List};

    int overload_counter = 0;
    for(auto &paramlist : sf.parameter_lists)
    {
        TemplateData paramlistdata{TemplateData::Type::Object};

        paramlistdata.set("function_declaration", paramlist.declaration);
        paramlistdata.set("index", get_index_incrementer());

        paramlistdata.set("overload_counter", std::to_string(overload_counter++));

        paramlistdata.set("overload_is_expanded", paramlist.clone ? TemplateData::Type::True : TemplateData::Type::False);

        TemplateData params{TemplateData::Type::List};
        int local_index = 1;
        for(int i = 0; i < paramlist.params.size(); i++)
        {
            auto &param = paramlist.params[i];

            TemplateData paramdata{TemplateData::Type::Object};
            paramdata.set("type_protobuf", param.type==PRIMITIVE_TYPES::P_FLOAT ? "float" :
                         param.type==PRIMITIVE_TYPES::P_INT ? "int32" : "string");
            paramdata.set("is_int", param.type==PRIMITIVE_TYPES::P_INT ? TemplateData::Type::True : TemplateData::Type::False);
            paramdata.set("is_float", param.type==PRIMITIVE_TYPES::P_FLOAT ? TemplateData::Type::True : TemplateData::Type::False);
            paramdata.set("is_string", param.type==PRIMITIVE_TYPES::P_STR ? TemplateData::Type::True : TemplateData::Type::False);

            paramdata.set("param_name", param.name);
            paramdata.set("local_index", std::to_string(i+1));
            paramdata.set("not_last_param", i == paramlist.params.size()-1 ? TemplateData::Type::False : TemplateData::Type::True);
            params << paramdata;
        }
        paramlistdata.set("params", params);
        overloads << paramlistdata;
    }
    curfunction.set("parameter_lists", overloads);

    return curfunction;
}

TemplateData fill_templatedata(ParserContext &data, const string &ns)
{
    TemplateData tmpldata{TemplateData::Type::Object};

    tmpldata.set("file_comment", "// This file gets generated!\n"
                 "// Do not modify it directly but its corresponding template file instead!");

    // namespace string -> protobuf syntax: replace :: with .
    vector<string> ns_list(split_by_delimiter(ns, "::"));
    const string &proto_pkg = boost::join(ns_list, ".");
    tmpldata.set("package", proto_pkg);
    tmpldata.set("namespace", ns);

    tmpldata.set("index_reset", get_index_incrementer(true)); // This design is so fucked up.. mustache forces us too though.

    TemplateData sharedvars{TemplateData::Type::List};

    for(ShTreeNode *node : data.instances)
    {
        sharedvars << get_shared_var_templatedata(*node, -1, data);
    }
    tmpldata.set("shared_vars", sharedvars);

    TemplateData sharedclasses{TemplateData::Type::List};

    for(auto class_def_it : data.shared_class_definitions)
    {
        sharedclasses << get_shared_class_templatedata(class_def_it.second, data);
    }
    tmpldata.set("shared_class_definitions", sharedclasses);


    TemplateData sharedfunctionsdata{TemplateData::Type::List};

    for(auto sf_it : data.shared_functions)
        sharedfunctionsdata << get_shared_function_templatedata(sf_it.second);
    tmpldata.set("shared_functions", sharedfunctionsdata);

    return tmpldata;
}

} } } // namespace inexor::rpc::gluegen
