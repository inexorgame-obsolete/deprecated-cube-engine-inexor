declare_module(vscript .)
add_lib(vscript)

require_sdl(module_vscript NOLINK)
require_math(module_vscript NOLINK)

function(require_vscript targ)
  message(STATUS "Configuring ${targ} with module_vscript")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_vscript ${NOLINK})

  require_sdl(${targ} ${NOLINK})
  require_math(${CLIENT_BINARY})
  require_entity(${CLIENT_BINARY})

endfunction()
