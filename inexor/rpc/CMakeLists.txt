
# Generate Tree API Glue code

# Before building Inexor we generate our serialization glue.

set(gluegen_out_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(gluegen_out_h ${gluegen_out_dir}/treedata.gen.hpp)
set(gluegen_out_proto ${gluegen_out_dir}/treedata.gen.proto)
set(gluegen_out ${gluegen_out_h} ${gluegen_out_proto})

set(gluegen_template_h ${gluegen_out_dir}/treedata.gen.template.hpp)
set(gluegen_template_proto ${gluegen_out_dir}/treedata.gen.template.proto)

if (NOT DEFINED GLUEGEN_EXE)
  find_program(GLUEGEN_EXE gluecodegenerator)
endif()

set(DOXYGEN_XML_FOLDER ${MAINDIR}/doc/xml)

message(STATUS "Gluegen runs with command: "
              " --template-proto " "${gluegen_template_proto}"
              " --template-header " "${gluegen_template_h}"
              " --out-proto " "${gluegen_out_proto}"
              " --out-header " "${gluegen_out_h}"
              " --namespace " "inexor::tree"
              " --XML-AST-folder " "${DOXYGEN_XML_FOLDER}")

add_custom_target(
  run_gluegen
  COMMAND ${GLUEGEN_EXE}
  "--template-proto" "${gluegen_template_proto}"
  "--template-header" "${gluegen_template_h}"
  "--out-proto" "${gluegen_out_proto}"
  "--out-header" "${gluegen_out_h}"
  "--namespace" "inexor::tree"
  "--XML-AST-folder" "${DOXYGEN_XML_FOLDER}")

set_source_files_properties(${gluegen_out} PROPERTIES GENERATED TRUE)

# Generate RPC PROTOCOL API Headers/Sources

# Before building Inexor we generate our serialization headers from
# language independent .proto files

set(RPC_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(protoc_in ${RPC_FILE_DIR}/treedata.gen.proto)

set(protoc_out_dir_should "${CMAKE_BINARY_DIR}/inexor/rpc/") # this should be the outdir
set(protoc_out_dir "${CMAKE_BINARY_DIR}/inexor/rpc/inexor/rpc/") # But this actually is 
                                                             # (since we want to include with full namespace paths)

set(protoc_out_cc ${protoc_out_dir}/treedata.gen.pb.cc ${protoc_out_dir}/treedata.gen.grpc.pb.cc)
set(protoc_out_h ${protoc_out_dir}/treedata.gen.pb.h ${protoc_out_dir}/treedata.gen.grpc.pb.h)
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
set(RPC_MODULE_SOURCES ${RPC_MODULE_SOURCES} ${protoc_out} ${gluegen_out} CACHE INTERNAL "") # Attach to generated source module list

add_lib(rpc)

target_include_directories(module_rpc PUBLIC ${RPC_INCLUDE_DIRS})

if(COMPILER_MSVC)
  set_target_properties(module_rpc PROPERTIES COMPILE_FLAGS "/bigobj")
  #needed since our generated header is rich in templates and big in general, which makes it super big.
endif()

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

