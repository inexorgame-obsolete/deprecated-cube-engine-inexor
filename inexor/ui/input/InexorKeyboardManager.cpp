#include "inexor/ui/input/InexorKeyboardManager.hpp"
#include "inexor/ui/input/SDL2Keyboard.hpp"

#include <SDL.h>
#include <include/cef_base.h>

#include <string>
#include <locale>
#include <codecvt>

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

#if _MSC_VER == 1900 // visual studio 2015 bug see https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
std::u16string utf8_to_utf16(std::string utf8_string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
    return reinterpret_cast<const char16_t *>(convert.from_bytes(utf8_string).data());
}
#else
std::u16string utf8_to_utf16(std::string utf8_string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.from_bytes(utf8_string);
}

#endif

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

        //cef_event.type = KEYEVENT_CHAR;
        //layer_manager->SendKeyEvent(cef_event);
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
        CefKeyEvent cef_event;
//        cef_string_utf8_to_utf16(e.text.text, SDL_TEXTINPUTEVENT_TEXT_SIZE, )
        std::u16string decodedstr(utf8_to_utf16(e.text.text)); //SDL gives us utf8 and CEF has char16. we could also just assign it though (so the highest bits would be nulled).

        for(char16_t cha : decodedstr)
        {
            cef_event.character = cha;
            cef_event.windows_key_code = cha;
            cef_event.type = KEYEVENT_CHAR;
            layer_manager->SendKeyEvent(cef_event);
        }
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
