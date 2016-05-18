

#include <grpc++/grpc++.h>


#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "inexor/rpc/RpcSubsystem.hpp"
#include "inexor/util/Logging.hpp"

#include "inexor/rpc/inexor_service.grpc.pb.h"

#include <moodycamel/concurrentqueue.h>
#include <moodycamel/blockingconcurrentqueue.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerAsyncReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using grpc::CompletionQueue;
using grpc::ServerCompletionQueue;
using inexor::tree::ChangedValue;
using inexor::tree::TreeService;

/*
// Helper (Maybe): Can we get sth like this maybe?
void findsetfield(inexor::tree::Value val)
{
    const std::string path = val.GetTypeName();
    val.GetDescriptor()->FindFieldByName(path);
    val.innerqueue().innerthing();
}

// This one gets generated
void connectall()
{
    auto lambdaj = [](const T &oldvalue, const T &newvalue)
    {
        inexor::tree::Value val;
        inexor::tree::innerqueue q;
        val.mainpath().
        q.set_innerthing();
        val.set_innerqueue(q);
        main2net_interthread_queue.enqueue(val);
    };
    SharedVar j;
    j.onchange.connect(lambdaj);
}

// This one too:
void connectnet2main(inexor::tree::Value receivedval)
{
option1:
    loop over all values; / or findsetfield() somehow
    switchcase for all values;
    security layer in switch case (generated).
    return net2main_interthread_queue.enque(SharedVar *pointer)
}
*/

moodycamel::ConcurrentQueue<std::string> main2net_interthread_queue; // Something gets pushed on this (lockless threadsafe queue) when we changed value. Gets handled by serverthread.
moodycamel::ConcurrentQueue<std::string> net2main_interthread_queue; // Something gets pushed on this (lockless threadsafe queue) when a value has arrived. Gets handled by Subsystem::tick();


ChangedValue MakeChangedValue(const char *path)
{
    ChangedValue c;
    c.set_path(path);
    return c;
}

/// Bidirectional Server (able to read and write) which receives changes from our sendchangequeue/the network 
/// and put it into the network/readchangequeue (respectively)
class BiDiServer
{
    std::unique_ptr<Server> grpc_server;       // instanciated only
    ServerContext grpc_context;
    TreeService::AsyncService service;

    /// The completion queue (where notifications of the succcess of a network commands get retrieved).
    std::unique_ptr<ServerCompletionQueue> cq;

    /// The stream we write into / receive data from (asynchronously).
    ServerAsyncReaderWriter<ChangedValue, ChangedValue> stream;

    /// Either a reading or writing request
    struct CallInstance
    {
        enum TYPES { READER, WRITER } type;

        bool isbusy = false;                    // only filled when request was write: workaround for grpc behavior to only allow one write at a time. 
        ChangedValue change;                    // the read will fill this on completion, the write filled it for later reference when requesting the async write.

        ServerAsyncReaderWriter<ChangedValue, ChangedValue> *stream;

        CallInstance(TYPES type_, ServerAsyncReaderWriter<ChangedValue, ChangedValue> *stream_) : type(type_), stream(stream_) {}

        void startreading()
        {
            stream->Read(&change, (void *)this); // we pass the address of this class as the callback tag we retrieve on completion from cq.Next()
        }

        void startwrite(const std::string &str)
        {
            change = MakeChangedValue(str.c_str());
            stream->Write(change, (void *)this);
        }
    };

    CallInstance *reader = nullptr;
    CallInstance *writer = nullptr;

public:

    std::string server_address;

    BiDiServer(const char *address)
        : server_address(address), stream(&grpc_context)
    {
        ServerBuilder builder;

        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);

        cq = builder.AddCompletionQueue();

