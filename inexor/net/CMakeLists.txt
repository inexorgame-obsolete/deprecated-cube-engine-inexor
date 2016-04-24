declare_module(net .)
add_lib(net)

require_asio(module_net NOLINK)
require_cxx11_abi(module_net NOLINK)

function(require_net targ)
  message(STATUS "Configuring ${targ} with module_net")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_net ${NOLINK})

  require_cxx11_abi(module_net ${NOLINK})
  require_asio(${targ} ${NOLINK})
endfunction()
