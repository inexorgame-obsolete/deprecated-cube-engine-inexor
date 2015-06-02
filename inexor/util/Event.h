#ifndef INEXOR_UTIL_EVENT_HEADER
#define INEXOR_UTIL_EVENT_HEADER

#include <unordered_map>
#include <functional>
#include <algorithm>
#include <typeinfo>

#include <boost/variant.hpp>

#include "inexor/util/InexorException.h"

namespace inexor {
namespace util {

IEXCEPTION(EventException, "Some problem with the "
    "event code happened!");
EXCEPTION(NoSuchListener, EventException, "Tried to "
    "remove a non existent listener.");


namespace _event_ {
#include "inexor/util/Event_internal.h"
}

/// An instance of the event class represents a single event
/// that can be fired with it's own set of listeners
///
/// Listeners can be registered with `listen(...)` and removed
/// with `rm(...)`.
///
/// The event can be fired with `fire(...)` or with the call
/// operator `event_instance(...)`
///
/// Events can have arguments, these can be specified as
/// template parameters; listeners must either take all
/// of the arguments or none of them.
///
/// # Example:
///
/// ```
/// Event<int, int, int> onSex;
///
/// void l1() {
///     cout << "l1 was called" << endl;
/// }
///
/// void l2(int a, int b, int c) {
///     cout << "l2(" << a << ", " << b << ", " << c
///          << ") was called" << endl;
/// }
///
/// int main() {
///   Event<int, int, int>::iteartor l1_ = onSex.listen(l1);
///   Event<int, int, int>::iterator l2_ = onSex.listen(l2);
///
///   onSex(2, 3, 4);
///
///   onSex.rm(l1_);
///   onSex.fire(5,6,7)
/// }
///
/// ```
///
/// ## Output:
///
/// ```
/// l1 was called
/// l2(2,3,4) was called
/// l2(5,6,7) was called
/// ```
///
/// @tparam Args The arguments for the listeners
template<typename... Args>
    using Event = inexor::util::_event_::Event<Args...>;

}
}

#endif
