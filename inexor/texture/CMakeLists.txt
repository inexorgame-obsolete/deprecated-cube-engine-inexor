declare_module(texture .)
add_lib(texture)

require_sdl(module_texture NOLINK)
require_filesystem(module_texture NOLINK)

function(require_texture targ)
  message(STATUS "Configuring ${targ} with module_texture")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_texture ${NOLINK})

  require_sdl(${targ} ${NOLINK})
  require_filesystem(${targ} ${NOLINK})
endfunction()
