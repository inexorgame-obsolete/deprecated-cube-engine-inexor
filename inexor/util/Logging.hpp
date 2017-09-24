/// @file Logging.hpp
/// Logging stuff including the ingame console logging functionality.

#pragma once

#include "inexor/network/SharedClass.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#undef LOG_INFO  //conflicting between spdlog and cef
#undef LOG_WARNING

#include <iomanip>
#include <map>
#include <array>
#include <string>
#include <vector>



namespace inexor {
namespace util {

#define DEFAULT_LOG_PATTERN "%H:%M:%S [%n] [%l] %v"

    /// Wrapper around spdlog::logger to put it into the InexorTree
    /// We want to set the pattern and the level on a per-logger-base and expose it.
    class Logger
    {
    public:
        std::shared_ptr<spdlog::logger> spdlog_logger;
        SharedVar<char *> pattern;
        SharedVar<int> level; // TODO: ranges min max value

        Logger() : pattern((char*)DEFAULT_LOG_PATTERN), level(2) // spdlog::level::info
        {
            /// Add the listeners for the pattern and the level variables.
            pattern.onChange.connect([this](char *const &old_pattern, char *const &new_pattern)
            {
                try
                {
                    spdlog_logger->set_pattern(new_pattern);
                }
                catch(const spdlog::spdlog_ex& ex) {}
            });
            level.onChange.connect([this](const int &old_level, const int &new_level)
            {
                try
                {
                    spdlog_logger->set_level(static_cast<spdlog::level::level_enum>(new_level));
                }
                catch(const spdlog::spdlog_ex& ex) {}
            });
        }
        Logger(const Logger &old) : spdlog_logger(old.spdlog_logger), pattern(old.pattern), level(old.level) {}

        const std::shared_ptr<spdlog::logger> &operator->() const
        {
            return spdlog_logger;
        };

        void create_spdlog_logger(const std::string logger_name);

        /// Wrapper for create_spdlog_logger, taking the current logger_name as argument.
        void recreate_spdlog_logger();
    };

    /// The global inexor logging API
    /// TODO: enable sharing.
    class log_manager
    {
    private:
        /// After adding a sink we need to recreate all loggers to make them use them.
        /// Since we can't modify the sinks of existing loggers.
        void all_loggers_apply_sinks_change();

    public:
        log_manager();

        /// The absolute path of the logfile which gets created as sink.
        SharedVar<char *> logfile;

        /// Logger for everything not fitting elsewhere.
        static Logger std;

        /// Logger for the startup and the shut down of the game.
        static Logger start_stop;

        /// Logger for synchronization messages.
        /// e.g. between the gameclient and its gameserver or between inexor-flex and inexor-core.
        static Logger sync;

        /// Logger for the filesystem messages and other input/output.
        /// E.g. "file not available" or "no keyboard available" or "model xy has a malformatted header".
        static Logger io;

        /// Logger for utility functions.
        /// e.g. you may want all string_copy-warnings to be on "error"-level in production.
        static Logger util;

        /// Logger for rendering messages.
        static Logger render;

        /// Logger for the user interface rendering (CEF bindings).
        static Logger ui;

        /// Logger for all general game messages.
        /// e.g. "evil captured base 2".
        static Logger game;

        /// Logger for "you got killed" or "you killed xy"
        static Logger frag_involved;

        /// Logger for "player1 killed playerC"
        static Logger frag_not_involved;

        /// Logger for chat messages.
        static Logger chat;

        /// Logger for team chat messages.
        static Logger team_chat;

        /// Logger for world related functions.
        /// e.g. verbose("octree-extension has been loaded to (0, 1024, 1024).");
        static Logger world;

        /// Logger for messages of the editing mode.
        /// e.g. "player1 has recalculated his lightmaps."
        /// may be conflicting with the "world"-logger sometimes: in that case prefer edit.
        static Logger edit;

        /// We allow the syntax Log.info("hallo") and forward it to the logger log_manager::default
        Logger &operator->() const
        {
            return std;
        };

        static Logger create_and_register_logger(std::string logger_name,
                                                 const std::string pattern = DEFAULT_LOG_PATTERN,
                                                 int level = spdlog::level::info);
    };


////// Logging helper utilities:


    // ANSI Console colors: everything behind it will be in that particular color.
    // \x1b[38;2; is the ANSI escape sequence for 24bit foreground color, then the RGB values follow (+ closing 'm').
    #define COL_GREEN   "\x1b[38;2;64;255;128m"     // == legacy \f0
    #define COL_BLUE    "\x1b[38;2;96;160;255m"     // == legacy \f1
    #define COL_YELLOW  "\x1b[38;2;255;192;64m"     // == legacy \f2
    #define COL_RED     "\x1b[38;2;255;64;64m"      // == legacy \f3
    #define COL_GREY    "\x1b[38;2;128;128;128m"    // == legacy \f4
    #define COL_MAGENTA "\x1b[38;2;192;64;192m"     // == legacy \f5
    #define COL_ORANGE  "\x1b[38;2;255;128;0m"      // == legacy \f6
    #define COL_WHITE   "\x1b[38;2;255;255;255m"    // == legacy \f7

    /// Helper class to allow the writing of std::cout << embraced("I should be inside curly brackets", "{", "}");
    /// Same works for numbers, but it may destroy std::setprecision.
    struct embraced
    {
        const std::string _text;
        const char *_leading,  // e.g. "{"
            *_trailing; // e.g. "}"

        embraced(const char *text, const char *leading, const char *trailing) : _text(text), _leading(leading), _trailing(trailing) {}

        /// Also allow all kind of number formats beeing embraced:
        template<typename T>
        embraced(T number, const char *leading, const char *trailing) : _text(std::to_string(number)), _leading(leading), _trailing(trailing) {}

        /// Construct a std::string from this class.
        operator std::string() const
        {
            std::string quotedStr = _leading;
            quotedStr += _text;
            quotedStr += _trailing;
            return quotedStr;
        }

        /// Pass this class directly into a stream.
        friend std::ostream &operator<< (std::ostream & ostr, const embraced & q)
        {
            ostr << q._leading << q._text << q._trailing;
            return ostr;
        }
    };

    /// A simple helper class to allow you writing inexor::util::quoted(string) which automatically adds quotation marks.
    /// When either constructing an std::string from it or << it into a stream (e.g. LOG()).
    struct quoted : embraced
    {
        quoted(const char *text) : embraced(text, "\"", "\"") {}
    };
} } // ns inexor::util

extern inexor::util::log_manager Log;

