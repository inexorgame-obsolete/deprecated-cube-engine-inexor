set(mod cef_subprocess)
string(TOUPPER ${mod} MOD)

declare_module(${mod} .)
add_app(${mod} ${${MOD}_MODULE_SOURCES} CONSOLE_APP)

require_ui(${mod})
