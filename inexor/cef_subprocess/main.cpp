#include <iostream>

#include <include/cef_base.h>

#include "inexor/ui/InexorCefApp.hpp"

#include "inexor/engine/engine.hpp"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "en_US.utf8");
    std::cerr << "init: cef: cef_subprocess\n";
#ifdef WIN32
    CefMainArgs main_args(GetModuleHandle(NULL));
#else
    const CefMainArgs main_args(argc, argv);
#endif
    // TODO: do we really need the cef_app initialized again in the subprocess?
    // if not, we are able to decouple the rendering code again!
    return CefExecuteProcess(main_args, NULL, NULL);
}
