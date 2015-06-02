#include <array>
#include <limits>

#include <cstdint>
#include <cstdbool>

#include "gtest/gtest.h"

#include "inexor/util/Observe.h"
#include "inexor/test/helpers.h"

using namespace std;
using namespace inexor::util;

namespace {

template<typename T>
void test_primitive(T seed, T overw) {
    T m1 = seed, m2 = seed, m3 = seed, m4 = seed;

    expectNothrow( Observe<T> X(seed); ) << "Observe should"
        "be initializable via copy constructor";
    expectNothrow( Observe<T> Y; Y =seed; ) << "Observe should"
        "be initializable via copy assignment";
    expectNothrow( Observe<T> Z(std::move(m1)); ) <<
        "Observe should be initializable via move constructor";
    expectNothrow( Observe<T> A; A = std::move(m2); ) <<
        "Observe should be initializable via move assignment";

    // Redo, just so the variables are available
    Observe<T> X(seed);
    Observe<T> Y; Y = seed;
    Observe<T> Z(std::move(m3));
    Observe<T> A; A = std::move(m4);

    expectEq((T)X, seed) << "Assignment via copy "
        "constructor should set the right value";
    expectEq((T)Y, seed) << "Assignment via copy "
        "assignment should set the right value";
    expectEq((T)Z, seed) << "Assignment via move "
        "constructor should set the right value";
    expect(A == seed) << "Assignment via move "
        "assignment should set the right value";

    expectEq((T)X, (T)Y);
    expect(Z == A);

    expectEq(X + 2, seed + 2);
    expectEq(Y - 2, seed - 2);
    expectEq(Z << 2, seed << 2);
    expectEq(A * 2, seed * 2);

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
        Observe<T> X(seed);                                \
        X.onChange.listen(listener);                       \
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
    test(Observe, name ## 0) {                             \
      test_primitive<type>(0, 32); }                       \
    test(Observe, name ## 5) {                             \
      test_primitive<type>(5, 42); }                       \
    test(Observe, name ## Min) {                           \
      test_primitive<type>(                                \
          std::numeric_limits<type>::min(), 4); }          \
    test(Observe, name ## Max) {                           \
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

test(Observe, Boolean) {
    Observe<bool> a;
    Observe<bool> b(true);

    bool called = false;
    if (b) called = true;
    expect(called) << "if (Observe<bool>(true)) should be executed.";

    b = false;

    called = false;
    if (b) called = true;
    expectNot(called) << "if (Observe<bool>(false)) "
        "should not be executed.";

    Observe<int> ib(1);

    called = false;
    if (ib) called = true;
    expect(called) << "if (Observe<int>(1)) should be executed.";

    ib = 0;

    called = false;
    if (ib) called = true;
    expectNot(called) << "if (Observe<int>(0)) "
        "should not be executed.";
}

test(Observe, String) {
  Observe<string> s("Hello World");
  s = "foo";
  expectEq(s->size(), 3);
  expectEq(*s, string("foo"));
}

}
