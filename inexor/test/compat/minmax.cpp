#include "gtest/gtest.h"
#include <functional>

#include "inexor/test/helpers.hpp"
#include "inexor/compat/minmax.hpp"

using namespace inexor;

// Tests for the 4 different overloads of min and max.

// We need to relax the tests to at least support clang 3.5 and gcc4.9
// as soon as we updated our travis infrastructure this codesnippet can be entirely removed
#if defined (__cpp_constexpr) && (__cpp_constexpr > 201304L)
#define HAS_C14_CONSTEXPR
#endif

template <class T>
void PassTestMin(const T& a, const T& b, const T& x)
{
    EXPECT_EQ(&compat::min(a, b), &x);
}

/// Test whether we are able to use min for passed by ref data.
TEST(InexorCompatMin, Pass)
{
    {
        int x = 0;
        int y = 0;
        PassTestMin(x, y, x);
        PassTestMin(y, x, y);
    }
    {
        int x = 0;
        int y = 1;
        PassTestMin(x, y, x);
        PassTestMin(y, x, x);
    }
    {
        int x = 1;
        int y = 0;
        PassTestMin(x, y, y);
        PassTestMin(y, x, y);
    }

#ifdef HAS_C14_CONSTEXPR
    {
        constexpr int x = 1;
        constexpr int y = 0;
        static_assert(compat::min(x, y) == y, "");
        static_assert(compat::min(y, x) == y, "");
    }
#endif
}

template <class T, class C>
void CompareTestMin(const T& a, const T& b, C c, const T& x)
{
    EXPECT_EQ(&compat::min(a, b, c), &x);
}

/// We are doing the same as for the Pass-test, but with a compare function.
TEST(InexorCompatMin, PassCompare)
{
    {
        int x = 0;
        int y = 0;
        CompareTestMin(x, y, std::greater<int>(), x);
        CompareTestMin(y, x, std::greater<int>(), y);
    }
    {
        int x = 0;
        int y = 1;
        CompareTestMin(x, y, std::greater<int>(), y);
        CompareTestMin(y, x, std::greater<int>(), y);
    }
    {
        int x = 1;
        int y = 0;
        CompareTestMin(x, y, std::greater<int>(), x);
        CompareTestMin(y, x, std::greater<int>(), x);
    }

#ifdef HAS_C14_CONSTEXPR
    {
        constexpr int x = 1;
        constexpr int y = 0;
        static_assert(compat::min(x, y, std::greater<int>()) == x, "");
        static_assert(compat::min(y, x, std::greater<int>()) == x, "");
    }
#endif
}

TEST(InexorCompatMin, InitList)
{
    EXPECT_EQ(compat::min({ 2, 3, 1 }), 1);
    EXPECT_EQ(compat::min({ 2, 1, 3 }), 1);
    EXPECT_EQ(compat::min({ 3, 1, 2 }), 1);
    EXPECT_EQ(compat::min({ 3, 2, 1 }), 1);
    EXPECT_EQ(compat::min({ 1, 2, 3 }), 1);
    EXPECT_EQ(compat::min({ 1, 3, 2 }), 1);
}

TEST(InexorCompatMin, InitListCompare)
{
    EXPECT_EQ(compat::min({ 2, 3, 1 }, std::greater<int>()), 3);
    EXPECT_EQ(compat::min({ 2, 1, 3 }, std::greater<int>()), 3);
    EXPECT_EQ(compat::min({ 3, 1, 2 }, std::greater<int>()), 3);
    EXPECT_EQ(compat::min({ 3, 2, 1 }, std::greater<int>()), 3);
    EXPECT_EQ(compat::min({ 1, 2, 3 }, std::greater<int>()), 3);
    EXPECT_EQ(compat::min({ 1, 3, 2 }, std::greater<int>()), 3);
}

template <class T>
void PassTestMax(const T& a, const T& b, const T& x)
{
    EXPECT_EQ(&compat::max(a, b), &x);
}

TEST(InexorCompatMax, Pass)
{
    {
        int x = 0;
        int y = 0;
        PassTestMax(x, y, x);
        PassTestMax(y, x, y);
    }
    {
        int x = 0;
        int y = 1;
        PassTestMax(x, y, y);
        PassTestMax(y, x, y);
    }
    {
        int x = 1;
        int y = 0;
        PassTestMax(x, y, x);
        PassTestMax(y, x, x);
    }

#ifdef HAS_C14_CONSTEXPR
    {
        constexpr int x = 1;
        constexpr int y = 0;
        static_assert(compat::max(x, y) == x, "");
        static_assert(compat::max(y, x) == x, "");
    }
#endif
}

template <class T, class C>
void CompareTestMax(const T& a, const T& b, C c, const T& x)
{
    EXPECT_EQ(&compat::max(a, b, c), &x);
}

TEST(InexorCompatMax, PassCompare)
{
    {
        int x = 0;
        int y = 0;
        CompareTestMax(x, y, std::greater<int>(), x);
        CompareTestMax(y, x, std::greater<int>(), y);
    }
    {
        int x = 0;
        int y = 1;
        CompareTestMax(x, y, std::greater<int>(), x);
        CompareTestMax(y, x, std::greater<int>(), x);
    }
    {
        int x = 1;
        int y = 0;
        CompareTestMax(x, y, std::greater<int>(), y);
        CompareTestMax(y, x, std::greater<int>(), y);
    }

#ifdef HAS_C14_CONSTEXPR
    {
        constexpr int x = 1;
        constexpr int y = 0;
        static_assert(compat::max(x, y, std::greater<int>()) == y, "");
        static_assert(compat::max(y, x, std::greater<int>()) == y, "");
    }
#endif
}

TEST(InexorCompatMax, InitList)
{
    EXPECT_EQ(compat::max({ 2, 3, 1 }), 3);
    EXPECT_EQ(compat::max({ 2, 1, 3 }), 3);
    EXPECT_EQ(compat::max({ 3, 1, 2 }), 3);
    EXPECT_EQ(compat::max({ 3, 2, 1 }), 3);
    EXPECT_EQ(compat::max({ 1, 2, 3 }), 3);
    EXPECT_EQ(compat::max({ 1, 3, 2 }), 3);
}

TEST(InexorCompatMax, InitListCompare)
{
    EXPECT_EQ(compat::max({ 2, 3, 1 }, std::greater<int>()), 1);
    EXPECT_EQ(compat::max({ 2, 1, 3 }, std::greater<int>()), 1);
    EXPECT_EQ(compat::max({ 3, 1, 2 }, std::greater<int>()), 1);
    EXPECT_EQ(compat::max({ 3, 2, 1 }, std::greater<int>()), 1);
    EXPECT_EQ(compat::max({ 1, 2, 3 }, std::greater<int>()), 1);
    EXPECT_EQ(compat::max({ 1, 3, 2 }, std::greater<int>()), 1);
}
