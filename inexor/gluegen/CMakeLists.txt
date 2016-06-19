## This is the cmake file for the gluegen standalone tool.
## Its used for generating reflection boilerplate code and hence gets
## shipped precompiled as tool which is integrated in the build-process on every platform.
## If you still need to compile this generator e.g. for extending the tool for other needs,
## you need to edit the LLVM_DIR and the other marked stuff below.

# clang is a subproject of llvm
 
if(COMPILER_GCC OR COMPILER_CLANG)
  list(INSERT CMAKE_LIBRARY_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR} /usr/lib/llvm-3.8/lib)
  list(INSERT CMAKE_INCLUDE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR} /usr/lib/llvm-3.8/include)
endif()

find_path(LLVM_INCLUDE_DIR llvm/AsmParser/Parser.h)
find_path(CLANG_INCLUDE_DIR clang/Tooling/Tooling.h)
find_path(MUSTACHE_INCLUDE_DIR kainjow/mustache.hpp)

find_libs(LLVM_LIBS
     clangFrontend
 LIB clangSerialization
 LIB clangDriver
 LIB clangParse
 LIB clangSema
 LIB clangAnalysis
 LIB clangASTMatchers
 LIB clangAST
 LIB clangBasic
 LIB clangEdit
 LIB clangLex
 LIB clangTooling
 LIB clangFormat
 LIB clangToolingCore
 LIB clangRewrite
 LIB LLVMOption
 LIB LLVMMCParser
 LIB LLVMMC
 LIB LLVMBitReader
 LIB LLVMCore
 LIB LLVMSupport
)

declare_module(gluegen .)
add_app(gluecodegenerator ${GLUEGEN_MODULE_SOURCES} CONSOLE_APP)

target_link_libs(gluecodegenerator ${LLVM_LIBS})

require_cxx11_abi(gluecodegenerator)
require_boost_program_options(gluecodegenerator)
require_boost_regex(gluecodegenerator)
require_threads(gluecodegenerator) # Need to be required after the llvm libs!
require_zlib(gluecodegenerator)

if(COMPILER_GCC OR COMPILER_CLANG)
  target_link_libs(gluecodegenerator dl tinfo)
endif()


include_directories(
  ${MUSTACHE_INCLUDE_DIR}
  ${LLVM_INCLUDE_DIR}
  ${CLANG_INCLUDE_DIR}
)
