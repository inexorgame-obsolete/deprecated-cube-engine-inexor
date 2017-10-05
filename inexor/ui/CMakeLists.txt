# UI MODULE
declare_module(ui .)

# exclude the subfolder cef_subprocess from the source file list, as these files are in a different binary.
foreach(src ${UI_MODULE_SOURCES})
  if(src MATCHES ".*cef_subprocess.*")
    list(REMOVE_ITEM UI_MODULE_SOURCES ${src})
  endif()
endforeach()

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

add_subdirectory(cef_subprocess)
