/// This file contains the implementation of
/// inexor::util::Event it should be treated as a section of
/// Event.h and should be included nowhere else.
///
/// One requirement for Event is to be able to deal with
/// listeners that take arguments and those that take none.
/// No big deal, boost variant can be used to do that - it
/// holds either a function that takes args OR one that does
/// not.
///
/// Then however there are Events that do not provide
/// parameters in the first place; here we run into
/// a problem: boost::variant with two times the same type
/// gives us problems.
///
/// As a solution we use a bit of template logic: For Events
/// that provide parameters, we use the either listener, for
/// those that do not, we use a ZeroListener in the entire
/// event.
///
/// Since at this point the entire thing becomes a bit
/// complex, we put the implementation in it's own file and
/// in it's own namespace.
///
/// namespace inexor::util::_event_;

/// The listener type with no arguments
typedef std::function<void()> ZeroListener;
/// The listener type with arguments
template<typename... Args> using
    ArgsListener = std::function<void(Args...)>;

/// A composite listener type, that incorporates both
/// ZeroListener and ArgsListener
///
/// It is callable; if this contains a ZeroListener all
/// arguments are dropped, otherwise all the arguments are
/// passed to the real listener
template<typename... Args>
class EitherListener :
    public  boost::variant<ZeroListener, ArgsListener<Args...>> {

    typedef ZeroListener ZL;
    typedef ArgsListener<Args...> AL;
    typedef boost::variant<ZL, AL> TSuper;
public:
    EitherListener(ZL l) : TSuper(l) {}
    EitherListener(AL l) : TSuper(l) {}

    void operator ()(Args... args) {
        if (this->type() == typeid(ZL))
            boost::get<ZL>(*this)();
        else
            boost::get<AL>(*this)(args...);
    }
};


template<typename Listener, typename... Args>
class basic_event {
public:
    /// A reference that can be used to retrieve or delete
    /// listeners;
    typedef int lid;

    /// The listeners waiting to be called; they are in
    /// a hash table so we can delete them (comparing
    /// callables is pretty hard)
    std::unordered_map<lid, Listener> listeners;

    /// We just count up to generate uniq listener ids
    /// TODO: Consider initializing randomly, to mitigate
    /// using lids on the wrong container
    lid lid_counter = 0;

    /// Register a listener
    ///
    /// @param l The listener to register
    /// @return The listener stored in an EitherListener;
    ///   this is most useful to store the result and use it
    ///   as an id when deleting the listener again
    template<typename L> lid listen(L l_) {
        lid id = lid_counter++;
        Listener l(l_);
        listeners.emplace(id, l);
        return id;
    }

    /// Delete a listener
    void rm(lid &id) {
        auto it = listeners.find(id);
        if (it == listeners.end()) throw NoSuchListener();
        listeners.erase(it);
    }

    /// Fire the event
    ///
    /// @param args Any arguments to pass to the listeners;
    ///   listeners that do not take any arguments do not
    ///   receive these values
    void fire(Args... args) {
        for (auto &el : listeners) el.second(args...);
    }

    /// Fire the event
    ///
    /// Alias for `fire(...)`
    void operator ()(Args... args) { fire(args...); }
};

template<typename... Args>
struct Event : basic_event<EitherListener<Args...>, Args...> {};

template<> struct Event<> : basic_event<ZeroListener> {};
