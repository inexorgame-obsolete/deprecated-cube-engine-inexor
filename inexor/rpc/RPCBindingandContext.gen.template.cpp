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
#include "inexor/rpc/SharedTree.hpp"
#include "inexor/rpc/RpcSubsystem.hpp"
#include "inexor/rpc/RpcTestClient.hpp"

{{#shared_classes}}
#include "{{definition_header_file}}"{{/shared_classes}}


SUBSYSTEM_REGISTER(rpc, inexor::rpc::RpcSubsystem<{{namespace}}::TreeEvent, {{namespace}}::TreeService::AsyncService>); // needs to be in no namespace!

using {{namespace}}::TreeEvent;    // The message type.
using {{namespace}}::TreeService;        // The RPC service (used only for instancing the RpcServer


using std::string; // shared functions sometimes have string arguments.

// List of extern (global) SharedVar declarations
{{#shared_vars}}{{#is_global}}{{namespace_sep_open}}
    extern {{{type_cpp_full}}} {{name_cpp_short}};
{{namespace_sep_close}}
{{/is_global}}{{/shared_vars}}

// List of extern SharedClass declarations
{{#shared_classes}}{{namespace_sep_open}}
    extern {{{type_parent_cpp_full}}} {{name_parent_cpp_short}};
{{namespace_sep_close}}
{{/shared_classes}}

// List of extern SharedFunc declarations
{{#shared_functions}}{{#parameter_lists}}{{namespace_sep_open}}
    extern {{{function_declaration}}};
{{namespace_sep_close}}
{{/parameter_lists}}{{/shared_functions}}


namespace inexor { namespace rpc {

/// Just a pretty basic/stupid test rpc client for debugging purpose.
void testrpcclient()
{
    std::thread t([]
    {
        TestRpcClient<TreeEvent, TreeService> *guide = new TestRpcClient<TreeEvent, TreeService>();

        guide->Start();
    });
    t.detach();
}

// We currently use a static function to signal the subsystem changes (since we cant yet SUBSYSTEM_GET it) .. so this is a temporary workaround.
template <>
std::vector<RpcServer<TreeEvent, TreeService::AsyncService>::clienthandler> RpcServer<TreeEvent, TreeService::AsyncService>::clients = {};


void set_on_change_functions()
{
    // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
{{#shared_vars}}        {{name_cpp_full}}.onChange.connect([](const {{type_cpp_primitive}} oldvalue, const {{type_cpp_primitive}} newvalue)
        {
            {{namespace}}::TreeEvent val;
            val.set_{{name_unique}}(newvalue);
            inexor::rpc::RpcServer<{{namespace}}::TreeEvent, {{namespace}}::TreeService::AsyncService>::send_msg(std::move(val));
        }
    );
{{/shared_vars}}
}

void send_all_vars()
{
    // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
{{#shared_vars}}        {{name_cpp_full}}.sync();
{{/shared_vars}}
}

/// (proto)index -> pointer to the to-be-updated-variable.
const std::unordered_map<int64, void *> cppvar_pointer_map
{
    // { index, pointer_to_the_changed_var (see net2maintupel::ptr2var) }
{{#shared_vars}}    { {{index}}, (void *) &{{name_cpp_full}} },
{{/shared_vars}}
};

/// (proto)index -> Data type (cpp_type_t)
const std::unordered_map<int64, int> index_to_type_map
{
    // { index, enum_type(string=0,float=1,int=2,function=3) }
{{#shared_vars}}    { {{index}}, {{type_numeric}} },  // {{path}}, {{type_cpp_primitive}}
{{/shared_vars}}
// TODO functions
};

template<typename MSG_TYPE>
bool execute_function(int index, MSG_TYPE &receivedval)
{
    switch(index) {
{{#shared_functions}}{{#parameter_lists}}    case {{index}}:
        {{function_name_cpp_full}}({{#params}}SharedFunction_{{function_name_unique}}_params_{{index}}.{{param_name}}() {{#not_last_param}},{{/not_last_param}}
{{/params}});
        break;
{{/parameter_lists}}{{/shared_functions}}
      default: return false;
    }
    return true;
}

} } // namespace inexor::rpc
