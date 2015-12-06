#ifndef INEXOR_NET_MULTI_CONNECT_HEADER
#define INEXOR_NET_MULTI_CONNECT_HEADER

#include <functional>
#include "inexor/net/MessageConnect.hpp"

namespace inexor {
namespace net {

/// Receive on any MessageConnect in a range of
/// MessageConnect pointers or pointer like objects (e.g.
/// unique_ptr)
///
/// @tparam Itr – Some kind of iterator; It should contain
///   a pointer to a MessageConnect or a pointer like object
///   that references a message connect.
/// @param start – The beginning of the sequence
/// @param end – The end of the sequence
/// @return bytes_on_channel; the data we received and
///   a plain pointer to the MessageConnect we where receiving
///   it on
template<typename Itr>
MC::bytes_on_channel receiveOnAny(Itr start, Itr end) {
    MC::bytes_on_channel r;

    for (; start != end && r.first.empty(); start++)
        r = (*start)->ReceiveChannel();

    return r;
}

/// Receive on any MessageConnect* in any container
///
/// This just calls .begin() and .end() on the container and
/// delegates to receiveOnAny(Itr, Itr).
///
/// @tparam Some container type. The container must support
///   the .begin() and .end() iterators;
template<typename Container>
MC::bytes_on_channel receiveOnAny(const Container &c) {
    return receiveOnAny(c.begin(), c.end());
}

/// Broadcast to all MessageConnects in a range.
///
/// @tparam Itr – Some kind of iterator. It must contain
///   a MessageConnect* or a pointer like object (something
///   that supports the * and -> operators) that references
///   a MessageConnect
/// @param data The message to broadcast
template<typename Itr>
void broadcast(Itr start, Itr end, const bytes &data) {
    for (; start != end; start++)
        (*start)->Send(data);
}

/// Broadcast to all MessageConnects in a container.
///
/// This basically just uses the .begin() and .end()
/// iterators and delegates to
/// broadcast(Itr, Itr, const bytes&)
template<typename Container>
void broadcast(const Container &c, const bytes &data) {
    broadcast(c.begin(), c.end(), data);
}


/// This is a Hub for multiple MessageConnects.
///
/// It stores a reference to a container and redirects all
/// Send calls to broadcast(...) and all Receive calls to
/// receiveOnAny
template<typename Container>
class MCHub : public MessageConnect {
public:
  const Container &hub_connections;

  explicit MCHub(const Container &cont) : hub_connections(cont) {}

  virtual bytes_on_channel ReceiveChannel() {
    return receiveOnAny(hub_connections);
  }

  virtual void Send(const bytes &dat) {
    broadcast(hub_connections, dat);
  }
};

}
}

#endif
