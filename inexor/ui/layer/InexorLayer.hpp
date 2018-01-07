#pragma once
#include <list>
#include <string>
#include <sstream>

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_load_handler.h"
#include "include/wrapper/cef_helpers.h"

#include "inexor/io/Logging.hpp"
#include "inexor/ui/InexorBrowserSettings.hpp"
#include "inexor/ui/InexorRenderHandler.hpp"
#include "inexor/ui/InexorWindowInfo.hpp"

namespace inexor {
namespace ui {
namespace layer {

class InexorLayer : public CefClient,
                    public CefLifeSpanHandler,
                    public CefLoadHandler,
                    public CefKeyboardHandler,
                    public CefDisplayHandler,
                    public CefRequestContextHandler
{

    public:
        InexorLayer(std::string name, int x, int y, int width, int height, std::string url);
        ~InexorLayer() override;

        std::string GetName() { return name; }
        std::string GetUrl() { return url; }
        InexorWindowInfo GetWindowInfo() { return window_info; }
        CefBrowserSettings GetBrowserSettings() { return browser_settings; };

        // void Render() { render_handler->Render(); };
        void Destroy();

        void Copy();
        void Paste();
        void Cut();

        void ShowDevTools();

        /// A layer can be visible or hidden.
        bool IsVisible() { return is_visible && browser.get(); };
        void SetVisibility(bool is_visible);

        bool IsAcceptingKeyInput() { return is_accepting_key_input && browser.get(); };
        bool IsAcceptingMouseInput() { return is_accepting_mouse_input && browser.get(); };
        void SetIsAcceptingKeyInput(bool is_accepting_key_input);
        void SetIsAcceptingMouseInput(bool is_accepting_mouse_input);

        bool IsClosing() { return is_closing; }

        // Getters for handlers
        virtual CefRefPtr<InexorLayer> GetClientHandler() { return this; };
        CefRefPtr<CefRenderHandler> GetRenderHandler() override { return render_handler; }
        virtual CefRefPtr<InexorRenderHandler> GetInexorRenderHandler() { return render_handler; }
        virtual CefRefPtr<CefBrowser> GetBrowser() { return browser; };
        CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
        CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
        CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override { return this; }
        CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
        virtual CefRefPtr<CefRequestContextHandler> GetRequestContextHandler() { return this; }
        CefRefPtr<CefCookieManager> GetCookieManager() override { return cookie_manager; }

        // CefLifeSpanHandler
        void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        bool DoClose(CefRefPtr<CefBrowser> browser) override;
        void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

        // CefLoadHandler
        void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;

        // CefKeyboardHandler
        bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut) override;
        bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event) override;
        void SendKeyEvent(const CefKeyEvent& event) { browser->GetHost()->SendKeyEvent(event); }

        // CefDisplayHandler
        void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url) override;
        void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value) override;
        bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line) override;

	private:

        void UpdateFocus();

	    std::string name;
        std::string url;

	    bool is_visible;
	    bool is_accepting_key_input;
        bool is_accepting_mouse_input;

	    int browser_id;
        int browser_count;
        bool is_closing;

        InexorWindowInfo window_info;
        InexorBrowserSettings browser_settings;
        CefRefPtr<InexorRenderHandler> render_handler;
        CefRefPtr<CefBrowser> browser;
        CefRefPtr<CefCookieManager> cookie_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorLayer);

};

}
}
}
