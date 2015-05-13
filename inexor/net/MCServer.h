#ifndef INEXOR_NET_CONNECT_HEADER
#define INEXOR_NET_CONNECT_HEADER

#include <list>
#include <algorithm>
#include <iostream>

#include "inexor/net/MessageConnect.h"
#include "inexor/net/MCHub.h"
#include "inexor/util/util.h"

namespace inexor {
namespace net {
  
  /**
   * Abstract interface for a server that accepts
   * connections as MessageConnect.
   *
   * The connections will be closed and the MessageConnects
   * attached to this will be deleted, when the server is
   * deleted.
   */
  class MCServer {
  protected:
    /** List of all the connections */
    std::list<MessageConnect*> cons;

    /** What broadcast() returns */
    MCHub bcast;

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
    virtual MessageConnect* getNextStream() = 0;

  public:
    MCServer() : bcast(&cons) {}

    /**
     * The destructor deletes all the messages in
     * connects()
     */
    virtual ~MCServer() {
      std::for_each(cons.begin(), cons.end(),
          util::f_delete<MessageConnect>);
    }

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
      MessageConnect *c = getNextStream();
      if (c != NULL)
        cons.push_back(c);
      return c;
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

    /**
     * A message hub that has all the connections accepted
     * by this server attached.
     *
     * The boradcast() can be used to get messages from all
     * connections accepted and to send broadcasts.
     *
     * The broadcast exists as long as this server exists.
     *
     * @return A MessageHub for sending BROADCASTS
     */
    MCHub& broadcast() {
      return bcast;
    }

    /**
     * List all the connects attached
     *
     * TODO: Make read only!
     *
     * @return The lists of connections on this server
     */
    std::list<MessageConnect*>& connects() {
      return cons;
    }
  };

}
}

#endif
