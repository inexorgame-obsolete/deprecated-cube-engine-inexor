#include "inexor/util/Logging.hpp"
#include "inexor/network/SharedTree.hpp"
#include "inexor/network/SharedList.hpp"

#include <spdlog/sinks/msvc_sink.h>

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <exception>
#include <iostream>

/// Function which displayes console text ingame. (legacy UI)
extern void conline(int type, const char *sf);

namespace inexor {
namespace util {

////// Different sinks:

/// Ingame GUI console.
class InexorConsoleSink : public spdlog::sinks::sink
{
public:
    void log(const spdlog::details::log_msg& msg) override
    {
        int type = 0;
        // Convert loggers and levels to legacy conline types:
        switch(msg.level)
        {
            default:
            case spdlog::level::info:
                type = 1<<0;
                break;
            case spdlog::level::warn:
                type = 1<<1;
                break;
            case spdlog::level::err:
                type = 1<<2;
                break;
            case spdlog::level::debug:
                type = 1<<3;
                break;
        }
        std::string str = msg.formatted.str();
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        conline(type, str.c_str());
    }

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
    std::string cutANSICodes(std::string logline)
    {
        const char *escapesequence = "\x1b["; // CSI code: 'Escape' + '['
        std::string _logline = logline;
        for(std::string::size_type escpos = _logline.find(escapesequence); escpos != std::string::npos; escpos = _logline.find(escapesequence))
            for(std::string::size_type curletter = escpos + 2; curletter < _logline.length(); curletter++) // look for the final letter
                if(_logline[curletter] > '@' && _logline[curletter] < '~')
                {
                    _logline.erase(escpos, curletter - escpos + 1);
                    break;
                }
        return _logline;
    }

    spdlog::sink_ptr sink_;
};


bool is_file_writeable(const std::string &filename)
{
    std::ofstream outfile(filename.c_str());
    return outfile.good();
}

/// Modifies the given logname until its a writeable file.
/// Does so by simply appending a number to it.
/// @return false if it exceeded 100 rename tries and none worked.
bool find_logfile_name(std::string &logfile_without_extension)
{
    // logfile is writeable without modification
    if(is_file_writeable(logfile_without_extension + ".log")) return true;

    constexpr int max_log_renamed_versions = 100;
    for(int i = 2; i < max_log_renamed_versions; i++)
    {
        if(is_file_writeable(logfile_without_extension + std::to_string(i) + ".log"))
        {
            logfile_without_extension = logfile_without_extension + std::to_string(i);
            return true;
        }
    }
    return false;
}


/// Some sinks are not dependend on settings and hence they get used even before the Tree is initialized.
/// So these are the "not-logfile" sinks.
std::vector<spdlog::sink_ptr> create_startup_sinks()
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    sinks.push_back(std::make_shared<InexorConsoleSink>());

#if defined(_MSC_VER) && !defined(NDEBUG)
    sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
#endif
    return sinks;
}

std::vector<spdlog::sink_ptr> startup_sinks;
/// The logfile gets added thereafter.
spdlog::sink_ptr logfile_sink;

/// Returns a vector with startup_sinks + logfile_sink (if logfile_sink != nullptr).
std::vector<spdlog::sink_ptr> get_all_sinks()
{
    if(startup_sinks.empty()) startup_sinks = create_startup_sinks();
    auto new_sink_container = startup_sinks;

    if(logfile_sink) new_sink_container.push_back(logfile_sink);
    return new_sink_container;
}


void Logger::create_spdlog_logger(const std::string logger_name)
{
    std::vector<spdlog::sink_ptr> cur_sinks = get_all_sinks();
    auto new_spdlogger = std::make_shared<spdlog::logger>(logger_name, cur_sinks.begin(), cur_sinks.end());
    spdlog::drop(logger_name);
    spdlog::register_logger(new_spdlogger);
    spdlog_logger = new_spdlogger;
    spdlog_logger->set_pattern(*pattern);
    spdlog_logger->set_level(static_cast<spdlog::level::level_enum>(*level));
}

void Logger::recreate_spdlog_logger()
{
    spdlog_logger->flush();
    create_spdlog_logger(spdlog_logger->name());
}

log_manager::log_manager() : logfile((char*)"default_inexor_log.log")
{
    // Queue size for async mode must be power of 2
    size_t q_size = 4096;
    // Set async mode
    spdlog::set_async_mode(q_size);

    logfile.onChange.connect([&, this](char * const &old_logfile, char * const &new_logfile)
    {
        // if logfile changed: remove old logfile from sinks and add new logfile to sinks
        std::string logfile_name(new_logfile);
        std::string logfile_name_without_ext = logfile_name.substr(0, logfile_name.find_last_of("."));

        if(!find_logfile_name(logfile_name_without_ext)) throw std::runtime_error("There was no way to create a logfile.");
        logfile_name = logfile_name_without_ext + ".log";
        logfile_sink = std::make_shared<InexorCutAnsiCodesSink>(std::make_shared<spdlog::sinks::simple_file_sink_mt>(logfile_name, true, true));

        io->debug("changed the logfile to {}", logfile_name, old_logfile);
        all_loggers_apply_sinks_change();
    });
}

void log_manager::all_loggers_apply_sinks_change()
{
    std.recreate_spdlog_logger();
    start_stop.recreate_spdlog_logger();
    sync.recreate_spdlog_logger();
    io.recreate_spdlog_logger();
    util.recreate_spdlog_logger();
    render.recreate_spdlog_logger();
    ui.recreate_spdlog_logger();
    game.recreate_spdlog_logger();
    chat.recreate_spdlog_logger();
    team_chat.recreate_spdlog_logger();
    frag_involved.recreate_spdlog_logger();
    frag_not_involved.recreate_spdlog_logger();
    world.recreate_spdlog_logger();
    edit.recreate_spdlog_logger();
}

/// Register logger to spdlog or replace it if the name is already taken.
Logger log_manager::create_and_register_logger(std::string logger_name, const std::string pattern, int level)
{
    Logger logger;
    logger.create_spdlog_logger(logger_name);
    logger.level = level;
    //logger.pattern = pattern.c_str(); // TODO: string sharedvars
    return logger;
}

/// Initialize the static members of the log_manager class.
/// static members have no explicit parent, meaning first usage initializes these members.
Logger log_manager::std      = log_manager::create_and_register_logger("std");
Logger log_manager::start_stop   = log_manager::create_and_register_logger("start_stop");
Logger log_manager::sync         = log_manager::create_and_register_logger("sync");
Logger log_manager::io           = log_manager::create_and_register_logger("io");
Logger log_manager::util         = log_manager::create_and_register_logger("util");
Logger log_manager::render       = log_manager::create_and_register_logger("render");
Logger log_manager::ui           = log_manager::create_and_register_logger("ui");
Logger log_manager::game         = log_manager::create_and_register_logger("game");
Logger log_manager::chat         = log_manager::create_and_register_logger("chat");
Logger log_manager::team_chat    = log_manager::create_and_register_logger("teamchat");
Logger log_manager::frag_involved = log_manager::create_and_register_logger("frag_involved");
Logger log_manager::frag_not_involved = log_manager::create_and_register_logger("frag_not_involved");
Logger log_manager::world        = log_manager::create_and_register_logger("world");
Logger log_manager::edit         = log_manager::create_and_register_logger("edit");

}
}
inexor::util::log_manager Log;

