extern void logoutf(const char *fmt, ...);

#include <string>

#include "cefapp.h"
#include "cefclienthandler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"

InexorCefApp::InexorCefApp(std::string url) : url(url) {
    // The window info
    window_info.x = 0;
    window_info.y = 0;
    window_info.width = 1900;
    window_info.height = 1000;
    window_info.windowless_rendering_enabled = true;
    window_info.transparent_painting_enabled = true;

    // The browser settings
    browser_settings.windowless_frame_rate = 60;
    browser_settings.file_access_from_file_urls = STATE_ENABLED;
    browser_settings.plugins = STATE_DISABLED;
    browser_settings.webgl = STATE_DISABLED;
    browser_settings.java = STATE_DISABLED;
    browser_settings.caret_browsing = STATE_ENABLED;
    browser_settings.javascript = STATE_ENABLED;
}

void InexorCefApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    logoutf("init: cef: browser instance");
    render_handler = new InexorCefRenderHandler(true, true, window_info.width, window_info.height);
    render_handler->Initialize();
    client_handler = new InexorCefClientHandler(render_handler);
    browser = CefBrowserHost::CreateBrowserSync(window_info, client_handler.get(), url, browser_settings, NULL);
    if (browser.get()) {
        logoutf("init: cef: successfully created browser instance");
    }
    /*
    url2 = "http://data.t-r-w.com/inexor.html";
    browser2 = CefBrowserHost::CreateBrowserSync(window_info, client_handler.get(), url2, browser_settings, NULL);
    if (browser2.get()) {
        logoutf("init: cef: successfully created second browser instance");
    }
    */
}
