#ifndef INEXOR_UI_CEF_SUBSYSTEM_HEADER
#define INEXOR_UI_CEF_SUBSYSTEM_HEADER

#include "ui/ui.h"
#include "ui/cefcontextbindings.h"

#include "util/InexorException.h"
#include "util/StringFormatter.h"
#include "util/Subsystem.h"

namespace inexor {
namespace ui {

IEXCEPTION(CefProcessException, "The CEF process was "
    "started with a non-zero exit code");

class CefSubsystem : public inexor::util::Subsystem {
public:
    CefSubsystem();
    virtual ~CefSubsystem();
    virtual void tick();
    virtual void paint();
};

}
}

#endif
