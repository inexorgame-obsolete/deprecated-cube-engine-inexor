declare_module(math .)
add_lib(math)

require_sdl(module_math NOLINK)

function(require_math targ)
  message(STATUS "Configuring ${targ} with module_math")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_math ${NOLINK})

  require_sdl(${targ} ${NOLINK})

endfunction()
