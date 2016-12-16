#include <iostream>

#include "inexor/ui/context/InexorContextProvider.hpp"

namespace inexor {
namespace ui {
namespace context {

CefRefPtr<CefV8Value> InexorContextProvider::GetContext()
{
    if (!context.get())
    {
        // This has to be happen when the context is initialized
        spdlog::get("global")->debug("init: cef: context \"{}\"", GetContextName());
        InitializeSubContexts();
        InitializeContext();
    }
    return context;
}

void InexorContextProvider::InitializeSubContexts()
{
    for(std::list<InexorContextProvider*>::iterator it = sub_contexts.begin(); it != sub_contexts.end(); ++it)
    {
        CreateSubContext(*it);
    }
}

void InexorContextProvider::AddSubContext(InexorContextProvider* sub_context)
{
    sub_contexts.push_back(sub_context);
}

void InexorContextProvider::CreateFunction(const CefString& name)
{
    context->SetValue(name, CefV8Value::CreateFunction(name, this), V8_PROPERTY_ATTRIBUTE_READONLY);
}

void InexorContextProvider::CreateFunction(const CefString& name, CefRefPtr<CefV8Handler> handler)
{
    context->SetValue(name, CefV8Value::CreateFunction(name, handler), V8_PROPERTY_ATTRIBUTE_READONLY);
}

void InexorContextProvider::CreateVariable(const CefString& name, bool readonly)
{
    if (readonly)
        context->SetValue(name, V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    else
        context->SetValue(name, V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
}

void InexorContextProvider::CreateSubContext(CefRefPtr<InexorContextProvider> sub_context)
{
    context->SetValue(sub_context->GetContextName(), sub_context->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}

}
}
}
