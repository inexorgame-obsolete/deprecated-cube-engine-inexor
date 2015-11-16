
add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
declare_module(geom .)
add_lib(geom)

config_sdl(module_geom NOLINK)

function(config_geom targ)
  message(STATUS "Configuring ${targ} with geom")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()
  add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
  target_link_libs(${targ} module_geom ${NOLINK})

  config_sdl(${targ} ${NOLINK})
endfunction()
