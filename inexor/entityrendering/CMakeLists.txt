declare_module(entityrendering .)
add_lib(entityrendering)

require_sdl(module_entityrendering NOLINK)
require_math(module_entityrendering NOLINK)

function(require_entityrendering targ)
  message(STATUS "Configuring ${targ} with module_entityrendering")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_entityrendering ${NOLINK})

  require_sdl(${targ} ${NOLINK})
  require_math(${CLIENT_BINARY})
  require_entity(${CLIENT_BINARY})

endfunction()
