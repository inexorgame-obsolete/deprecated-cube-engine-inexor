#include "cefnetwork.h"

void InexorCefNetworkManager::Connect(std::string hostname, int port)
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &InexorCefNetworkManager::Connect, hostname, port));
    } else {
        connectserv(hostname.c_str(), port, "");
    }
}

void InexorCefNetworkManager::Disconnect()
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &InexorCefNetworkManager::Disconnect));
    } else {
        trydisconnect(false);
    }
}

void InexorCefNetworkManager::LocalConnect()
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &InexorCefNetworkManager::LocalConnect));
    } else {
        localconnect();
    }
}

void InexorCefNetworkManager::LocalDisconnect()
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &InexorCefNetworkManager::LocalDisconnect));
    } else {
        localdisconnect();
    }
}

void InexorCefNetworkManager::InitializeContext()
{
    CreateFunction("connect", this);
    CreateFunction("disconnect", this);
    CreateFunction("localconnect", this);
    CreateFunction("localdisconnect", this);
    CreateVariable("hostname", true);
    CreateVariable("port", true);
}

bool InexorCefNetworkManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "connect") {
        if (arguments.size() == 2 && arguments[0]->IsString() && arguments[1]->IsInt()) {
            Connect(arguments[0]->GetStringValue().ToString(), arguments[1]->GetIntValue());
            return true;
        }
    } else if (name == "disconnect") {
        Disconnect();
        return true;
    } else if (name == "localconnect") {
        LocalConnect();
        return true;
    } else if (name == "localdisconnect") {
        LocalDisconnect();
        return true;
    }
    return false;
}

bool InexorCefNetworkManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "hostname") {
        std::string hostname = connectname;
        return_value = CefV8Value::CreateString(hostname);
        return true;
    } else if (name == "port") {
        return_value = CefV8Value::CreateInt(connectport);
        return true;
    }
    return false;
}

bool InexorCefNetworkManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}
