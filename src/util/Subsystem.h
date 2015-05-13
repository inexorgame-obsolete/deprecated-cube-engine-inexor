#ifndef INEXOR_UTIL_SERVICE_HEADER
#define INEXOR_UTIL_SERVICE_HEADER

#include <string>
#include <unordered_map>
#include <utility>
#include <functional>
#include <map>
#include <initializer_list>

#include "util/util.h"
#include "util/InexorException.h"

namespace inexor {
namespace util {

/// Subsystems are loosely coupled parts of inexor.
///
/// Instead of using subsystems, one could just call one
/// function on program start, program end and once per
/// frame in main(), but Subsystems are more flexible.
///
/// A Metasystem is used to manage a set of subsystems;
/// Subsystems can be registered with the macro
/// SUBSYSTEM_REGISTERto enable starting it by name (as
/// a string, during runtime).
class Subsystem {
public:

    /// Called to startup of the subsystem; usually when
    /// inexor is started
    Subsystem() {};

    /// Called to stop the subsystem; usually called when
    /// inexor is quit
    virtual ~Subsystem() {};

    /// Called once per frame, or what ever our event loop
    /// is
    virtual void tick() {};

    /// Called to paint stuff; after everything inexor and
    /// possibly other modules have been called.
    virtual void paint() {};

    /// A function that starts a subsystem and returns
    /// a pointer to the instance
    /// this exists for the register: we can not store classes
    /// at run time, so we instead store these functions as
    /// proxies to the Constructors.
    /// We create these as lambdas in the SUBSYSTEM_REGISTER macro;
    typedef Subsystem*(*Starter)();

    // A map of all registered Starters and their names.
    //
    // This is a singleton hash map, with static aliases Get
    // and Set for convenience.
    //
    // Since we register Subsystems during global variable
    // initialization, we need to make sure, that the hash map
    // is always available at that point.
    // Just using another global variable would not guarantee
    // that.
    // Hence we use the singleton pattern, which initializes
    // the unordered map as soon as the first subsystem is
    // registered.
    class Register :
        public std::unordered_map<std::string, Starter> {
    private:
        Register() {};
        Register(Register const&) = delete;
        void operator=(Register const&) = delete;
    public:
        static Register& GetInstance() {
            static Register instance;
            return instance;
        }

        static Starter& Get(std::string k) {
            return GetInstance()[k];
        }
        static Starter& Get(const char *k) {
            std::string s(k);
            return Get(s);
        }

        /// Thats an alias for setting a k/v pair in the map
        ///
        /// @return Always 0. (In order so we can use that in
        ///     SUBSYSTEM_REGISTER with a dummy variable).
        static int Set(std::string &k, Starter v) {
            GetInstance()[k] = v;
            return 0;
        }
        static int Set(const char *k, Starter v) {
            std::string s(k);
            return Set(s,v);
        }
    };
};

/// A metasystem is a collection of multiple subsystems
///
/// All the calls are simply distributed to all subsystems
/// this contains.
class Metasystem : public Subsystem  {
public:
    std::map<std::string, Subsystem*> subsystems;

    /// Start this Metasystem with no subsystems
    Metasystem() {}

    /// Shutdown/Destroy all subsystems
    virtual ~Metasystem() {
        for (auto &e : this->subsystems) delete e.second;
    }

    /// Start a subsystem by name
    void start(std::string &sub) {
        auto &starter = Subsystem::Register::Get(sub);
        subsystems[sub] = starter();
    }
    void start(const char *sub) {
        std::string s(sub);
        start(s);
    }

    /// Stop a subsystem by name
    void stop(std::string &sub) {
        delete subsystems[sub];
        subsystems.erase(sub);
    }
    void stop(const char *sub) {
        std::string s(sub);
        stop(s);
    }

    /// Forwarded to all subsystems
    virtual void tick() {
        for (auto &e : this->subsystems) e.second->tick();
    }

    /// Forwarded to all subsystems
    virtual void paint() {
        for (auto &e : this->subsystems) e.second->paint();
    }
};

#define __SUBSYSTEM_DUMMY(name) \
  subsystem_register_stub_for_ ## name

/// Register a subsystem so it can later be started by name
/// in a Metasystem
///
/// NOTE: DO NOT call SUBSYSTEM_REGISTER in headers. This is
///       because in order to register a subsystem we need
///       to execute some code. And since we usually can not
///       execute code outside main() we need to use
///       a trick: We create a dummy variable and use the
///       assignments right side to execute code.
///       If you were to call this in a header, a subsystem
///       would be registered for every include (or never
///       if not included) and we would create that variable
///       in multiple files.
///
/// NOTE: This must be called in the GLOBAL namespace!
/// TODO: Can we get rid of that restriction?
///
/// @param name The name to register the subsystem as
/// @param clazz The class of the subsystem
#define SUBSYSTEM_REGISTER(name, clazz)               \
    int __SUBSYSTEM_DUMMY(name) INEXOR_ATTR_UNUSED = \
      ::inexor::util::Subsystem::Register::Set( #name, \
          []() -> ::inexor::util::Subsystem* {        \
              return new clazz ; });

/// Make sure that a specific subsystem is included
///
/// NOTE: This must be called in a function in the global
///       namespace!
/// @param name The name of the subsystem to require
#define SUBSYSTEM_REQUIRE(name)                 \
    {                                                \
        extern int __SUBSYSTEM_DUMMY(name); \
        __SUBSYSTEM_DUMMY(name) = 0;        \
    }

}
}

#endif
