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
#include "cefcontext.h"
#include "cefmouse.h"
#include "ceflayer.h"
#include "cefwindowinfo.h"

extern void logoutf(const char *fmt, ...);

class InexorCefApp : public CefApp,
                     public CefBrowserProcessHandler,
                     public CefRenderProcessHandler
{

    public:
        InexorCefApp(int width, int height);

        // Layers
        InexorCefLayer* CreateLayer(std::string name, int x, int y, int width, int height, std::string url);
        InexorCefLayer* GetLayer(std::string name);
        void SetScreenSize(int width, int height);
        void RenderLayer(std::string name);
        void Render();
        // void ShowLayer(std::string name);
        // void HideLayer(std::string name);
        // void BringLayerToFront(std::string name);
        // void BringLayerToBack(std::string name);
        // void MoveLayerUp(std::string name);
        // void MoveLayerBack(std::string name);

        // JavaScript Events
        // void FireEvent();
        // void SubscribeEvent();

        // Input events
        void SendKeyEvent(CefKeyEvent event);
        void SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount);
        void SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave);
        void SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY);

        // Getters for handlers
        CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() { return this; }
        CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() { return this; }

        // CefBrowserProcessHandler
        void OnContextInitialized();

        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

	private:
        std::list<InexorCefLayer*> layers;
        int width;
        int height;

        // Global mouse
        InexorCefMouse mouse;

        // Global context
        InexorCefContext context;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefApp);

};

#endif  // _CEF_APP_H
