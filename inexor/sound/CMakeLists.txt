
declare_module(sound .)
add_lib(sound)

# Acquire our dependencies for this module
require_util(module_sound)

# This function is used to bind this module into another module/application
function(require_sound targ)
  message(STATUS "Configuring ${targ} with module_sound")
  target_link_libraries(${targ} module_sound) # Tell the requiring module that it needs to link with our static lib

  require_util(${targ})

endfunction()
