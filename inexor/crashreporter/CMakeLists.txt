declare_module(crashreporter .)
add_lib(crashreporter)

require_cxx11_abi(${targ} NOLINK)

function(require_crashreporter targ)
  message(STATUS "Configuring ${targ} with module_crashreporter")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  require_cxx11_abi(${targ} ${NOLINK})
  target_link_libs(${targ} module_crashreporter ${NOLINK})

endfunction()
