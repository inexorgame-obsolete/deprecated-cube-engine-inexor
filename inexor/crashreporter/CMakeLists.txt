declare_module(crashreporter .)
add_lib(crashreporter)

function(config_crashreporter targ)
  message(STATUS "Configuring ${targ} with crashreporter")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_crashreporter ${NOLINK})

endfunction()