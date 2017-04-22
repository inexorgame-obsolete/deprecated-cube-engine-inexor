/// The distribution of values is done on c++ side via an GRPC bidirectional streaming server.
/// This file soley contains a not very useful client for debugging purpose.

#pragma once

#include <cstdint>

#include <grpc/grpc.h>
#include <grpc++/grpc++.h>

#include "inexor/util/Logging.hpp"

namespace inexor { namespace rpc {

/// Temporary test client
template<typename DATA_TYPE, typename SERVICE_TYPE>
class TestRpcClient
{
private:
    DATA_TYPE make_test_msg()
    {
        DATA_TYPE t;
        //t.set__masterport(25);
        return t;
    }


public:

    void Start(std::string port)
    {
        std::shared_ptr<grpc::Channel> channel(grpc::CreateChannel("localhost:"+port, grpc::InsecureChannelCredentials()));
        std::unique_ptr<typename SERVICE_TYPE::Stub> stub_(SERVICE_TYPE::NewStub(channel));
        grpc::ClientContext context;
        grpc::CompletionQueue cq;

        std::unique_ptr<grpc::ClientAsyncReaderWriter<DATA_TYPE, DATA_TYPE> > stream(stub_->AsyncSynchronize(&context, &cq, (void *)2));

        /// Wait for connection
        void *tag;
        bool ok = false;
        cq.Next(&tag, &ok);
        // ASSERT(ok && tag == (void *)2)
        ///

        constexpr uintptr_t writetag = 4;
        constexpr uintptr_t readtag =  3;

        DATA_TYPE receivedvalue;

        stream->Write(make_test_msg(), (void *)writetag);
        stream->Read(&receivedvalue, (void *)readtag);

        for(int i = 0; i <1000; i++)
        {
            cq.Next(&tag, &ok);
            if(!ok)
            {
                spdlog::get("global")->info("[Client] Not okay: for = {}", ((tag == (void *)writetag) ? "writer" : "reader"));
                return;
            }
            if(tag == (void *)writetag)
            {
                spdlog::get("global")->info("[Client] Sent testmessage");
            }
            else if(tag == (void *)readtag)
            {
                spdlog::get("global")->info("[Client] Received. Index: {}", receivedvalue.key_case());
                stream->Read(&receivedvalue, (void *)readtag);
            }
            //  stream->WritesDone();
        }
    }
};

} } // ns inexor::rpc
