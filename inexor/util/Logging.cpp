#include "inexor/util/Logging.hpp"

#include <spdlog/sinks/msvc_sink.h>

#include <vector>
#include <string>
#include <memory>

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
    std::vector<spdlog::sink_ptr> sinks = getSinksForLogger(logger_name);
    auto logger = std::make_shared<spdlog::logger>(logger_name, begin(sinks), end(sinks));
    logger->set_pattern("%H:%M:%S [%n] [%l] %v");
    spdlog::register_logger(logger);
}

// TODO: Here we should configure which sinks are used in which logger using a configuration file
std::vector<spdlog::sink_ptr> Logging::getSinksForLogger(std::string logger_name)
{
    return allsinks;
}

// TODO: Here we should configure which sinks are used in which logger using a configuration file
void Logging::createSinks()
{
    allsinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    allsinks.push_back(std::make_shared<inexor::util::InexorConsoleSink>());
    allsinks.push_back(std::make_shared<inexor::util::InexorCutAnsiCodesSink>(std::make_shared<spdlog::sinks::rotating_file_sink_st>("inexor", "log", 5242880, 3)));
#if defined(_MSC_VER) && !defined(NDEBUG)
    allsinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_st>());
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

}
}
