#include <iostream>
#include <chrono>
#include <thread>

#include <include/cef_base.h>

#include "inexor/ui/InexorCefApp.hpp"
#include "inexor/ui/InexorCefSubprocessApp.hpp"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "en_US.utf8");
    std::cerr << "init: cef: cef_subprocess\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

#ifdef WIN32
    CefMainArgs main_args(GetModuleHandle(NULL));
#else
    const CefMainArgs main_args(argc, argv);
#endif
    // TODO: do we really need the cef_app initialized again in the subprocess?
    // if not, we are able to decouple the rendering code again!
    // return CefExecuteProcess(main_args, NULL, NULL);
    CefRefPtr<InexorCefSubprocessApp> cef_app = new InexorCefSubprocessApp();
    return CefExecuteProcess(main_args, cef_app.get(), NULL);
}
