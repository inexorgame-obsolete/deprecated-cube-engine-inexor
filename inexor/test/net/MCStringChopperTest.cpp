#include "gtest/gtest.h"

#include "inexor/test/helpers.h"
#include "inexor/test/net/helpers.h"

#include "inexor/test/net/SimplexMCTest.h"
#include "inexor/test/net/DuplexMCTest.h"

#include "inexor/net.h"

#include <utility>
#include <sstream>

using namespace std;
using namespace testing;
using namespace inexor::net;

class DuplexTestProvider : public SimplexMCTest_Provider {
public:
  stringstream a,b;
  MCStreamChopper chopa, chopb;

  DuplexTestProvider() : chopa(&a, &b), chopb(&b, &a) {}

  virtual MCStreamChopper* From() { return &chopa; }
  virtual MCStreamChopper* To() { return &chopb; }
};

// Tests whether a stringstream backed MCStreamChopper fully
// works as a duplex connection
// TODO: Maybe do simplex testing too?
// TODO: Maybe do simplex negative (not working the other
// way) too.
newDuplexMCTest(MCStreamChopper_Stringstream,
    DuplexTestProvider);

// TODO: Write a generic MessageConnect test:
// * Implements enough methods
// * Throw error when doing something unsupported
// * Iterates over multiple instances.
// TODO: Write generic MCByteBuffer test for the same thing?
class MCStreamChoppertest : public Test {
public:

  stringstream a,b,c;
  MCStreamChopper peera, peerb, from, to;

  MCStreamChoppertest() : peera(&a,&b), peerb(&b,&a),
      from(&c, NULL), to(NULL, &c) {}
};

#define itest(name) TEST_F(MCStreamChoppertest, name)

itest(SimplexStreamsSupportOneway) {
  expect( !from.supportReceive() ) << "Expected simplex "
    << "sender message connect not to support receiving, "
    << "but it does!";
  expect( !to.supportSend() ) << "Expected simplex "
    << "receiver not to support sending, but it does.";
}

#undef itest

