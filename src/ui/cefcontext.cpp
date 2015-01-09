#include "cefcontext.h"

InexorCefContext::InexorCefContext(CefRefPtr<InexorCefLayerManager> layer_manager) {
    this->event_manager = new InexorCefEventManager();
    this->layer_manager = layer_manager;
}

CefRefPtr<CefV8Value> InexorCefContext::GetContext()
{
    if (!context.get())
    {
        // This has to be happen when the context is initialized
    	InitializeContext();
    }
    return context;
}

void InexorCefContext::InitializeContext()
{
    context = CefV8Value::CreateObject(this);

    // Global Methods
    context->SetValue("logoutf", CefV8Value::CreateFunction("logoutf", this), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("quit", CefV8Value::CreateFunction("quit", this), V8_PROPERTY_ATTRIBUTE_READONLY);

    // Event Manager
    context->SetValue("subscribe", CefV8Value::CreateFunction("subscribe", event_manager), V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("fire", CefV8Value::CreateFunction("fire", event_manager), V8_PROPERTY_ATTRIBUTE_NONE);

    // Layer Manager
    context->SetValue("createLayer", CefV8Value::CreateFunction("createLayer", layer_manager), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("showLayer", CefV8Value::CreateFunction("showLayer", layer_manager), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("hideLayer", CefV8Value::CreateFunction("hideLayer", layer_manager), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("getLayers", CefV8Value::CreateFunction("getLayers", layer_manager), V8_PROPERTY_ATTRIBUTE_READONLY);

    // Variables
    context->SetValue("curtime", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("lastmillis", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("elapsedtime", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("totalmillis", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("totalsecs", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("thirdperson", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("fullscreen", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("scr_w", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("scr_h", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("vsync", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("fps", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);

    // Variables Client
    context->SetValue("name", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
}

bool InexorCefContext::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "logoutf") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            logoutf("[%d] %s", lastmillis, arguments[0]->GetStringValue().ToString().c_str());
        }
        return true;
    } else if (name == "quit") {
    	quit();
    	return true;
    }
    return false;
}

bool InexorCefContext::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "curtime")
        return_value = CefV8Value::CreateInt(curtime);
    else if (name == "lastmillis")
        return_value = CefV8Value::CreateInt(lastmillis);
    else if (name == "elapsedtime")
        return_value = CefV8Value::CreateInt(elapsedtime);
    else if (name == "totalmillis")
        return_value = CefV8Value::CreateInt(totalmillis);
    else if (name == "totalsecs")
        return_value = CefV8Value::CreateUInt(totalsecs);
    else if (name == "thirdperson")
        return_value = CefV8Value::CreateInt(thirdperson);
    else if (name == "fullscreen")
        return_value = CefV8Value::CreateInt(fullscreen);
    else if (name == "scr_w")
        return_value = CefV8Value::CreateInt(scr_w);
    else if (name == "scr_h")
        return_value = CefV8Value::CreateInt(scr_h);
    else if (name == "vsync")
        return_value = CefV8Value::CreateInt(vsync);
    else if (name == "name")
        return_value = CefV8Value::CreateString(game::player1->name);
    else if (name == "fps") {
        int fps, bestdiff, worstdiff;
        getfps(fps, bestdiff, worstdiff);
        return_value = CefV8Value::CreateInt(fps);
    }
    else
        return false;
    return true;
}

bool InexorCefContext::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (value->IsInt()) {
        if (name == "thirdperson")
            thirdperson = value->GetIntValue();
        else if (name == "fullscreen")
            fullscreen = value->GetIntValue();
        else if (name == "scr_w")
            scr_w = value->GetIntValue();
        else if (name == "scr_h")
            scr_h = value->GetIntValue();
        else if (name == "vsync")
            vsync = value->GetIntValue();
        else if (name == "name")
            game::switchname(value->GetStringValue().ToString().c_str());
        else
            return false;
        return true;
    }
   	return false;
}
