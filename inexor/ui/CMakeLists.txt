# CEF LIB

# TODO: Automatically fuzzy find suffixes?
find_libs(CEF_LIBS cef_dll_wrapper LIB cef)
find_path(CEF_INCLUDE_DIRS include/cef_app.h)

find_library(UDEV_LIBS udev)
set(CEF_LIBS ${UDEV_LIBS} ${CEF_LIBS})
# UI MODULE

include_directories(${CEF_INCLUDE_DIRS})

declare_module(ui .)
add_lib(ui)

# Pulled in by including cube.h
config_enet(module_ui NOLINK)
config_sdl(module_ui NOLINK)

function(config_ui targ)
  message(STATUS "Configuring ${targ} with ui")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  include_directories(${CEF_INCLUDE_DIRS})
  target_link_libs(${targ} module_ui ${CEF_LIBS} module_util ${NOLINK})

  config_enet(${targ} ${NOLINK})
  config_sdl(${targ} ${NOLINK})
endfunction()
