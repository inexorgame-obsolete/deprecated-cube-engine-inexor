#ifndef _CEF_CLIENT_HANDLER_H
#define _CEF_CLIENT_HANDLER_H

#include "cefrenderhandler.h"
#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"

class InexorCefClientHandler : public CefClient,
                               public CefLifeSpanHandler,
                               public CefLoadHandler,
                               public CefKeyboardHandler
{
    public:
        InexorCefClientHandler(InexorCefRenderHandler *renderHandler); // : m_renderHandler(renderHandler) { };
        virtual ~InexorCefClientHandler();
        virtual CefRefPtr<CefRenderHandler> GetRenderHandler();

        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() { return this; }

        void OnAfterCreated(CefRefPtr<CefBrowser> browser);
        bool DoClose(CefRefPtr<CefBrowser> browser);
        void OnBeforeClose(CefRefPtr<CefBrowser> browser);

        virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl);

        bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut);
        bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event);

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
