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
    const char* getclientteam(int cn);
    int getclientmodel(int cn);
    const char *getclienticon(int cn);
    bool ismaster(int cn);
    bool isauth(int cn);
    bool isadmin(int cn);
    bool isspectator(int cn);
    bool isai(int cn, int type);

    void clearbans();
    void setteam(const char *arg1, const char *arg2);
    void kick(const char *victim, const char *reason);
    void authkick(const char *desc, const char *victim, const char *reason);
    void ignore(int cn);
    void unignore(int cn);
    bool isignored(int cn);
    void togglespectator(int val, const char *who);
}

class InexorCefGameManager : public InexorCefContextProvider
{

    public:
        InexorCefGameManager() {};

        CefRefPtr<CefV8Value> GetPlayer(int cn);
        void SetValue(CefRefPtr<CefV8Value> player, std::string key, CefRefPtr<CefV8Value> value);
        void UpdatePlayer(CefRefPtr<CefV8Value> player, int cn);
        void UpdatePlayer(CefRefPtr<CefV8Value> player);
        void UpdatePlayer(int cn);
        void UpdatePlayers();

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
