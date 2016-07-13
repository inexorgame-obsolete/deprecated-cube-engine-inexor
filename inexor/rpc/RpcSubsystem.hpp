#pragma once

#include <memory>

#include <moodycamel/concurrentqueue.h>
#include <moodycamel/blockingconcurrentqueue.h>

#include <boost/variant.hpp>

#include "inexor/rpc/treedata.gen.grpc.pb.h"

#include "inexor/util/Subsystem.hpp"
#include "inexor/rpc/SharedTree.hpp"

typedef int64_t int64; // size is important for us, proto explicitly specifies int64

namespace inexor {
namespace rpc {

class RpcSubsystem : public inexor::util::Subsystem
{
public:
    RpcSubsystem();
    virtual ~RpcSubsystem();
    virtual void tick();
};

struct net2maintupel
{
    // we pass a pointer to the variable instead of the variablename to the main thread (thats faster, and no mainthread function need to be generated).
    // Note that the pointer is valid as long as we deal with static data only (sidenote for vectors).
    void* ptr2var;
    int type;

    boost::variant<std::string, int64, float> value;
};

extern moodycamel::ConcurrentQueue<inexor::tree::TreeNodeChanged>  main2net_interthread_queue; // Something gets pushed on this (lockless threadsafe queue) when we changed values. Gets handled by serverthread.
extern moodycamel::ConcurrentQueue<net2maintupel> net2main_interthread_queue; // Something gets pushed on this (lockless threadsafe queue) when a value has arrived. Gets handled by Subsystem::tick();

} // namespace inexor
} // namespace rpc
