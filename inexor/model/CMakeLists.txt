
declare_module(model .)
add_lib(model)

# Acquire our dependencies for this module
require_util(module_model)

# This function is used to bind this module into another module/application
function(require_model targ)
  message(STATUS "Configuring ${targ} with module_model")
  target_link_libraries(${targ} module_model) # Tell the requiring module that it needs to link with our static lib

  require_util(${targ})

endfunction()
