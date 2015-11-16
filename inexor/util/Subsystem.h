#ifndef INEXOR_UTIL_SERVICE_HEADER
#define INEXOR_UTIL_SERVICE_HEADER

#include <string>
#include <unordered_map>

#include "inexor/util/util.h"
#include "inexor/util/InexorException.h"
#include "inexor/compat/make_unique.h"

namespace inexor {
namespace util {

IEXCEPTION(SubsystemException, "Some problem with the "
  "subsystems occurred.");
EXCEPTION(NoSuchSubsystem, SubsystemException,
  "The subsystem you're trying to start does not exist.");
EXCEPTION(SubsystemAlreadyRunning, SubsystemException,
  "The subsystem you're trying to start is already running.");
EXCEPTION(SubsystemNotRunning, SubsystemException,
  "The subsystem you're trying to stop is not running.");

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
    typedef std::function<std::unique_ptr<Subsystem>()> Starter;

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

        /// Check if the given subsystem exists
        static bool Exist(std::string k) {
            auto &m = GetInstance();
            return m.find(k) != m.end();
        }


        /// Ensure that the given subsystem exists. If it does
        /// not, throws an exception.
        static void EnsureExist(std::string k) {
            if (!Exist(k)) {
                std::string s = inexor::util::fmt
                  << "The subsystem '" << k
                  << "' does not exist.";
                throw NoSuchSubsystem(s);
            }
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
    std::unordered_map<
        std::string, std::unique_ptr<Subsystem>> subsystems;

    /// Start this Metasystem with no subsystems
    Metasystem() {}


    /// Start a subsystem by name
    void start(std::string &sub) {
        Subsystem::Register::EnsureExist(sub);
        if (subsystems.find(sub) != subsystems.end()){
            std::string s = inexor::util::fmt
              << "Trying to start subsystem '" << sub
              << "', but it is already running.";
            throw SubsystemAlreadyRunning(s);
        }

        subsystems[sub] = Subsystem::Register::Get(sub)();
    }

    void start(const char *sub) {
        std::string s(sub);
        start(s);
    }

    /// Stop a subsystem by name
    void stop(std::string &sub) {
        Subsystem::Register::EnsureExist(sub);
        if (subsystems.find(sub) == subsystems.end()){
            std::string s = inexor::util::fmt << "Trying to "
              << "stop subsystem '" << sub << "', but it is "
              << "not running.";
            throw SubsystemNotRunning(s);
        }

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
        [](){ return ::inexor::util::dynamic_pointer_cast<Subsystem>( \
          ::inexor::compat::make_unique<clazz>()); });

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
