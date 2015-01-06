#ifndef _CEF_APP_H
#define _CEF_APP_H

#include <string>
#include <list>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "cefbrowsersettings.h"
#include "cefclienthandler.h"
#include "cefmouse.h"
#include "ceflayer.h"
#include "cefwindowinfo.h"

class InexorCefApp : public CefApp,
                     public CefBrowserProcessHandler
{

    public:
        InexorCefApp(int width, int height);
        InexorCefLayer* CreateLayer(std::string name, int x, int y, int width, int height, std::string url);
        InexorCefLayer* GetLayer(std::string name);
        void SetScreenSize(int width, int height);
        void RenderLayer(std::string name);
        void Render();
        // void BringToFront(std::string name);
        void SendKeyEvent(CefKeyEvent event);
        void SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount);
        void SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave);
        void SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY);

        // CefBrowserProcessHandler
        virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() { return this; }
        virtual void OnContextInitialized();

	private:
        std::list<InexorCefLayer*> layers;
        int width;
        int height;

        InexorCefMouse mouse;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefApp);

};

#endif  // _CEF_APP_H
