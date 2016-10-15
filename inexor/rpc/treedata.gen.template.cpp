{{file_comment}} {{!
  This is the input mustache-template for our treedatacontext file containing info about the Tree.
  This is part of a state sync machine to generate the network code for variables whichs state get automatically synced in the background.
  Instead of modifying the generated .gen.cpp you should modify this file.
  Generation takes place on each build of Inexor (for each target having a different TreeContext aka a different set of Shared Vars).
  For more info about how to use this template engine, read the manual of mustache (its easy).
}}
#include <unordered_map>

#include "treedata.gen.grpc.pb.h" // got generated into the same folder.

#include "inexor/rpc/SharedTree.hpp"
#include "inexor/rpc/RpcSubsystem.hpp"


// List of extern SharedVar declarations
{{#shared_vars}}{{namespace_sep_open}}
    extern SharedVar<{{type_cpp_primitive}}> {{name_cpp_short}};
{{namespace_sep_close}}
{{/shared_vars}}

namespace inexor { namespace rpc {

void set_on_change_functions()
{
    // TODO: Dont call by type but by reference if not a ptr: *or& -> {cpp_observer_type}
{{#shared_vars}}        {{name_cpp_full}}.onChange.connect([](const {{type_cpp_primitive}} oldvalue, const {{type_cpp_primitive}} newvalue)
        {
            {{namespace}}::TreeNodeChanged val;
            val.set_{{name_unique}}(newvalue);
            main2net_interthread_queue.enqueue(std::move(val));
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
    // { index, enum_type(string=0,float=1,int=2) }
{{#shared_vars}}    { {{index}}, {{type_numeric}} },  // {{path}}, {{type_cpp_primitive}}
{{/shared_vars}}
};

} } // namespace inexor::rpc
