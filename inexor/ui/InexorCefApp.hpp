#ifndef INEXOR_UI_INEXOR_CEF_APP_HEADER
#define INEXOR_UI_INEXOR_CEF_APP_HEADER

#include <string>
#include <list>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_process_handler.h"

#include "inexor/ui/InexorBrowserSettings.hpp"
#include "inexor/ui/InexorFrame.hpp"
#include "inexor/ui/InexorContextManager.hpp"
#include "inexor/ui/InexorKeyboardManager.hpp"
#include "inexor/ui/InexorLayerManager.hpp"
#include "inexor/ui/InexorMouseManager.hpp"
#include "inexor/ui/InexorWindowInfo.hpp"

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
        CefRefPtr<InexorContextManager> GetContextManager() { return context_manager; }
        CefRefPtr<InexorLayerManager> GetLayerManager() { return layer_manager; }
        CefRefPtr<InexorMouseManager> GetMouseManager() { return mouse_manager; }
        CefRefPtr<InexorKeyboardManager> GetKeyboardManager() { return keyboard_manager; }
        CefRefPtr<InexorFrame> GetFrame() { return frame; }

        // Rendering / Window Management
        void Render();
        void SetScreenSize(int width, int height);

        // CefBrowserProcessHandler
        void OnContextInitialized();

        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

        /// Whether the keyboard/mouse events should go to
        /// CEF rather than the 3D renderer.
        bool HasFocus() {
            return context_manager->cef_focus;
        }

        /// Tell CEF that it should receive input events
        /// rather than inexor
        void SetFocus() {
          SetFocus(true);
        }

        /// Set, whether CEF should receive input events
        /// rather than inexor
        void SetFocus(bool cef_focus) {
            context_manager->cef_focus = cef_focus;
        }

        /// Handle SDL events for CEF
        ///
        /// @return Whether this event was handled by CEF;
        ///     if false the event should be handled by
        ///     inexor
        bool HandleSdlEvent(SDL_Event event);

	private:
        CefRefPtr<InexorContextManager> context_manager;
        CefRefPtr<InexorLayerManager> layer_manager;
        CefRefPtr<InexorMouseManager> mouse_manager;
        CefRefPtr<InexorKeyboardManager> keyboard_manager;
        CefRefPtr<InexorFrame> frame;

        IMPLEMENT_REFCOUNTING(InexorCefApp);
};

#endif
