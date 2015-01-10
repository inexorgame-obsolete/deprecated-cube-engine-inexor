#ifndef _CEF_NETWORK_MANAGER_H
#define _CEF_NETWORK_MANAGER_H

#include "engine.h"

#include "include/cef_app.h"
#include "include/cef_runnable.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

#include "cefcontextprovider.h"

extern char* connectname;
extern int connectport;

extern void connectserv(const char *servername, int serverport, const char *serverpassword);
extern void trydisconnect(bool local);

class InexorCefNetworkManager : public InexorCefContextProvider
{

    public:
        InexorCefNetworkManager() {};

        void Connect(std::string hostname, int port);
        void Disconnect();

        void LocalConnect();
        void LocalDisconnect();

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "network"; };

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefNetworkManager);

};

#endif  // _CEF_NETWORK_MANAGER_H
