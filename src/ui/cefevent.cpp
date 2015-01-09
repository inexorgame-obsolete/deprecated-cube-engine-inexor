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
