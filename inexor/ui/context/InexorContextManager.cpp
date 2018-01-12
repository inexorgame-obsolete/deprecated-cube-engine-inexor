#include "include/base/cef_logging.h"     // for COMPACT_GOOGLE_LOG_DCHECK
#include "include/wrapper/cef_helpers.h"  // for CEF_REQUIRE_RENDERER_THREAD
#include "inexor/ui/context/InexorContextManager.hpp"

namespace inexor {
namespace ui {
namespace context {

void InexorContextManager::InitializeContext()
{
}

bool InexorContextManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return true;
}

bool InexorContextManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return true;
}


bool InexorContextManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
   	return false;
}

}
}
}
