#include <chrono>
#include <thread>

#include "inexor/cef_subprocess/main.hpp"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "en_US.utf8");
    std::cerr << "init: cef: cef_subprocess\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

#ifdef WIN32
    CefMainArgs main_args(GetModuleHandle(NULL));
#else
    const CefMainArgs main_args(argc, argv);
#endif
    // TODO: do we really need the cef_app initialized again in the subprocess?
    // if not, we are able to decouple the rendering code again!
    // return CefExecuteProcess(main_args, NULL, NULL);
    CefRefPtr<inexor::ui::InexorCefSubprocessApp> cef_app = new inexor::ui::InexorCefSubprocessApp();
    return CefExecuteProcess(main_args, cef_app.get(), NULL);
}
