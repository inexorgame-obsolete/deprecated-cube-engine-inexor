#include <SDL.h>
#include <include/cef_base.h>
#include "inexor/ui/input/SDL2Keyboard.hpp"

int getKeyboardModifiers(uint16_t const mod)
{
    int result = EVENTFLAG_NONE;

    if(mod & KMOD_SHIFT)
        result |= EVENTFLAG_SHIFT_DOWN;
    if(mod & KMOD_CTRL)
        result |= EVENTFLAG_CONTROL_DOWN;
    if(mod & KMOD_ALT)
        result |= EVENTFLAG_ALT_DOWN;
    // if(mod & KMOD_GUI) we don't handle the "Windows" button.
    if(mod & KMOD_NUM)
        result |= EVENTFLAG_NUM_LOCK_ON;
    if(mod & KMOD_CAPS)
        result |= EVENTFLAG_CAPS_LOCK_ON;
    return result;
}

uint16_t convertSDLtoJSKeyCode(SDL_Keycode sdl_keycode, bool shift, bool numlock)
{
    if(sdl_keycode >= SDLK_F1 && sdl_keycode <= SDLK_F12)
    {
        return JSK_F1 + (sdl_keycode - SDLK_F1);
    }
    else switch(sdl_keycode)
    {
    case SDLK_LEFTPAREN:
        /*char_code*/return JSC_PARENTHESES_LEFT;
        break;
    case SDLK_RIGHTPAREN:
        /*char_code*/return JSC_PARENTHESES_RIGHT;
        break;
    case SDLK_LEFTBRACKET:
        /*char_code*/return JSC_BRACKET_LEFT;
        break;
    case SDLK_RIGHTBRACKET:
        /*char_code*/return JSC_BRACKET_RIGHT;
        break;
    case '{':
        /*char_code*/return JSC_BRACE_LEFT;
        break;
    case '}':
        /*char_code*/return JSC_BRACE_RIGHT;
        break;
    case SDLK_COMMA:
        /*char_code*/return JSC_COMMA;
        break;
    case SDLK_SEMICOLON:
        /*char_code*/return JSC_SEMI_COLON;
        break;
    case SDLK_MINUS:
        /*char_code*/return JSC_SUBTRACT;
        break;
    case SDLK_UNDERSCORE:
        /*char_code*/return JSC_UNDERSCORE;
        break;
    case SDLK_HASH:
        /*char_code*/return JSC_HASH;
        break;
    case SDLK_QUOTE:
        /*char_code*/return JSC_SINGLE_QUOTE;
        break;
    case SDLK_PLUS:
        /*char_code*/return JSC_PLUS;
        break;
    case SDLK_ASTERISK:
        /*char_code*/return JSC_ASTERISK;
        break;
    case '~': // TODO not found?
        /*char_code*/return JSC_TILDE;
        break;
    case SDLK_QUESTION:
        /*char_code*/return JSC_QUESTION;
        break;
    case SDLK_BACKSLASH:
        /*char_code*/return JSC_BACK_SLASH;
        break;
    case '|':
        /*char_code*/return JSC_PIPE;
        break;
    case SDLK_BACKSPACE:
        return JSK_BACKSPACE;
        break;
    case SDLK_TAB:
        return JSK_TAB;
        break;
    case SDLK_RETURN:
        return JSK_ENTER;
        /*char_code*/return JSK_ENTER;
        break;
    case SDLK_PAUSE:
        return JSK_PAUSE;
        break;
    case SDLK_SCROLLLOCK:
        return JSK_SCROLL_LOCK;
        break;
    case SDLK_ESCAPE:
        return JSK_ESCAPE;
        break;
    case SDLK_LEFT:
        return JSK_LEFT_ARROW;
        break;
    case SDLK_UP:
        return JSK_UP_ARROW;
        break;
    case SDLK_RIGHT:
        return JSK_RIGHT_ARROW;
        break;
    case SDLK_DOWN:
        return JSK_DOWN_ARROW;
        break;
    case SDLK_HOME:
        return JSK_HOME;
        break;
    case SDLK_END:
        return JSK_END;
        break;
    case SDLK_PAGEUP:
        return JSK_PAGE_UP;
        break;
    case SDLK_PAGEDOWN:
        return JSK_PAGE_DOWN;
        break;
    case SDLK_INSERT:
        return JSK_INSERT;
        break;
    case SDLK_DELETE:
        return JSK_DELETE;
        /*char_code*/return JSC_DELETE;
        break;
    case SDLK_KP_DIVIDE:

        return JSK_DIVIDE;
        /*char_code*/return JSC_NUM_DIVIDE;
        break;
    case SDLK_KP_MULTIPLY:

        return JSK_MULTIPLY;
        /*char_code*/return JSC_NUM_MULTIPLY;
        break;
    case SDLK_KP_MINUS:

        return JSK_SUBTRACT;
        /*char_code*/return JSC_NUM_SUBTRACT;
        break;
    case SDLK_KP_PLUS:

        return JSK_ADD;
        /*char_code*/return JSC_NUM_ADD;
        break;
    case SDLK_KP_DECIMAL:
        if(numlock)
        {
            return JSK_DECIMAL_POINT; // keyboard layout dependent!
            /*char_code*/return JSK_DELETE;
        }
        else
        {
            return JSK_DELETE;
        }
        break;
    case SDLK_KP_0:
        return JSK_INSERT;
        // /*char_code*/return JSC_ TODO
        break;
    case SDLK_KP_1:
        return JSK_END;
        break;
    case SDLK_KP_2:
        return JSK_DOWN_ARROW;
        break;
    case SDLK_KP_3:
        return JSK_PAGE_DOWN;
        break;
    case SDLK_KP_4:
        return JSK_LEFT_ARROW;
        break;
    case SDLK_KP_5:
        return JSK_NUM5_SECOND;
        break;
    case SDLK_KP_6:
        return JSK_RIGHT_ARROW;
        break;
    case SDLK_KP_7:
        return JSK_HOME;
        break;
    case SDLK_KP_8:
        return JSK_UP_ARROW;
        break;
    case SDLK_KP_9:
        return JSK_PAGE_UP;
        break;
    case SDLK_CAPSLOCK:
        return JSK_CAPS_LOCK;
        break;
    case SDLK_NUMLOCKCLEAR:
        return JSK_NUM_LOCK;
        break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
        return JSK_CTRL;
        break;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
        return JSK_SHIFT;
        break;
    case SDLK_LALT:
        return JSK_LEFT_ALT;
        break;
    case SDLK_LGUI:
    case SDLK_APPLICATION:
        return JSK_LEFT_WIN;
        break;
    case SDLK_RGUI:
        return JSK_RIGHT_WIN;
        break;
    case SDLK_RALT:
        return JSK_RIGHT_ALT;
        break;
    case SDLK_SELECT:
        return JSK_SELECT;
        break;
        // missing:
        /*  case SDLK_SPACE: break;
        case SDLK_EXCLAIM: break;
        case SDLK_QUOTEDBL: break;
        case SDLK_HASH: break;
        case SDLK_PERCENT: break;
        case SDLK_DOLLAR: break;
        case SDLK_AMPERSAND: break;
        case SDLK_QUOTE: break;
        case SDLK_LEFTPAREN: break;
        case SDLK_RIGHTPAREN: break;
        case SDLK_ASTERISK: break;
        case SDLK_PLUS: break;
        case SDLK_COMMA: break;
        case SDLK_MINUS: break;
        case SDLK_PERIOD: break;
        case SDLK_SLASH: break;
        case SDLK_0: break;
        case SDLK_1: break;
        case SDLK_2: break;
        case SDLK_3: break;
        case SDLK_4: break;
        case SDLK_5: break;
        case SDLK_6: break;
        case SDLK_7: break;
        case SDLK_8: break;
        case SDLK_9: break;
        case SDLK_COLON: break;
        case SDLK_SEMICOLON: break;
        case SDLK_LESS: break;
        case SDLK_EQUALS: break;
        case SDLK_GREATER: break;
        case SDLK_QUESTION: break;
        case SDLK_AT: break;
        case SDLK_LEFTBRACKET: break;
        case SDLK_BACKSLASH: break;
        case SDLK_RIGHTBRACKET: break;
        case SDLK_CARET: break;
        case SDLK_UNDERSCORE: break;
        case SDLK_BACKQUOTE: break;
        case SDLK_a: break;
        case SDLK_b: break;
        case SDLK_c: break;
        case SDLK_d: break;
        case SDLK_e: break;
        case SDLK_f: break;
        case SDLK_g: break;
        case SDLK_h: break;
        case SDLK_i: break;
        case SDLK_j: break;
        case SDLK_k: break;
        case SDLK_l: break;
        case SDLK_m: break;
        case SDLK_n: break;
        case SDLK_o: break;
        case SDLK_p: break;
        case SDLK_q: break;
        case SDLK_r: break;
        case SDLK_s: break;
        case SDLK_t: break;
        case SDLK_u: break;
        case SDLK_v: break;
        case SDLK_w: break;
        case SDLK_x: break;
        case SDLK_y: break;
        case SDLK_z: break;

        case SDLK_PRINTSCREEN: break;
        case SDLK_KP_ENTER: break;
        case SDLK_KP_PERIOD: break;
        case SDLK_POWER: break;
        case SDLK_KP_EQUALS: break;
        case SDLK_F13: break;
        case SDLK_F14: break;
        case SDLK_F15: break;
        case SDLK_F16: break;
        case SDLK_F17: break;
        case SDLK_F18: break;
        case SDLK_F19: break;
        case SDLK_F20: break;
        case SDLK_F21: break;
        case SDLK_F22: break;
        case SDLK_F23: break;
        case SDLK_F24: break;
        case SDLK_EXECUTE: break;
        case SDLK_HELP: break;
        case SDLK_MENU: break;
        case SDLK_STOP: break;
        case SDLK_AGAIN: break;
        case SDLK_UNDO: break;
        case SDLK_CUT: break;
        case SDLK_COPY: break;
        case SDLK_PASTE: break;
        case SDLK_FIND: break;
        case SDLK_MUTE: break;
        case SDLK_VOLUMEUP: break;
        case SDLK_VOLUMEDOWN: break;
        case SDLK_KP_COMMA: break;
        case SDLK_KP_EQUALSAS400: break;

        case SDLK_ALTERASE: break;
        case SDLK_SYSREQ: break;
        case SDLK_CANCEL: break;
        case SDLK_CLEAR: break;
        case SDLK_PRIOR: break;
        case SDLK_RETURN2: break;
        case SDLK_SEPARATOR: break;
        case SDLK_OUT: break;
        case SDLK_OPER: break;
        case SDLK_CLEARAGAIN: break;
        case SDLK_CRSEL: break;
        case SDLK_EXSEL: break;

        case SDLK_KP_00: break;
        case SDLK_KP_000: break;
        case SDLK_THOUSANDSSEPARATOR: break;
        case SDLK_DECIMALSEPARATOR: break;
        case SDLK_CURRENCYUNIT: break;
        case SDLK_CURRENCYSUBUNIT: break;
        case SDLK_KP_LEFTPAREN: break;
        case SDLK_KP_RIGHTPAREN: break;
        case SDLK_KP_LEFTBRACE: break;
        case SDLK_KP_RIGHTBRACE: break;
        case SDLK_KP_TAB: break;
        case SDLK_KP_BACKSPACE: break;
        case SDLK_KP_A: break;
        case SDLK_KP_B: break;
        case SDLK_KP_C: break;
        case SDLK_KP_D: break;
        case SDLK_KP_E: break;
        case SDLK_KP_F: break;
        case SDLK_KP_XOR: break;
        case SDLK_KP_POWER: break;
        case SDLK_KP_PERCENT: break;
        case SDLK_KP_LESS: break;
        case SDLK_KP_GREATER: break;
        case SDLK_KP_AMPERSAND: break;
        case SDLK_KP_DBLAMPERSAND: break;
        case SDLK_KP_VERTICALBAR: break;
        case SDLK_KP_DBLVERTICALBAR: break;
        case SDLK_KP_COLON: break;
        case SDLK_KP_HASH: break;
        case SDLK_KP_SPACE: break;
        case SDLK_KP_AT: break;
        case SDLK_KP_EXCLAM: break;
        case SDLK_KP_MEMSTORE: break;
        case SDLK_KP_MEMRECALL: break;
        case SDLK_KP_MEMCLEAR: break;
        case SDLK_KP_MEMADD: break;
        case SDLK_KP_MEMSUBTRACT: break;
        case SDLK_KP_MEMMULTIPLY: break;
        case SDLK_KP_MEMDIVIDE: break;
        case SDLK_KP_PLUSMINUS: break;
        case SDLK_KP_CLEAR: break;
        case SDLK_KP_CLEARENTRY: break;
        case SDLK_KP_BINARY: break;
        case SDLK_KP_OCTAL: break;
        case SDLK_KP_HEXADECIMAL: break;

        case SDLK_MODE: break;*/
    }

    // Still not mapped
    return sdl_keycode;
}

