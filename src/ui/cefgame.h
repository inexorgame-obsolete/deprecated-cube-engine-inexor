#ifndef _CEF_GAME_MANAGER_H
#define _CEF_GAME_MANAGER_H

#include "include/cef_app.h"
#include "include/cef_runnable.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

#include "cefcontextprovider.h"

namespace game
{
    extern const char* getclientname(int cn);
}

class InexorCefGameManager : public InexorCefContextProvider
{

    public:
        InexorCefGameManager() {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "game"; };

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorCefGameManager);

};

#endif  // _CEF_GAME_MANAGER_H
