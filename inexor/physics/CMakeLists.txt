
declare_module(physics .)
add_lib(physics)

# Acquire our dependencies for this module
require_util(module_physics)

# This function is used to bind this module into another module/application
function(require_physics targ)
  message(STATUS "Configuring ${targ} with module_physics")
  target_link_libraries(${targ} module_physics) # Tell the requiring module that it needs to link with our static lib

  require_util(${targ})

endfunction()
