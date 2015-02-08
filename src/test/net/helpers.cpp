#include "test/helpers.h"
#include "test/net/helpers.h"

#include <sstream>
#include <algorithm>

using namespace std;
using namespace inexor::net;

std::default_random_engine default_rng;

bytes mkpkg() {
  bytes r(1024);
  generate(r.begin(), r.end(),
      [&]{ return rand<char>(); });

  return r;
}

bytes mcbytebuffer_encode(bytes &msg) {
  stringstream ss; // TODO: Could do this quicker with custom subclass!

  MCStreamChopper chop(&ss, NULL);
  chop.Send(msg);

  string rs = ss.str();
  return bytes(rs.begin(), rs.end());
}

