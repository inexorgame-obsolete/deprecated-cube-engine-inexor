# UTIL Module ##############

declare_module(util .)

add_lib(util)
require_boost_thread(module_util)
require_boost_random(module_util)
require_spdlog(module_util)

function(require_util targ)
  message(STATUS "Configuring ${targ} with module_util")

  target_link_libraries(${targ} module_util)

  require_boost_thread(${targ})
  require_boost_random(${targ})
  require_spdlog(${targ})
endfunction()
