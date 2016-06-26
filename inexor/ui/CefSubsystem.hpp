#ifndef INEXOR_UI_CEF_SUBSYSTEM_HEADER
#define INEXOR_UI_CEF_SUBSYSTEM_HEADER

#include "inexor/ui.hpp"

#include "inexor/util/InexorException.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/util/Subsystem.hpp"

namespace inexor {
namespace ui {

IEXCEPTION(CefProcessException, "The CEF process was started with a non-zero exit code");

class CefSubsystem : public inexor::util::Subsystem {
public:
    CefSubsystem();
    virtual ~CefSubsystem();
    virtual void tick();
    virtual void initialize(int argc, char **argv);
};

}
}

#endif
