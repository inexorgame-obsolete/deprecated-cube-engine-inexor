declare_module(crashreporter .)
add_lib(crashreporter)

config_cxx11_abi(${targ} NOLINK)

function(config_crashreporter targ)
  message(STATUS "Configuring ${targ} with crashreporter")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  config_cxx11_abi(${targ} ${NOLINK})
  target_link_libs(${targ} module_crashreporter ${NOLINK})

endfunction()
