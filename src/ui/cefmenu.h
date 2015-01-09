#ifndef _CEF_MENU_H
#define _CEF_MENU_H

#include "include/cef_app.h"

#include "cefcontextprovider.h"
#include "ceflayerprovider.h"

extern void logoutf(const char *fmt, ...);

class InexorCefMenu : public InexorCefContextProvider,
                         public InexorCefLayerProvider
{

    public:
        InexorCefMenu() {};
        ~InexorCefMenu() {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "menu"; };

        // InexorCefLayerProvider
        std::string GetLayerName() { return "menu"; };
        std::string GetUrl() { return "http://gitdemo.inexor.org/menuprototype/"; };
        bool GetVisibility() { return false; };
        bool GetAcceptingInput() { return false; };
        bool GetFocus() { return false; };

    private:
        //


        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefMenu);

};

#endif  // _CEF_MENU_H
