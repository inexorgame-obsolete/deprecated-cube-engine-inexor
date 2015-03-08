message(STATUS "Detecting Protobuf...")

find_cpp_library(PROTOBUF_LIBRARIES protobuf)
find_path(PROTOBUF_INCLUDE_DIRS google/protobuf/service.h)

# PROTOBUF COMPILER #######

if (NOT DEFINED PROTOC_EXE)
  find_program(PROTOC_EXE protoc)
endif()

# RPC PROTOCOL FILE TARGET

set(RPC_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(protoc_in ${RPC_FILE_DIR}/inexor_service.proto)
set(protoc_out_cc ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc)
set(protoc_out
  ${protoc_out_cc}
  ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.h)

add_custom_command(
  OUTPUT ${protoc_out}
  COMMAND ${PROTOC_EXE} --proto_path=${SOURCE_DIR}
      --cpp_out=${CMAKE_BINARY_DIR}/src ${protoc_in}
  DEPENDS ${protoc_in})
set_source_files_properties(${protoc_out} PROPERTIES GENERATED TRUE)
add_custom_target(inexor_protoc DEPENDS ${protoc_out})

set(RPC_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/src/" CACHE INTERNAL "")

set_source_files_properties(
  ${protoc_out_cc} PROPERTIES GENERATED TRUE)

# MODULE ###############

add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)
include_directories(${PROTOBUF_INCLUDE_DIRS} ${RPC_INCLUDE_DIRS})

declare_module(rpc .)
set(RPC_MODULE_SOURCES ${RPC_MODULE_SOURCES} ${protoc_out_cc}
  CACHE INTERNAL "")

add_library(inexor_rpc STATIC ${RPC_MODULE_SOURCES})
config_net(inexor_rpc NOLINK)

function(config_rpc targ)
  message(STATUS "Configuring ${targ} with rpc")

  add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)
  add_dependencies(${targ} inexor_protoc)
  include_directories(${PROTOBUF_INCLUDE_DIRS} ${RPC_INCLUDE_DIRS})
  target_link_libraries_wrapper(${targ} inexor_rpc
    inexor_net ${PROTOBUF_LIBRARIES})
  config_net(${targ})
endfunction()

