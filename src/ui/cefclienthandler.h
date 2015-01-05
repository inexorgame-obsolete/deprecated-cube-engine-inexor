#ifndef _CEF_CLIENT_HANDLER_H
#define _CEF_CLIENT_HANDLER_H

#include "cefrenderhandler.h"
#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"

class InexorCefClientHandler : public CefClient,
                               public CefLifeSpanHandler,
                               public CefLoadHandler,
                               public CefKeyboardHandler,
                               public CefDisplayHandler,
                               public CefRequestContextHandler
{
    public:
        InexorCefClientHandler(InexorCefRenderHandler *renderHandler); // : m_renderHandler(renderHandler) { };
        virtual ~InexorCefClientHandler();

        // Getters for handlers
        virtual CefRefPtr<CefRenderHandler> GetRenderHandler() { return render_handler; }
        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() { return this; }
        virtual CefRefPtr<CefLoadHandler> GetLoadHandler() { return this; }
        virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() { return this; }
        virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() { return this; }
        virtual CefRefPtr<CefRequestContextHandler> GetRequestContextHandler() { return this; }

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

        // CefRequestContextHandler
        CefRefPtr<CefCookieManager> GetCookieManager() { return cookie_manager; }

        CefRefPtr<CefBrowser> GetBrowser() { return browser; }
        bool IsClosing() { return is_closing; }

    protected:
        CefRefPtr<CefBrowser> browser;
        CefRefPtr<CefRenderHandler> render_handler;
        CefRefPtr<CefCookieManager> cookie_manager;
        int browser_id;
        int browser_count;
        bool is_closing;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefClientHandler);
};

#endif
