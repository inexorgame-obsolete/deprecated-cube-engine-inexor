set(mod cef_subprocess)
string(TOUPPER ${mod} MOD)

declare_module(${mod} .)
add_app(${mod} ${${MOD}_MODULE_SOURCES})

require_ui(${mod})
