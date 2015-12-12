#include <include/cef_base.h>

#include "inexor/ui/cefapp.hpp"

int main(int argc, char **argv) {
    CefMainArgs ma{argc, argv};
    CefRefPtr<InexorCefApp> app = new InexorCefApp{1024, 1024};
    return CefExecuteProcess(ma, app.get(), NULL);
}
