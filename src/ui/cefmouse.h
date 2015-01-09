#ifndef _CEF_MOUSE_H
#define _CEF_MOUSE_H

#include "engine.h"

#include "include/cef_app.h"

#include "cefcontextprovider.h"

#define GL_ONE 1
extern bool settexture(const char *name, int clamp);

class InexorCefMouseManager : public InexorCefContextProvider
{

    public:
        InexorCefMouseManager() : x(0), y(0), max_x(0), max_y(0), size(0.03f), visible(false) {
            SetTexture("media/interface/guicursor.png", GL_ONE);
        };
        InexorCefMouseManager(int width, int height) : x(0), y(0), size(0.03f), visible(true) {
            SetTexture("media/interface/guicursor.png", GL_ONE);
            SetMax(width, height);
        };

        void Update(const CefMouseEvent& event);

        void SetMax(int width, int height);

        void SetTexture(std::string filename, int blendFunction);

        bool IsVisible() { return visible; };

        void Hide() { visible = false; };

        void Show() { visible = true; };

        void Render();

        // InexorCefContextProvider
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

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefMouseManager);

};

#endif  // _CEF_MOUSE_H
