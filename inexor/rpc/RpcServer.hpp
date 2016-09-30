/// This file contains the Remote Procedure Call Server which synchronizes our shared variables with the Scripting Env.

/// Note: This is a header only template library ("header-only" as a consequence of "template").
#pragma once

#include <memory>
#include <string>
#include <exception>
#include <queue>

#include <grpc/grpc.h>
#include <grpc++/grpc++.h>

#include "inexor/util/Logging.hpp"


namespace inexor {
namespace rpc {

#define MAX_RPC_EVENT_CHECKS_PER_TICK 100
#define MAX_RPC_CLIENTS 128 // possible highest value is 255, see encode_signal()

template<typename MSG_TYPE, typename ASYNC_SERVICE_TYPE>
class RpcServer
{
    typedef grpc::ServerAsyncReaderWriter<MSG_TYPE, MSG_TYPE> stream_type;

    std::unique_ptr<grpc::Server> grpc_server; // GRPC server instance, running while this class is alive.
    grpc::ServerContext server_context;        // settings like the ip/port of the server are saved in here.
    ASYNC_SERVICE_TYPE service;

    /// The completion queue (where notifications of the succcess of a network commands get retrieved).
    std::unique_ptr<grpc::ServerCompletionQueue> cq;

    class clienthandler
    {
        /// The stream we write into / receive data from (asynchronously).
        std::unique_ptr<stream_type> stream;

        /// We read asynchronously into this and we always just read one at a time.
        MSG_TYPE read_buffer;

        /// There's always only one write allowed at a time.
        bool writer_busy = false;

        /// Keep a list of outstanding writes, since GRPC limits us to only one outstanding write per stream/client!
        std::queue<MSG_TYPE> outstanding_writes;

        /// Did disconnecting work? If it didn't, why?
        grpc::Status disconnect_status;
    public:

        /// The clients identifier number.
        int id;

        clienthandler(int id_, std::unique_ptr<stream_type> &&stream_) : id(id_), stream(std::move(stream_)) {}

        /// Start an asynchronous read.
        void request_read();
        /// Get the message the last read spit out.
        MSG_TYPE &get_read_result()      { return read_buffer; }

        /// Add message to the queue of to-be-sent messages.
        void write(MSG_TYPE &msg)        { outstanding_writes.push(msg); }

        /// Whether or not writes are outstanding.
        bool has_writes()                { return !outstanding_writes.size(); }
        bool currently_writing()         { return writer_busy; }

        /// Send the next item from the queue, needs to be called only if the queue was empty in the last finished_send_one() and in case of a kick-off
        void request_send_one();
        /// Handle a completed write, send the next item if our queue isnt empty.
        void finished_send_one();

        /// Tell the client he gets disconnected.
        void request_disconnect();
        /// Prints out any error info.
        void finished_disconnect();
    };
    std::vector<clienthandler> clients;

    /// Client which isn't connected yet, a buffer caused by the async API.
    std::unique_ptr<stream_type> connect_slot;
public:
    std::string server_address;

    RpcServer(const char *address);
    ~RpcServer();

    /// This is essentially doing the sending/receiving.
    /// Quits if there are no more values to send and we don't receive anything anymore or if MAX_RPC_EVENT_CHECKS_PER_TICK is reached.
    /// In case of errors it throws a std::exception (TODO).
    void process_queue();

    /// Send any variable changes in the core to all clients.
    /// @param excluded_id is given for broadcasting purpose: you don't want to send back a change you just received from a client.
    void send_msg(MSG_TYPE &&msg, int excluded_id = -1);

private:

    void open_connect_slot();
    void handle_new_connection();

    void request_disconnect_client(int id);
    void finish_disconnect_client(int id);

    clienthandler *get_client(int id)
    {
        for(clienthandler &ci : clients)
            if(ci.id == id) return &ci;
        return nullptr;
    }

    bool any_writes_outstanding();

    void kickoff_writes();

    void handle_queue_event(int encoded_callback);

