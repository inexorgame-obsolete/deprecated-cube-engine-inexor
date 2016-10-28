#ifndef INEXOR_UI_INEXOR_RENDER_HANDLER_HEADER
#define INEXOR_UI_INEXOR_RENDER_HANDLER_HEADER
#pragma once

#include "include/cef_browser.h"
#include "include/cef_render_handler.h"
#include "include/wrapper/cef_helpers.h"

#include "inexor/engine/engine.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace ui {

class InexorRenderHandler : public CefRenderHandler {
    public:
        InexorRenderHandler(bool transparent, int x, int y, int width, int height);
        virtual ~InexorRenderHandler();

        // Initialize the OpenGL environment.
        void Initialize();

        // Clean up the OpenGL environment.
        void Cleanup();

        // Forwarded from CefRenderHandler callbacks.
        void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show);

        void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect);

        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);

        bool SetViewRect(int view_x, int view_y, int view_width, int view_height);

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

        bool IsInitialized() { return initialized; };
        unsigned int GetTextureId() { return texture_id; };

    private:
        const bool transparent;
        bool initialized;
        bool texture_initialized;
        unsigned int texture_id;
        int view_x;
        int view_y;
        int view_width;
        int view_height;
        bool _view_change_defered;
        int _view_x;
        int _view_y;
        int _view_width;
        int _view_height;
        CefRect popup_rect;
        CefRect original_popup_rect;

        // Provides atomic refcounting implementation.
        IMPLEMENT_REFCOUNTING(InexorRenderHandler);

};

}
}

#endif
