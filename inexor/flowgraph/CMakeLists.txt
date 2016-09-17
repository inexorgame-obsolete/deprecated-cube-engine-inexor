declare_module(flowgraph .)
add_lib(flowgraph)

function(require_flowgraph targ)
  message(STATUS "Configuring ${targ} with module_flowgraph")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_flowgraph ${NOLINK})
endfunction()
