#include <list>

#include <cstddef>

#include "inexor/net/MessageConnect.h"
#include "inexor/net/MCHub.h"

using namespace std;

namespace inexor {
namespace net {

  list<MessageConnect*>* MCHub::connects() {
    return cons;
  }

  void MCHub::Send(bytes &dat) {
    list<MessageConnect*>::iterator itr;
    for (itr = cons->begin(); itr != cons->end(); itr++)
      (*itr)->Send(dat);
  }

  // TODO: Is there a better way to solve this
  MCHub::bytes_on_channel MCHub::ReceiveChannel() {
    bytes r;
    MessageConnect *con;

    list<MessageConnect*>::iterator itr = cons->begin();
    for (; r.empty() && itr != cons->end(); itr++) {
      con = *itr;
      r = con->Receive();
    }

    return make_pair(r, con);
  }

}
}
