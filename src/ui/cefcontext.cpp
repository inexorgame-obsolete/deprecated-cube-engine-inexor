#include "cefcontext.h"

InexorCefContext::InexorCefContext(CefRefPtr<InexorCefLayerManager> layer_manager) {
    this->event_manager = new InexorCefEventManager();
    this->layer_manager = layer_manager;
}

CefRefPtr<CefV8Value> InexorCefContext::GetContext()
{
    // cefdebug("InexorCefContext::GetContext", "");

    if (!context.get())
    {
        // This has to be happen when the context is initialized
    	InitializeContext();
    }
    return context;
}

void InexorCefContext::InitializeContext()
{
    // cefdebug("InexorCefContext::InitializeContext", "");

    context = CefV8Value::CreateObject(this);

    // Events
    context->SetValue("subscribe", CefV8Value::CreateFunction("subscribe", this), V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("fire", CefV8Value::CreateFunction("fire", this), V8_PROPERTY_ATTRIBUTE_NONE);

    // Methods
    context->SetValue("logoutf", CefV8Value::CreateFunction("logoutf", this), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("quit", CefV8Value::CreateFunction("quit", this), V8_PROPERTY_ATTRIBUTE_READONLY);

    // Layer Management Methods
    context->SetValue("createLayer", CefV8Value::CreateFunction("createLayer", this), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("showLayer", CefV8Value::CreateFunction("showLayer", this), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("hideLayer", CefV8Value::CreateFunction("hideLayer", this), V8_PROPERTY_ATTRIBUTE_READONLY);

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
    // cefdebug("InexorCefContext::Execute", name.ToString());

    CEF_REQUIRE_RENDERER_THREAD();

    if (name == "subscribe") {
        // JavaScript:
        //
        // inexor.subscribe("event_name", callback_function);
        //
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsFunction()) {
            event_manager->SubscribeEvent(arguments[0]->GetStringValue(), new InexorCefCallback(arguments[1], CefV8Context::GetCurrentContext()));
            return true;
        }
    } else if (name == "fire") {
        // JavaScript:
        //
        // inexor.fire("event_name", arg1, arg2, ...);
        //
        if (arguments.size() >= 1 && arguments[0]->IsString()) {
            CefV8ValueList event_arguments(arguments.begin() + 1, arguments.end());
            event_manager->FireEvent(arguments[0]->GetStringValue(), event_arguments);
        }
    } else if (name == "createLayer") {
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsString()) {
            layer_manager->CreateLayer(arguments[0]->GetStringValue().ToString(), arguments[1]->GetStringValue().ToString());
        }
    } else if (name == "showLayer") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            layer_manager->ShowLayer(arguments[0]->GetStringValue().ToString());
        }
    } else if (name == "hideLayer") {
        if (arguments.size() == 1 && arguments[0]->IsString()) {
            layer_manager->HideLayer(arguments[0]->GetStringValue().ToString());
        }
    } else if (name == "logoutf") {
        logoutf("logoutf lastmillis: %d", lastmillis);
        retval = CefV8Value::CreateUndefined();
        return true;
    } else if (name == "quit") {
    	quit();
    	return true;
    }
    return false;
}

bool InexorCefContext::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    // cefdebug("InexorCefContext::Get", name.ToString());

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
    // cefdebug("InexorCefContext::Set", name.ToString());

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
