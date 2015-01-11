#include "cefgame.h"

void InexorCefGameManager::InitializeContext()
{
    CreateFunction("getClientName", this);
}

bool InexorCefGameManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "getClientName") {
        if (arguments.size() == 1 && arguments[0]->IsInt()) {
            retval = CefV8Value::CreateString(game::getclientname(arguments[0]->GetIntValue()));
            return true;
        }
    }
    return false;
}

bool InexorCefGameManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorCefGameManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}
