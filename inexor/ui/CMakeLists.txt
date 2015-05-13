# CEF LIB

# TODO: Automatically fuzzy find suffixes?
find_libs(CEF_LIBS cef_dll_wrapper LIB cef)
find_path(CEF_INCLUDE_DIRS include/cef_app.h)

# UI MODULE

include_directories(${CEF_INCLUDE_DIRS})

declare_module(ui .)
add_lib(ui)

function(config_ui targ)
  message(STATUS "Configuring ${targ} with ui")
  include_directories(${CEF_INCLUDE_DIRS})
  target_link_libs(${targ} module_ui ${CEF_LIBS} module_util)
endfunction()
