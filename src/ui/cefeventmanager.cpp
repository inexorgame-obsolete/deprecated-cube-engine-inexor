#include "cefeventmanager.h"

void InexorCefEventManager::InitializeContext()
{
    CreateFunction("subscribe", this);
    CreateFunction("fire", this);
    CreateFunction("list", this);
}

bool InexorCefEventManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "subscribe") {
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsFunction()) {
            SubscribeEvent(arguments[0]->GetStringValue(), new InexorCefCallback(arguments[1], CefV8Context::GetCurrentContext()));
            return true;
        }
    } else if (name == "fire") {
        if (arguments.size() >= 1 && arguments[0]->IsString()) {
            CefV8ValueList event_arguments(arguments.begin() + 1, arguments.end());
            FireEvent(arguments[0]->GetStringValue(), event_arguments);
            return true;
        }
    } else if (name == "list") {
        std::list<std::string> event_names;
        retval = CefV8Value::CreateArray(events.size());
        int i = 0;
        for(std::list<InexorCefEvent*>::iterator it = events.begin(); it != events.end(); ++it)
        {
            InexorCefEvent* event = (*it);
            retval->SetValue(i, CefV8Value::CreateString(event->GetName()));
            i++;
        }
        return true;
    }
    return false;
}

bool InexorCefEventManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorCefEventManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

InexorCefEvent* InexorCefEventManager::GetEvent(const CefString& name)
{
    for(std::list<InexorCefEvent*>::iterator it = events.begin(); it != events.end(); ++it)
    {
        InexorCefEvent* event = (*it);
        if (event->GetName() == name) {
            return event;
        }
    }
    InexorCefEvent* event = new InexorCefEvent(name);
    events.push_back(event);
    return event;
}

void InexorCefEventManager::SubscribeEvent(const CefString& name, InexorCefCallback *callback)
{
    if (!CefCurrentlyOn(TID_RENDERER)) {
        CefPostTask(TID_RENDERER, NewCefRunnableMethod(this, &InexorCefEventManager::SubscribeEvent, name, callback));
    } else {
        GetEvent(name)->AddCallback(callback);
    }
}

void InexorCefEventManager::FireEventWithContext(const CefString& name, const InexorCefValueList& arguments)
{
    if (!CefCurrentlyOn(TID_RENDERER)) {
        CefPostTask(TID_RENDERER, NewCefRunnableMethod(this, &InexorCefEventManager::FireEventWithContext, name, arguments));
    } else {
        GetEvent(name)->FireEventWithContext(arguments);
    }
}

void InexorCefEventManager::FireEvent(const CefString& name, const CefV8ValueList& arguments)
{
    GetEvent(name)->FireEvent(arguments);
}
