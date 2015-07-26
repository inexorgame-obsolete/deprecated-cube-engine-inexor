#ifndef INEXOR_UTIL_THREAD_LOCAL_HEADER
#define INEXOR_UTIL_THREAD_LOCAL_HEADER

#include <boost/thread/tss.hpp>

#include <functional>

namespace inexor {
namespace util {

/// Portable thread local storage with automatic
/// initialization.
///
/// There is this cool feature in C++11, called thread local
/// storage. This specifies that a different version of
/// a variable is used in every thread.
///
/// Unfortunately some compilers (I am looking at you intel
/// and visual studio) implement their own non-standard
/// versions for thread local storage; those often support
/// only POD types.
///
/// As a solution, boost::thread_specific_ptr can be used,
/// which makes thread local storage (it stores a pointer
/// thread local, which is a POD type).
/// That one supports no automatic initialization thou and
/// initially just sets the pointer to NULL.
///
/// As a solution this class can be used: It implements
/// a quasi-singleton pattern, where the pointer is
/// initialized when *(), ->() or get() is first used.
///
/// @tparam T What type this thread specific pointer is
/// holding
template<typename T>
class thread_local_ptr : public boost::thread_specific_ptr<T> {
    typedef boost::thread_specific_ptr<T> superc;

    superc *super = dynamic_cast<superc*>(this);
public:
    /// The type of function used to clean the pointer
    typedef std::function<void(T*)> cleanup_f;
    /// The type of function used to initialize the pointer
    typedef std::function<T*()> generate_f;

private:
    generate_f generator;

public:
    /// Initialize with the type's default constructor
    thread_local_ptr() {  
        generator = [](){ return new T; };
    }

    /// Initialize with a factory function.
    ///
    /// When *(), ->() or get() is first used, the generator
    /// is called to initialize the pointer.
    ///
    /// see the doc of boost::thread_specific_ptr on how the
    /// pointer is destructed.
    ///
    /// @param gen The function that generate the pointer
    thread_local_ptr(generate_f gen) : generator(gen) {}

    /// Initialize with a factory function and a special
    /// destructor.
    ///
    /// When *(), ->() or get() is first used, the generator
    /// is called to initialize the pointer.
    ///
    /// see the doc of boost::thread_specific_ptr on how the
    /// cleanup function is used
    ///
    /// @param gen The function that generate the pointer
    /// @param clean The function that is used to delete the pointer
    thread_local_ptr(generate_f gen, cleanup_f clean) :
      superc(clean), generator(gen) {}

    /// Initialize with the arguments for the types
    /// constructor.
    ///
    /// This just passes the given arguments to the
    /// constructor of the type for every thread.
    template<typename... Args>
    static thread_local_ptr<T> from_args(Args... args) {
        return new thread_local_ptr<T>([args...]() {
            return new T(args...);
        });
    }

    /// Get the plain value of the pointer.
    /// This returns null if the value has not been
    /// initialized.
    T* get_value() {
        return super->get();
    }

    /// Get the pointer. Automatically initializes the
    /// pointer, if this is the first access.
    T* get() {
        T *cur = get_value();
        if (cur == NULL) {
            cur = generator();
            super->reset(cur);
        }
        return cur;
    };

    /// Call a function in the pointer. Automatically
    /// initializes the pointer, if this is the first
    /// access.
    T* operator->() {
        return this->get();
    };

    /// Dereference the pointer. Automatically initializes
    /// the pointer, if this is the first access.
    typename boost::detail::sp_dereference<T>::type operator*() {
        return *(this->get());
    };

};

}
}

#endif
