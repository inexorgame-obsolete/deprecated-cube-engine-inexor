# CEF LIB

# TODO: Automatically fuzzy find suffixes?
find_libs(CEF_LIBS cef_dll_wrapper LIB cef)
find_path(CEF_INCLUDE_DIRS include/cef_app.h)

# UI MODULE

include_directories(${CEF_INCLUDE_DIRS})

declare_module(ui .)
add_lib(ui)

# Pulled in by including cube.h
require_enet(module_ui NOLINK)
require_sdl(module_ui NOLINK)
require_cxx11_abi(module_ui NOLINK)

function(require_ui targ)
  message(STATUS "Configuring ${targ} with ui")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  include_directories(${CEF_INCLUDE_DIRS})
  target_link_libs(${targ} module_ui ${CEF_LIBS} module_util ${NOLINK})

  require_enet(${targ} ${NOLINK})
  require_sdl(${targ} ${NOLINK})
  require_cxx11_abi(${targ} ${NOLINK})
endfunction()
