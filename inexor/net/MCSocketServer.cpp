#include "inexor/net/MCSocketServer.h"

boost::asio::ip::tcp inexor::net::v4() {
  return boost::asio::ip::tcp::v4();
}

boost::asio::ip::tcp inexor::net::v6() {
  return boost::asio::ip::tcp::v6();
}
