#include <iostream>

#include "inexor/ui/InexorCefSubprocessApp.hpp"

namespace inexor {
namespace ui {

InexorCefSubprocessApp::InexorCefSubprocessApp()
    : _blah("Blah!")
{
}

void InexorCefSubprocessApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    std::cerr << " ====================== InexorCefApp::OnContextCreated() Injecting inexor object into javascript context\n";
    CefRefPtr<CefV8Value> window_object = context->GetGlobal();
    window_object->SetValue("registerEventHandler", CefV8Value::CreateFunction("registerEventHandler", this), V8_PROPERTY_ATTRIBUTE_NONE);

    std::string context_name = "blah";
    window_object->SetValue(context_name, CefV8Value::CreateString(_blah), V8_PROPERTY_ATTRIBUTE_NONE);
}

bool InexorCefSubprocessApp::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "registerEventHandler") {
        if (arguments.size() == 1 && arguments[0]->IsFunction()) {
            event_handlers.insert(std::pair<CefRefPtr<CefV8Value>, CefRefPtr<CefV8Context> >(arguments[0], CefV8Context::GetCurrentContext()));
            return true;
        }
    }
    return false;
}

bool InexorCefSubprocessApp::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "blah") {
        // Return the value.
        retval = CefV8Value::CreateString(_blah);
        return true;
    }
    return false;
}

bool InexorCefSubprocessApp::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    if (name == "blah") {
        if (value->IsString()) {
            _blah = value->GetStringValue();
        } else {
            exception = "Invalid value type";
        }
        return true;
    }
    return false;
}

void InexorCefSubprocessApp::FireUiEvent(std::string name, const CefV8ValueList& arguments_list)
{
    for (auto const &event_handler : event_handlers) {
        // Don't handle exceptions of the event handlers
        CefRefPtr<CefV8Value> retval = event_handler.first->ExecuteFunctionWithContext(event_handler.second, NULL, arguments_list);
    }
}

bool InexorCefSubprocessApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    const std::string& message_name = message->GetName();
    if (message_name == "user_interface") {
        CefRefPtr<CefListValue> arguments = message->GetArgumentList();
        CefV8ValueList arguments_list;
        for (int i = 0; i < arguments->GetSize(); i++) {
            CefValueType value_type = arguments->GetType(i);
            switch (value_type) {
                case VTYPE_BOOL:
                    arguments_list.push_back(CefV8Value::CreateBool(arguments->GetBool(i)));
                    break;
                case VTYPE_DOUBLE:
                    arguments_list.push_back(CefV8Value::CreateDouble(arguments->GetDouble(i)));
                    break;
                case VTYPE_INT:
                    arguments_list.push_back(CefV8Value::CreateInt(arguments->GetInt(i)));
                    break;
                case VTYPE_STRING:
                    arguments_list.push_back(CefV8Value::CreateString(arguments->GetString(i)));
                    break;
                default:
                    break;
            }

        }
        FireUiEvent(arguments->GetString(0), arguments_list);
        return true;
    }
    return false;
}

}
}
