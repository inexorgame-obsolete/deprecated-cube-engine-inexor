#ifndef _CEF_LAYER_H
#define _CEF_LAYER_H

#include <list>

#include "include/cef_app.h"

#include "cefbrowsersettings.h"
#include "cefclienthandler.h"
#include "cefwindowinfo.h"

class InexorCefLayer
{

    public:
        InexorCefLayer(std::string name, int x, int y, int width, int height, std::string url);

        std::string GetName() { return name; }
        std::string GetUrl() { return url; }
        InexorCefWindowInfo GetWindowInfo() { return window_info; }
        CefBrowserSettings GetBrowserSettings() { return browser_settings; };
        CefRefPtr<InexorCefClientHandler> GetClientHandler() { return client_handler; };
        CefRefPtr<InexorCefRenderHandler> GetRenderHandler() { return render_handler; };
        CefRefPtr<CefBrowser> GetBrowser() { return browser; };

        bool IsVisible() { return is_visible; };
        void SetVisibility(bool is_visible);

        bool HasFocus() { return has_focus; };
        void SetFocus(bool has_focus);

        bool IsAcceptingInput() { return is_accepting_input; };
        void SetIsAcceptingInput(bool is_accepting_input);


	private:
	    std::string name;
	    bool is_visible;
	    bool is_accepting_input;
	    bool has_focus;
	    std::string url;

        InexorCefWindowInfo window_info;
        InexorCefBrowserSettings browser_settings;
        CefRefPtr<InexorCefClientHandler> client_handler;
        CefRefPtr<InexorCefRenderHandler> render_handler;
        CefRefPtr<CefBrowser> browser;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefLayer);

};

class InexorCefLayerManager
{

    public:
        InexorCefLayerManager(int width, int height);

        // Rendering
        void Render();
        void RenderLayer(std::string name);
        void SetScreenSize(int width, int height);

        // Layers
        InexorCefLayer* CreateLayer(std::string name, std::string url);
        InexorCefLayer* CreateLayer(std::string name, int x, int y, int width, int height, std::string url);
        InexorCefLayer* GetLayer(std::string name);
        void ShowLayer(std::string name);
        void HideLayer(std::string name);
        // void BringLayerToFront(std::string name);
        // void BringLayerToBack(std::string name);
        // void MoveLayerUp(std::string name);
        // void MoveLayerBack(std::string name);

        // Input events
        void SendKeyEvent(CefKeyEvent event);
        void SendMouseClickEvent(const CefMouseEvent& event, CefBrowserHost::MouseButtonType type, bool mouseUp, int clickCount);
        void SendMouseMoveEvent(const CefMouseEvent& event, bool mouseLeave);
        void SendMouseWheelEvent(const CefMouseEvent& event, int deltaX, int deltaY);

    private:
        std::list<InexorCefLayer*> layers;

        int width;
        int height;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefLayerManager);

};

#endif  // _CEF_LAYER_H
