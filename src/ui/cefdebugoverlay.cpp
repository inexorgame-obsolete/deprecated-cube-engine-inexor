#include "cefdebugoverlay.h"

void InexorCefDebugOverlay::InitializeContext()
{
    CreateFunction("show", this);
    CreateFunction("hide", this);
    CreateFunction("toggle", this);
    CreateVariable("visible", true);
}

bool InexorCefDebugOverlay::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "show") {
        Show();
        return true;
    } else if (name == "hide") {
        Hide();
        return true;
    } else if (name == "toggle") {
        Toggle();
        return true;
    }
    return false;
}

bool InexorCefDebugOverlay::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "visible") {
        return_value = CefV8Value::CreateBool(is_visible);
        return true;
    }
    return false;
}

bool InexorCefDebugOverlay::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

