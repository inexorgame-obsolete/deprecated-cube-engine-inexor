#include "inexor/cef_subprocess/main.hpp"

int main(int argc, char **argv) {
#ifdef WIN32
    CefMainArgs main_args(GetModuleHandle(NULL));
#else
    const CefMainArgs main_args(argc, argv);
#endif
    CefRefPtr<InexorCefApp> cef_app(new InexorCefApp(1980, 1080));
    return CefExecuteProcess(main_args, cef_app.get(), NULL);
}
