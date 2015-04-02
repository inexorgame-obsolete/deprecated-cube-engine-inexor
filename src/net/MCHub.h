#ifndef INEXOR_NET_MULTI_CONNECT_HEADER
#define INEXOR_NET_MULTI_CONNECT_HEADER

#include <list>
#include "net/MessageConnect.h"

namespace inexor {
namespace net {

  /// This is a Hub for multiple MessageConnect.
  ///
  /// Supports listening for Messages on the attached
  /// connects and broadcasting messages to the attached
  /// connects.
  class MCHub : public MessageConnect {
    /// All the connects that are attached to this
    std::list<MessageConnect*> *cons;

    /// We want ownership over the list for the
    /// template/non-pointer constructor.
    std::list<MessageConnect*> mine_cons;
  public:
    /// Create a new MCHub and set the list of attached
    /// connects.
    MCHub(std::list<MessageConnect*> *cons_) : cons(cons_) {}

    /// Create a MCHub from any sequence type that
    /// contains any type of MessageConnects (not the pointers)
    /// In this case we will get all the pointers of the
    /// MessageConnects and copy them into a new list;
    ///
    /// Future changes to the list will be ignored.
    /// This class retains ownership over cons when using
    /// this constructor.
    ///
    /// @tparam Iterable The type of container the connects
    ///     are stored in; could be a list or a vector.
    /// @tparam Connect The type of MessageConnect we're
    ///     dealing with
    /// @param list The connects to import
    template<typename Iterable>
    MCHub(Iterable &list) : cons(&mine_cons) {
      for (auto &con : list) mine_cons.push_back(&con);
    }

    virtual bytes_on_channel ReceiveChannel();
    virtual void Send(bytes &dat);

    /// The list of attached connects
    std::list<MessageConnect*>* connects();
  };
}
}

#endif