int getWindowsKeyCode(SDL_Keysym const &key)
{
    int result = 0;

    bool shift = !!(key.mod & KMOD_SHIFT);
    bool caps = !!(key.mod & KMOD_CAPS);
    bool alt_gr = !!(key.mod & KMOD_RALT);
    bool uppercase = (caps && !shift) || (shift && !caps);

    // mapped from azerty windows 8 asus laptop
    switch(key.sym)
    {
    case SDLK_RETURN:
        result = 13;
        break;
    case SDLK_ESCAPE:
        result = 27;
        break;
    case SDLK_BACKSPACE:
        result = 8;
        break;
    case SDLK_TAB:
        result = 9;
        break;
    case SDLK_SPACE:
        result = 32;
        break;
    case SDLK_EXCLAIM:
        result = uppercase ? 167 : 33; // § : !
        break;

    case SDLK_QUOTEDBL:
        result = 34;
        break;
    case SDLK_HASH:
        result = 35;
        break;
    case SDLK_DOLLAR:
        result = 36;
        break;
    case SDLK_PERCENT:
        result = 37;
        break;
    case SDLK_AMPERSAND:
        result = 38;
        break;
    case SDLK_QUOTE:
        result = 39;
        break;
    case SDLK_LEFTPAREN:
        result = 40;
        break;
    case SDLK_RIGHTPAREN:
        result = alt_gr ? 93 : uppercase ? 176 : 41; // ] ? ° : )
        break;
    case SDLK_ASTERISK:
        result = uppercase ? 181 : 42; // µ : *
        break;
    case SDLK_PLUS:
        result = 43;
        break;
    case SDLK_COMMA:
        result = uppercase ? 63 : 44; // '?' : ,
        break;
    case SDLK_MINUS:
        result = 45;
        break;
    case SDLK_PERIOD:
        result = 46;
        break;
    case SDLK_SLASH:
        result = 47;
        break;

    case SDLK_0:
        result = alt_gr ? 64 : uppercase ? 48 : 224; // @ ? 0 : à
        break;
    case SDLK_1:
        result = uppercase ? 49 : 38; // 1 : & (KO)
        break;
    case SDLK_2:
        result = alt_gr ? 126 : uppercase ? 50 : 233; // ~ ? 2 : é
        break;
    case SDLK_3:
        result = alt_gr ? 35 : uppercase ? 51 : 34; // # ? 3 : "
        break;
    case SDLK_4:
        result = alt_gr ? 123 : uppercase ? 52 : 39; // { ? 4 : '
        break;
    case SDLK_5:
        result = alt_gr ? 91 : uppercase ? 53 : 40; // [ ? 5 : ( (KO)
        break;
    case SDLK_6:
        result = alt_gr ? 124 : uppercase ? 54 : 45; // | ? 6 : -
        break;
    case SDLK_7:
        result = alt_gr ? 96 : uppercase ? 55 : 232; // ` ? 7 : è
        break;
    case SDLK_8:
        result = alt_gr ? 92 : uppercase ? 56 : 95; // \ ? 8 : _
        break;
    case SDLK_9:
        result = alt_gr ? 94 : uppercase ? 57 : 231; // ^ ? 9 : ç
        break;

    case SDLK_COLON:
        result = uppercase ? 47 : 58; // / : :
        break;
    case SDLK_SEMICOLON:
        result = uppercase ? 46 : 59; // . (KO) : ;
        break;
    case SDLK_LESS:
        result = uppercase ? 62 : 60; // > : <
        break;
    case SDLK_EQUALS:
        result = alt_gr ? 125 : uppercase ? 43 : 61; // } ? + : =
        break;
    case SDLK_GREATER:
        result = 62;
        break;
    case SDLK_QUESTION:
        result = 63;
        break;
    case SDLK_AT:
        result = 64;
        break;
    case SDLK_LEFTBRACKET:
        result = 91;
        break;
    case SDLK_BACKSLASH:
        result = 92;
        break;
    case SDLK_RIGHTBRACKET:
        result = 93;
        break;
    case SDLK_CARET:
        result = uppercase ? 168 : 94; // ^ : ¨
        break;
    case SDLK_UNDERSCORE:
        result = 95;
        break;
    case SDLK_BACKQUOTE:
        result = 96;
        break;

    case SDLK_a:
        result = uppercase ? 65 : 97;
        break;
    case SDLK_b:
        result = uppercase ? 66 : 98;
        break;
    case SDLK_c:
        result = uppercase ? 67 : 99;
        break;
    case SDLK_d:
        result = uppercase ? 68 : 100;
        break;
    case SDLK_e:
        result = uppercase ? 69 : 101;
        break;
    case SDLK_f:
        result = uppercase ? 70 : 102;
        break;
    case SDLK_g:
        result = uppercase ? 71 : 103;
        break;
    case SDLK_h:
        result = uppercase ? 72 : 104;
        break;
    case SDLK_i:
        result = uppercase ? 73 : 105;
        break;
    case SDLK_j:
        result = uppercase ? 74 : 106;
        break;
    case SDLK_k:
        result = uppercase ? 75 : 107;
        break;
    case SDLK_l:
        result = uppercase ? 76 : 108;
        break;
    case SDLK_m:
        result = uppercase ? 77 : 109;
        break;
    case SDLK_n:
        result = uppercase ? 78 : 110;
        break;
    case SDLK_o:
        result = uppercase ? 79 : 111;
        break;
    case SDLK_p:
        result = uppercase ? 80 : 112;
        break;
    case SDLK_q:
        result = uppercase ? 81 : 113;
        break;
    case SDLK_r:
        result = uppercase ? 82 : 114;
        break;
    case SDLK_s:
        result = uppercase ? 83 : 115;
        break;
    case SDLK_t:
        result = uppercase ? 84 : 116;
        break;
    case SDLK_u:
        result = uppercase ? 85 : 117;
        break;
    case SDLK_v:
        result = uppercase ? 86 : 118;
        break;
    case SDLK_w:
        result = uppercase ? 87 : 119;
        break;
    case SDLK_x:
        result = uppercase ? 88 : 120;
        break;
    case SDLK_y:
        result = uppercase ? 89 : 121;
        break;
    case SDLK_z:
        result = uppercase ? 90 : 122;
        break;
    }
    return result;
}
 // fehlt noch: großbuchstaben
