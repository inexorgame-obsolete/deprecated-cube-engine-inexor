declare_module(entitysys .)
add_lib(entitysys)

function(require_entitysys targ)
  message(STATUS "Configuring ${targ} with module_entitysys")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_entitysys ${NOLINK})
endfunction()
