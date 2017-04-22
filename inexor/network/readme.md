# inexor::rpc

The rpc module is supposed to implement a powerful RPC and
Remote Object interface, for external *trusted*
applications.  
Ultimately this may create a CRUD like interface and thus
allow us moving lots of the functions that are not critical
for performance to external applications.

At the moment this already allows us to connect with another
application and issue any Cubescript command.

For this purpose we open a MCSocketServer on a port or
a unix socket and, every frame, we accept more connections
poll for messages on the Server's broadcast _channel_.  We
parse this message with google protobuf (the type is called
ServiceCall) and extract the call arguments (as the
approptiate protobuf type) and the name of the function to
call.  
Then we use protobuf's RPC/Service facilities to call the
proper function, get the return value (also as a protobuf
type) and send a return message to the caller on the other
side.

## MCRpcServer.h
The server implementing the stuff described above.

## InexorServiceImpl.cpp
Actual implementation of the functions exposed to the clients.

## inexor_service.proto
Protobuf protocol file.
Contains a description of what services we expose, of the
abstract function call package and of all data types we
transmit.  
This file is used to automatically generate/metaprogram the
data types' classes and the sub for the service
implementation.

This file can be used in a lot of programming languages.

## rpc_sb_compat.h
Functions for starting, stopping the RPC module and for
polling messages.
These should be called by main.

# Requires

* C++11
* stdc++
* [inexor::net](../net/)
* Google protocol buffers

This module is tied with the rest of inexor, since the RPC
procedures call Cubescript code.