    int pick_unused_id();
    bool change_variable(MSG_TYPE &receivedval);
};

/// The events we request GRPC to do.
enum EVENT_TYPE
{
    E_WRITE,
    E_READ,
    E_CONNECT,
    E_DISCONNECT
};

/// The GRPC queue signals finished events with void* callbacks.
/// So we compress the needed info (EVENT_TYPE and the clients id) into one integer and cast it to void*.
const inline int encode_signal(EVENT_TYPE event, int clientid)
{
    return event << 16 | clientid;
}

const inline int get_id_from_encoded(int encodedsignal)
{
    return encodedsignal&0xff; // returns just the first 15 bits
}

const inline int get_event_from_encoded(int encodedsignal)
{
    return encodedsignal>>16; // looses the 15 lowest bits (the clientid).
}


template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::clienthandler::request_read()
{
    const int cq_id = encode_signal(E_READ, id);
    stream->Read(&read_buffer, cq_id);
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::clienthandler::request_send_one()
{
    if(writer_busy || has_writes()) return;
    writer_busy = true;
    const int cq_id = encode_signal(E_WRITE, id);
    stream->Write(outstanding_writes.front(), (void *)cq_id);
    outstanding_writes.pop();
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::clienthandler::finished_send_one()
{
    writer_busy = false;
    request_send_one();
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::clienthandler::request_disconnect()
{
    const int cq_id = encode_signal(E_DISCONNECT, id);
    stream->Finish(disconnect_status, (void *)cq_id);
}

/// Prints out any error info.
template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::clienthandler::finished_disconnect()
{
    if(!disconnect_status.ok())
        spdlog::get("global")->error("Disconnecting client errored (msg: {})", disconnect_status.error_message());
}

template<typename MSG_TYPE, typename U> inline
RpcServer<MSG_TYPE, U>::RpcServer(const char *address) : server_address(address)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    cq = builder.AddCompletionQueue();
    grpc_server = builder.BuildAndStart();

    open_connect_slot(); // wait for the first client to connect.
}

template<typename MSG_TYPE, typename U> inline
RpcServer<MSG_TYPE, U>::~RpcServer()
{
    grpc_server->Shutdown();
    cq->Shutdown();          // Always shutdown the completion queue after the server.
}

/// Send any variable changes in the core to all clients.
/// For broadcasting purpose param excluded_id is given: you don't want to send back a change you just received from a client.
template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::send_msg(MSG_TYPE &&msg, int excluded_id = -1)
{
    for(clienthandler &ci: clients)
    {
        if(ci.id != excluded_id) ci.write(msg);
    }
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::open_connect_slot()
{
    connect_slot = std::make_unique<stream_type>(&server_context);
    service.RequestSynchronize(&server_context, connect_slot.get(), cq.get(), cq.get(), (void*)E_CONNECT);
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::handle_new_connection()
{
    int n_id = pick_unused_id();
    clients.push_back(clienthandler(n_id, std::move(connect_slot)));
    connect_slot = nullptr;
    if(clients.size() < MAX_RPC_CLIENTS) open_connect_slot();
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::request_disconnect_client(int id)
{
    clienthandler *client = getclient(id)
    if(client) client->request_disconnect();
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::finish_disconnect_client(int id)
{
    for(auto ci = clients.begin(); ci != clients.end(); ++ci)
        if(ci->id == id) 
        {
            ci->finished_disconnect();
            clients.erase(ci);
        }
    if(!connect_slot) open_connect_slot(); // a slot just became free.
}

template<typename MSG_TYPE, typename U> inline
bool RpcServer<MSG_TYPE, U>::any_writes_outstanding()
{
    for(clienthandler &client : clients)
        if(client.has_writes() || client.currently_writing())
            return true;
    return false;
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::kickoff_writes()
{
    for(clienthandler &client : clients)
        client.request_send_one();
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::process_queue()
{
    kickoff_writes();

    using grpc::CompletionQueue;

    for(int i = 0; i < MAX_RPC_EVENT_CHECKS_PER_TICK; i++)
    {
        int callback_value;
        bool no_internal_grpc_error = false;

        // read the next event from the completion queue (in nonblocking fashion)
        // TODO: adapt blocking time to the time budget and whether or not writes are outstanding
        CompletionQueue::NextStatus stat = cq->AsyncNext((void **)(&callback_value), &no_internal_grpc_error, gpr_inf_past(GPR_CLOCK_REALTIME));

        if(!no_internal_grpc_error) throw std::exception("GRPC had an internal error: Shutting down.");

        if(stat ==  CompletionQueue::NextStatus::GOT_EVENT)
            handle_queue_event(callback_value);
        else if(stat == CompletionQueue::NextStatus::TIMEOUT)
        {
            if(!any_writes_outstanding()) break;
        }
        else if(stat == CompletionQueue::NextStatus::SHUTDOWN)
            throw std::exception("[GRPC Server] Completion Queue Shutdown status received..");
    }
}

template<typename MSG_TYPE, typename U> inline
void RpcServer<MSG_TYPE, U>::handle_queue_event(int encoded_callback)
{

    int event_type = get_event_from_encoded(encoded_callback);
    switch(event_type)
    {
    case E_READ:
    {
        clienthandler *ci = get_client(get_id_from_encoded(encoded_callback));
        if(!ci) break; // TODO we should better process its last messages, but we dont have the clients read_buffer anymore.

        MSG_TYPE &msg = ci->get_read_result();
        change_variable(msg);
        send_msg(std::move(msg), ci->id); //broadcast changes from one client to other clients.
        break;
    }
    case E_WRITE:
    {
        clienthandler *ci = get_client(get_id_from_encoded(encoded_callback));
        if(!ci) break;
        ci->finished_send_one();
        break;
    }
    case E_CONNECT:
        handle_new_connection();
        break;
    case E_DISCONNECT:
        finish_disconnect_client(get_id_from_encoded(encoded_callback));
        break;
    }
}

template<typename T, typename U>
int RpcServer<T, U>::pick_unused_id() // TODO get some uuid thing here.
{
    for(int id_try = 0; id_try < INT_MAX; id_try++)
    {
        bool hasid = false;
        for(auto &ci: clients)
            if(ci.id == id_try)
            {
                hasid = true; break;
            }
        if(!hasid) return id_try;
    }
    throw std::exception("grpc system: no client id could be generated.");
    return -1;
}

template<typename MSG_TYPE, typename U> inline
bool RpcServer<MSG_TYPE, U>::change_variable(MSG_TYPE &receivedval)
{
    int64 index = receivedval.key_case();
    if(index <= 0)
    {
        spdlog::get("global")->info() << "[Server] Received illegal message index (none was set)";
        return false;
    }

    auto ptr2variable_itr = cppvar_pointer_map.find(index);
    auto expected_type_itr = index_to_type_map.find(index);

    if(ptr2variable_itr == cppvar_pointer_map.end() || expected_type_itr == index_to_type_map.end())
    {
        spdlog::get("global")->info() << "network: received non-supported index: " << index; // -> to debug
        return false;
    }

    /*
    generated security layer network here
    */

    auto type = expected_type_itr->second;
    inexor::tree::TreeNodeChanged msg;
    msg.GetDescriptor();
    auto field = receivedval.GetDescriptor()->FindFieldByNumber(index);

    switch(type)
    { // TODO: renew this passage to generated shit for every variable to get rid of (runtime?) reflection (only in case its runtime reflection ofc)
        case cpp_type_t::t_cstring:
        {
            SharedVar<char *> *changed = static_cast<SharedVar<char *>*>(ptr2variable_itr->second);
            std::string newvalue(receivedval.GetReflection()->GetString(receivedval, field)); //TODO remove double type conversation..
            changed->setnosync(strdup(newvalue.c_str()));
            break;
        }
        case cpp_type_t::t_int:
        {
            SharedVar<int> *changed = static_cast<SharedVar<int>*>(ptr2variable_itr->second);
            int newvalue = (int64)receivedval.GetReflection()->GetInt64(receivedval, field);
            // TODO actually type is int32!
            changed->setnosync(newvalue);
            break;
        }
        case cpp_type_t::t_float:
        {
            SharedVar<float> *changed = static_cast<SharedVar<float>*>(ptr2variable_itr->second);
            float newvalue = receivedval.GetReflection()->GetFloat(receivedval, field);
            changed->setnosync(newvalue);
            break;
        }
    }
    return true;
}


} // namespace inexor
} // namespace rpc
