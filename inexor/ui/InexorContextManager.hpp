#ifndef INEXOR_UI_INEXOR_CONTEXT_MANAGER_HEADER
#define INEXOR_UI_INEXOR_CONTEXT_MANAGER_HEADER

#include <list>

#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"

#include "inexor/ui/InexorContextProvider.hpp"

class InexorContextManager : public InexorContextProvider
{

    public:
        bool cef_focus = true;
        
        InexorContextManager() {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "inexor"; };

	private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorContextManager);

};

#endif