        grpc_server = builder.BuildAndStart();
    }

    ~BiDiServer()
    {
        grpc_server->Shutdown();
        cq->Shutdown();                       // Always shutdown the completion queue after the server.
    }

    /// Wait for a client to connect on this address.
    /// @note blocks until someone arrived.
    void waitforconnection()
    {
        service.RequestSynchronize(&grpc_context, &stream, cq.get(), cq.get(), (void *)1);
        void *tag;
        bool succeed=false;
        cq->Next(&tag, &succeed);

        writer = new CallInstance(CallInstance::WRITER, &stream);
        reader = new CallInstance(CallInstance::READER, &stream);
    }

    void run()
    {
        GPR_ASSERT(writer != nullptr && reader != nullptr);

        std::vector<std::string> testservermsgs{
            "First servermsg",
            "Second servermsg",
            "Third servermsg",
            "Fourth servermsg"
        };

        reader->startreading();

        int i = 0;
        while(true)
        {
            if(!writer->isbusy && i < 4)
            {
                writer->isbusy = true;
                writer->startwrite(testservermsgs[i]);
                i++;
            }

            void *tag;
            bool succeed=false;
            if(!cq->Next(&tag, &succeed))
            {
                spdlog::get("global")->info() << "RPC state syncing failed: Client did shutdown(?)";
                break;
            }
            else if(succeed)
            {
                CallInstance *completed = static_cast<CallInstance*>(tag);

                if(completed->type == CallInstance::WRITER)
                {
                    spdlog::get("global")->info() << "[Server] Sent " << completed->change.path();
                    completed->isbusy = false;
                }
                else
                {
                    spdlog::get("global")->info() << "[Server] Received " << completed->change.path();
                    net2main_interthread_queue.enqueue(completed->change.path());
                    reader->startreading(); // request new read
                }
            }
            else // we do not always succeed.. WHY? probably timeout.. change to cq-AsyncNext() to finetune.
            {
                CallInstance *call = static_cast<CallInstance*>(tag);
                spdlog::get("global")->info() << "[Server] received msg  was incomplete for " << (call->type == CallInstance::WRITER ? "writer" : "reader") << " .. Shutting down";
                break; // we break on purpose (atm) to escape our blocking client (which is for testing only) so this line would need to go for a all-the-time syncing server..
            }
        }
    }

    void finish()
    {
        Status status;
        stream.Finish(status, (void *)1);
        void *tag;
        bool succeed=false;

        do { cq->Next(&tag, &succeed); } //wait for the finish tag to come back.
        while(tag != (void *)1);
    }
};

void RunServer()
{

    std::thread t([]
    {
        BiDiServer server("0.0.0.0:50051");


        spdlog::get("global")->info() << "RPC server listening on " << server.server_address;

        server.waitforconnection();
        server.run(); // this should run forever
        server.finish();
    }
    );
    t.detach();
}

//////// Client



class RouteGuideClient
{
private:

    std::unique_ptr<TreeService::Stub> stub_;
    ClientContext context;

public:
    std::shared_ptr<ClientReaderWriter<ChangedValue, ChangedValue> > stream;
    RouteGuideClient(std::shared_ptr<Channel> channel)
        : stub_(TreeService::NewStub(channel)), stream(stub_->Synchronize(&context))
    {
    }

    void RouteChat()
    {
        std::thread writer([this]()
        {
            std::vector<ChangedValue> notes{
                MakeChangedValue("First message"),
                MakeChangedValue("Second message"),
                MakeChangedValue("Third message"),
                MakeChangedValue("Fourth message")
            };
            for (const ChangedValue& note : notes) {
                spdlog::get("global")->info() << "[Client] Sending message " << note.path();
                stream->Write(note);
            }

            stream->WritesDone();
        });
        ChangedValue new_value;
        while (stream->Read(&new_value))
        {
            spdlog::get("global")->info() << "[Client] Received message " << new_value.path();
        }
        writer.join();
        //Status status = stream->Finish();
        //if (!status.ok()) {
        //    spdlog::get("global")->info() << "RouteChat rpc failed.";
        //}
    }
};

void clientrpc()
{
    RouteGuideClient *guide = new RouteGuideClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    guide->RouteChat();
}




