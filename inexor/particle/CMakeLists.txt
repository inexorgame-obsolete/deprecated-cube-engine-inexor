declare_module(particle .)
add_lib(particle)

require_sdl(module_particle NOLINK)
require_math(module_particle NOLINK)

function(require_particle targ)
  message(STATUS "Configuring ${targ} with module_particle")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_particle ${NOLINK})

  require_sdl(${targ} ${NOLINK})
  require_math(${CLIENT_BINARY})
  require_entity(${CLIENT_BINARY})

endfunction()
