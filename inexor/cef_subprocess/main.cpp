#include "inexor/cef_subprocess/main.hpp"

int main(int argc, char **argv) {
    const CefMainArgs main_args(argc, argv);
    CefRefPtr<InexorCefApp> cef_app(new InexorCefApp(1980, 1080));
    return CefExecuteProcess(main_args, cef_app.get(), NULL);
}
