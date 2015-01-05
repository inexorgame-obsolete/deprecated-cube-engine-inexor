#ifndef _CEF_CLIENT_HANDLER_H
#define _CEF_CLIENT_HANDLER_H

#include "cefrenderhandler.h"
#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"

class InexorCefClientHandler : public CefClient,
                               public CefLifeSpanHandler,
                               public CefLoadHandler,
                               public CefKeyboardHandler,
                               public CefDisplayHandler
{
    public:
        InexorCefClientHandler(InexorCefRenderHandler *renderHandler); // : m_renderHandler(renderHandler) { };
        virtual ~InexorCefClientHandler();

        // Getters for handlers
        virtual CefRefPtr<CefRenderHandler> GetRenderHandler() { return m_renderHandler; }
        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() { return this; }
        virtual CefRefPtr<CefLoadHandler> GetLoadHandler() { return this; }
        virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() { return this; }
        virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() { return this; }

        // CefLifeSpanHandler
        void OnAfterCreated(CefRefPtr<CefBrowser> browser);
        bool DoClose(CefRefPtr<CefBrowser> browser);
        void OnBeforeClose(CefRefPtr<CefBrowser> browser);

        // CefLoadHandler
        virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl);

        // CefKeyboardHandler
        bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut);
        bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event);
        void SendKeyEvent(const CefKeyEvent& event) { m_Browser->GetHost()->SendKeyEvent(event); }

        // CefDisplayHandler
        void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value);
        bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line);

        CefRefPtr<CefBrowser> GetBrowser() { return m_Browser; }
        bool IsClosing() { return m_bIsClosing; }

    protected:
        CefRefPtr<CefBrowser> m_Browser;
        CefRefPtr<CefRenderHandler> m_renderHandler;
        int m_BrowserId;
        int m_BrowserCount;
        bool m_bIsClosing;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefClientHandler);
};

#endif
