#include <iostream>

#include "inexor/ui/CefSubsystem.hpp"
#include "inexor/ui/InexorSettings.hpp"
#include "inexor/filesystem/ExecutablePath.hpp"
#include "inexor/network/SharedTree.hpp"

using namespace inexor::filesystem;
using namespace inexor::util;

// TODO: Namespace; encapsulate in the class; damint

SUBSYSTEM_REGISTER(cef, inexor::ui::CefSubsystem);

namespace inexor {
namespace ui {

CefRefPtr<InexorCefApp> cef_app;

CefSubsystem::CefSubsystem() {
}

CefSubsystem::~CefSubsystem() {
    cef_app->Destroy();

    // Make sure any outstanding IPC messages are processed
    for(int i = 0; i < 100; i++)
        tick();

    // Stop any forked processes
    CefShutdown();

    // Destroy the cef app
    cef_app = nullptr; // this crashes bc its refcount isnt zero
}

void CefSubsystem::tick() {
    // std::cerr << "CefSubsystem::tick() --> CefDoMessageLoopWork()\n";
    CefDoMessageLoopWork();
}

void CefSubsystem::initialize(int argc, char **argv)
{
	spdlog::get("global")->info("CefSubsystem::initialize() --> CefInitialize()");

    if(argc < 2) return;
    std::string port = argv[1];

    cef_app = new InexorCefApp(port, 1920, 1080);


#ifdef WIN32
    const CefMainArgs args(GetModuleHandle(NULL));
#else
    const CefMainArgs args(argc, argv);
#endif
    std::string executable_path = ExecutablePathWithoutBinary(argv[0]);
    InexorSettings settings(executable_path);
    if (!CefInitialize(args, settings, cef_app.get(), NULL)) {
        spdlog::get("global")->error("FATAL: Initialization of CEF subprocess failed!");
    }
}


}
}
