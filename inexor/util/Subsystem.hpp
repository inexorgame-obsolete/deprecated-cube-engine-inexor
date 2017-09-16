#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <queue>

#include "inexor/util.hpp"
#include "inexor/util/InexorException.hpp"
#include "inexor/compat/make_unique.hpp"

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

    /// Called once
    virtual void initialize(int argc, char **argv) {};

    /// Called once per frame, or what ever our event loop
    /// is
    virtual void tick() {};

    bool is_initialized = false;

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
        static bool Exist(const std::string &k) {
            auto &m = GetInstance();
            return m.find(k) != m.end();
        }


        /// Ensure that the given subsystem exists. If it does
        /// not, throws an exception.
        static void EnsureExist(const std::string &k) {
            if (!Exist(k)) throw NoSuchSubsystem();
        }

        static Starter& Get(const std::string &k) {
            return GetInstance()[k];
        }

        /// Thats an alias for setting a k/v pair in the map
        ///
        /// @return Always 0. (In order so we can use that in
        ///     SUBSYSTEM_REGISTER with a dummy variable).
        static void Set(const std::string &k, Starter v) {
            GetInstance()[k] = v;
        }
    };
};

/// A metasystem is a collection of multiple subsystems
///
/// All the calls are simply distributed to all subsystems
/// this contains.
class Metasystem : public Subsystem  {
public:
    typedef std::function<void()> tick_cb;

private:
    /// The list of functions to be called on the next tick
    struct : std::queue<tick_cb> {
        /// Tick is executed with every frame
        void tick() {
            while (!empty()) {
                front()();
                pop();
            }
        }
    } next_tick_queue;


public:
    std::unordered_map<
        std::string, std::unique_ptr<Subsystem>> subsystems;

    /// Start this Metasystem with no subsystems
    Metasystem() {}

    ~Metasystem() {
        next_tick_queue.tick();
    }

    /// Check whether the given subsystem is running or not
    bool is_running(const std::string &sub) noexcept {
      return subsystems.count(sub) > 0;
    }

    /// Start a subsystem by name
    ///
    /// If the subsystem is already running, no change will
    /// be done.
    ///
    /// The subsystem will be started during the next tick.
    /// This means there might be some delay.
    ///
    /// @throws NoSuchSubsystem
    void start(const std::string &sub) {
        Subsystem::Register::EnsureExist(sub);
        if (!is_running(sub))
            subsystems[sub] = Subsystem::Register::Get(sub)();
    }

    /// Stop a subsystem by name
    ///
    /// If the subsystem is not running, no change will be
    /// applied.
    ///
    /// The subsystem will be started during the next tick.
    /// This means there might be some delay.
    ///
    /// @throws NoSuchSubsystem
    void stop(const std::string &sub) {
        Subsystem::Register::EnsureExist(sub);

        if (is_running(sub))
            subsystems.erase(sub);
    }

    /// Forwarded to all subsystems
    virtual void tick() {
        next_tick_queue.tick();
        for (auto &e : this->subsystems) e.second->tick();
    }

    /// Forwarded to all subsystems
    virtual void initialize(int argc, char **argv)
    {
        for (auto &e : this->subsystems) {
            if (!e.second->is_initialized) {
                e.second->initialize(argc, argv);
                e.second->is_initialized = true;
            }
        }
    }

    /// Initialize a specific subsystem
    void initialize(const std::string &sub, int argc, char **argv)
    {
        for (auto &e : this->subsystems) {
            if (e.first == sub && !e.second->is_initialized) {
                e.second->initialize(argc, argv);
                e.second->is_initialized = true;
            }
        }
    }

    /// Execute code on the next tick.
    ///
    /// This will take a function and execute once on the
    /// next tick. If you want to execute something multiple
    /// times, use a submodule.
    ///
    /// The function will definitely be called. Even if the
    /// Metasystem is destructed, the functions will be
    /// invoked in the destructor.
    void next_tick(tick_cb f) {
        next_tick_queue.push(f);
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
/// @param ... The class of the subsystem
///            (its an argument list because macros are dump and can't 
///            handle template lists otherwise, since they contain ",").
#define SUBSYSTEM_REGISTER(name, ...)                \
    int __SUBSYSTEM_DUMMY(name) INEXOR_ATTR_UNUSED = ( \
      ::inexor::util::Subsystem::Register::Set( #name, \
        [](){ return ::inexor::util::dynamic_pointer_cast<::inexor::util::Subsystem>( \
          ::inexor::compat::make_unique<__VA_ARGS__>()); })  \
      , 0);

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

