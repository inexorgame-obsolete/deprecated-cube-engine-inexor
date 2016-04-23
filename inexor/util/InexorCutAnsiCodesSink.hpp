/// @file Sink for the inexor game console.

#pragma once

#include <string>
#include <iostream>
#include "spdlog/sinks/sink.h"

/// Function which displayes console text ingame.
extern void conline(int type, const char *sf);

namespace inexor {
namespace util {

    class InexorCutAnsiCodesSink : public spdlog::sinks::sink
    {
    public:
        InexorCutAnsiCodesSink(spdlog::sink_ptr wrapped_sink);
        virtual ~InexorCutAnsiCodesSink();


        InexorCutAnsiCodesSink(const InexorCutAnsiCodesSink& other) = delete;
        InexorCutAnsiCodesSink& operator=(const InexorCutAnsiCodesSink& other) = delete;

        virtual void log(const spdlog::details::log_msg& msg) override;
        virtual void flush() override;
        virtual std::string cutANSICodes(std::string logline);

    protected:
        spdlog::sink_ptr sink_;
    };

    inline InexorCutAnsiCodesSink::InexorCutAnsiCodesSink(spdlog::sink_ptr wrapped_sink) : sink_(wrapped_sink)
    {
    }

    inline InexorCutAnsiCodesSink::~InexorCutAnsiCodesSink()
    {
        flush();
    }

    inline void InexorCutAnsiCodesSink::log(const spdlog::details::log_msg& msg)
    {
        spdlog::details::log_msg new_msg;
        new_msg.formatted << cutANSICodes(msg.formatted.str());
        sink_->log(new_msg);
    }

    inline void InexorCutAnsiCodesSink::flush()
    {
        sink_->flush();
    }

    /// @brief cut any valid ANSI Codes (used e.g. for colors in terminals) from a string.
    inline std::string InexorCutAnsiCodesSink::cutANSICodes(std::string logline)
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
