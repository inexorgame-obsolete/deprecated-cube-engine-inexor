declare_module(muparser .)
add_lib(muparser)

function(require_muparser targ)
  message(STATUS "Configuring ${targ} with module_muparser")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_muparser ${NOLINK})
endfunction()
