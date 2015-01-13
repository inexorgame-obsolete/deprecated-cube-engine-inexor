#ifndef _CEF_LAYER_H
#define _CEF_LAYER_H

#include <list>
#include <string>
#include <sstream>

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_load_handler.h"
#include "include/wrapper/cef_helpers.h"

#include "cefbrowsersettings.h"
#include "cefrenderhandler.h"
#include "cefwindowinfo.h"

extern void logoutf(const char *fmt, ...);

class InexorCefLayer : public CefClient,
                       public CefLifeSpanHandler,
                       public CefLoadHandler,
                       public CefKeyboardHandler,
                       public CefDisplayHandler,
                       public CefRequestContextHandler
{

    public:
        InexorCefLayer(std::string name, int x, int y, int width, int height, std::string url);
        virtual ~InexorCefLayer();

        std::string GetName() { return name; }
        std::string GetUrl() { return url; }
        InexorCefWindowInfo GetWindowInfo() { return window_info; }
        CefBrowserSettings GetBrowserSettings() { return browser_settings; };

        void Render() { render_handler->Render(); };
        void Destroy();

        void ShowDevTools();

        bool IsVisible() { return is_visible; };
        void SetVisibility(bool is_visible);

        bool HasFocus() { return has_focus; };
        void SetFocus(bool has_focus);

        bool IsAcceptingInput() { return is_accepting_input; };
        void SetIsAcceptingInput(bool is_accepting_input);

        bool IsClosing() { return is_closing; }

        // Getters for handlers
        virtual CefRefPtr<InexorCefLayer> GetClientHandler() { return this; };
        virtual CefRefPtr<CefRenderHandler> GetRenderHandler() { return render_handler; }
        virtual CefRefPtr<CefBrowser> GetBrowser() { return browser; };
        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() { return this; }
        virtual CefRefPtr<CefLoadHandler> GetLoadHandler() { return this; }
        virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() { return this; }
        virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() { return this; }
        virtual CefRefPtr<CefRequestContextHandler> GetRequestContextHandler() { return this; }
        virtual CefRefPtr<CefCookieManager> GetCookieManager() { return cookie_manager; }

        // CefLifeSpanHandler
        void OnAfterCreated(CefRefPtr<CefBrowser> browser);
        bool DoClose(CefRefPtr<CefBrowser> browser);
        void OnBeforeClose(CefRefPtr<CefBrowser> browser);

        // CefLoadHandler
        virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl);

        // CefKeyboardHandler
        bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut);
        bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event);
        void SendKeyEvent(const CefKeyEvent& event) { browser->GetHost()->SendKeyEvent(event); }

        // CefDisplayHandler
        void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url);
        void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value);
        bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line);

	private:
	    std::string name;
        std::string url;

	    bool is_visible;
	    bool is_accepting_input;
	    bool has_focus;
        bool is_closing;
        int browser_id;
        int browser_count;

        InexorCefWindowInfo window_info;
        InexorCefBrowserSettings browser_settings;
        CefRefPtr<InexorCefRenderHandler> render_handler;
        CefRefPtr<CefBrowser> browser;
        CefRefPtr<CefCookieManager> cookie_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefLayer);

};

#endif  // _CEF_LAYER_H
