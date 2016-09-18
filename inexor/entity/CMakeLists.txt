declare_module(entity .)
add_lib(entity)

require_sdl(module_entity NOLINK)
require_muparser(module_entity NOLINK)

function(require_entity targ)
  message(STATUS "Configuring ${targ} with module_entity")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_entity ${NOLINK})

  require_sdl(${targ} ${NOLINK})
  require_muparser(${targ} ${NOLINK})

endfunction()
