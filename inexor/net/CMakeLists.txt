declare_module(net .)
add_lib(net)

config_asio(module_net NOLINK)

function(config_net targ)
  message(STATUS "Configuring ${targ} with net")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_net ${NOLINK})

  config_asio(${targ} ${NOLINK})
endfunction()
