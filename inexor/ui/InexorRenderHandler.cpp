#include <iostream>

#include "inexor/ui/InexorRenderHandler.hpp"
#include "inexor/engine/engine.hpp"


// DCHECK on gl errors.
#ifndef NDEBUG
#define VERIFY_NO_ERROR { \
    int _gl_error = glGetError(); \
    DCHECK(_gl_error == GL_NO_ERROR) << \
    "glGetError returned " << _gl_error; \
  }
#else
#define VERIFY_NO_ERROR
#endif

InexorRenderHandler::InexorRenderHandler(bool transparent, int x, int y, int width, int height)
    : transparent(transparent),
      initialized(false),
      texture_id(0),
      view_x(x),
      view_y(y),
      view_width(width),
      view_height(height) {
}

InexorRenderHandler::~InexorRenderHandler() {
    Cleanup();
}

void InexorRenderHandler::Initialize() {
    if (initialized)
        return;

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); VERIFY_NO_ERROR;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); VERIFY_NO_ERROR;

    // Necessary for non-power-of-2 textures to render correctly.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); VERIFY_NO_ERROR;

    // Create the texture.
    glGenTextures(1, &texture_id); VERIFY_NO_ERROR;

    if (0u == texture_id) {
        throw GLException("texture id is 0");
    }

    glBindTexture(GL_TEXTURE_2D, texture_id); VERIFY_NO_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); VERIFY_NO_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); VERIFY_NO_ERROR;
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); VERIFY_NO_ERROR;

    initialized = true;
}

void InexorRenderHandler::Cleanup() {
    if (texture_id != 0) {
        glDeleteTextures(1, &texture_id);
    }
}

void InexorRenderHandler::Render() {
    /*
    if (view_width == 0 || view_height == 0 || !initialized)
        return;

    DCHECK(initialized);

    hudmatrix.ortho(0, view_width, view_height, 0, -1, 1);
    resethudmatrix();

    hudshader->set();
    gle::colorf(1, 1, 1);

    gle::defvertex(2);
    gle::deftexcoord0();

    // Alpha blending style. Texture values have premultiplied alpha.
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); VERIFY_NO_ERROR;

    // Enable alpha blending.
    glEnable(GL_BLEND); VERIFY_NO_ERROR;

    // Draw the facets with the texture.
    if (0u == texture_id) throw GLException("texture id is 0");

    glBindTexture(GL_TEXTURE_2D, texture_id); VERIFY_NO_ERROR;

    // Render Texture on the whole screen. TODO: Function initialization not threadsafe.
    screenquad(); VERIFY_NO_ERROR;

    // evtl flushhudmatrix here..

    // Disable alpha blending.
    glDisable(GL_BLEND); VERIFY_NO_ERROR;
    */
}

void InexorRenderHandler::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
{
    if (!show) {
        // Clear the popup rectangle.
        ClearPopupRects();
    }
}

void InexorRenderHandler::OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)
{
    if (rect.width <= 0 || rect.height <= 0)
        return;
    original_popup_rect = rect;
    popup_rect = GetPopupRectInWebView(original_popup_rect);
}

CefRect InexorRenderHandler::GetPopupRectInWebView(const CefRect& original_rect)
{
    CefRect rc(original_rect);
    // if x or y are negative, move them to 0.
    if (rc.x < 0)
        rc.x = 0;
    if (rc.y < 0)
        rc.y = 0;
    // if popup goes outside the view, try to reposition origin
    if (rc.x + rc.width > view_width)
        rc.x = view_width - rc.width;
    if (rc.y + rc.height > view_height)
        rc.y = view_height - rc.height;
    // if x or y became negative, move them to 0 again.
    if (rc.x < 0)
        rc.x = 0;
    if (rc.y < 0)
        rc.y = 0;
    return rc;
}

void InexorRenderHandler::ClearPopupRects()
{
    popup_rect.Set(0, 0, 0, 0);
    original_popup_rect.Set(0, 0, 0, 0);
}

bool InexorRenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
    rect = CefRect(view_x, view_y, view_width, view_height);
    return true;
}

void InexorRenderHandler::OnPaint(
    CefRefPtr<CefBrowser> browser,
    CefRenderHandler::PaintElementType type,
    const CefRenderHandler::RectList& dirtyRects,
    const void* buffer, int width, int height
) {
    if (!initialized) {
    	if (CefCurrentlyOn(TID_UI)) {
            Initialize();
    	} else {
    	    return;
    	}
    }

   	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); VERIFY_NO_ERROR;
    glEnable(GL_BLEND); VERIFY_NO_ERROR;

    // Enable 2D textures.
    glEnable(GL_TEXTURE_2D); VERIFY_NO_ERROR;

    if (0u == texture_id) {
        throw GLException("texture id is 0");
    } else {
        glBindTexture(GL_TEXTURE_2D, texture_id); VERIFY_NO_ERROR;
    }

    if (type == PET_VIEW) {
        int old_width = view_width;
        int old_height = view_height;
        view_width = width;
        view_height = height;
        glPixelStorei(GL_UNPACK_ROW_LENGTH, view_width); VERIFY_NO_ERROR;
        if (old_width != view_width || old_height != view_height
            || (dirtyRects.size() == 1 && dirtyRects[0] == CefRect(0, 0, view_width, view_height))
        ) {
            // Update/resize the whole texture.
        	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0); VERIFY_NO_ERROR;
        	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0); VERIFY_NO_ERROR;
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, view_width, view_height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, buffer); VERIFY_NO_ERROR;
        } else {
            // Update just the dirty rectangles.
            CefRenderHandler::RectList::const_iterator i = dirtyRects.begin();
            for (; i != dirtyRects.end(); ++i) {
                const CefRect& rect = *i;
                glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect.x); VERIFY_NO_ERROR;
                glPixelStorei(GL_UNPACK_SKIP_ROWS, rect.y); VERIFY_NO_ERROR;
                glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.width,
                    rect.height, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV,
                    buffer); VERIFY_NO_ERROR;
            }
        }
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); VERIFY_NO_ERROR;
    } else if (type == PET_POPUP && popup_rect.width > 0 && popup_rect.height > 0) {
        int skip_pixels = 0, x = popup_rect.x;
        int skip_rows = 0, y = popup_rect.y;
        int w = width;
        int h = height;

        // Adjust the popup to fit inside the view.
        if (x < 0) {
            skip_pixels = -x;
            x = 0;
        }
        if (y < 0) {
            skip_rows = -y;
            y = 0;
        }
        if (x + w > view_width)
            w -= x + w - view_width;
        if (y + h > view_height)
            h -= y + h - view_height;

        // Update the popup rectangle.
        glPixelStorei(GL_UNPACK_ROW_LENGTH, width); VERIFY_NO_ERROR;
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, skip_pixels); VERIFY_NO_ERROR;
        glPixelStorei(GL_UNPACK_SKIP_ROWS, skip_rows); VERIFY_NO_ERROR;
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, buffer); VERIFY_NO_ERROR;
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); VERIFY_NO_ERROR;
    }

    // Disable 2D textures.
    glDisable(GL_TEXTURE_2D); VERIFY_NO_ERROR;

    // Disable alpha blending.
    glDisable(GL_BLEND); VERIFY_NO_ERROR;
}
