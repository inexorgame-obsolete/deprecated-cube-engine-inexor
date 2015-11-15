#include "inexor/ui/CefSubsystem.h"
#include "inexor/ui/cefsettings.h"
#include <cstdlib>
#include "inexor/engine/engine.h"

using namespace inexor::util;

// TODO: Namespace; encapsulate in the class; damint
CefRefPtr<InexorCefApp> cef_app = NULL;

SUBSYSTEM_REGISTER(cef, inexor::ui::CefSubsystem);

namespace inexor {
namespace ui {

CefSubsystem::CefSubsystem() {
    initialized = false;
}

CefSubsystem::~CefSubsystem() {
    ::cef_app->Destroy();
    ::cef_app = NULL;
}

int CefSubsystem::init(int argc, char** argv)
{
    conoutf("[[CefSubsystem::init]] Got %d command line arguments", argc);
    for (int i = 0; i < argc; i++) conoutf("  arg %d: %s", i, argv[i]);

    conoutf("[[CefSubsystem::init]] scr_w=%d scr_h=%d", *scr_w, *scr_h);
    ::cef_app = new InexorCefApp(scr_w, scr_h);
    const CefMainArgs args(argc, argv);

    // The following instruction forks a new process
    // The main process continues immediately and returns with exit code -1
    // The forked process blocks until finished and returns with exit code > 0
    conoutf("[[CefSubsystem::init]] before");
    int exit_code = CefExecuteProcess(args, cef_app, NULL);
    conoutf("[[CefSubsystem::init]] after: exitcode=%d", exit_code);
    if (exit_code >= 0) {
        // The forked process has ended.
        conoutf("[[CefSubsystem::init]] Terminating child process");
        std::exit(0);
        /*
        std::string msg = fmt << "Forking the CEF process "
            << "yielded a non zero exit code: "
            << exit_code << ".";
        throw CefProcessException(msg);
        */
    } else {
        // The main process does not block and continues immediately
        conoutf("[[CefSubsystem::init]] Initializing CEF");
        InexorCefSettings settings;
        CefInitialize(args, settings, cef_app.get(), NULL);

        // tick() and paint() are executed only if the submodule has been initialized
        initialized = true;
        tick();
        return 0;
    }
}

void CefSubsystem::tick() {
    if (initialized)
        CefDoMessageLoopWork();
}

void CefSubsystem::paint() {
    if (initialized)
        ::cef_app->Render();
}


}
}
