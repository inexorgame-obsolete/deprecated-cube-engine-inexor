#pragma once

#include "inexor/util/InexorException.hpp"
#include "inexor/util/Subsystem.hpp"

namespace inexor {
namespace ui {

IEXCEPTION(CefProcessException, "The CEF process was started with a non-zero exit code");

class CefSubsystem : public inexor::util::Subsystem {
public:
    ~CefSubsystem();
    virtual void tick() override;
    virtual void initialize(int argc, char **argv) override;
};

}
}


