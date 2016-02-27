#ifndef INEXOR_UI_INEXOR_FRAME_HEADER
#define INEXOR_UI_INEXOR_FRAME_HEADER

#include "include/cef_app.h"

#include "inexor/ui/InexorContextProvider.hpp"
#include "inexor/ui/InexorLayerProvider.hpp"

class InexorUserInterface : public InexorContextProvider,
                            public AbstractInexorLayerProvider
{

    public:
        InexorUserInterface(std::string &name, std::string &url) : AbstractInexorLayerProvider(name, url), _name(name), _url(url) {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return _name; };

        void Reload() {
            std::string url = GetUrl();
            SetUrl(url);
        };

    private:
        std::string _name;
        std::string _url;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorUserInterface);
};

#endif
