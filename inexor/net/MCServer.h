#ifndef INEXOR_NET_CONNECT_HEADER
#define INEXOR_NET_CONNECT_HEADER

#include <list>
#include <algorithm>
#include <iostream>
#include <memory>

#include "inexor/net/MessageConnect.h"
#include "inexor/net/MCHub.h"
#include "inexor/util.h"

namespace inexor {
namespace net {
  
  /**
   * Abstract interface for a server that accepts
   * connections as MessageConnect.
   *
   * The connections will be closed and the MessageConnects
   * attached to this will be deleted, when the server is
   * deleted.
   *
   * This also acts as a MCHub, which in turn acts like
   * a MessageConnect: Calls to send are broadcast id to all
   * connections, calls to receive try receiving from any
   * message Connect
   *
   * @tparam SpecifcMC – The subclass of MessageConnect this
   *   MCServer holds for each connection
   *
   * TODO: Handle closing connections.
   */
  class MCServer :
      public MCHub<std::list<std::unique_ptr<MessageConnect>>> {
  public:

    /// The full container type used to store the message
    /// connects.
    typedef std::list<std::unique_ptr<MessageConnect>> Container;

    typedef MCHub<std::list<std::unique_ptr<MessageConnect>>> AsHub;

  protected:


    /** List of all the connections */
    Container cons;

    /**
     * Accept a new connection if one is available.
     *
     * This should be overwritten instead of overwriting
     * accept().
     * Accept will use this function and in addition to that
     * add the new connection to cons. This function does
     * not need to do this.
     *
     * @return A MessageConnect if a connection is
     *   available; otherwise NULL.
     */
    virtual std::unique_ptr<MessageConnect> getNextStream() = 0;

  public:
    MCServer() : AsHub(cons) {}

    /**
     * Accept a new connection if one is available.
     *
     * If a new connection can be established it is also
     * added to connects().
     *
     * @return A MessageConnect if a connection was
     *   accepted; otherwise NULL.
     */
    virtual MessageConnect* accept() {
      std::unique_ptr<MessageConnect> c = getNextStream();
      MessageConnect* ptr = c.get();
      if (ptr != NULL)
        cons.push_back(std::move(c));
      return ptr;
    }

    /**
     * Accept all connections available.
     *
     * Calls accept() until accept() fails.
     *
     * @return The number of messages accepted.
     */
    virtual int accept_all() {
      int r = 0;
      while (accept() != NULL) r++;
      return r;
    }

    /// List all the connects attached
    /// TODO: Make read only!
    /// @return The lists of connections on this server
    Container& connects() {
      return cons;
    }
  };

}
}

#endif
