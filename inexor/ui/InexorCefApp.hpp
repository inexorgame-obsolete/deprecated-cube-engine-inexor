#ifndef INEXOR_UI_INEXOR_CEF_APP_HEADER
#define INEXOR_UI_INEXOR_CEF_APP_HEADER

#include <string>
#include <list>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_process_handler.h"

#include "inexor/ui/InexorBrowserSettings.hpp"
#include "inexor/ui/InexorWindowInfo.hpp"
#include "inexor/ui/context/InexorContextManager.hpp"
#include "inexor/ui/input/InexorKeyboardManager.hpp"
#include "inexor/ui/input/InexorMouseManager.hpp"
#include "inexor/ui/layer/InexorLayerManager.hpp"
#include "inexor/ui/layer/InexorAppLayer.hpp"
#include "inexor/ui/layer/InexorHudLayer.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace ui {

class InexorCefApp : public CefApp,
                     public CefBrowserProcessHandler
{

    public:
        InexorCefApp(int width, int height);

        void Destroy();

        // Getters for handlers
        CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() { return this; }
        CefRefPtr<context::InexorContextManager> GetContextManager() { return context_manager; }
        CefRefPtr<input::InexorMouseManager> GetMouseManager() { return mouse_manager; }
        CefRefPtr<input::InexorKeyboardManager> GetKeyboardManager() { return keyboard_manager; }
        CefRefPtr<layer::InexorLayerManager> GetLayerManager() { return layer_manager; }
        CefRefPtr<layer::InexorHudLayer> GetHudLayer() { return hud_layer; }
        CefRefPtr<layer::InexorAppLayer> GetAppLayer() { return app_layer; }

        // Rendering / Window Management
        void SetScreenSize(int width, int height);

        // CefBrowserProcessHandler
        void OnContextInitialized();
        // void OnBeforeChildProcessLaunch(CefRefPtr app, CefRefPtr command_line) {}
        // void OnRenderProcessThreadCreated(CefRefPtr app, CefRefPtr extra_info) {}

        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

        /// Handle SDL events for CEF
        ///
        /// @return Whether this event was handled by CEF;
        ///     if false the event should be handled by
        ///     inexor
        bool HandleSdlEvent(SDL_Event &e);

	private:
        CefRefPtr<context::InexorContextManager> context_manager;
        CefRefPtr<input::InexorMouseManager> mouse_manager;
        CefRefPtr<input::InexorKeyboardManager> keyboard_manager;
        CefRefPtr<layer::InexorLayerManager> layer_manager;
        CefRefPtr<layer::InexorHudLayer> hud_layer;
        CefRefPtr<layer::InexorAppLayer> app_layer;

        void InitHudLayer();
        void InitAppLayer();

        IMPLEMENT_REFCOUNTING(InexorCefApp);
};

}
}

#endif
