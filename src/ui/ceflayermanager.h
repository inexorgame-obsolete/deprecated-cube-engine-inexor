#ifndef _CEF_LAYER_MANAGER_H
#define _CEF_LAYER_MANAGER_H

#include <list>

#include "include/cef_app.h"

#include "cefcontextprovider.h"
#include "ceflayer.h"
#include "ceflayerprovider.h"

class InexorCefLayerManager : public InexorCefContextProvider
{

    public:
        InexorCefLayerManager(int width, int height);

        // Rendering
        void Render();
        void RenderLayer(std::string name);
        void SetScreenSize(int width, int height);

        // Layers
        void InitializeLayers();
        void DestroyLayers();
        void AddLayerProvider(InexorCefLayerProvider* layer_provider);

        InexorCefLayer* CreateLayer(std::string name, std::string url);
        InexorCefLayer* CreateLayer(std::string name, int x, int y, int width, int height, std::string url);
        InexorCefLayer* GetLayer(std::string name);
        std::list<std::string> GetLayers();
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

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "layer"; };

    private:
        std::list<InexorCefLayer*> layers;
        std::list<InexorCefLayerProvider*> layer_providers;

        int width;
        int height;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefLayerManager);

};

#endif  // _CEF_LAYER_MANAGER_H
