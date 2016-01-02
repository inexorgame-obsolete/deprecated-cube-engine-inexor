declare_module(texture .)
add_lib(texture)

config_sdl(module_texture NOLINK)

function(config_texture targ)
  message(STATUS "Configuring ${targ} with texture")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_texture ${NOLINK})

  config_sdl(${targ} ${NOLINK})
endfunction()
