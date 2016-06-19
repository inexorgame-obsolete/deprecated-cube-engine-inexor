#include <iostream>

#include "inexor/ui/InexorFrame.hpp"

void InexorFrame::InitializeContext()
{
    CreateFunction("log", this);
}

bool InexorFrame::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "log") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            spdlog::get("global")->info() << arguments[0]->GetStringValue().ToString();
            return true;
        }
    }
    return false;
}

bool InexorFrame::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorFrame::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

