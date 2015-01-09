#ifndef _CEF_CONTEXT_PROVIDER_H
#define _CEF_CONTEXT_PROVIDER_H

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

class InexorCefContextProvider : public CefV8Handler,
                                 public CefV8Accessor
{
    public:
        // Initializes the context (or subcontext of a context) as a V8 object
        virtual void InitializeContext() = 0;

        // Returns the common context as a V8 object
        CefRefPtr<CefV8Value> GetContext();

        // Helper Methods for reducing verbose code
        void AddFunction(const CefString& name, CefRefPtr<CefV8Handler> handler);
        void AddVariable(const CefString& name, bool readonly = false);
        void AddSubContext(const CefString& name, CefRefPtr<InexorCefContextProvider> subcontext);

    protected:
        CefRefPtr<CefV8Value> context;

};

#endif  // _CEF_CONTEXT_PROVIDER_H
