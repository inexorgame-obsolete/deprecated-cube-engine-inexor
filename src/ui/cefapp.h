#ifndef _CEF_APP_H
#define _CEF_APP_H

#include <string>
#include <list>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_process_handler.h"

#include "cefbrowsersettings.h"
#include "cefclienthandler.h"
#include "cefconsole.h"
#include "cefcontextmanager.h"
#include "cefdebug.h"
#include "cefdebugoverlay.h"
#include "cefeventmanager.h"
#include "cefkeyboard.h"
#include "ceflayermanager.h"
#include "cefnetwork.h"
#include "cefmenu.h"
#include "cefmouse.h"
#include "cefwindowinfo.h"

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
        CefRefPtr<InexorCefEventManager> GetEventManager() { return event_manager; }
        CefRefPtr<InexorCefMouseManager> GetMouseManager() { return mouse_manager; }
        CefRefPtr<InexorCefKeyboardManager> GetKeyboardManager() { return keyboard_manager; }
        CefRefPtr<InexorCefNetworkManager> GetNetworkManager() { return network_manager; }
        CefRefPtr<InexorCefConsole> GetConsole() { return console; }
        CefRefPtr<InexorCefMenu> GetMenu() { return menu; }
        CefRefPtr<InexorCefDebugOverlay> GetDebugOverlay() { return debug_overlay; }

        // Rendering / Window Management
        void Render();
        void SetScreenSize(int width, int height);

        // CefBrowserProcessHandler
        void OnContextInitialized();

        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

	private:

        // JavaScript Context Manager
        CefRefPtr<InexorCefContextManager> context_manager;

        // Layer Manager
        CefRefPtr<InexorCefLayerManager> layer_manager;

        // Event Manager
        CefRefPtr<InexorCefEventManager> event_manager;

        // Mouse Manager
        CefRefPtr<InexorCefMouseManager> mouse_manager;

        // Keyboard Manager
        CefRefPtr<InexorCefKeyboardManager> keyboard_manager;

        // Network Manager
        CefRefPtr<InexorCefNetworkManager> network_manager;

        // Console
        CefRefPtr<InexorCefConsole> console;

        // Menu
        CefRefPtr<InexorCefMenu> menu;

        // Debug Overlay
        CefRefPtr<InexorCefDebugOverlay> debug_overlay;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefApp);

};

#endif  // _CEF_APP_H
