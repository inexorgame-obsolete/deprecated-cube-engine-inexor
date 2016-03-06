#ifndef INEXOR_UI_INEXOR_CEF_APP_HEADER
#define INEXOR_UI_INEXOR_CEF_APP_HEADER

#include <string>
#include <list>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_process_handler.h"

#include "inexor/ui/InexorBrowserSettings.hpp"
#include "inexor/ui/InexorContextManager.hpp"
#include "inexor/ui/InexorKeyboardManager.hpp"
#include "inexor/ui/InexorLayerManager.hpp"
#include "inexor/ui/InexorMouseManager.hpp"
#include "inexor/ui/InexorUserInterface.hpp"
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
        CefRefPtr<InexorUserInterface> GetUserInterface() { return user_interface; }

        // Rendering / Window Management
        void SetScreenSize(int width, int height);

        // CefBrowserProcessHandler
        void OnContextInitialized();

        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

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
        CefRefPtr<InexorUserInterface> user_interface;

        IMPLEMENT_REFCOUNTING(InexorCefApp);
};

#endif
