#ifndef _CEF_DEBUGOVERLAY_H
#define _CEF_DEBUGOVERLAY_H

#include "include/cef_app.h"

#include "cefcontextprovider.h"
#include "ceflayerprovider.h"

extern void logoutf(const char *fmt, ...);

class InexorCefDebugOverlay : public InexorCefContextProvider,
                              public AbstractInexorCefLayerProvider
{

    public:
        InexorCefDebugOverlay() {};
        ~InexorCefDebugOverlay() {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "debugoverlay"; };

        // InexorCefLayerProvider
        std::string GetLayerName() { return "debugoverlay"; };
        std::string GetUrl() { return GetLocalUrl("/src/ui/web/debugoverlay.html"); };

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefDebugOverlay);

};

#endif  // _CEF_DEBUGOVERLAY_H
