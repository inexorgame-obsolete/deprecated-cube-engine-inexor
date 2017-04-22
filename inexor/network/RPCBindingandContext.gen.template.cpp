{{file_comment}} {{!
  This is the input mustache-template for our treedatacontext file containing info about the Tree.
  This is part of a state sync machine to generate the network code for variables whichs state get automatically synced in the background.
  Instead of modifying the generated .gen.cpp you should modify this file.
  Generation takes place on each build of Inexor (for each target having a different TreeContext aka a different set of Shared Vars).
  For more info about how to use this template engine, read the manual of mustache (its easy).
}}
#include <unordered_map>
#include <vector>
#include <string>

#include "RPCTreeData.gen.grpc.pb.h" // got generated into the same folder.

#include "inexor/util/Subsystem.hpp"
#include "inexor/network/SharedTree.hpp"
#include "inexor/network/RpcSubsystem.hpp"
#include "inexor/network/RpcTestClient.hpp"

{{#shared_class_definitions}}{{^is_shared_list}}#include "{{definition_header_file}}"
{{/is_shared_list}}{{/shared_class_definitions}}


SUBSYSTEM_REGISTER(rpc, inexor::rpc::RpcSubsystem<{{namespace}}::TreeEvent, {{namespace}}::TreeService::AsyncService>); // needs to be in no namespace!

using {{namespace}}::TreeEvent;    // The message type.
using {{namespace}}::TreeService;        // The RPC service (used only for instancing the RpcServer


using std::string; // shared functions sometimes have string arguments.

// List of extern (global) SharedVar declarations
{{#shared_vars}}{{#is_global}}{{namespace_sep_open}}
    extern {{{type_cpp_full}}} {{name_cpp_short}};
{{namespace_sep_close}}
{{/is_global}}{{/shared_vars}}

// List of extern global SharedClass declarations
{{#shared_class_definitions}}{{^is_shared_list}}{{#instances}}{{namespace_sep_open}}
    extern {{{definition_name_cpp}}} {{name_parent_cpp_short}};
{{namespace_sep_close}}
{{/instances}}{{/is_shared_list}}{{/shared_class_definitions}}

// List of extern global SharedList declarations
{{#shared_class_definitions}}{{#is_shared_list}}{{#instances}}{{#first_template_type}}{{namespace_sep_open}}
    extern SharedList<{{{definition_name_cpp}}}> {{name_parent_cpp_short}};
{{namespace_sep_close}}
{{/first_template_type}}{{/instances}}{{/is_shared_list}}{{/shared_class_definitions}}

// List of extern SharedFunc declarations
{{#shared_functions}}{{#parameter_lists}}{{^overload_is_expanded}}{{namespace_sep_open}}
    extern {{{function_declaration}}};
{{namespace_sep_close}}
{{/overload_is_expanded}}{{/parameter_lists}}{{/shared_functions}}


namespace inexor { namespace rpc {

/// Just a pretty basic/stupid test rpc client for debugging purpose.
void testrpcclient(std::string port)
{
    std::thread t([port]
    {
        TestRpcClient<TreeEvent, TreeService> *guide = new TestRpcClient<TreeEvent, TreeService>();

        guide->Start(port);
    });
    t.detach();
}

// We currently use a static function to signal the subsystem changes (since we cant yet SUBSYSTEM_GET it) .. so this is a temporary workaround.
template <>
std::vector<RpcServer<TreeEvent, TreeService::AsyncService>::clienthandler> RpcServer<TreeEvent, TreeService::AsyncService>::clients = {};

/// This function sets the functions which get executed when specific stuff has been done on our SharedDeclarations.
void set_on_change_functions()
{
    // Set all Global sharedvars onchange functions
{{#shared_vars}}        {{name_cpp_full}}.onChange.connect([](const {{type_cpp_primitive}} oldvalue, const {{type_cpp_primitive}} newvalue)
        {
            {{namespace}}::TreeEvent val;
            val.set_{{name_unique}}(newvalue);
            inexor::rpc::RpcServer<{{namespace}}::TreeEvent, {{namespace}}::TreeService::AsyncService>::send_msg(std::move(val));
        }
    );
{{/shared_vars}}
      
    // Set all onchange functions for remove/push_back/member_modifed for sharedlists
{{#shared_class_definitions}}{{#is_shared_list}}{{#instances}}{{#first_template_type}}

    {{name_parent_cpp_full}}.element_removed_func = [](int id) {
        {{namespace}}::TreeEvent tevent;
        {{namespace}}::list_{{definition_name_unique}}_removed *rem_msg(tevent.mutable_list_{{instance_name_unique}}_removed());
        rem_msg->set_intern_shared_list_id_number(id);

        inexor::rpc::RpcServer<{{namespace}}::TreeEvent, {{namespace}}::TreeService::AsyncService>::send_msg(std::move(tevent));
    };

    {{name_parent_cpp_full}}.element_pushed_back_func = [](int id, {{definition_name_cpp}} &element) {
        {{namespace}}::TreeEvent tevent;
        {{namespace}}::list_{{definition_name_unique}}_added *added_msg(tevent.mutable_list_{{instance_name_unique}}_added());
        added_msg->set_intern_shared_list_id_number(id);
{{#members}}        added_msg->set_sharedclass_member_{{name_unique}}(element.{{name_cpp_short}});
{{/members}}


        inexor::rpc::RpcServer<{{namespace}}::TreeEvent, {{namespace}}::TreeService::AsyncService>::send_msg(std::move(tevent));
{{#members}}        element.{{name_cpp_short}}.onChange.connect([id](const {{type_cpp_primitive}} oldvalue, const {{type_cpp_primitive}} newvalue)
        {
            {{namespace}}::TreeEvent tevent;
            {{namespace}}::list_{{definition_name_unique}}_modified *modified_msg(tevent.mutable_list_{{instance_name_unique}}_modified());
            modified_msg->set_intern_shared_list_id_number(id);
            modified_msg->set_sharedclass_member_{{name_unique}}(newvalue);

            inexor::rpc::RpcServer<{{namespace}}::TreeEvent, {{namespace}}::TreeService::AsyncService>::send_msg(std::move(tevent));
        });
{{/members}}
    };
{{/first_template_type}}{{/instances}}{{/is_shared_list}}{{/shared_class_definitions}}
}

void send_all_vars()
{
   // TODO reimplement to allow multiple clients again..
}

template<typename MSG_TYPE>
bool handle_index(int index, const MSG_TYPE &tree_event)
{
// our first index is {{>index_reset}}
    switch(index) {
  // All basic global shared vars singeltons.
{{#shared_vars}}    case {{>index}}:{{#is_string}}
        {{name_cpp_full}}.setnosync(strdup(tree_event.{{name_unique}}().c_str()));{{/is_string}}{{^is_string}}
        {{name_cpp_full}}.setnosync(tree_event.{{name_unique}}());{{/is_string}}
        break;
{{/shared_vars}}

  // All event message for the SharedLists
{{#shared_class_definitions}}{{#is_shared_list}}{{#instances}}{{#first_template_type}}    case {{>index}}: // list  {{instance_name_unique}} add event
    {
        {{definition_name_cpp}} new_entry;
        auto &add_sub_msg = tree_event.list_{{instance_name_unique}}_added();
{{#members}}        new_entry.{{name_cpp_short}}.setnosync(add_sub_msg.sharedclass_member_{{name_unique}}());
        {{name_parent_cpp_full}}.push_back(std::move(new_entry));
{{/members}}
        break;
    }
    case {{>index}}: // list {{instance_name_unique}} modify event
    {
        auto &modify_sub_msg = tree_event.list_{{instance_name_unique}}_modified();
        int id = modify_sub_msg.intern_shared_list_id_number();
        if(id < 0 || id >= {{name_parent_cpp_full}}.size()) break;
        {{definition_name_cpp}} &ref = {{name_parent_cpp_full}}[id];
        switch(modify_sub_msg.key_case()) {
{{#members}}        case {{local_index}}:
            ref.{{name_cpp_short}}.setnosync(modify_sub_msg.sharedclass_member_{{name_unique}}()); break;
{{/members}}
        }
        break;
    }
    case {{>index}}: // list {{instance_name_unique}} remove event
    {
        int id = tree_event.list_{{instance_name_unique}}_modified().intern_shared_list_id_number();
        if(id < 0 || id >= {{name_parent_cpp_full}}.size()) break;
        {{name_parent_cpp_full}}.erase(id);
        break;
    }
{{/first_template_type}}{{/instances}}{{/is_shared_list}}{{/shared_class_definitions}}

  // All event message for global SharedClasses
{{#shared_class_definitions}}{{^is_shared_list}}{{#instances}}{{#members}}    case {{>index}}: // global  {{name_parent_cpp_full}}.{{name_cpp_short}} event
        {{name_parent_cpp_full}}.{{name_cpp_short}}.setnosync(tree_event.class_{{instance_name_unique}}_var_{{name_unique}}());
        break;
{{/members}}{{/instances}}{{/is_shared_list}}{{/shared_class_definitions}}

  // All shared function events (function gets executed when event comes in)
{{#shared_functions}}{{#parameter_lists}}    case {{>index}}:
        {{function_name_cpp_full}}({{#params}}{{#is_string}}strdup({{/is_string}}tree_event.sharedfunction_{{function_name_unique}}_params_{{overload_counter}}().function_param_{{param_name}}(){{#is_string}}.c_str()){{/is_string}} {{#not_last_param}},{{/not_last_param}}
{{/params}});
        break;
{{/parameter_lists}}{{/shared_functions}}
      default: return false;
    }
    return true;
}

} } // namespace inexor::rpc
