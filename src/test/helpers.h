#include "gtest/gtest.h"

#include <random>

#ifndef INEXOR_TEST_HELPERS_HEADER
#define INEXOR_TEST_HELPERS_HEADER

#undef assert // Ignore assert.h asserts
#define assert ASSERT_TRUE
#define assertThrow ASSERT_THROW
#define assertEq ASSERT_EQ
#define assertNeq ASSERT_NE

#define expect EXPECT_TRUE
#define expectThrow EXPECT_THROW
#define expectEq EXPECT_EQ
#define expectNeq EXPECT_NE

extern std::default_random_engine default_rng;

/// Create a random number
///
/// @tparam R The type of the random number
/// @param a The minimum value of the number, by default the
///          minimum number the type supports
/// @param z The maximum value of the number, by default the
///          maximum value the type supports
/// @return A random number of type R between [a; z]
template <typename R=int>
R rand(R a=std::numeric_limits<R>::min(),
       R z=std::numeric_limits<R>::max()) {
  std::uniform_int_distribution<R> d(a,z);
  return d(default_rng);
}

#endif
