#include "cefdebug.h"

void cefdebug(std::string method_name, std::string message) {
    std::string thread;
    std::string context_in;
    std::string context_valid;
    if (CefCurrentlyOn(TID_RENDERER)) {
        thread = "TID_RENDERER";
    } else if (CefCurrentlyOn(TID_UI)) {
        thread = "TID_UI";
    } else if (CefCurrentlyOn(TID_FILE)) {
        thread = "TID_FILE";
    } else if (CefCurrentlyOn(TID_IO)) {
        thread = "TID_IO";
    } else {
        thread = "unknown";
    }
    CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
    if (context.get()) {
        if (context->InContext())
            context_in = "in context";
        else
            context_in = "not in context";
        if (context->IsValid())
            context_valid = "valid";
        else
            context_valid = "not valid";
    } else {
        context_in = "no context";
        context_valid = "";
    }
    logoutf("=== %s ===\n  Thread:    %s\n  Context:   %s, %s\n  Message:   %s", method_name.c_str(), thread.c_str(), context_in.c_str(), context_valid.c_str(), message.c_str());
}

void cefdebugargs(const CefV8ValueList& arguments) {
    std::string type;
    std::string value;
    int i = 0;
    logoutf("1");
    for(std::vector<CefRefPtr<CefV8Value> >::const_iterator it = arguments.begin(); it != arguments.end(); ++it)
    {
        logoutf("2");
        CefRefPtr<CefV8Value> argument = (*it);
        if (argument.get()) {
            logoutf("2.0");
            if (argument->IsBool()) {
                logoutf("2.1");
                type = "bool";
                if (argument.get()->GetBoolValue())
                    value = "true";
                else
                    value = "false";
            } else if (argument->IsInt()) {
                logoutf("2.2");
                type = "int";
                value = "";
            } else if (argument->IsString()) {
                logoutf("2.3");
                type = "string";
                value = "";
            } else if (argument->IsUInt()) {
                logoutf("2.4");
                type = "uint";
                value = "";
            } else if (argument->IsDouble()) {
                logoutf("2.5");
                type = "double";
                value = "";
            } else if (argument->IsObject()) {
                logoutf("2.6");
                type = "object";
                value = "";
            } else if (argument->IsFunction()) {
                logoutf("2.7");
                type = "function";
                value = "";
            } else if (argument->IsArray()) {
                logoutf("2.8");
                type = "array";
                value = "";
            } else if (argument->IsNull()) {
                logoutf("2.9");
                type = "null";
                value = "null";
            } else if (argument->IsUndefined()) {
                logoutf("2.10");
                type = "undefined";
                value = "";
            } else {
                type = "unknown";
                value = "";
            }
            logoutf("--- Argument %d ---\n  Type:  %s\n  Value: %s", i, type.c_str(), value.c_str());
        } else {
            logoutf("--- Argument %d not set! ---", i);
        }
        i++;
    }
}
