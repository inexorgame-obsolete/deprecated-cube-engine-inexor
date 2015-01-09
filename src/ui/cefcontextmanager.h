#ifndef _CEF_CONEXT_H
#define _CEF_CONEXT_H

#include <list>

#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"

#include "cefcontextbindings.h"
#include "cefcontextprovider.h"
#include "cefdebug.h"

class InexorCefContextManager : public InexorCefContextProvider
{

    public:
        InexorCefContextManager() {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "inexor"; };

	private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefContextManager);

};

#endif  // _CEF_CONEXT_H
