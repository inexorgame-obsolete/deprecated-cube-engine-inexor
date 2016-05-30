

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
using grpc::ClientAsyncReaderWriter;
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
std::atomic_bool serverstarted = false;

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
        serverstarted = true;
    }

    ~BiDiServer()
    {
        grpc_server->Shutdown();
        cq->Shutdown();                       // Always shutdown the completion queue after the server.
        delete reader;
        delete writer;
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
            "1. server2client message",
            "2. server2client message",
            "3. server2client message",
            "4. server2client message"
        };

        reader->startreading();

        int i = 0;
        while(serverstarted)
        {
            std::string queueout;
            if(!writer->isbusy && i < 4)
            {
                writer->isbusy = true;
                writer->startwrite(testservermsgs[i]);
                i++;
            }
            else if(!writer->isbusy && main2net_interthread_queue.try_dequeue(queueout))
            {
                writer->startwrite(queueout);
            }

            void *tag;
            bool succeed=false;
            
            CompletionQueue::NextStatus stat = cq->AsyncNext(&tag, &succeed, gpr_inf_past(GPR_CLOCK_REALTIME));
            if(stat == CompletionQueue::NextStatus::SHUTDOWN)
            {
                spdlog::get("global")->info() << "RPC state syncing failed: Client did shutdown";
                break;
            }
            else if(stat == CompletionQueue::NextStatus::GOT_EVENT && succeed)
            {
                CallInstance *completed = static_cast<CallInstance*>(tag);

                if(completed->type == CallInstance::WRITER)
                {
                    spdlog::get("global")->info() << "[Server] Sent: " << completed->change.path();
                    completed->isbusy = false;
                }
                else
                {
                    spdlog::get("global")->info() << "[Server] Received: " << completed->change.path();
                    net2main_interthread_queue.enqueue(completed->change.path());
                    reader->startreading(); // request new read
                }
            }
            else if(stat != CompletionQueue::NextStatus::TIMEOUT)
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

void StopServer()
{
    serverstarted = false;
}
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

void sendtestmessage(const char *message)
{
    std::string gotback;
    if(net2main_interthread_queue.try_dequeue(gotback))
        spdlog::get("global")->info() << "Mainthread: " << gotback;
    main2net_interthread_queue.enqueue(message);
}

//////// Client



class RouteGuideClient
{
private:



public:

    void RouteChat()
    {
        std::shared_ptr<Channel> channel(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
        std::unique_ptr<TreeService::Stub> stub_(TreeService::NewStub(channel));
        ClientContext context;
        CompletionQueue cq;

        std::unique_ptr<ClientAsyncReaderWriter<ChangedValue, ChangedValue> > stream(stub_->AsyncSynchronize(&context, &cq, (void *) 2));

        /// Wait for connection
        void *tag;
        bool ok = false;
        cq.Next(&tag, &ok);
        // ASSERT(ok && tag == (void *)2)
        ///

        {
            const int writetag = 4;
            const int readtag =  3;

            const std::vector<ChangedValue> testclientmsgs{
                MakeChangedValue("1. client2server message"),
                MakeChangedValue("2. client2server message"),
                MakeChangedValue("3. client2server message"),
                MakeChangedValue("4. client2server message")
            };
            auto msgiterator = testclientmsgs.begin();
            ChangedValue receivedvalue;

            stream->Write(*msgiterator, (void *)writetag);
            stream->Read(&receivedvalue, (void *)readtag);

            void *tag;
            bool ok = false;
            while(true)
            {
                cq.Next(&tag, &ok);
                if(!ok)
                {
                    spdlog::get("global")->info() << "[Client] Not okay: for = " << ((tag == (void *)writetag) ? "writer" : "reader");
                    return;
                }
                if(tag == (void *)writetag)
                {
                    spdlog::get("global")->info() << "[Client] Sent: " << msgiterator->path();
                    msgiterator++;
                    if(msgiterator != testclientmsgs.end())
                    {
                        stream->Write(*msgiterator, (void *)writetag);
                    }
                }
                else if(tag == (void *)readtag)
                {
                    spdlog::get("global")->info() << "[Client] Received: " << receivedvalue.path();
                    stream->Read(&receivedvalue, (void *)readtag);
                }
              //  stream->WritesDone();
            }
        }
    }
};

void clientrpc()
{
    std::thread t([]
    {
        RouteGuideClient *guide = new RouteGuideClient();

        guide->RouteChat();
    });
    t.detach();
}




