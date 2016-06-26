#include "inexor/ui/input/InexorKeyboardManager.hpp"

namespace inexor {
namespace ui {
namespace input {

InexorKeyboardManager::InexorKeyboardManager(CefRefPtr<inexor::ui::layer::InexorLayerManager> layer_manager) : layer_manager(layer_manager)
{
}

void InexorKeyboardManager::InitializeContext()
{
}

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

void InexorKeyboardManager::SendKeyEvent(SDL_Event event)
{
    /** Modifiers **/
    bool shift = (event.key.keysym.mod & KMOD_LSHIFT) || (event.key.keysym.mod & KMOD_RSHIFT);
    bool ctrl = (event.key.keysym.mod & KMOD_LCTRL) || (event.key.keysym.mod & KMOD_RCTRL);
    bool alt = (event.key.keysym.mod & KMOD_LALT) || (event.key.keysym.mod & KMOD_RALT);
    bool num_lock = !(event.key.keysym.mod & KMOD_NUM);
    bool caps_lock = event.key.keysym.mod & KMOD_CAPS;
    int modifiers = 0;
    if (shift)
        modifiers += EVENTFLAG_SHIFT_DOWN;
    if (ctrl)
        modifiers += EVENTFLAG_CONTROL_DOWN;
    if (alt)
        modifiers += EVENTFLAG_ALT_DOWN;
    if (num_lock)
        modifiers += EVENTFLAG_NUM_LOCK_ON;
    if (caps_lock)
        modifiers += EVENTFLAG_CAPS_LOCK_ON;

    /** Output codes **/
    int key_code = 0;
    int char_code = 0;
    bool is_char = false;

    if (event.type == SDL_TEXTINPUT) {
        spdlog::get("global")->debug() << "text: " << event.text.text << " char[0]: " << (int) event.text.text[0];
        is_char = true;
        if (event.text.text[0] >= 32 && event.text.text[0] <= SDLK_z)
            char_code = event.text.text[0];
        else
            switch(event.text.text[0])
            {
                case '(':
                    char_code = JSC_PARENTHESES_LEFT;
                    break;
                case ')':
                    char_code = JSC_PARENTHESES_RIGHT;
                    break;
                case '[':
                    char_code = JSC_BRACKET_LEFT;
                    break;
                case ']':
                    char_code = JSC_BRACKET_RIGHT;
                    break;
                case '{':
                    char_code = JSC_BRACE_LEFT;
                    break;
                case '}':
                    char_code = JSC_BRACE_RIGHT;
                    break;
                case ',':
                    char_code = JSC_COMMA;
                    break;
                case ';':
                    char_code = JSC_SEMI_COLON;
                    break;
                case '-':
                    char_code = JSC_SUBTRACT;
                    break;
                case '_':
                    char_code = JSC_UNDERSCORE;
                    break;
                case '#':
                    char_code = JSC_HASH;
                    break;
                case '\'':
                    char_code = JSC_SINGLE_QUOTE;
                    break;
                case '+':
                    char_code = JSC_PLUS;
                    break;
                case '*':
                    char_code = JSC_ASTERISK;
                    break;
                case '~':
                    char_code = JSC_TILDE;
                    break;
                case '?':
                    char_code = JSC_QUESTION;
                    break;
                case '\\':
                    char_code = JSC_BACK_SLASH;
                    break;
                case '|':
                    char_code = JSC_PIPE;
                    break;
                default:
                    // char_code = event.text.text[0];
                    break;
            }
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        spdlog::get("global")->debug("type: {0} mod: {1} sym: {2} ({3}) scan: {4} ({5})",
                                     event.key.state, event.key.keysym.mod, event.key.keysym.sym,
                                     SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.scancode,
                                     SDL_GetScancodeName(event.key.keysym.scancode));

        /** Function Keys **/
        if (event.key.keysym.sym >= _SDLK_F1 && event.key.keysym.sym <= _SDLK_F12) {
            key_code = JSK_F1 + (event.key.keysym.sym - _SDLK_F1);
        }
        /** Special Keys **/
        switch(event.key.keysym.sym)
        {
            case SDLK_BACKSPACE:
                key_code = JSK_BACKSPACE;
                break;
            case SDLK_TAB:
                key_code = JSK_TAB;
                break;
            case SDLK_RETURN:
                is_char = true;
                key_code = JSK_ENTER;
                char_code = JSK_ENTER;
                break;
            case SDLK_PAUSE:
                key_code = JSK_PAUSE;
                break;
            case _SDLK_SCROLL_LOCK:
                key_code = JSK_SCROLL_LOCK;
                break;
            case SDLK_ESCAPE:
                key_code = JSK_ESCAPE;
                break;
            case SDLK_LEFT:
                key_code = JSK_LEFT_ARROW;
                break;
            case SDLK_UP:
                key_code = JSK_UP_ARROW;
                break;
            case SDLK_RIGHT:
                key_code = JSK_RIGHT_ARROW;
                break;
            case SDLK_DOWN:
                key_code = JSK_DOWN_ARROW;
                break;
            case _SDLK_HOME:
                key_code = JSK_HOME;
                break;
            case _SDLK_END:
                key_code = JSK_END;
                break;
            case _SDLK_PAGEUP:
                key_code = JSK_PAGE_UP;
                break;
            case _SDLK_PAGEDOWN:
                key_code = JSK_PAGE_DOWN;
                break;
            case _SDLK_INSERT:
                key_code = JSK_INSERT;
                break;
            case SDLK_DELETE:
                is_char = true;
                key_code = JSK_DELETE;
                char_code = JSC_DELETE;
                break;
            case _SDLK_NUM_DIVIDE:
                is_char = true;
                key_code = JSK_DIVIDE;
                char_code = JSC_NUM_DIVIDE;
                break;
            case _SDLK_NUM_MULTIPLY:
                is_char = true;
                key_code = JSK_MULTIPLY;
                char_code = JSC_NUM_MULTIPLY;
                break;
            case _SDLK_NUM_SUBTRACT:
                is_char = true;
                key_code = JSK_SUBTRACT;
                char_code = JSC_NUM_SUBTRACT;
                break;
            case _SDLK_NUM_ADD:
                is_char = true;
                key_code = JSK_ADD;
                char_code = JSC_NUM_ADD;
                break;
            case _SDLK_NUM_DECIMAL:
                if (num_lock) {
                    is_char = true;
                    key_code = JSK_DECIMAL_POINT; // keyboard layout dependent!
                    char_code = JSK_DELETE;
                } else {
                    key_code = JSK_DELETE;
                }
                break;
            case _SDLK_KP0:
                key_code = JSK_INSERT;
                break;
            case _SDLK_KP1:
                key_code = JSK_END;
                break;
            case _SDLK_KP2:
                key_code = JSK_DOWN_ARROW;
                break;
            case _SDLK_KP3:
                key_code = JSK_PAGE_DOWN;
                break;
            case _SDLK_KP4:
                key_code = JSK_LEFT_ARROW;
                break;
            case _SDLK_KP5:
                key_code = JSK_NUM5_SECOND;
                break;
            case _SDLK_KP6:
                key_code = JSK_RIGHT_ARROW;
                break;
            case _SDLK_KP7:
                key_code = JSK_HOME;
                break;
            case _SDLK_KP8:
                key_code = JSK_UP_ARROW;
                break;
            case _SDLK_KP9:
                key_code = JSK_PAGE_UP;
                break;
            case _SDLK_CAPS_LOCK:
                key_code = JSK_CAPS_LOCK;
                break;
            case _SDLK_NUM:
                key_code = JSK_NUM_LOCK;
                break;
            case _SDLK_LCTRL:
            case _SDLK_RCTRL:
                key_code = JSK_CTRL;
                break;
            case _SDLK_LSHIFT:
            case _SDLK_RSHIFT:
                key_code = JSK_SHIFT;
                break;
            case _SDLK_LALT:
                key_code = JSK_LEFT_ALT;
                break;
            case _SDLK_LMETA:
                key_code = JSK_LEFT_WIN;
                break;
            case _SDLK_RALT:
                key_code = JSK_RIGHT_ALT;
                break;
            case _SDLK_RMETA:
                key_code = JSK_RIGHT_WIN;
                break;
            case _SDLK_SELECT:
                key_code = JSK_SELECT;
                break;
        }

    }

    /** Still not mapped? **/
    if (key_code == 0) {
        key_code = event.key.keysym.sym;
    }

    /** Fire key events to CEF **/
    if (event.key.state == SDL_PRESSED || event.type == SDL_TEXTINPUT) {
        // onkeydown
        CefKeyEvent key_event_key_down;
        key_event_key_down.type = KEYEVENT_KEYDOWN;
        key_event_key_down.modifiers = modifiers;
        key_event_key_down.windows_key_code = key_code;
        layer_manager->SendKeyEvent(key_event_key_down);
        // Fire a second key event for characters only
        if (is_char) {
            // onkeypress
            CefKeyEvent key_event_char;
            key_event_char.type = KEYEVENT_CHAR;
            key_event_char.modifiers = modifiers;
            key_event_char.character = char_code;
            layer_manager->SendKeyEvent(key_event_char);
        }
    } else if (event.key.state == SDL_RELEASED) {
        // onkeyup
        CefKeyEvent key_event_key_up;
        key_event_key_up.type = KEYEVENT_KEYUP;
        key_event_key_up.modifiers = modifiers;
        key_event_key_up.windows_key_code = key_code;
        layer_manager->SendKeyEvent(key_event_key_up);
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
