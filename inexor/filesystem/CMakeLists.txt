
# We work in 2 different scopes in this file: One is this subproject added through add_lib and called module_<ourname>
#                                             The other one is the scope of require_<ourname> used to bind this module
#                                             into other modules and hence operates **in the scope of where it gets executed!**

declare_module(filesystem .) # Get the source lists of all files in this folder (and register us as module)
add_lib(filesystem)          # Our module is **a static lib** which gets linked into other modules or apps.
                             # Its name is "module_filesystem" (due to this function)

# Acquire our dependencies for this module
# ("module_filesystem" is used and not just "filesystem", since we require it for this subproject)
require_sdl(module_filesystem)
require_boost_filesystem(module_filesystem)
require_rapidjson(module_filesystem)
require_util(module_filesystem)
require_enet(module_filesystem)

# This function is used to bind this module into another module/application
function(require_filesystem targ)
  message(STATUS "Configuring ${targ} with module_filesystem")
  target_link_libraries(${targ} module_filesystem) # Tell the requiring module that it needs to link with our static lib

  # Also tell the other module that it needs our dependencies:
  require_sdl(${targ}) # we need sdl since we havent refractored cube.hpp good enough yet
  require_boost_filesystem(${targ})
  require_rapidjson(${targ})
  require_util(${targ})
  require_enet(${targ}) # same cube.hpp shit

endfunction()
