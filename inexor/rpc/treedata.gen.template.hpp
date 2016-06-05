{{file_comment}} {{!
  This is the input mustache-template for our state syncing machines header file containing an instance
  of sharedvardata containg the reflected info about the Tree.
  Instead of modifying the generated .proto you should modify this file.
  Generation takes place on each build of Inexor.
  For more info about how to use this template engine, read the manual of mustache (its easy).
}}

#pragma once

#include <unordered_map>

#include "inexor/rpc/inexor_service.grpc.pb.h"

#include "inexor/rpc/SharedTree.hpp"
#include "inexor/rpc/RpcSubsystem.hpp"


// List of extern SharedVar declarations
{{#shared_vars}}{{namespace_sep_open}}
    extern SharedVar<{{cpp_type}}> {{cpp_raw_name}};
{{namespace_sep_close}}
{{/shared_vars}}

namespace inexor { namespace rpc {

/// Known C++ SharedVar types
enum cpp_type_t
{
    t_cstring = 0,
    t_float,
    t_int
};

class treedata {
  public:

    void connectall()
    {
        // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
{{#shared_vars}}        {{cpp_name}}.onChange.connect([](const {{cpp_type}} oldvalue, const {{cpp_type}} newvalue)
            {
                {{namespace}}::TreeNodeChanged val;
                val.set_{{unique_name}}(newvalue);
                main2net_interthread_queue.enqueue(std::move(val));
            }
        );
{{/shared_vars}}
    }

    void syncall()
    {
        // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
{{#shared_vars}}        {{cpp_name}}.sync();
{{/shared_vars}}
    }

    /// (proto)index -> pointer to the to-be-updated-variable.
    const std::unordered_map<int64, void *> cppvar_pointer_map 
    {
        // { index, pointer_to_the_changed_var (see net2maintupel::ptr2var) }
    {{#shared_vars}}    { {{index}}, (void *) &{{cpp_name}} },
    {{/shared_vars}}
    };

    /// (proto)index -> Data type (cpp_type_t)
    const std::unordered_map<int64, int> index_to_type_map
    {
        // { index, enum_type(string=0,float=1,int=2) }
    {{#shared_vars}}    { {{index}}, {{type}} },  // {{path}}, {{cpp_type}}
    {{/shared_vars}}
    };

} client_treedata;

} } // namespace inexor::rpc
