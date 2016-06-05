
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

set(gluegen_out_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(gluegen_out_h ${gluegen_out_dir}/treedata.gen.hpp)
set(gluegen_out_proto ${gluegen_out_dir}/treedata.gen.proto)
set(gluegen_out ${gluegen_out_h} ${gluegen_out_proto})

set(gluegen_template_h ${gluegen_out_dir}/treedata.gen.template.hpp)
set(gluegen_template_proto ${gluegen_out_dir}/treedata.gen.template.proto)

if (NOT DEFINED GLUEGEN_EXE)
  find_program(GLUEGEN_EXE gluecodegenerator)
endif()

set(CLANG_FLAGS_AND_DEFS
  "${GNU_OR_CLANG_COMPILER_FLAGS} ${GCC_OR_CLANG_CXX_COMPILER_FLAGS} -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS" #TODO
)

# Search sources
file(GLOB_RECURSE PARSED_FILES ${SOURCE_DIR}/**.cpp)
#set(PARSED_FILES "E:/weitere-Dokumente/Git/code2/inexor/engine/main.cpp")
set(ALL_PARSED_FILES "")

set(FLAGS_AND_DEFS "-pipe -fno-strict-aliasing -fsigned-char -Wall -Wno-switch -Wno-deprecated-declarations -Wno-missing-braces -fdiagnostics-show-option -fno-threadsafe-statics -std=c++14  -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -I\"E:/weitere-Dokumente/Git/code2/\" -I\"E:/weitere-Dokumente/Git/code2/platform/include/all/\" -I\"E:/weitere-Dokumente/Git/code2/platform/include/windows/\" -I\"E:/weitere-Dokumente/Git/code2/platform/include/windows/SDL2/\" -frtti -fexceptions -DWIN32 -D_WIN32 -D_WINDOWS -DWINDOWS -DNOMINMAX -D_WIN32_WINNT=0x0600 -D_MATH_DEFINES_DEFINED -DWIN64 -DBOOST_OS_WINDOWS -DBOOST_ASIO_HAS_STD_CHRONO -D__REFLECTION_PASS__ -fno-ms-compatibility")

foreach(curfile ${PARSED_FILES})
  set(ALL_PARSED_FILES "${ALL_PARSED_FILES} --parse-file ${curfile}")
endforeach()

message(STATUS "ALL_PARSED_FILES: ${ALL_PARSED_FILES}")
message(STATUS "CLANG_FLAGS_AND_DEFS: ${CLANG_FLAGS_AND_DEFS}")
message(STATUS "gluegen_out: ${gluegen_out}")
add_custom_command(
  OUTPUT ${gluegen_out}
  COMMAND ${GLUEGEN_EXE}
      "--template-proto ${gluegen_template_proto} \
      --template-header  ${gluegen_template_h}    \
      --out-proto ${gluegen_out_proto}            \
      --out-header ${gluegen_out_h}               \
      --namespace inexor::tree                    \
      ${FLAGS_AND_DEFS}                           \
      ${ALL_PARSED_FILES}")
set_source_files_properties(${gluegen_out} PROPERTIES GENERATED TRUE)
add_custom_target(run_gluegen DEPENDS ${gluegen_out})


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

