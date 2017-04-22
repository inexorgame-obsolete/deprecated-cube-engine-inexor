
# generate source file list
declare_module(network .)

# exclude any template file from the source list (it wont compile)
foreach(src ${NETWORK_MODULE_SOURCES})
  if(src MATCHES ".*template.*")
    list(REMOVE_ITEM NETWORK_MODULE_SOURCES ${src})
  endif()
endforeach()
group_sources(${NETWORK_MODULE_HEADERS} ${NETWORK_MODULE_SOURCES})

include(require_run_gluegen.cmake)


# @param BUILD_FLAGS see require_run_gluegen
function(require_network targ BUILD_FLAGS)
  require_grpc(${targ})
  require_util(${targ})
  require_enet(${targ})

  # Folder where generated files land: somewhere in the build/ dir.
  set(GLUEGEN_OUT_DIR "${CMAKE_BINARY_DIR}/inexor/network/${targ}")
  set(network_dir "${SOURCE_DIR}/network")
  require_run_gluegen(${targ} ${BUILD_FLAGS} ${network_dir} ${GLUEGEN_OUT_DIR})

  target_include_directories(${targ} PUBLIC ${GLUEGEN_OUT_DIR})
endfunction()

