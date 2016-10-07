#ifndef INEXOR_UI_INEXOR_MOUSE_MANAGER_HEADER
#define INEXOR_UI_INEXOR_MOUSE_MANAGER_HEADER

#include "inexor/engine/engine.hpp"

#include "include/cef_app.h"

#include "inexor/ui/InexorContextProvider.hpp"
#include "inexor/ui/InexorLayerManager.hpp"

#ifndef GL_ONE
#define GL_ONE 0x1
#endif

extern bool settexture(const char *name, int clamp);

class InexorMouseManager : public InexorContextProvider
{

    public:
        InexorMouseManager(CefRefPtr<InexorLayerManager> layer_manager) : x(0), y(0), max_x(0), max_y(0), size(0.03f), visible(false) {
            this->layer_manager = layer_manager;
            SetTexture("interface/cursor/default.png", GL_ONE);
        };
        InexorMouseManager(CefRefPtr<InexorLayerManager> layer_manager, int width, int height) : x(0), y(0), size(0.03f), visible(true) {
            this->layer_manager = layer_manager;
            SetTexture("interface/cursor/default.png", GL_ONE);
            SetMax(width, height);
        };

        void Update(const CefMouseEvent& event);

        void SetMax(int width, int height);

        void SetTexture(std::string filename, int blendFunction);

        bool IsVisible() { return visible; };

        void Hide() { visible = false; };

        void Show() { visible = true; };

        void Render();

        // SDL Events
        void SendMouseMoveEvent(SDL_Event event);
        void SendMouseClickEvent(SDL_Event event);
        void SendMouseWheelEvent(SDL_Event event);

        // InexorContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "mouse"; };

	private:
        int x;
        int y;
        int max_x;
        int max_y;
        float size;
        bool visible;
        int blendFunction;
        std::string texture;

        // Layer Manager
        CefRefPtr<InexorLayerManager> layer_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorMouseManager);

};

#endif
