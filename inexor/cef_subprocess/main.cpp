#include <include/cef_base.h>

#include "inexor/ui/InexorCefApp.hpp"

#include "inexor/engine/engine.hpp"

int main(int argc, char **argv) {
    const CefMainArgs main_args(argc, argv);
    CefRefPtr<InexorCefApp> cef_app = new InexorCefApp{1980, 1080};
    return CefExecuteProcess(main_args, cef_app.get(), NULL);
}
