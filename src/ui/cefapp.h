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
#include "cefeventmanager.h"
#include "ceflayermanager.h"
#include "cefmenu.h"
#include "cefmouse.h"
#include "cefwindowinfo.h"

class InexorCefApp : public CefApp,
                     public CefBrowserProcessHandler,
                     public CefRenderProcessHandler
{

    public:
        InexorCefApp(int width, int height);

        // Getters for handlers
        CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() { return this; }
        CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() { return this; }
        CefRefPtr<InexorCefContextManager> GetContextManager() { return context_manager; }
        CefRefPtr<InexorCefLayerManager> GetLayerManager() { return layer_manager; }
        CefRefPtr<InexorCefEventManager> GetEventManager() { return event_manager; }
        CefRefPtr<InexorCefMouseManager> GetMouseManager() { return mouse_manager; }
        CefRefPtr<InexorCefConsole> GetConsole() { return console; }
        CefRefPtr<InexorCefMenu> GetMenu() { return menu; }

        // Rendering / Window Management
        void Render();
        void SetScreenSize(int width, int height);

        // Input events
        void SendKeyEvent(CefKeyEvent event);
        void SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount);
        void SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave);
        void SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY);

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

        // Global mouse
        CefRefPtr<InexorCefMouseManager> mouse_manager;

        // Console
        CefRefPtr<InexorCefConsole> console;

        // Menu
        CefRefPtr<InexorCefMenu> menu;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefApp);

};

#endif  // _CEF_APP_H
