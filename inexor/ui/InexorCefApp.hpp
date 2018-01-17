#pragma once

#include <list>
#include <string>                                      // for string

#include "SDL_events.h"                                // for SDL_Event
#include "include/cef_app.h"                           // for CefApp
#include "include/cef_base.h"                          // for CefRefPtr, IMP...
#include "include/cef_browser_process_handler.h"       // for CefBrowserProc...
#include "inexor/ui/context/InexorContextManager.hpp"  // for InexorContextM...
#include "inexor/ui/input/InexorKeyboardManager.hpp"   // for InexorKeyboard...
#include "inexor/ui/input/InexorMouseManager.hpp"      // for InexorMouseMan...
#include "inexor/ui/layer/InexorAppLayer.hpp"          // for InexorAppLayer
#include "inexor/ui/layer/InexorConsoleLayer.hpp"      // for InexorConsoleL...
#include "inexor/ui/layer/InexorHudLayer.hpp"          // for InexorHudLayer
#include "inexor/ui/layer/InexorLayerManager.hpp"      // for InexorLayerMan...

class CefBrowser;
class CefFrame;
class CefV8Context;

namespace inexor {
namespace ui {

class InexorCefApp : public CefApp,
                     public CefBrowserProcessHandler
{

    public:
        InexorCefApp(std::string instance_id, std::string host, std::string port, int width, int height);

        void Destroy();

        // Getters for handlers
        CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
        CefRefPtr<context::InexorContextManager> GetContextManager() { return context_manager; }
        CefRefPtr<input::InexorMouseManager> GetMouseManager() { return mouse_manager; }
        CefRefPtr<input::InexorKeyboardManager> GetKeyboardManager() { return keyboard_manager; }
        CefRefPtr<layer::InexorLayerManager> GetLayerManager() { return layer_manager; }
        CefRefPtr<layer::InexorHudLayer> GetHudLayer() { return hud_layer; }
        CefRefPtr<layer::InexorConsoleLayer> GetConsoleLayer() { return console_layer; }
        CefRefPtr<layer::InexorAppLayer> GetAppLayer() { return app_layer; }

        // Rendering / Window Management
        void SetScreenSize(int width, int height);

        // CefBrowserProcessHandler
        void OnContextInitialized() override;
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
        CefRefPtr<layer::InexorConsoleLayer> console_layer;
        CefRefPtr<layer::InexorAppLayer> app_layer;

        void InitHudLayer(std::string instance_id, std::string host, std::string port);
        void InitConsoleLayer(std::string instance_id, std::string host, std::string port);
        void InitAppLayer(std::string instance_id, std::string host, std::string port);

        IMPLEMENT_REFCOUNTING(InexorCefApp);
};
extern CefRefPtr<InexorCefApp> cef_app;

}
}
