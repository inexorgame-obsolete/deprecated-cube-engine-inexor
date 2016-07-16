set(mod cef_subprocess)
string(TOUPPER ${mod} MOD)

# We are including cube.h TODO: Get rid of this
add_definitions(-DCLIENT)

declare_module(${mod} .)
message(STATUS "SOURCES: ${mod} –– ${MOD}_MODULE_SOURCES ${${MOD}_MODULE_SOURCES}")
add_app(${mod} ${${MOD}_MODULE_SOURCES} CONSOLE_APP)

require_ui(${mod})
