#include "inexor/ui/input/InexorKeyboardManager.hpp"
#include "inexor/ui/input/SDL2Keyboard.hpp"

#include <SDL.h>
#include <include/cef_base.h>

namespace inexor {
namespace ui {
namespace input {

bool InexorKeyboardManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorKeyboardManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorKeyboardManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

void InexorKeyboardManager::SendKeyEvent(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN)
    {
        CefKeyEvent cef_event;
        cef_event.modifiers = getKeyboardModifiers(e.key.keysym.mod);
        uint32_t javascript_keycode = convertSDLtoJSKeyCode(e.key.keysym.sym);
        cef_event.windows_key_code = javascript_keycode;
        cef_event.character = javascript_keycode;

        cef_event.type = KEYEVENT_RAWKEYDOWN; // or shall we send keydown?
        layer_manager->SendKeyEvent(cef_event);

        cef_event.type = KEYEVENT_CHAR;
        layer_manager->SendKeyEvent(cef_event);
        return;
    }
    if(e.type == SDL_KEYUP)
    {
        CefKeyEvent cef_event;
        cef_event.modifiers = getKeyboardModifiers(e.key.keysym.mod);
        cef_event.windows_key_code = convertSDLtoJSKeyCode(e.key.keysym.sym);

        cef_event.type = KEYEVENT_KEYUP;
        layer_manager->SendKeyEvent(cef_event);
        return;
    }
    if(e.type == SDL_TEXTINPUT)
    {
        char *text = e.text.text;
    }
}

bool InexorKeyboardManager::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut) {
    CEF_REQUIRE_UI_THREAD();
    spdlog::get("global")->debug("InexorCefKeyboardManager::OnPreKeyEvent: key_event.type: {0} native_key_code: {1} windows_key_code: {2} is_system_key: {3}",
                                 key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
    return false;
}

bool InexorKeyboardManager::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event) {
    CEF_REQUIRE_UI_THREAD();
    spdlog::get("global")->debug("InexorCefKeyboardManager::OnKeyEvent: key_event.type: {0} native_key_code: {1} windows_key_code: {2} is_system_key: {3}",
                                 key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
    return false;
}

}
}
}
