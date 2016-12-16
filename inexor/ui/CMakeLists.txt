# UI MODULE
declare_module(ui .)
add_lib(ui)

# Pulled in by including cube.h
require_enet(module_ui)
require_sdl(module_ui)
require_util(module_ui)
require_cef(module_ui)

function(require_ui targ)
  message(STATUS "Configuring ${targ} with module_ui")

  include_directories(${CEF_INCLUDE_DIRS})
  target_link_libraries(${targ} module_ui ${CEF_LIBS})

  require_util(${targ})
  require_enet(${targ})
  require_sdl(${targ})
  require_cef(${targ})
endfunction()
