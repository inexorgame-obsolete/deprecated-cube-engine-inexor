
add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
declare_module(flowgraph .)
add_lib(flowgraph)

config_sdl(module_flowgraph NOLINK)

function(config_flowgraph targ)
  message(STATUS "Configuring ${targ} with flowgraph")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()
  add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
  target_link_libs(${targ} module_flowgraph ${NOLINK})

  config_sdl(${targ} ${NOLINK})
endfunction()
