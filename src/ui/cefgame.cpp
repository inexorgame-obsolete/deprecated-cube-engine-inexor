#include "cefgame.h"

void InexorCefGameManager::InitializeContext()
{
    CreateFunction("update", this);
    CreateFunction("getClientName", this);
    CreateFunction("getClientTeam", this);
    CreateFunction("getClientModel", this);
    CreateFunction("getClientIcon", this);

    bool ismaster(int cn);
    bool isauth(int cn);
    bool isadmin(int cn);
    bool isspectator(int cn);
    bool isai(int cn, int type);
    CefRefPtr<CefV8Value> players = CefV8Value::CreateArray(255);
    for (int cn = 0; cn < 255; cn++)
    {
        CefRefPtr<CefV8Value> player = CefV8Value::CreateObject(NULL);
        player->SetValue("cn", CefV8Value::CreateInt(cn), V8_PROPERTY_ATTRIBUTE_READONLY);
        players->SetValue(cn, player);
    }
    context->SetValue("players", players, V8_PROPERTY_ATTRIBUTE_READONLY);
}

CefRefPtr<CefV8Value> InexorCefGameManager::GetPlayer(int cn)
{
    return context->GetValue("players")->GetValue(cn);
}

void InexorCefGameManager::SetValue(CefRefPtr<CefV8Value> player, std::string key, CefRefPtr<CefV8Value> value)
{
    player->SetValue(key, value, V8_PROPERTY_ATTRIBUTE_READONLY);
}

void InexorCefGameManager::UpdatePlayer(CefRefPtr<CefV8Value> player, int cn)
{
    SetValue(player, "name", CefV8Value::CreateString(game::getclientname(cn)));
    SetValue(player, "team", CefV8Value::CreateString(game::getclientteam(cn)));
    SetValue(player, "model", CefV8Value::CreateInt(game::getclientmodel(cn)));
    SetValue(player, "icon", CefV8Value::CreateString(game::getclienticon(cn)));
    SetValue(player, "connected", CefV8Value::CreateBool(false));
    SetValue(player, "master", CefV8Value::CreateBool(game::ismaster(cn)));
    SetValue(player, "auth", CefV8Value::CreateBool(game::isauth(cn)));
    SetValue(player, "admin", CefV8Value::CreateBool(game::isadmin(cn)));
    SetValue(player, "spectator", CefV8Value::CreateBool(game::isspectator(cn)));
    SetValue(player, "ai", CefV8Value::CreateBool(game::isai(cn, 1)));
}

void InexorCefGameManager::UpdatePlayer(CefRefPtr<CefV8Value> player)
{
    int cn = player->GetValue("cn")->GetIntValue();
    UpdatePlayer(player, cn);
}

void InexorCefGameManager::UpdatePlayer(int cn)
{
    UpdatePlayer(GetPlayer(cn), cn);
}

void InexorCefGameManager::UpdatePlayers()
{
    for (int i = 0; i < 255; i++)
        UpdatePlayer(i);
}

bool InexorCefGameManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    if (name == "update") {
        UpdatePlayers();
        return true;
    } else if (name == "getClientName") {
        if (arguments.size() == 1 && arguments[0]->IsInt()) {
            retval = CefV8Value::CreateString(game::getclientname(arguments[0]->GetIntValue()));
            return true;
        }
    } else if (name == "getClientTeam") {
        if (arguments.size() == 1 && arguments[0]->IsInt()) {
            retval = CefV8Value::CreateString(game::getclientteam(arguments[0]->GetIntValue()));
            return true;
        }
    } else if (name == "getClientModel") {
        if (arguments.size() == 1 && arguments[0]->IsInt()) {
            retval = CefV8Value::CreateInt(game::getclientmodel(arguments[0]->GetIntValue()));
            return true;
        }
    } else if (name == "getClientIcon") {
        if (arguments.size() == 1 && arguments[0]->IsInt()) {
            retval = CefV8Value::CreateString(game::getclienticon(arguments[0]->GetIntValue()));
            return true;
        }
    }
    return false;
}

bool InexorCefGameManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorCefGameManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}
