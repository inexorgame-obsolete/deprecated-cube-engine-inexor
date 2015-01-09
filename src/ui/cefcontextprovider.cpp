#include "cefcontextprovider.h"

CefRefPtr<CefV8Value> InexorCefContextProvider::GetContext()
{
    if (!context.get())
    {
        // This has to be happen when the context is initialized
        InitializeContext();
    }
    return context;
}

void InexorCefContextProvider::AddFunction(const CefString& name, CefRefPtr<CefV8Handler> handler)
{
    context->SetValue(name, CefV8Value::CreateFunction(name, handler), V8_PROPERTY_ATTRIBUTE_READONLY);
}

void InexorCefContextProvider::AddVariable(const CefString& name, bool readonly)
{
    if (readonly)
        context->SetValue(name, V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    else
        context->SetValue(name, V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
}

void InexorCefContextProvider::AddSubContext(const CefString& name, CefRefPtr<InexorCefContextProvider> subcontext)
{
    context->SetValue(name, subcontext->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}
