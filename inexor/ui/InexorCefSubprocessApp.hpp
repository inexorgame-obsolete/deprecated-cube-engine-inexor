#ifndef INEXOR_UI_INEXOR_CEF_SUB_APP_HEADER
#define INEXOR_UI_INEXOR_CEF_SUB_APP_HEADER

#include <string>
#include <list>
#include <map>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"

#include "inexor/util/Logging.hpp"

namespace inexor {
namespace ui {

class InexorCefSubprocessApp : public CefApp,
                               public CefRenderProcessHandler,
                               public CefV8Handler,
                               public CefV8Accessor
{

    public:
        InexorCefSubprocessApp();

        // Getters for handlers
        CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() { return this; }

        // CefV8Handler
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);

        // CefV8Accessor
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);

        // CefRenderProcessHandler
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

        // Event Handling
        bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message);
        void FireUiEvent(std::string name, const CefV8ValueList& arguments);


        // void OnRenderThreadCreated(CefRefPtr<CefApp> app, CefRefPtr extra_info) {
        //      std::cerr << "OnRenderThreadCreated()\n";
        // }
        // void OnWebKitInitialized(CefRefPtr app) {
        //     std::cerr << "OnRenderThreadCreated()\n";
        // }
        // void OnBrowserCreated(CefRefPtr app, CefRefPtr browser) {}
        // void OnBrowserDestroyed(CefRefPtr app, CefRefPtr browser) {}
        // bool OnBeforeNavigation(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr request, cef_navigation_type_t navigation_type, bool is_redirect) { return false; }
        // void OnContextReleased(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr context) {}
        // void OnUncaughtException(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr context, CefRefPtr exception, CefRefPtr stackTrace) {}
        // void OnFocusedNodeChanged(CefRefPtr app, CefRefPtr browser, CefRefPtr frame, CefRefPtr node) {}

	private:

        std::string _blah;

        std::map<CefRefPtr<CefV8Value>, CefRefPtr<CefV8Context> > event_handlers;

        IMPLEMENT_REFCOUNTING(InexorCefSubprocessApp);
};

}
}

#endif
