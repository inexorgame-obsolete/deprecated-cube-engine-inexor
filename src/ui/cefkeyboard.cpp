#include "cefkeyboard.h"

InexorCefKeyboardManager::InexorCefKeyboardManager(CefRefPtr<InexorCefLayerManager> layer_manager) : layer_manager(layer_manager)
{
}

void InexorCefKeyboardManager::InitializeContext()
{
}

bool InexorCefKeyboardManager::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorCefKeyboardManager::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

bool InexorCefKeyboardManager::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    return false;
}

void InexorCefKeyboardManager::SendKeyEvent(SDL_Event event)
{
    bool is_char = false;
    bool shift = false;
    bool num_lock = false;
    int key_code = 0;
    int char_code = 0;
    int which = 0;
    int modifiers = 0;

    logoutf("type: %d mod: %d sym: %d (%s) scan: %d (%s)", event.key.state, event.key.keysym.mod, event.key.keysym.sym, SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.scancode, SDL_GetScancodeName(event.key.keysym.scancode));

    /** Modifiers **/

    if ((event.key.keysym.mod & KMOD_LSHIFT) || (event.key.keysym.mod & KMOD_RSHIFT)) {
        modifiers += EVENTFLAG_SHIFT_DOWN;
        shift = true;
    }
    if ((event.key.keysym.mod & KMOD_LCTRL) || (event.key.keysym.mod & KMOD_RCTRL)) {
        modifiers += EVENTFLAG_CONTROL_DOWN;
    }
    if ((event.key.keysym.mod & KMOD_LALT) || (event.key.keysym.mod & KMOD_RALT)) {
        modifiers += EVENTFLAG_ALT_DOWN;
    }
    if (event.key.keysym.mod & KMOD_NUM) {
        // Num Lock is OFF!!!
    } else {
        num_lock = true;
        modifiers += EVENTFLAG_NUM_LOCK_ON;
    }
    if (event.key.keysym.mod & KMOD_CAPS) {
        modifiers += EVENTFLAG_CAPS_LOCK_ON;
    }

    /** Alphanumeric and keypad **/

    if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
        is_char = true;
        key_code = event.key.keysym.sym;
        if (shift) {
            char_code = event.key.keysym.sym - 32;
        } else {
            char_code = event.key.keysym.sym;
        }
    } else if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) {
        is_char = true;
        key_code = event.key.keysym.sym;
        if (!shift) {
            char_code = event.key.keysym.sym;
        } else {
            // keyboard layout dependent
            switch(event.key.keysym.sym)
            {
                case SDLK_0:
                    char_code = JSC_EQUAL;
                    break;
                case SDLK_1:
                    char_code = JSC_EXCLAIM;
                    break;
                case SDLK_2:
                    char_code = JSC_DOUBLE_QUOTE;
                    break;
                case SDLK_3:
                    char_code = 0;
                    break;
                case SDLK_4:
                    char_code = JSC_DOLLAR;
                    break;
                case SDLK_5:
                    char_code = JSC_PERCENT;
                    break;
                case SDLK_6:
                    char_code = JSC_AMPERSAND;
                    break;
                case SDLK_7:
                    char_code = JSC_SLASH;
                    break;
                case SDLK_8:
                    char_code = JSC_BRACE_LEFT;
                    break;
                case SDLK_9:
                    char_code = JSC_BRACE_RIGHT;
                    break;
            }
            // char_code = SDLK_EXCLAIM;
        }
    } else if (event.key.keysym.sym >= _SDLK_KP0 && event.key.keysym.sym <= _SDLK_KP9) {
        if (!num_lock) {
            is_char = true;
            int diff = event.key.keysym.sym - _SDLK_KP0;
            key_code = JSK_NUM_0 + diff;
            char_code = JSK_0 + diff;
        } else {
            switch (event.key.keysym.sym)
            {
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
            }
        }
    } else if (event.key.keysym.sym >= _SDLK_F1 && event.key.keysym.sym <= _SDLK_F12) {
        key_code = JSK_F1 + (event.key.keysym.sym - _SDLK_F1);
    }

    switch(event.key.keysym.sym)
    {
        case SDLK_BACKSPACE:
            key_code = JSK_BACKSPACE;
            break;
        case SDLK_TAB:
            key_code = JSK_TAB;
            break;
        case SDLK_RETURN:
        case _SDLK_NUM_ENTER:
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
        case SDLK_SPACE:
            is_char = true;
            key_code = JSK_SPACE;
            char_code = SDLK_SPACE;
            break;
        case SDLK_MINUS:
        case SDLK_UNDERSCORE:
            if (!shift) {
                is_char = true;
                key_code = JSK_DASH;
                char_code = SDLK_MINUS;
            } else {
                is_char = true;
                key_code = JSK_DASH;
                char_code = SDLK_UNDERSCORE;
            }
            break;
        case SDLK_PERIOD:
        case SDLK_COLON:
            if (!shift) {
                is_char = true;
                key_code = JSK_PERIOD;
                char_code = SDLK_PERIOD;
            } else {
                is_char = true;
                key_code = JSK_PERIOD;
                char_code = SDLK_COLON;
            }
            break;
        case SDLK_COMMA:
        case SDLK_SEMICOLON:
            if (!shift) {
                is_char = true;
                key_code = JSK_COMMA;
                char_code = SDLK_COMMA;
            } else {
                is_char = true;
                key_code = JSK_COMMA;
                char_code = SDLK_SEMICOLON;
            }
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

    /** Still not mapped? **/

    if (key_code == 0) {
        key_code = event.key.keysym.sym;
    }

    /** Fire key events to CEF **/

    if (event.key.state == SDL_PRESSED) {
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

bool InexorCefKeyboardManager::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut) {
    CEF_REQUIRE_UI_THREAD();
    logoutf("InexorCefClientHandler::OnPreKeyEvent: key_event.type: %d native_key_code: %d windows_key_code: %d is_system_key: %d", key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
    return false;
}

bool InexorCefKeyboardManager::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event) {
    CEF_REQUIRE_UI_THREAD();
    logoutf("InexorCefClientHandler::OnKeyEvent: key_event.type: %d native_key_code: %d windows_key_code: %d is_system_key: %d", key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
    return false;
}

int InexorCefKeyboardManager::SDL2toJavaScript(SDL_Event event) {
    return 0;
/*
    int sdl_keycode = event.key.keysym.sym;
    switch(sdl_keycode) {
        case SDLK_EXCLAIM:
            return sdl_keycode; // TODO
        case SDLK_QUOTEDBL:
            return sdl_keycode; // TODO
        case SDLK_HASH:
            return sdl_keycode; // TODO
        case SDLK_DOLLAR:
            return sdl_keycode; // TODO
        case SDLK_AMPERSAND:
            return sdl_keycode; // TODO
        case SDLK_QUOTE:
            return JSK_SINGLE_QUOTE;
        case SDLK_LEFTPAREN:
            return sdl_keycode; // TODO
        case SDLK_RIGHTPAREN:
            return sdl_keycode; // TODO
        case SDLK_ASTERISK:
            return JSK_MULTIPLY;
        case SDLK_PLUS:
            return JSK_ADD;
        case SDLK_MINUS:
            return JSK_SUBTRACT;
        case SDLK_PERIOD:
            return JSK_PERIOD;
        case SDLK_SLASH:
            return JSK_FORWARD_SLASH;
        case SDLK_0:
            return JSK_0;
        case SDLK_1:
            return JSK_1;
        case SDLK_2:
            return JSK_2;
        case SDLK_3:
            return JSK_3;
        case SDLK_4:
            return JSK_4;
        case SDLK_5:
            return JSK_5;
        case SDLK_6:
            return JSK_6;
        case SDLK_7:
            return JSK_7;
        case SDLK_8:
            return JSK_8;
        case SDLK_9:
            return JSK_9;
        case SDLK_SEMICOLON:
            return JSK_SEMI_COLON;
        case SDLK_LESS:
            return sdl_keycode; // TODO
        case SDLK_EQUALS:
            return sdl_keycode; // TODO
        case SDLK_GREATER:
            return sdl_keycode; // TODO
        case SDLK_QUESTION:
            return sdl_keycode; // TODO
        case SDLK_AT:
            return sdl_keycode; // TODO
        case SDLK_LEFTBRACKET:
            return JSK_OPEN_BRACKET; // TODO
        case SDLK_BACKSLASH:
            return sdl_keycode; // TODO
        case SDLK_RIGHTBRACKET:
            return JSK_CLOSE_BRACKET; // TODO
        case SDLK_CARET:
            return sdl_keycode; // TODO
        case SDLK_UNDERSCORE:
            return sdl_keycode; // TODO
        case SDLK_BACKQUOTE:
            return sdl_keycode; // TODO
        case SDLK_KP0:
            return JSK_NUM_0;
        case SDLK_KP1:
            return JSK_NUM_1;
        case SDLK_KP2:
            return JSK_NUM_2;
        case SDLK_KP3:
            return JSK_NUM_3;
        case SDLK_KP4:
            return JSK_NUM_4;
        case SDLK_KP5:
            return JSK_NUM_5;
        case SDLK_KP6:
            return JSK_NUM_6;
        case SDLK_KP7:
            return JSK_NUM_7;
        case SDLK_KP8:
            return JSK_NUM_8;
        case SDLK_KP9:
            return JSK_NUM_9;
        case SDLK_KP_PERIOD:
            return JSK_PERIOD;
        case SDLK_KP_DIVIDE:
            return JSK_DIVIDE;
        case SDLK_KP_MULTIPLY:
            return JSK_MULTIPLY;
        case SDLK_KP_MINUS:
            return JSK_SUBTRACT;
        case SDLK_KP_PLUS:
            return JSK_ADD;
        case SDLK_KP_ENTER:
            return sdl_keycode; // TODO
        case SDLK_KP_EQUALS:
            return JSK_EQUAL_SIGN;
        case SDLK_UP:
            return JSK_UP_ARROW;
        case SDLK_DOWN:
            return JSK_DOWN_ARROW;
        case SDLK_RIGHT:
            return JSK_RIGHT_ARROW;
        case SDLK_LEFT:
            return JSK_LEFT_ARROW;
        case SDLK_INSERT:
            return JSK_INSERT;
        case SDLK_HOME:
            return JSK_HOME;
        case SDLK_END:
            return JSK_END;
        case SDLK_PAGEUP:
            return JSK_PAGE_UP;
        case SDLK_PAGEDOWN:
            return JSK_PAGE_DOWN;
        case SDLK_F1:
            return JSK_F1;
        case SDLK_F2:
            return JSK_F2;
        case SDLK_F3:
            return JSK_F3;
        case SDLK_F4:
            return JSK_F4;
        case SDLK_F5:
            return JSK_F5;
        case SDLK_F6:
            return JSK_F6;
        case SDLK_F7:
            return JSK_F7;
        case SDLK_F8:
            return JSK_F8;
        case SDLK_F9:
            return JSK_F9;
        case SDLK_F10:
            return JSK_F10;
        case SDLK_F11:
            return JSK_F11;
        case SDLK_F12:
            return JSK_F12;
        case SDLK_F13:
            return sdl_keycode; // TODO
        case SDLK_F14:
            return sdl_keycode; // TODO
        case SDLK_F15:
            return sdl_keycode; // TODO

        default:
            return sdl_keycode;
    }
*/
}
