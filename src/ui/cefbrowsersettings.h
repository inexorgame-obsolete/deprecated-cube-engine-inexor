#ifndef _CEF_BROWSER_SETTINGS_H
#define _CEF_BROWSER_SETTINGS_H
#pragma once

class InexorCefBrowserSettings : public CefBrowserSettings {
    public:
        InexorCefBrowserSettings() {
            windowless_frame_rate = 60;
            file_access_from_file_urls = STATE_ENABLED;
            plugins = STATE_DISABLED;
            webgl = STATE_DISABLED;
            java = STATE_DISABLED;
            caret_browsing = STATE_ENABLED;
            javascript = STATE_ENABLED;
        };
};

#endif
