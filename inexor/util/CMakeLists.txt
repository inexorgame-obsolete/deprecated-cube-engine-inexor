# UTIL Module ##############

declare_module(util .)

add_lib(util)
require_boost_thread(module_util NOLINK)
require_boost_random(module_util NOLINK)
require_spdlog(module_util NOLINK)
require_cxx11_abi(module_util NOLINK)

function(require_util targ)
  message(STATUS "Configuring ${targ} with module_util")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_util ${NOLINK})

  require_boost_thread(${targ} ${NOLINK})
  require_boost_random(${targ} ${NOLINK})
  require_spdlog(${targ} ${NOLINK})
  require_cxx11_abi(${targ} ${NOLINK})
endfunction()
