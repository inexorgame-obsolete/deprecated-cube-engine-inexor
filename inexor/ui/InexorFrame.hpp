#ifndef INEXOR_UI_INEXOR_FRAME_HEADER
#define INEXOR_UI_INEXOR_FRAME_HEADER

#include "include/cef_app.h"

#include "inexor/ui/InexorContextProvider.hpp"
#include "inexor/ui/InexorLayerProvider.hpp"

class InexorFrame : public InexorContextProvider,
                    public InexorLayerProvider
{

    public:
        std::string url = "http://localhost:48702/";
        std::string name = "";

        InexorFrame() {};
        InexorFrame(std::string &name) : name(name) {}
        InexorFrame(std::string &name, std::string &url)
          : url(url), name(name) {}

        // InexorContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return name; };

        // InexorLayerProvider
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
        IMPLEMENT_REFCOUNTING(InexorFrame);
};

#endif  // _CEF_FRAME_H
