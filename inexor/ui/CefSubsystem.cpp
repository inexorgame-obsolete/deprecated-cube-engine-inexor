#include <iostream>

#include "inexor/ui/CefSubsystem.hpp"
#include "inexor/ui/InexorSettings.hpp"
#include "inexor/util/ExecutablePath.hpp"

using namespace inexor::util;

CefRefPtr<InexorCefApp> cef_app;

// TODO: Namespace; encapsulate in the class; damint

SUBSYSTEM_REGISTER(cef, inexor::ui::CefSubsystem);

namespace inexor {
namespace ui {

CefSubsystem::CefSubsystem() {
    ::cef_app = new InexorCefApp(1920, 1080);

    const CefMainArgs args;
    int exit_code = CefExecuteProcess(args, cef_app, NULL);
    if (exit_code >= 0) {
        /*
        std::string msg = fmt << "Forking the CEF process "
            << "yielded a non zero exit code: "
            << exit_code << ".";
        */
        std::string msg = "Forking the CEF process yielded a non zero exit code";
        throw CefProcessException(msg);
    }
    InexorSettings settings;

    tick();
}

CefSubsystem::~CefSubsystem() {
    ::cef_app->Destroy();

    // Make sure any outstanding IPC messages are processed
    for(int i = 0; i < 100; i++)
        tick();

    // Stop any forked processes
    CefShutdown();

    // Destroy the cef app
    ::cef_app = nullptr;
}

void CefSubsystem::tick() {
    // std::cerr << "CefSubsystem::tick() --> CefDoMessageLoopWork()\n";
    CefDoMessageLoopWork();
}

void CefSubsystem::initialize(int argc, char **argv) {
    std::cerr << "CefSubsystem::initialize() --> CefInitialize()\n";
    const CefMainArgs args(argc, argv);
    std::string executable_path = inexor::util::ExecutablePathWithoutBinary(argv[0]);
    // TODO: easylogging debug
    std::cerr << "Detected executable path: " << executable_path << "\n";
    InexorSettings settings(executable_path);
    if (!CefInitialize(args, settings, ::cef_app.get(), NULL)) {
        // TODO: easylogging
        std::cerr << "FATAL: Initialization of CEF subprocess failed!\n";
    }
}


}
}
