#include "inexor/test/helpers.h"
#include "inexor/test/net/helpers.h"

#include <sstream>
#include <algorithm>

using namespace std;
using namespace inexor::net;

bytes mkpkg(size_t size) {
  bytes r(size);
  rndcopy(&r[0], size);
  return r;
}

bytes mcbytebuffer_encode(bytes &msg) {
  stringstream ss; // TODO: Could do this quicker with custom subclass!

  MCStreamChopper chop(&ss, NULL);
  chop.Send(msg);

  string rs = ss.str();
  return bytes(rs.begin(), rs.end());
}

