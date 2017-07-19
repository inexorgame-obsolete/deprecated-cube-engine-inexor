#include "inexor/util/Logging.hpp"

#include <spdlog/sinks/msvc_sink.h>

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <exception>

using std::make_shared;

namespace inexor {
namespace util {

Logging::Logging()
{
    // Queue size for async mode must be power of 2
    size_t q_size = 4096;
    // Set async mode
    spdlog::set_async_mode(q_size);
}

Logging::~Logging()
{
    spdlog::drop_all();
}

void Logging::initDefaultLoggers()
{
    createSinks();
    for(const auto& default_logger_name : default_logger_names) {
        createAndRegisterLogger(default_logger_name.c_str());
    }
    spdlog::get("global")->debug("Default loggers initialized");
}

void Logging::createAndRegisterLogger(std::string logger_name)
{

    try
    {
        std::vector<spdlog::sink_ptr> sinks = getSinksForLogger(logger_name);
        auto logger = std::make_shared<spdlog::logger>(logger_name, begin(sinks), end(sinks));
        logger->set_pattern("%H:%M:%S [%n] [%l] %v");
        spdlog::register_logger(logger);
    }
    catch(...)
    {

    }
}

// TODO: Here we should configure which sinks are used in which logger using a configuration file
std::vector<spdlog::sink_ptr> &Logging::getSinksForLogger(std::string logger_name)
{
    return allsinks;
}

bool is_file_writeable(const std::string &filename)
{
    std::ofstream outfile(filename.c_str());
    return outfile.good();
}

/// Modifies the given logname until its a writeable file.
/// Does so by simply appending a number to it.
/// @return false if it exceeded 100 rename tries and none worked.
bool find_logger_name(std::string &logname_without_extension)
{
    constexpr int max_log_renamed_versions = 100;
    for(int i = 0; i < max_log_renamed_versions; i++)
    {
        if(is_file_writeable(logname_without_extension + std::to_string(i) + ".log"))
        {
            logname_without_extension = logname_without_extension + std::to_string(i);
            return true;
        }
    }
    return false;
}

// TODO: Here we should configure which sinks are used in which logger using a configuration file
void Logging::createSinks()
{
    allsinks.push_back(make_shared<spdlog::sinks::stdout_sink_mt>());
    allsinks.push_back(make_shared<InexorConsoleSink>());

    std::string logger_name = "inexor";
    if(!find_logger_name(logger_name)) throw std::runtime_error("There was no way to create a logfile.");

    allsinks.push_back(make_shared<InexorCutAnsiCodesSink>(make_shared<spdlog::sinks::rotating_file_sink_mt>(logger_name, "log", 5242880, 3)));
#if defined(_MSC_VER) && !defined(NDEBUG)
    allsinks.push_back(make_shared<spdlog::sinks::msvc_sink_mt>());
#endif
}

// TODO: note that we cannot set the log level for a specific sink at the moment
void Logging::setLogLevel(std::string logger_name, std::string log_level)
{
    try {
        if(log_level.empty() || logger_name.empty()) return;
        auto logger = spdlog::get(logger_name);
        logger->set_level(log_levels.at(log_level));
    } catch (const spdlog::spdlog_ex& ex) {
    }
}

// TODO: note that we cannot set the log format for a specific sink at the moment
void Logging::setLogFormat(std::string logger_name, std::string pattern)
{
    try {
        if(pattern.empty() || logger_name.empty()) return;
        auto logger = spdlog::get(logger_name);
        logger->set_pattern(pattern);
    } catch (const spdlog::spdlog_ex& ex) {
    }
}

void InexorConsoleSink::log(const spdlog::details::log_msg & msg)
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

std::string InexorCutAnsiCodesSink::cutANSICodes(std::string logline)
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

}
}
