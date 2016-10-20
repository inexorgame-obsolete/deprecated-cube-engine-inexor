
# generate source file list
declare_module(rpc .)

# exclude any template file from the source list (it wont compile)
foreach(src ${RPC_MODULE_SOURCES})
  if(src MATCHES ".*template.*")
    list(REMOVE_ITEM RPC_MODULE_SOURCES ${src})
  endif()
endforeach()
group_sources(${RPC_MODULE_HEADERS} ${RPC_MODULE_SOURCES})

include(${SOURCE_DIR}/gluegen/require_run_gluegen.cmake)


# @param BUILD_FLAGS see require_run_gluegen
function(require_rpc targ BUILD_FLAGS)
  message(STATUS "Configuring ${targ} with module_rpc")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()


  require_grpc(${targ} ${NOLINK})
  require_cxx11_abi(${targ} ${NOLINK})
  require_util(${targ} ${NOLINK})

  # Folder where generated files land: somewhere in the build/ dir.
  set(GLUEGEN_OUT_DIR "${CMAKE_BINARY_DIR}/inexor/rpc/${targ}")
  set(rpc_dir "${SOURCE_DIR}/rpc")
  require_run_gluegen(${targ} ${BUILD_FLAGS} ${rpc_dir} ${GLUEGEN_OUT_DIR})

  target_include_directories(${targ} PUBLIC ${GLUEGEN_OUT_DIR})

  # add_dependencies(${targ} run_doxygen_${targ})
  # add_dependencies(${targ} run_gluegen_${targ})
  # add_dependencies(${targ} run_protoc_${targ})
endfunction()

