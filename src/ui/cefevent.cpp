#include "cefevent.h"

void InexorCefEvent::ExecuteCallback(CefRefPtr<CefV8Value> callback_function, const CefV8ValueList& arguments)
{
    CEF_REQUIRE_RENDERER_THREAD();
    CefRefPtr<CefV8Value> ret_value = callback_function->ExecuteFunction(NULL, arguments);
    if (ret_value == NULL) {
        logoutf("  ==> Failed to fire event!");
    }
}

void InexorCefEvent::ConvertArgumentsAndExecuteCallbackWithContext(CefRefPtr<CefV8Value> callback_function, CefRefPtr<CefV8Context> callback_context, const InexorCefValueList& arguments)
{
    bool entered = false;
    if (!callback_context->InContext()) {
        callback_context->Enter();
        entered = true;
    }
    if (!callback_context->IsSame(CefV8Context::GetCurrentContext())) {
        logoutf("  ==> Not the same context!");
    }

    CefV8ValueList _arguments;
    for(std::list<CefRefPtr<InexorCefValue> >::const_iterator it = arguments.begin(); it != arguments.end(); ++it) {
        CefRefPtr<InexorCefValue> argument = (*it);
        _arguments.push_back(argument->GetValue());
    }

    ExecuteCallback(callback_function, _arguments);
    if (entered) {
        callback_context->Exit();
    }
}

void InexorCefEvent::ExecuteCallbackWithContext(CefRefPtr<CefV8Value> callback_function, CefRefPtr<CefV8Context> callback_context, const CefV8ValueList& arguments)
{
    CEF_REQUIRE_RENDERER_THREAD();
    CefRefPtr<CefV8Value> ret_value = callback_function->ExecuteFunctionWithContext(callback_context, NULL, arguments);
    if (ret_value == NULL) {
        logoutf("  ==> Failed to fire event!");
    }
}

void InexorCefEvent::FireEventWithContext(const InexorCefValueList& arguments)
{
    logoutf("Fired event: %s", name.ToString().c_str());
    for(std::list<InexorCefCallback*>::iterator it = callbacks.begin(); it != callbacks.end(); ++it)
    {
        InexorCefCallback *callback = (*it);
        CefRefPtr<CefV8Context> callback_context = callback->GetCallbackContext();
        CefRefPtr<CefV8Value> callback_function = callback->GetCallbackFunction();
        if (callback_context.get()) {
            InexorCefEvent::ConvertArgumentsAndExecuteCallbackWithContext(callback_function, callback_context, arguments);
        }
    }
}

void InexorCefEvent::FireEvent(const CefV8ValueList& arguments)
{
    for(std::list<InexorCefCallback*>::iterator it = callbacks.begin(); it != callbacks.end(); ++it)
    {
        InexorCefCallback *callback = (*it);
        CefRefPtr<CefV8Context> callback_context = callback->GetCallbackContext();
        CefRefPtr<CefV8Value> callback_function = callback->GetCallbackFunction();
        if (callback_context.get()) {
            InexorCefEvent::ExecuteCallbackWithContext(callback_function, callback_context, arguments);
        }
    }
}

void InexorCefEventManager::InitializeContext()
{
    context = CefV8Value::CreateObject(this);
    AddFunction("subscribe", this);
    AddFunction("fire", this);
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
