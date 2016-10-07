#include "inexor/ui/InexorContextManager.hpp"

void InexorContextManager::InitializeContext()
{
    // Global Methods
//    CreateFunction("quit", this);
//    CreateFunction("stealFocus", this);
//    CreateFunction("releaseFocus", this);
//
//    // Variables
//    CreateVariable("curtime", true);
//    CreateVariable("lastmillis", true);
//    CreateVariable("elapsedtime", true);
//    CreateVariable("totalmillis", true);
//    CreateVariable("thirdperson");
//    CreateVariable("fullscreen");
//    CreateVariable("scr_w");
//    CreateVariable("scr_h");
//    CreateVariable("vsync");
//    CreateVariable("fps", true);
//    CreateVariable("name");
//    CreateVariable("cef_focus", cef_focus);
}

bool InexorContextManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
//    if (name == "quit")
//    	//quit();
//    else
//    if (name == "stealFocus") {
//        std::cerr << "(c++) stealFocus()\n";
//        cef_focus = true;
//    } else if (name == "releaseFocus") {
//        std::cerr << "(c++) releaseFocus()\n";
//        cef_focus = false;
//    } else {
//        return false;
//    }
    return true;
}

bool InexorContextManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
//    if (name == "curtime")
//        return_value = CefV8Value::CreateInt(curtime);
//    else if (name == "lastmillis")
//        return_value = CefV8Value::CreateInt(lastmillis);
//    else if (name == "elapsedtime")
//        return_value = CefV8Value::CreateInt(elapsedtime);
//    else if (name == "totalmillis")
//        return_value = CefV8Value::CreateInt(totalmillis);
//    else if (name == "totalsecs")
//        return_value = CefV8Value::CreateUInt(totalsecs);
//    else if (name == "thirdperson")
//        return_value = CefV8Value::CreateInt(thirdperson);
//    else if (name == "fullscreen")
//        return_value = CefV8Value::CreateInt(fullscreen);
//    else if (name == "scr_w")
//        return_value = CefV8Value::CreateInt(scr_w);
//    else if (name == "scr_h")
//        return_value = CefV8Value::CreateInt(scr_h);
//    else if (name == "vsync")
//        return_value = CefV8Value::CreateInt(vsync);
//    else if (name == "fps") {
//        int fps, bestdiff, worstdiff;
//        getfps(fps, bestdiff, worstdiff);
//        return_value = CefV8Value::CreateInt(fps);
//    }
//    else if (name == "name")
//        return_value = CefV8Value::CreateString(game::player1->name);
//    else if (name == "cef_focus")
//        return_value = CefV8Value::CreateBool(cef_focus);
//    else
//        return false;
    return true;
}


bool InexorContextManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
//    if (value->IsInt()) {
//        if (name == "thirdperson")
//            thirdperson = value->GetIntValue();
//        else if (name == "fullscreen")
//            fullscreen = value->GetIntValue();
//        else if (name == "scr_w")
//            scr_w = value->GetIntValue();
//        else if (name == "scr_h")
//            scr_h = value->GetIntValue();
//        else if (name == "vsync")
//            vsync = value->GetIntValue();
//        else if (name == "name")
//            game::switchname(value->GetStringValue().ToString().c_str());
//        else
//            return false;
//        return true;
//    }
   	return false;
}
