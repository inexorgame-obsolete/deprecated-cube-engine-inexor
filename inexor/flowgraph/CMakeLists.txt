declare_module(flowgraph .)
add_lib(flowgraph)

require_sdl(module_flowgraph NOLINK)
require_math(module_flowgraph NOLINK)

function(require_flowgraph targ)
  message(STATUS "Configuring ${targ} with module_flowgraph")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_flowgraph ${NOLINK})

  require_sdl(${targ} ${NOLINK})
  require_math(${CLIENT_BINARY})

endfunction()
