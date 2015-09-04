# CEF LIB

# TODO: Automatically fuzzy find suffixes?
find_libs(CEF_LIBS cef_dll_wrapper LIB cef)
find_path(CEF_INCLUDE_DIRS include/cef_app.h)

find_library(UDEV_LIBS udev)
find_path(UDEV_INCLUDE_DIR libudev.h)
# UI MODULE

include_directories(${CEF_INCLUDE_DIRS})
include_directories(${UDEV_INCLUDE_DIR})

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
  include_directories(${UDEV_INCLUDE_DIR})
  target_link_libs(${targ} module_ui ${CEF_LIBS} module_util ${NOLINK})
  target_link_libs(${targ} module_ui ${UDEV_LIBS} module_util ${NOLINK})

  config_enet(${targ} ${NOLINK})
  config_sdl(${targ} ${NOLINK})
endfunction()
