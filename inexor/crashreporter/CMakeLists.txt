declare_module(crashreporter .)
add_lib(crashreporter)


function(require_crashreporter targ)
  message(STATUS "Configuring ${targ} with module_crashreporter")

  target_link_libraries(${targ} module_crashreporter)
endfunction()
