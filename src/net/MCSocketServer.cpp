#include "net/MCSocketServer.h"

asio::ip::tcp inexor::net::v4() {
  return asio::ip::tcp::v4();
}

asio::ip::tcp inexor::net::v6() {
  return asio::ip::tcp::v6();
}
