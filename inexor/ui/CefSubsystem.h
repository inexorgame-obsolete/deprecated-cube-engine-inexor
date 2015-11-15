#ifndef INEXOR_UI_CEF_SUBSYSTEM_HEADER
#define INEXOR_UI_CEF_SUBSYSTEM_HEADER

#include "inexor/ui/ui.h"
#include "inexor/ui/cefcontextbindings.h"

#include "inexor/util/InexorException.h"
#include "inexor/util/StringFormatter.h"
#include "inexor/util/Subsystem.h"

namespace inexor {
namespace ui {

IEXCEPTION(CefProcessException, "The CEF process was "
    "started with a non-zero exit code");

class CefSubsystem : public inexor::util::Subsystem {
public:
    CefSubsystem();
    virtual ~CefSubsystem();
    int main(int argc, char** argv);
    virtual void tick();
    virtual void paint();
};

}
}

#endif
