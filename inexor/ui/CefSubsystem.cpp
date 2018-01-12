#include <memory>                                     // for __shared_ptr
#include <string>                                     // for string, to_string

#include "include/base/cef_ref_counted.h"             // for scoped_refptr
#include "include/cef_app.h"                          // for CefApp, CefDoMe...
#include "include/cef_base.h"                         // for CefRefPtr, CefM...
#include "inexor/io/Logging.hpp"                      // for Log, Logger
#include "inexor/io/filesystem/ExecutablePath.hpp"    // for ExecutablePathW...
#include "inexor/network/SharedVar.hpp"               // for SharedVar
#include "inexor/ui/CefSubsystem.hpp"
#include "inexor/ui/InexorCefApp.hpp"                 // for InexorCefApp
#include "inexor/ui/InexorSettings.hpp"               // for InexorSettings
#include "inexor/ui/screen/ScreenManager.hpp"         // for scr_h, scr_w

using namespace inexor::filesystem;
using namespace inexor::util;
using namespace inexor::rendering::screen;

// TODO: Namespace; encapsulate in the class; damint

SUBSYSTEM_REGISTER(cef, inexor::ui::CefSubsystem);

namespace inexor {
namespace ui {

CefRefPtr<InexorCefApp> cef_app;

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

SharedVar<char *> interface_hostname((char*)"localhost");
SharedVar<int> interface_port(31416);

void CefSubsystem::initialize(int argc, char **argv)
{
    if (argc < 2) return;
    std::string instance_id = argv[1];

    std::string host = *interface_hostname;
    std::string port = std::to_string(interface_port);
    Log.ui->info("CefSubsystem::initialize() --> CefInitialize({0}, {1}, {2}, {3}, {4})", instance_id, host, port, scr_w, scr_h);
    cef_app = new InexorCefApp(instance_id, host, port, scr_w, scr_h);


#ifdef WIN32
    const CefMainArgs args(GetModuleHandle(NULL));
#else
    const CefMainArgs args(argc, argv);
#endif
    std::string executable_path = ExecutablePathWithoutBinary(argv[0]);
    InexorSettings settings(executable_path);
    Log.ui->error("FATAL: Initialization of CEF subprocess failed!  {}", executable_path);
    for (int i = 0; i < argc; i++) {
        char *arg = argv[i];
        Log.ui->error("FATAL: {}!", arg);
    }
    if (!CefInitialize(args, settings, cef_app.get(), nullptr)) {
        Log.ui->error("FATAL: Initialization of CEF subprocess failed!");
    }
}


}
}
