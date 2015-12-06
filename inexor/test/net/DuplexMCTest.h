#ifndef INEXOR_TEST_NET_DUPLEX_MC_TEST_HEADER
#define INEXOR_TEST_NET_DUPLEX_MC_TEST_HEADER

#include "gtest/gtest.h"
#include "inexor/test/net/SimplexMCTest.h"
#include "inexor/net.h"

template<typename T_other>
class DuplexMCTest_SwapProvider : public SimplexMCTest_Provider {
public:
  T_other *other;

  DuplexMCTest_SwapProvider() : other(new T_other) {}

  inexor::net::MCByteBuffer* From() { return other->To(); }
  inexor::net::MCByteBuffer* To()   { return other->From(); }
};

#define newDuplexMCTest(prefix, provider)                    \
  newSimplexMCTest(prefix ## _DuplexMCTest_There, provider); \
  newSimplexMCTest(prefix ## _DuplexMCTest_Back,             \
      DuplexMCTest_SwapProvider< provider > )

#endif
