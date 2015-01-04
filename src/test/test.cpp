#include <cstdbool>
#include <cstdint>
#include <cstring>

#include <string>
#include <iostream>
#include <random>

#include "net/net.h"
#include "rpc/rpc.h"

using namespace std;
using namespace inexor::net;
using namespace inexor::rpc;
using namespace inexor::util;

int cnt = 0, fail = 0, success = 0;

string N = "";

void tst(bool pass, string msg="") {
  cnt++;
  if (pass)
    success++;
  else
    fail++;

  cout << "TEST " << cnt << " "
    << (pass ? "passed" : "FAILED") << " " << N
    << ": '" << msg << "'" << endl;
}

default_random_engine rng;

template <typename R=int>
R rand(R a=0, R z=numeric_limits<R>::max()) {
  uniform_int_distribution<R> d(a,z);
  return d(rng);
}

vector<char> mkpkg() {
  int len = rand(16, 1024);

  vector<char> r(len);
  generate(r.begin(), r.end(),
      [&]{ return rand<char>(); });

  return r;
}

bool cmppkg(vector<char> &x, vector<char> &y) {
  bool b = x.size() == y.size();
  if (b) b = memcmp(&x[0], &y[0], x.size()) == 0;
  return b;
}

// TESTS //////////////////////////////////////

namespace helpers {
  bool send_packet(MessageConnect &send, MessageConnect &recv) {
    vector<char> pkgout, pkgin;
    pkgout = mkpkg();

    send.Send(pkgout);
    pkgin = recv.Receive();

    return cmppkg(pkgout, pkgin);
  }

  bool duplex_send_packet(MessageConnect &a, MessageConnect &b) {
    return send_packet(a,b) && send_packet(b, a);
  }
}

namespace suites {

  void self() {
    N = "self";

    bool b;
    vector<char> p1=mkpkg(), p2=mkpkg(), p3=mkpkg();

    tst(true, "True is true");

    // It is reasonable to assume that they are different.
    // (they are 8Kbits long. UUIDs are 128bits long)
    b = !cmppkg(p1, p2) && !cmppkg(p1, p3) && !cmppkg(p2,p3);
    tst(b, "mkpkg packets should be random.");

    b = cmppkg(p1, p1) && cmppkg(p2, p2) && cmppkg(p3,p3);
    tst(b, "cmppkg really detects when packages are equal.");

  }

  void chopper() {
    N = "StreamChopper";
    bool b;

    stringstream rr(ios::in | ios::out | ios::binary);
    StreamChopper chop1(rr), chop2(rr);
    vector<char> pkgout, pkgin;

    string s1 = "Hello_World", s2;
    rr.clear();
    rr << s1;
    rr >> s2;
    tst(s1.compare(s2) == 0,
        "Can do basic I/O with stringstream.");

    char size1 = 101, size2 = 42;
    rr.clear();
    rr.write(&size1, 1);
    rr.read(&size2, 1);
    tst(size1 == size2,
        "Can do basic Binary IO with stringstream");

    b = helpers::send_packet(chop1, chop1);
    tst(b, "Can send/receive a packet on a stringstream "
        "with the same chopper.");

    b = helpers::duplex_send_packet(chop1, chop2);
    tst(b, "Can send/receive a packet on a stringstream "
        "on different choppers.");
  }

}

// MAIN //////////////////////////////////////

int main() {
  rpc_init();
  while (true) {
    rpc_tick();
    dsleep(1E-2);
  }
  suites::self();
  suites::chopper();

  cerr << cnt << " tests; "
    << success << " passed; "
    << fail << " failed." << endl;

  return 0;
}
