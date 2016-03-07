#include <iostream>

#include "inexor/ui/InexorUserInterface.hpp"

void InexorUserInterface::InitializeContext()
{
	CreateVariable("isVisible", false);
    CreateVariable("isAcceptingKeyInput", false);
    CreateVariable("isAcceptingMouseInput", false);
    CreateVariable("menuVisible", false);
    CreateVariable("menuState", false);
    CreateVariable("menuParentState", false);
}

bool InexorUserInterface::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorUserInterface::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "isVisible") {
        return_value = CefV8Value::CreateBool(is_visible);
        return true;
    } else if (name == "isAcceptingKeyInput") {
        return_value = CefV8Value::CreateBool(is_accepting_key_input);
        return true;
    } else if (name == "isAcceptingMouseInput") {
        return_value = CefV8Value::CreateBool(is_accepting_mouse_input);
        return true;
    } else if (name == "menuVisible") {
        return_value = CefV8Value::CreateBool(menu_visible);
        return true;
    } else if (name == "menuState") {
        return_value = CefV8Value::CreateString(menu_state);
        return true;
    } else if (name == "menuParentState") {
        return_value = CefV8Value::CreateString(menu_parent_state);
        return true;
    }
    return false;
}

bool InexorUserInterface::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "isVisible") {
        if (value->IsBool()) {
        	is_visible = value->GetBoolValue();
        } else {
            exception = "Invalid value type";
        }
        return true;
    } else if (name == "isAcceptingKeyInput") {
        if (value->IsBool()) {
        	is_accepting_key_input = value->GetBoolValue();
        } else {
            exception = "Invalid value type";
        }
        return true;
    } else if (name == "isAcceptingMouseInput") {
        if (value->IsBool()) {
        	is_accepting_mouse_input = value->GetBoolValue();
        } else {
            exception = "Invalid value type";
        }
        return true;
    } else if (name == "menuVisible") {
        if (value->IsBool()) {
        	menu_visible = value->GetBoolValue();
        } else {
            exception = "Invalid value type";
        }
        return true;
    } else if (name == "menuState") {
        if (value->IsString()) {
        	menu_state = value->GetStringValue();
        } else {
            exception = "Invalid value type";
        }
        return true;
    } else if (name == "menuParentState") {
        if (value->IsString()) {
        	menu_parent_state = value->GetStringValue();
        } else {
            exception = "Invalid value type";
        }
        return true;
    }
    return false;
}
