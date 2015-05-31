#ifndef _CEF_APP_H
#define _CEF_APP_H

#include <string>
#include <list>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_process_handler.h"

#include "inexor/ui/cefbrowsersettings.h"
#include "inexor/ui/cefframe.h"
#include "inexor/ui/cefcontextmanager.h"
#include "inexor/ui/cefkeyboard.h"
#include "inexor/ui/ceflayermanager.h"
#include "inexor/ui/cefmouse.h"
#include "inexor/ui/cefwindowinfo.h"

class InexorCefApp : public CefApp,
                     public CefBrowserProcessHandler,
                     public CefRenderProcessHandler
{

    public:
        InexorCefApp(int width, int height);

        void Destroy();

        // Getters for handlers
        CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() { return this; }
        CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() { return this; }
        CefRefPtr<InexorCefContextManager> GetContextManager() { return context_manager; }
        CefRefPtr<InexorCefLayerManager> GetLayerManager() { return layer_manager; }
        CefRefPtr<InexorCefMouseManager> GetMouseManager() { return mouse_manager; }
        CefRefPtr<InexorCefKeyboardManager> GetKeyboardManager() { return keyboard_manager; }
        CefRefPtr<InexorCefFrame> GetFrame() { return frame; }

        // Rendering / Window Management
        void Render();
        void SetScreenSize(int width, int height);

        // CefBrowserProcessHandler
        void OnContextInitialized();

        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

        /// Whether the keyboard/mouse events should go to
        /// CEF rather than the 3D renderer.
        ///
        /// Getter and setter
        bool steal_input() {
            return frame->GetVisibility();
        }
        /// Handle SDL events for CEF
        ///
        /// @return Whether this event was handled by CEF;
        ///     if false the event should be handled by
        ///     inexor
        bool handle_sdl_event(SDL_Event ev);

	private:
        CefRefPtr<InexorCefContextManager> context_manager;
        CefRefPtr<InexorCefLayerManager> layer_manager;
        CefRefPtr<InexorCefMouseManager> mouse_manager;
        CefRefPtr<InexorCefKeyboardManager> keyboard_manager;
        CefRefPtr<InexorCefFrame> frame;

        IMPLEMENT_REFCOUNTING(InexorCefApp);
};

#endif  // _CEF_APP_H
