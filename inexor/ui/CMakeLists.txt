# CEF LIB

# TODO: Automatically fuzzy find suffixes?
find_libs(CEF_LIBS cef_dll_wrapper LIB cef libcef)
find_path(CEF_INCLUDE_DIRS include/cef_app.h)

# UI MODULE

include_directories(${CEF_INCLUDE_DIRS})

declare_module(ui .)
add_lib(ui)

# Pulled in by including cube.h
require_enet(module_ui)
require_sdl(module_ui)
require_util(module_ui)

# Configure use of the sandbox.
option(USE_SANDBOX OFF)

if(USE_SANDBOX)
    # Definition required by CEF_sandbox.lib.
    add_definitions(-DPSAPI_VERSION=1)
    # Definition used by apps to test if the sandbox is enabled.
    add_definitions(-DCEF_USE_SANDBOX)
endif()

function(require_ui targ)
  message(STATUS "Configuring ${targ} with module_ui")

  include_directories(${CEF_INCLUDE_DIRS})
  target_link_libraries(${targ} module_ui ${CEF_LIBS})

  require_util(${targ})
  require_enet(${targ})
  require_sdl(${targ})
endfunction()
