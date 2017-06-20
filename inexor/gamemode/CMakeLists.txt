
declare_module(gamemode .)
add_lib(gamemode)

# This function is used to bind this module into another module/application
function(require_gamemode targ)
  message(STATUS "Configuring ${targ} with module_gamemode")

  target_link_libraries(${targ} module_gamemode)
endfunction()
