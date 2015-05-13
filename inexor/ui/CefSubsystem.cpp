#include "inexor/ui/CefSubsystem.h"
#include "inexor/ui/cefsettings.h"

using namespace inexor::util;

// TODO: Namespace; encapsulate in the class; damint
CefRefPtr<InexorCefApp> cef_app = NULL;

SUBSYSTEM_REGISTER(cef, inexor::ui::CefSubsystem);

namespace inexor {
namespace ui {

CefSubsystem::CefSubsystem() {
    ::cef_app = new InexorCefApp(scr_w, scr_h);
    const CefMainArgs args;
    int exit_code = CefExecuteProcess(args, cef_app, NULL);
    if (exit_code >= 0) {
        std::string msg = fmt << "Forking the CEF process "
            << "yielded a non zero exit code: "
            << exit_code << ".";
        throw CefProcessException(msg);
    }

    InexorCefSettings settings;
    CefInitialize(args, settings, cef_app.get(), NULL);

    tick();
}

CefSubsystem::~CefSubsystem() {
    ::cef_app->Destroy();
    ::cef_app = NULL;
}

void CefSubsystem::tick() {
    CefDoMessageLoopWork();
}

void CefSubsystem::paint() {
    ::cef_app->Render();
}


}
}
