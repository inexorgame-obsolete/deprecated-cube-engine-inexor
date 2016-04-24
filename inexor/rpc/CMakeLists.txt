message(STATUS "Detecting Protobuf...")

# RPC PROTOCOL FILE TARGET

set(RPC_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(protoc_in ${RPC_FILE_DIR}/inexor_service.proto)
set(protoc_out_dir "${CMAKE_BINARY_DIR}/inexor/rpc/inexor/rpc/")
set(protoc_out_cc ${protoc_out_dir}/inexor_service.pb.cc)
set(protoc_out
  ${protoc_out_cc}
  ${protoc_out_dir}/inexor_service.pb.h)

add_custom_command(
  OUTPUT ${protoc_out}
  COMMAND ${PROTOC_EXE}
      --proto_path=${MAINDIR}
      --cpp_out=${CMAKE_BINARY_DIR}/inexor/rpc/ ${protoc_in}
  DEPENDS ${protoc_in}
  MAIN_DEPENDENCY ${protoc_in})
set_source_files_properties(${protoc_out} PROPERTIES GENERATED TRUE)
add_custom_target(run_protoc DEPENDS ${protoc_out})

set(RPC_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/inexor/rpc/" CACHE INTERNAL "")

set_source_files_properties(
  ${protoc_out_cc} PROPERTIES GENERATED TRUE)

# MODULE ###############

declare_module(rpc .)
set(RPC_MODULE_SOURCES ${RPC_MODULE_SOURCES} ${protoc_out_cc}
  CACHE INTERNAL "")

add_lib(rpc)
require_net(module_rpc NOLINK)
require_sdl(module_rpc NOLINK)
require_enet(module_rpc NOLINK)
require_protobuf(module_rpc NOLINK)
require_cxx11_abi(module_rpc NOLINK)

function(require_rpc targ)
  message(STATUS "Configuring ${targ} with module_rpc")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  add_dependencies(${targ} run_protoc)
  target_link_libs(${targ} ${NOLINK} module_rpc module_net module_util)

  require_protobuf(${targ})
  require_net(${targ})
  require_enet(${targ})
  require_cxx11_abi(${targ} NOLINK)
endfunction()

