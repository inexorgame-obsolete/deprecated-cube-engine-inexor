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

// TODO: Remove CefRenderProcessHandler
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
        // void OnBeforeChildProcessLaunch(CefRefPtr app, CefRefPtr command_line) {}
        // void OnRenderProcessThreadCreated(CefRefPtr app, CefRefPtr extra_info) {}

        // TODO: remove (only available in the subprocess!)
        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);
        // void OnRenderThreadCreated(CefRefPtr<CefApp> app, CefRefPtr extra_info) {
        //      std::cerr << "OnRenderThreadCreated()\n";
        // }
        // void OnWebKitInitialized(CefRefPtr app) {
        //     std::cerr << "OnRenderThreadCreated()\n";
        // }
        // void OnBrowserCreated(CefRefPtr app, CefRefPtr browser) {}
        // void OnBrowserDestroyed(CefRefPtr app, CefRefPtr browser) {}
        // bool OnBeforeNavigation(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr request, cef_navigation_type_t navigation_type, bool is_redirect) { return false; }
        // void OnContextReleased(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr context) {}
        // void OnUncaughtException(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr context, CefRefPtr exception, CefRefPtr stackTrace) {}
        // void OnFocusedNodeChanged(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr node) {}

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
