declare_module(texture .)
add_lib(texture)

require_sdl(module_texture)
require_filesystem(module_texture)

function(require_texture targ)
  message(STATUS "Configuring ${targ} with module_texture")
  target_link_libraries(${targ} module_texture)

  require_sdl(${targ})
  require_filesystem(${targ})
endfunction()
