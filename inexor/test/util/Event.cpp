#include <array>
#include <tuple>
#include <functional>
#include <string>

#include <iostream>

#include "gtest/gtest.h"

#include "inexor/util/Event.h"
#include "inexor/test/helpers.h"

using namespace std;
using namespace inexor::util;

namespace {

test(Event, NoParamEvent) {
    Event<> ev;
    int c1=0, c2=0, c3=0;

    expectNothrow( ev() ) << "Firing the event without "
      "listeners should make no problem";

    expectNothrow(
        ev.listen( [&c1](){ c1++; } );
        ev.listen( [&c2](){ c2++; } );
        ev.listen( [&c3](){ c3++; } );
    ) << "Unable to register listener.";

    expectNothrow( ev(); ) << "Unable to fire event via () op.";
    expectEq(c1, 1) << "First listener was not called";
    expectEq(c2, 1) << "Second listener was not called";
    expectEq(c3, 1) << "Third listener was not called";

    expectNothrow( ev.fire(); ) << "Unable to fire event "
        "via fire method.";
    expectEq(c1, 2) << "First listener was not called";
    expectEq(c2, 2) << "Second listener was not called";
    expectEq(c3, 2) << "Third listener was not called";
}

test(Event, WithParams) {
    Event<int&, string&, const char*> ev;
    
    int    pi = 42,  ri;
    string ps = "Hello World",  rs;
    const char  *pc = "Don't panic!", *rc;

    int callc_zero = 0;
    int callc_args = 0;

    expectNothrow( ev(pi, ps, pc) ) << "Firing the event"
      "without listeners should make no problem";

    expectNothrow( ev.listen( [&callc_zero]{ callc_zero++; }); )
        << "Could not register a listener without params";

    expectNothrow(
        ev.listen(
          [&callc_args, &ri, &rs, &rc](int &i, string &s, const char *c){
            callc_args++;
            ri = i;
            rs = s;
            rc = c;
        });
    ) << "Could not register listener with params";

    expectNothrow( ev.listen( [&callc_zero]{ callc_zero++; }); )
        << "Could not register a listener without params";

    ev(pi, ps, pc);

    expectEq(callc_zero, 2) << "Expected two listeners "
        "without params to have been called";
    expectEq(callc_args, 1) << "Expected one listener "
        "with params to have been called";
    expectEq(pi, ri) << "Expect int param to have been "
        "passed as " << pi << "but it is " << ri;
    expectEq(ps, rs) << "Expect string param to have been "
        "passed as " << ps << "but it is " << rs;
    expectEq(pc, rc) << "Expect int param to have been "
        "passed as " << pc << "but it is " << rc;
}

test(Event, DeleteListener) {
    Event<> ev;

    array<int, 7> callv;
    array<int, 7> expv;
    array<Event<>::lid, 7> itv;


    for (int i = 0; i < 7; i++)
        itv[i] = ev.listen( [i, &callv]{
            callv[i]++; } );

    callv.fill(0);
    expv.fill(1);
    ev();
    expectEq(callv, expv) << "Expected"
      " all listeners to have been called: ";

    expectNothrow( ev.rm(itv[0]); ) << "Can not remove "
      "first listener";

    callv.fill(0);
    expv[0] = 0;
    ev();
    expectEq(callv, expv) << "Expected"
      " the first listener to not have been called: ";

    expectNothrow( ev.rm(itv[6]); ) << "Can not remove "
      "last listener";

    callv.fill(0);
    expv[6] = 0;
    ev();
    expectEq(callv, expv) << "Expected"
      " the first listener to not have been called: ";

    expectNothrow( ev.rm(itv[3]); ) << "Can not remove "
      "third listener";

    callv.fill(0);
    expv[3] = 0;
    ev();
    expectEq(callv, expv) << "Expected"
      " the first listener to not have been called: ";
}

test(Event, InvalidDelete) {
    Event<> ev;
    for (int i : {12172, 1, 42})
        expectThrow( ev.rm(i), NoSuchListener) << "Expected"
            "the event to throw NoSuchListener when an "
            "non-existent listener is deleted.";
}

}
