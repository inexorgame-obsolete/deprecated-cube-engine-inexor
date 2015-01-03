#ifndef _CEF_RENDER_HANDLER_H
#define _CEF_RENDER_HANDLER_H
#pragma once

#include "include/cef_browser.h"
#include "include/cef_render_handler.h"
#include "include/wrapper/cef_helpers.h"

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

        bool IsTransparent() { return transparent_; }

        int GetViewX() { return view_x_; }
        int GetViewY() { return view_y_; }
        int GetViewWidth() { return view_width_; }
        int GetViewHeight() { return view_height_; }

        const CefRect& popup_rect() const { return popup_rect_; }
        const CefRect& original_popup_rect() const { return original_popup_rect_; }

        CefRect GetPopupRectInWebView(const CefRect& original_rect);
        void ClearPopupRects();

    private:
        const bool transparent_;
        bool initialized_;
        unsigned int texture_id_;
        int view_x_;
        int view_y_;
        int view_width_;
        int view_height_;
        CefRect popup_rect_;
        CefRect original_popup_rect_;

        // Provides atomic refcounting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefRenderHandler);

};

#endif
