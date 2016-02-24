#include <include/cef_base.h>

#include "inexor/ui/InexorCefApp.hpp"

int main(int argc, char **argv) {
    CefMainArgs ma{argc, argv};
    CefRefPtr<InexorCefApp> inexor_cef_app = new InexorCefApp{1980, 1080};
    return CefExecuteProcess(ma, inexor_cef_app.get(), NULL);
}
