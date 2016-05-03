
# Generate RPC PROTOCOL API Headers/Sources

# Before building Inexor we generate our serialization headers from
# language independent .proto files

set(RPC_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(protoc_in ${RPC_FILE_DIR}/inexor_service.proto)

set(protoc_out_dir_should "${CMAKE_BINARY_DIR}/inexor/rpc/") # this should be the outdir
set(protoc_out_dir "${CMAKE_BINARY_DIR}/inexor/rpc/inexor/rpc/") # But this actually is 
                                                             # (since we want to include with full namespace paths)

set(protoc_out_cc ${protoc_out_dir}/inexor_service.pb.cc ${protoc_out_dir}/inexor_service.grpc.pb.cc)
set(protoc_out_h ${protoc_out_dir}/inexor_service.pb.h ${protoc_out_dir}/inexor_service.grpc.pb.h)
set(protoc_out ${protoc_out_cc} ${protoc_out_h})


add_custom_command(
  OUTPUT ${protoc_out}
  COMMAND ${PROTOC_EXE}
      --proto_path=${MAINDIR}
      --cpp_out=${protoc_out_dir_should} ${protoc_in}
  COMMAND ${PROTOC_EXE}
      --plugin=protoc-gen-grpc=${GRPC_EXE}
      --proto_path=${MAINDIR}
      --grpc_out=${protoc_out_dir_should} ${protoc_in}
  DEPENDS ${protoc_in}
  MAIN_DEPENDENCY ${protoc_in})
set_source_files_properties(${protoc_out} PROPERTIES GENERATED TRUE)
add_custom_target(run_protoc DEPENDS ${protoc_out})

# Folder where generated files land: somewhere in the build/ dir.
set(RPC_INCLUDE_DIRS "${protoc_out_dir_should}" CACHE INTERNAL "")

set_source_files_properties(
  ${protoc_out_cc} PROPERTIES GENERATED TRUE)

# MODULE ###############

declare_module(rpc .)
set(RPC_MODULE_SOURCES ${RPC_MODULE_SOURCES} ${protoc_out}
  CACHE INTERNAL "")

add_lib(rpc)

target_include_directories(module_rpc PUBLIC ${RPC_INCLUDE_DIRS})

require_sdl(module_rpc NOLINK)
#require_enet(module_rpc NOLINK)
require_grpc(module_rpc NOLINK)
require_cxx11_abi(module_rpc NOLINK)
require_util(module_rpc NOLINK)

function(require_rpc targ)
  message(STATUS "Configuring ${targ} with module_rpc")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  add_dependencies(${targ} run_protoc)
  target_include_directories(${targ} PUBLIC ${RPC_INCLUDE_DIRS})
  target_link_libs(${targ} ${NOLINK} module_rpc)

  require_sdl(${targ} ${NOLINK}) # Issue #194 "Server needs SDL to build"
  require_grpc(${targ} ${NOLINK})
#  require_enet(${targ})
  require_cxx11_abi(${targ} ${NOLINK})
  require_util(${targ} ${NOLINK})
endfunction()

