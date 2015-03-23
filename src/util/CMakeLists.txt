# UTIL Module ##############

declare_module(util .)

add_lib(util)

function(config_util targ)
  message(STATUS "Configuring ${targ} with util")

  target_link_libs(${targ} module_util)
endfunction()
