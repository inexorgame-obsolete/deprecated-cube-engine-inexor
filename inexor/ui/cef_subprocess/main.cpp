#include <locale.h>                              // for setlocale, LC_ALL
#include <chrono>                                // for milliseconds
#include <iostream>                              // for operator<<, cout
#include <thread>                                // for sleep_for

#include "include/cef_app.h"                     // for CefApp, CefExecutePr...
#include "include/cef_base.h"                    // for CefRefPtr, CefMainArgs
#include "inexor/ui/InexorCefSubprocessApp.hpp"  // for InexorCefSubprocessApp

#undef main

#ifdef WIN32
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
    setlocale(LC_ALL, "en_US.utf8");
    std::cout << "init: cef: cef_subprocess\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

#ifdef WIN32
    CefMainArgs main_args(hInstance);
#else
    const CefMainArgs main_args(argc, argv);
#endif
    // TODO: do we really need the cef_app initialized again in the subprocess?
    // if not, we are able to decouple the rendering code again!
    // return CefExecuteProcess(main_args, NULL, NULL);
    CefRefPtr<inexor::ui::InexorCefSubprocessApp> cef_app = new inexor::ui::InexorCefSubprocessApp();
    return CefExecuteProcess(main_args, cef_app.get(), nullptr);
}
