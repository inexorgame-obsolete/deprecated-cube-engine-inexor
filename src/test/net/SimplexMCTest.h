#ifndef INEXOR_TEST_NET_SIMPLEX_MC_TEST_HEADER
#define INEXOR_TEST_NET_SIMPLEX_MC_TEST_HEADER

#include "gtest/gtest.h"

#include "test/helpers.h"
#include "test/net/helpers.h"

#include "net/net.h"

#include <utility>
#include <list>
#include <algorithm>
#include <vector>
#include <cstddef>

class SimplexMCTest_Provider {
public:
  inexor::net::MCByteBuffer *from;
  inexor::net::MessageConnect *to;

  virtual inexor::net::MCByteBuffer* From() { return from; }
  virtual inexor::net::MessageConnect* To() { return to; }

  virtual ~SimplexMCTest_Provider() {}
};

template<typename ProviderImpl>
class SimplexMCTest : public testing::Test {
protected:
  inexor::net::MCByteBuffer *from;
  inexor::net::MessageConnect *to;
  SimplexMCTest_Provider *prov;

public:
  SimplexMCTest() {
    prov = new ProviderImpl;
    from = prov->From();
    to = prov->To();
  }

  ~SimplexMCTest() {
    delete prov;
  }

  // TODO: This is a nasty hack; rather use proper threading
  bytes force_receive(inexor::net::MessageConnect *r=NULL) {
    if (r==NULL) r = this->to;
    bytes b;
    for (size_t i=0; i<20 && b.empty(); i++)
      b = r->Receive();
    return b;
  }
};

TYPED_TEST_CASE_P(SimplexMCTest);

// Pseudo Initializer
#define newSimplexMCTest(prefix, provider) \
  INSTANTIATE_TYPED_TEST_CASE_P(prefix, SimplexMCTest, provider)

#define itest(name) TYPED_TEST_P( SimplexMCTest , name)

itest(SenderSupportsSending) {
  expect( this->from->supportSend() ) << "Sender should "
    << "indicate it supports sending but it does not!";
}

itest(RecipientSupportsReceiving) {
  expect( this->to->supportReceive() ) << "Receiver should"
    << "indicate it supports receiving but it does not!";
}

itest(CanTransmitAMessage) {
  bytes p = mkpkg();
  this->from->Send(p);
  bytes r = this->force_receive();

  expectEq(r, p) << "Message received "
      << (r.empty() ? "is empty"
                    : "does not match the message sent")
      << "! sizes: (sent) " << p.size() << "; (receivced) "
      << r.size();
}

itest(CanTransmitManyMessages) {
  auto from = this->from;

  std::list<bytes> pl(16);
  std::generate(pl.begin(), pl.end(), [](){ return mkpkg(); });

  expect(this->force_receive().empty()) << "Expected to receive "
    << "nothing before sending anything, but we did "
    << "receive a message";

  for(bytes &p : pl) from->Send(p);

  for (size_t x=pl.size(); x > 0; x--) {
    bytes r = this->force_receive();

    expect(!r.empty()) << "Sent many packages but "
      << "received nothing!";
    if (r.empty()) continue;

    pl.remove(r);
    expectEq(pl.size(), x-1) << "Received a package we did"
      << "not send!";
  }

  expect(pl.empty()) << "We did not receive all packages we sent!";

  expect(this->force_receive().empty()) << "Should have received all"
    << "messages, but received one more when we were "
    << "expecting no messages!";
}

itest(ReciveIsNonblocking) {
  auto from = this->from;

  for (int i=0; i<6; i++) { // We do that entire test 6 times
    bytes pkg=mkpkg(),
          wire = mcbytebuffer_encode(pkg);

    expect(this->force_receive().empty()) << "Expected to receive "
      << "nothing before sending anything, but we did "
      << "receive a message";

    // Tiers is the number of bytes at which we check if the
    // output stream is actually non blocking.
    // The first few tiers reflect the size of the message
    // (uint64_t) being sent.
    std::vector<size_t> tiers = {1,3,5,7};
    // The next couple of tiers are
    // randomly set to steps between 5% and 20% of the package
    // to send.
    size_t min_step = pkg.size() / 20,
           max_step = pkg.size() / 5;
    while (tiers.back() < wire.size())
      tiers.push_back(
          tiers.back() + rand(min_step, max_step) );
    // Finally we might need to ignore the last tier as,
    // because of the algorithm above, it may be bigger than
    // the actual buffer.
    if (tiers.back() >= wire.size()) tiers.pop_back();

    // Have the size but not enough data -> nothing
    size_t sent = 0;
    for (size_t tier : tiers) {
      // +8 bc. that's the size of the data prefix
      from->write(&wire[sent], tier - sent);
      expect(this->force_receive().empty()) << "Expected "
        << "to receive after having sent only " << tier
        << '/' << wire.size() << "bites, but we did "
        << "receive a message";
      sent = tier;
    }

    // Complete package -> the package
    from->write(&wire[sent], wire.size() - sent);
    bytes r = this->force_receive();
    expectEq(r, pkg) << "Expected to receive our package "
      << "after having transmitted all the data, but we "
      << "received "
      << (r.empty() ? "nothing" : "some other message")
      << "! sizes: (sent) " << pkg.size() << "; (received) "
      << r.size();

    // Package popped; again the pipeline should be clear -> nothing
    expect(this->force_receive().empty()) << "Expected to "
      << "receive nothing after we sent our one message, "
      << "but we did!";
  }
}

REGISTER_TYPED_TEST_CASE_P(SimplexMCTest,
    SenderSupportsSending,
    RecipientSupportsReceiving,
    CanTransmitAMessage,
    CanTransmitManyMessages,
    ReciveIsNonblocking);

#undef SimplexMCTest
#undef itest

#endif
