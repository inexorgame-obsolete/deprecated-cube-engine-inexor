#pragma once

#include <list>
#include <string>                                       // for string

#include "include/cef_app.h"
#include "include/cef_base.h"                           // for CefString
#include "include/cef_render_process_handler.h"
#include "include/cef_v8.h"                             // for CefV8Value (p...
#include "include/wrapper/cef_helpers.h"
#include "inexor/network/SharedTree.hpp"
#include "inexor/network/SharedVar.hpp"                 // for SharedVar
#include "inexor/ui/context/InexorContextProvider.hpp"  // for InexorContext...

namespace inexor {
namespace rendering {
namespace screen {
    extern SharedVar<int> fullscreen, scr_w, scr_h, vsync;
}
}
}

namespace inexor {
namespace ui {
namespace context {

class InexorContextManager : public InexorContextProvider
{

    public:
        InexorContextManager() {};

        // InexorCefContextProvider
        void InitializeContext() override;
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception) override;
        std::string GetContextName() override { return "inexor"; };

	private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorContextManager);

};

}
}
}
