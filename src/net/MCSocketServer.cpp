#include "net/MCSocketServer.h"

namespace inexor {
namespace net {

  boost::asio::ip::tcp v4() {
    return boost::asio::ip::tcp::v4();
  }
  boost::asio::ip::tcp v6() {
    return boost::asio::ip::tcp::v6();
  }

}
}
