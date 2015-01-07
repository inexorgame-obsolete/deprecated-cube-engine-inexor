#ifndef _CEF_RENDER_HANDLER_H
#define _CEF_RENDER_HANDLER_H
#pragma once

#include "include/cef_browser.h"
#include "include/cef_render_handler.h"
#include "include/wrapper/cef_helpers.h"

extern void logoutf(const char *fmt, ...);

class InexorCefRenderHandler : public CefRenderHandler {
    public:
        InexorCefRenderHandler(bool transparent, int x, int y, int width, int height);
        virtual ~InexorCefRenderHandler();

        // Initialize the OpenGL environment.
        void Initialize();

        // Clean up the OpenGL environment.
        void Cleanup();

        // Render to the screen.
        void Render();

        // Forwarded from CefRenderHandler callbacks.
        void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show);

        void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect);

        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);

        void OnPaint(CefRefPtr<CefBrowser> browser,
            CefRenderHandler::PaintElementType type,
            const CefRenderHandler::RectList& dirtyRects,
            const void* buffer, int width, int height);

        bool IsTransparent() { return transparent; }

        int GetViewX() { return view_x; }
        int GetViewY() { return view_y; }
        int GetViewWidth() { return view_width; }
        int GetViewHeight() { return view_height; }

        const CefRect& PopupRect() const { return popup_rect; }
        const CefRect& OriginalPopupRect() const { return original_popup_rect; }

        CefRect GetPopupRectInWebView(const CefRect& original_rect);
        void ClearPopupRects();

    private:
        const bool transparent;
        bool initialized;
        unsigned int texture_id;
        int view_x;
        int view_y;
        int view_width;
        int view_height;
        CefRect popup_rect;
        CefRect original_popup_rect;

        // Provides atomic refcounting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefRenderHandler);

};

#endif
