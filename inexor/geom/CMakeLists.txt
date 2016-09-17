declare_module(geom .)
add_lib(geom)

function(require_geom targ)
  message(STATUS "Configuring ${targ} with module_geom")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_geom ${NOLINK})
endfunction()
