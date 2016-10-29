#ifndef INEXOR_UI_SDL2_KEYBOARD_HEADER
#define INEXOR_UI_SDL2_KEYBOARD_HEADER

#include <SDL.h>
#include <include/cef_base.h>

extern int getKeyboardModifiers(uint16_t const mod);

extern uint16_t convertSDLtoJSKeyCode(SDL_Keycode sdl_keycode, bool shift = false, bool numlock = false);
#define JSK_BACKSPACE        8
#define JSK_TAB              9
#define JSK_NUM5_SECOND     12
#define JSK_ENTER           13
#define JSK_SHIFT           16
#define JSK_CTRL            17
#define JSK_LEFT_ALT        18
#define JSK_PAUSE           19
#define JSK_CAPS_LOCK       20
#define JSK_ESCAPE          27
#define JSK_SPACE           32
#define JSK_PAGE_UP         33
#define JSK_PAGE_DOWN       34
#define JSK_END             35
#define JSK_HOME            36
#define JSK_LEFT_ARROW      37
#define JSK_UP_ARROW        38
#define JSK_RIGHT_ARROW     39
#define JSK_DOWN_ARROW      40
#define JSK_INSERT          45
#define JSK_DELETE          46
#define JSK_0               48
#define JSK_1               49
#define JSK_2               50
#define JSK_3               51
#define JSK_4               52
#define JSK_5               53
#define JSK_6               54
#define JSK_7               55
#define JSK_8               56
#define JSK_9               57
#define JSK_A               65
#define JSK_B               66
#define JSK_C               67
#define JSK_D               68
#define JSK_E               69
#define JSK_F               70
#define JSK_G               71
#define JSK_H               72
#define JSK_I               73
#define JSK_J               74
#define JSK_K               75
#define JSK_L               76
#define JSK_M               77
#define JSK_N               78
#define JSK_O               79
#define JSK_P               80
#define JSK_Q               81
#define JSK_R               82
#define JSK_S               83
#define JSK_T               84
#define JSK_U               85
#define JSK_V               86
#define JSK_W               87
#define JSK_X               88
#define JSK_Y               89
#define JSK_Z               90
#define JSK_LEFT_WIN        91
#define JSK_RIGHT_WIN       92
#define JSK_SELECT          93
#define JSK_NUM_0           96
#define JSK_NUM_1           97
#define JSK_NUM_2           98
#define JSK_NUM_3           99
#define JSK_NUM_4          100
#define JSK_NUM_5          101
#define JSK_NUM_6          102
#define JSK_NUM_7          103
#define JSK_NUM_8          104
#define JSK_NUM_9          105
#define JSK_MULTIPLY       106
#define JSK_ADD            107
#define JSK_NUM_DECIMAL_COMMA 108
#define JSK_SUBTRACT       109
#define JSK_DECIMAL_POINT  110
#define JSK_DIVIDE         111
#define JSK_F1             112
#define JSK_F2             113
#define JSK_F3             114
#define JSK_F4             115
#define JSK_F5             116
#define JSK_F6             117
#define JSK_F7             118
#define JSK_F8             119
#define JSK_F9             120
#define JSK_F10            121
#define JSK_F11            122
#define JSK_F12            123

#define JSC_BRACE_LEFT     123
#define JSC_PIPE           124
#define JSC_BRACE_RIGHT    125
#define JSC_TILDE          126
#define JSC_DELETE         127

#define JSK_NUM_LOCK       144
#define JSK_SCROLL_LOCK    145

#define JSK_SEMI_COLON     186
#define JSK_EQUAL_SIGN     187
#define JSK_COMMA          188
#define JSK_DASH           189
#define JSK_PERIOD         190
#define JSK_FORWARD_SLASH  191
#define JSK_GRAVE_ACCENT   192

#define JSK_OPEN_BRACKET   219
#define JSK_BACK_SLASH     220
#define JSK_CLOSE_BRACKET  221
#define JSK_SINGLE_QUOTE   222
#define JSK_RIGHT_ALT      225

#define JSC_DOUBLE_QUOTE    34
#define JSC_HASH            35
#define JSC_DOLLAR          36
#define JSC_PERCENT         37
#define JSC_AMPERSAND       38
#define JSC_SINGLE_QUOTE    39
#define JSC_PARENTHESES_LEFT  40
#define JSC_PARENTHESES_RIGHT 41
#define JSC_ASTERISK        42
#define JSC_NUM_MULTIPLY    42
#define JSC_PLUS            43
#define JSC_NUM_ADD         43
#define JSC_COMMA           44
#define JSC_SUBTRACT        45
#define JSC_NUM_SUBTRACT    45
#define JSC_SLASH           47
#define JSC_NUM_DIVIDE      47
#define JSC_SEMI_COLON      59
#define JSC_EXCLAIM         33
#define JSC_EQUAL           61
#define JSC_QUESTION        63
#define JSC_BRACKET_LEFT    91
#define JSC_BACK_SLASH      92
#define JSC_BRACKET_RIGHT   93
#define JSC_UNDERSCORE      95

#endif
