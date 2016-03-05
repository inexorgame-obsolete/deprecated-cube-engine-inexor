# UTIL Module ##############

declare_module(util .)

add_lib(util)
<<<<<<< 38aaeb257094e375e5d1cadc9df4ff0ef97245c4
require_boost_thread(module_util NOLINK)
require_boost_random(module_util NOLINK)
require_cxx11_abi(module_util NOLINK)
=======
config_boost_thread(module_util NOLINK)
config_boost_random(module_util NOLINK)
config_boost_system(module_util NOLINK)
config_boost_filesystem(module_util NOLINK)
config_cxx11_abi(module_util NOLINK)
>>>>>>> Automatically detect the path of cef_subprocess (platform independent,

function(require_util targ)
  message(STATUS "Configuring ${targ} with module_util")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_util ${NOLINK})

  config_boost_thread(${targ} ${NOLINK})
  config_boost_random(${targ} ${NOLINK})
  config_boost_system(${targ} ${NOLINK})
  config_boost_filesystem(${targ} ${NOLINK})
  config_cxx11_abi(${targ} ${NOLINK})
endfunction()
