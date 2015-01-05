extern void logoutf(const char *fmt, ...);

#include <string>

#include "cefapp.h"
#include "cefclienthandler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"

InexorCefApp::InexorCefApp(std::string url, int x, int y, int width, int height) : url(url) {
    window_info.x = x;
    window_info.y = y;
    window_info.width = width;
    window_info.height = height;
}

InexorCefApp::InexorCefApp(std::string url) : url(url) {
}

void InexorCefApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    logoutf("init: cef: browser instance");
    render_handler = new InexorCefRenderHandler(true, window_info.x, window_info.y, window_info.width, window_info.height);
    render_handler->Initialize();
    client_handler = new InexorCefClientHandler(render_handler);
    browser = CefBrowserHost::CreateBrowserSync(window_info, client_handler.get(), url, browser_settings, NULL);
    if (browser.get()) {
        logoutf("init: cef: successfully created browser instance");
        browser->GetHost()->SendFocusEvent(true);
    }
}
