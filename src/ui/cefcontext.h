#ifndef _CEF_CONEXT_H
#define _CEF_CONEXT_H

#include <list>

#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"

#include "cefcontextbindings.h"
#include "cefdebug.h"
#include "cefevent.h"
#include "ceflayer.h"

class InexorCefContext : public CefV8Handler,
                         public CefV8Accessor
{

    public:
        InexorCefContext(CefRefPtr<InexorCefLayerManager> layer_manager);

        // Initializes the common context as a V8 object
        void InitializeContext();

        // Returns the common context as a V8 object
        CefRefPtr<CefV8Value> GetContext();

        // Returns the event manager.
        CefRefPtr<InexorCefEventManager> GetEventManager() { return event_manager; };

        // CefV8Handler
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);

        // CefV8Accessor
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);

	private:
	    CefRefPtr<CefV8Value> context;
	    CefRefPtr<InexorCefLayerManager> layer_manager;
	    CefRefPtr<InexorCefEventManager> event_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefContext);

};

#endif  // _CEF_CONEXT_H
