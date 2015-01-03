extern void logoutf(const char *fmt, ...);

#include <string>

#include "cefapp.h"
#include "cefclienthandler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"

InexorCefApp::InexorCefApp(std::string url, int x, int y, int width, int height) : url(url) {
    // The window info
    window_info.x = x;
    window_info.y = y;
    window_info.width = width;
    window_info.height = height;
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

InexorCefApp::InexorCefApp(std::string url) : url(url) {
    // The window info
    window_info.x = 50;
    window_info.y = 50;
    window_info.width = 1800;
    window_info.height = 900;
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
    render_handler = new InexorCefRenderHandler(true, window_info.x, window_info.y, window_info.width, window_info.height);
    render_handler->Initialize();
    client_handler = new InexorCefClientHandler(render_handler);
    browser = CefBrowserHost::CreateBrowserSync(window_info, client_handler.get(), url, browser_settings, NULL);
    if (browser.get()) {
        logoutf("init: cef: successfully created browser instance");
        browser->GetHost()->SendFocusEvent(true);
    }
}
