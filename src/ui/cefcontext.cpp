#include "cefcontext.h"

InexorCefContext::InexorCefContext(CefRefPtr<InexorCefLayerManager> layer_manager, CefRefPtr<InexorCefEventManager> event_manager, CefRefPtr<InexorCefMouseManager> mouse_manager) {
    this->layer_manager = layer_manager;
    this->event_manager = event_manager;
    this->mouse_manager = mouse_manager;
}

void InexorCefContext::InitializeContext()
{
    context = CefV8Value::CreateObject(this);
    AddSubContext("layer", layer_manager);
    AddSubContext("event", event_manager);

    // Global Methods
    AddFunction("logoutf", this);
    AddFunction("quit", this);

    // Variables
    AddVariable("curtime", true);
    AddVariable("lastmillis", true);
    AddVariable("elapsedtime", true);
    AddVariable("totalmillis", true);
    AddVariable("thirdperson");
    AddVariable("fullscreen");
    AddVariable("scr_w");
    AddVariable("scr_h");
    AddVariable("vsync");
    AddVariable("fps", true);
    AddVariable("name");
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
    else if (name == "fps") {
        int fps, bestdiff, worstdiff;
        getfps(fps, bestdiff, worstdiff);
        return_value = CefV8Value::CreateInt(fps);
    }
    else if (name == "name")
        return_value = CefV8Value::CreateString(game::player1->name);
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
