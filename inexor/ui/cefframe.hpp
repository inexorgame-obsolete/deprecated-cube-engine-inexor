#ifndef _CEF_CONSOLE_H
#define _CEF_CONSOLE_H

#include "include/cef_app.h"

#include "inexor/ui/cefcontextprovider.hpp"
#include "inexor/ui/ceflayerprovider.hpp"

extern void logoutf(const char *fmt, ...);

class InexorCefFrame : public InexorCefContextProvider,
                       public InexorCefLayerProvider
{

    public:
        std::string url = "http://localhost:48702/main.html";
        std::string name = "";

        InexorCefFrame() {};
        InexorCefFrame(std::string &name) : name(name) {}
        InexorCefFrame(std::string &name, std::string &url)
          : url(url), name(name) {}

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return name; };

        // InexorCefLayerProvider
        std::string GetLayerName() { return name; };
        std::string GetUrl() { return url; };
        bool GetVisibility() { return true; };
        bool GetAcceptingInput() { return true; };
        bool GetFocus() { return true; };

        void SetUrl(std::string &u2) { url = u2;};
        std::string GetName() { return name; }
        void SetName(std::string &n2) { name = n2; }

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefFrame);
};

#endif  // _CEF_FRAME_H
