#ifndef _CEF_CONSOLE_H
#define _CEF_CONSOLE_H

#include "include/cef_app.h"

#include "cefcontextprovider.h"
#include "ceflayerprovider.h"

extern void logoutf(const char *fmt, ...);

class InexorCefConsole : public InexorCefContextProvider,
                         public InexorCefLayerProvider
{

    public:
        InexorCefConsole() {};
        ~InexorCefConsole() {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "console"; };

        // InexorCefLayerProvider
        std::string GetLayerName() { return "console"; };
        std::string GetUrl() { return GetLocalUrl("/src/ui/web/console.html"); };
        bool GetVisibility() { return true; };
        bool GetAcceptingInput() { return true; };
        bool GetFocus() { return true; };

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefConsole);

};

#endif  // _CEF_CONSOLE_H
