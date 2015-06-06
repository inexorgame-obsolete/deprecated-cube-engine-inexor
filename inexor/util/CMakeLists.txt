# UTIL Module ##############

declare_module(util .)

add_lib(util)
config_boost_thread(module_util NOLINK)
config_boost_random(module_util NOLINK)

function(config_util targ)
  message(STATUS "Configuring ${targ} with util")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_util ${NOLINK})

  config_boost_thread(${targ} ${NOLINK})
  config_boost_random(${targ} ${NOLINK})
endfunction()
