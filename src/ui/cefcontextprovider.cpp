#include "cefcontextprovider.h"

CefRefPtr<CefV8Value> InexorCefContextProvider::GetContext()
{
    if (!context.get())
    {
        // This has to be happen when the context is initialized
        logoutf("init: cef: context \"%s\"", GetContextName().c_str());
        context = CefV8Value::CreateObject(this);
        InitializeSubContexts();
        InitializeContext();
    }
    return context;
}

void InexorCefContextProvider::InitializeSubContexts()
{
    for(std::list<InexorCefContextProvider*>::iterator it = sub_contexts.begin(); it != sub_contexts.end(); ++it)
    {
        CreateSubContext(*it);
    }
}

void InexorCefContextProvider::AddSubContext(InexorCefContextProvider* sub_context)
{
    sub_contexts.push_back(sub_context);
}

void InexorCefContextProvider::CreateFunction(const CefString& name)
{
    context->SetValue(name, CefV8Value::CreateFunction(name, this), V8_PROPERTY_ATTRIBUTE_READONLY);
}

void InexorCefContextProvider::CreateFunction(const CefString& name, CefRefPtr<CefV8Handler> handler)
{
    context->SetValue(name, CefV8Value::CreateFunction(name, handler), V8_PROPERTY_ATTRIBUTE_READONLY);
}

void InexorCefContextProvider::CreateVariable(const CefString& name, bool readonly)
{
    if (readonly)
        context->SetValue(name, V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    else
        context->SetValue(name, V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
}

void InexorCefContextProvider::CreateSubContext(CefRefPtr<InexorCefContextProvider> sub_context)
{
    context->SetValue(sub_context->GetContextName(), sub_context->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}
