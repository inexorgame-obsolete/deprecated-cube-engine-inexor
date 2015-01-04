#include <list>

#include "net/MessageConnect.h"

#ifndef INEXOR_NET_MULTI_CONNECT_HEADER
#define INEXOR_NET_MULTI_CONNECT_HEADER

namespace inexor {
namespace net {

  /**
   * This is a Hub for multiple MessageConnect.
   *
   * Supports listening for Messages on the attached
   * connects and broadcasting messages to the attached
   * connects. 
   */
  class MCHub : public MessageConnect {
    /** All the connects that are attached to this */
    std::list<MessageConnect*> *cons;
  public:
    /**
     * Create a new MCHub with no attached connects.
     * connects() will return an empty list.
     */
    MCHub() {
      cons = new std::list<MessageConnect*>();
    }

    /**
     * Create a new MCHub and set the list of attached
     * connects.
     */
    MCHub(std::list<MessageConnect*> *cons_) : cons(cons_) {}

    virtual bytes_on_channel ReceiveChannel();
    virtual void Send(std::vector<char> &dat);

    /** The list of attached connects */
    std::list<MessageConnect*>* connects();
  };
}
}

#endif
