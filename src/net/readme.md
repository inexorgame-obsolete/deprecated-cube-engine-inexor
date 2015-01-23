# inexor::net

NOTE: This is not related to ENET. See the bottom of this
page.

The net module is supposed to harbor low level
network/point-to-point protocols and wrappers for C++.

At the moment it contains an abstract, minimal client/server
interfaces via which messages may be sent and
implementations, that support TCP, Unix Sockets and an
IOstream as basis.

## MessageConnect.h
The abstract interface

## MCserver.h
Abstract interface for a server maintaining multiple
MessageConnects.

## MCHub.h
Managing multiple MessageConnects all at once; listening to
all; broadcasting.

## StreamChopper.h
MessageConnect implementation that uses an underlying iostream.

## MCSocket.h
TCP/Unix Socket client implementation.

## MCSocketServer.h
TCP/Unix Socket server implementation.


# Requires

* C++11
* stdc++
* [ASIO](http://think-async.com/)

This module does not require any other part of inexor.

# Usage

This module; more specifically the MessageConnect is
currently used as a _transport layer_ for
[inexor::rpc](../rpc/)

The Enet protocol and anything related to ingame the
client-server protocol is not using this module at the
moment.
Enet is it's own library; the instances where we use it and
the concrete ingame protocoll is scattered through engine/
and fpsgame/.
