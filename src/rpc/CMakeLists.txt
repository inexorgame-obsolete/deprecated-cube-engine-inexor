message(STATUS "Detecting Protobuf...")

find_cpp_library(PROTOBUF_LIBRARIES protobuf)
find_path(PROTOBUF_INCLUDE_DIRS google/protobuf/service.h)

# PROTOBUF COMPILER #######

if (NOT DEFINED PROTOC_EXE)
  find_program(PROTOC_EXE protoc)
endif()

# RPC PROTOCOL FILE TARGET

set(RPC_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

function(config_rpc targ)
  add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)

  add_custom_command(
    OUTPUT
      ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.h
      ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc
    COMMAND
    ${PROTOC_EXE} --proto_path=${SOURCE_DIR}
        --cpp_out=${CMAKE_BINARY_DIR}/src
        ${RPC_FILE_DIR}/inexor_service.proto
    DEPENDS
    ${RPC_FILE_DIR}/inexor_service.proto)

  set_source_files_properties(
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.h
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc
    PROPERTIES GENERATED TRUE)

  add_custom_target(${targ}_protoc DEPENDS
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.h
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc)
  add_dependencies(${targ} ${targ}_protoc)
endfunction()

# INCLUDES ###############

set(RPC_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/src/" CACHE INTERNAL "")

declare_module(rpc .)
set(RPC_MODULE_SOURCES
  ${RPC_MODULE_SOURCES}
  ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc
  CACHE INTERNAL "")
