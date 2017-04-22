#include <array>
#include <limits>

#include <cstdint>
#include <cstdbool>

#include "gtest/gtest.h"

#include "inexor/network/SharedVar.hpp"
#include "inexor/test/helpers.hpp"

using namespace std;
using namespace inexor::rpc;

namespace {

template<typename T>
void test_primitive(T seed, T overw) {
    T m1 = seed, m2 = seed;

    expectNothrow( SharedVar<T> X(seed); ) << "SharedVar should be initializable via copy constructor";
    expectNothrow( SharedVar<T> Z(std::move(m1)); ) << "SharedVar should be initializable via move constructor";

    // Redo, just so the variables are available
    SharedVar<T> X(seed);
    SharedVar<T> Z(std::move(m2));

    expectEq((T)X, seed) << "Assignment via copy constructor should set the right value";
    expectEq((T)Z, seed) << "Assignment via move constructor should set the right value";

    expect(Z == X);

    expectEq(X + 2, seed + 2);
    expectEq(X - 2, seed - 2);
    expectEq(Z << 2, seed << 2);
    expectEq(Z * 2, seed * 2);

    T exold, exnew, exret;
    bool called;
    string desc = "INITIAL VALUE; SHOULD NEVER BE SEEN";

    auto listener =
      [&called, &desc, &exold, &exnew](const T &old, const T &rnew) {
        called = true;
        expectEq(exold, old) << "Expected a different `old` "
            "value (" << exold << "), but got (" << old <<
            ") after "  << desc;
        expectEq(exnew, rnew) << "Expected a different `new` "
            "value (" << exnew << "), but got (" << rnew <<
            ") after "  << desc;
    };

#define act(action, _new, _ret, description)               \
    {                                                      \
        called = false;                                    \
        SharedVar<T> X(seed);                                \
        X.onChange.connect(listener);                      \
        desc = description;                                \
        exold = seed;                                      \
        exnew = (_new);                                    \
        exret = (_ret);                                    \
        auto ret = (action);                               \
        expectEq(exret, ret) << "Expected `" #action "`"   \
          " to result in " << (_ret) << ", but it "        \
          "returned " << ret << "with seed=" << seed;      \
        expect(called) << "Expected the callback to be "   \
            "called when " << desc << "(`" #action "`)";   \
    }

    act((X=overw), overw, overw, "assigning another value");

    act(X++, seed+1, seed,   "doing a right side increment");
    act(X--, seed-1, seed,   "doing a right side decrement");
    act(++X, seed+1, seed+1, "doing a left side increment");
    act(--X, seed-1,  seed-1, "doing a left side decrement");

#define asop_n(op, n)        \
    {                        \
      T nu = seed;           \
      T re = (nu op ## = n); \
      act((X op ## = n), nu, re, "using the `" #op "` operator"); \
    }

// This is designed to overflow
#define asop(op)               \
    {                          \
        asop_n(op, 2);         \
        asop_n(op, 4);         \
        asop_n(op, 6);         \
        asop_n(op, 7);         \
    }

    asop(+);
    asop(-);
    asop(*);
    asop(/);
    asop(%);
    asop(&);
    asop(|);
    asop(^);
    asop(<<);
    asop(>>);

#undef asop_n
#undef asop
#undef act
}

#define ptest(name, type)                                  \
    test(SharedVar, name ## 0) {                             \
      test_primitive<type>(0, 32); }                       \
    test(SharedVar, name ## 5) {                             \
      test_primitive<type>(5, 42); }                       \
    test(SharedVar, name ## Min) {                           \
      test_primitive<type>(                                \
          std::numeric_limits<type>::min(), 4); }          \
    test(SharedVar, name ## Max) {                           \
      test_primitive<type>(                                \
          std::numeric_limits<type>::max(), 23); }

ptest(Char, char);
ptest(SignedChar, signed char);
ptest(UnsignedChar, unsigned char);
ptest(Short, short);
ptest(Int, int);
ptest(SignedInt, signed int);
ptest(UnsignedInt, unsigned int);
ptest(SizeT, size_t);

#undef ptest

test(SharedVar, Boolean) {
    SharedVar<bool> b(true);

    bool called = false;
    if (b) called = true;
    expect(called) << "if (SharedVar<bool>(true)) should be executed.";

    b = false;

    called = false;
    if (b) called = true;
    expectNot(called) << "if (SharedVar<bool>(false)) should not be executed.";

    SharedVar<int> ib(1);

    called = false;
    if (ib) called = true;
    expect(called) << "if (SharedVar<int>(1)) should be executed.";

    ib = 0;

    called = false;
    if (ib) called = true;
    expectNot(called) << "if (SharedVar<int>(0)) should not be executed.";
}

test(SharedVar, String) {
  SharedVar<string> s("Hello World");
  s = "foo";
  expectEq(s->size(), (size_t)3);
  expectEq(*s, string("foo"));
}

}
