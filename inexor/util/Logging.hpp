/** @file Logging.hpp
  * stuff including the ingame console logging functionality.
  */
#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#undef LOG_INFO  //conflicting between spdlog and cef
#undef LOG_WARNING

#include <iomanip>
#include <map>
#include <array>
#include <string>

/// Function which displayes console text ingame.
extern void conline(int type, const char *sf);

namespace inexor {
namespace util {

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

    /// The default logger names which are used in inexor
    static const std::array<std::string, 8> default_logger_names = {
        "ui",
        "global",
        "chat",
        "gameplay",
        "edit",
        "server",
        "frag_involved",
        "frag_not_involved"
    };

    /// Map to lookup for log level names
    static const std::map<std::string, spdlog::level::level_enum> log_levels = {
        {"trace", spdlog::level::trace},
        {"debug", spdlog::level::debug},
        {"info", spdlog::level::info},
        {"warning", spdlog::level::warn},
        {"error", spdlog::level::err},
        {"critical", spdlog::level::critical},
        {"off", spdlog::level::off}
    };

    /// The global inexor logging API
    class Logging
    {
        std::vector<spdlog::sink_ptr> allsinks;
        public:
            Logging();
            ~Logging();
            void initDefaultLoggers();
            void createAndRegisterLogger(std::string logger_name);
            void createSinks();
            std::vector<spdlog::sink_ptr> &getSinksForLogger(std::string logger_name);
            void setLogLevel(std::string logger_name, std::string log_level);
            void setLogFormat(std::string logger_name, std::string pattern);
    };

    /// Ingame GUI console.
    class InexorConsoleSink : public spdlog::sinks::sink
    {
    public:
        void log(const spdlog::details::log_msg& msg) override;
        void flush() override {}
    };

    /// Sink wrapper for removing any color codes from the log.
    class InexorCutAnsiCodesSink : public spdlog::sinks::sink
    {
      public:
        InexorCutAnsiCodesSink(spdlog::sink_ptr wrapped_sink) : sink_(wrapped_sink) {}
        InexorCutAnsiCodesSink(const InexorCutAnsiCodesSink& other) = delete;
        InexorCutAnsiCodesSink& operator=(const InexorCutAnsiCodesSink& other) = delete;

        ~InexorCutAnsiCodesSink()
        {
            flush();
        }

        /// spdlog hook we override.
        virtual void log(const spdlog::details::log_msg& msg) override
        {
            spdlog::details::log_msg new_msg;
            new_msg.formatted << cutANSICodes(msg.formatted.str());
            sink_->log(new_msg);
        }

        virtual void flush() override
        {
            sink_->flush();
        }

    protected:

        /// @brief cut any valid ANSI Codes (used e.g. for colors in terminals) from a string.
        std::string cutANSICodes(std::string logline);

        spdlog::sink_ptr sink_;
    };
}
}
