## This is the cmake file for the gluegen standalone tool.
## Its used for generating reflection boilerplate code and hence gets
## shipped precompiled as tool which is integrated in the build-process on every platform.
## If you still need to compile this generator e.g. for extending the tool for other needs,
## you need to edit the LLVM_DIR and the other marked stuff below.

# clang is a subproject of llvm
####################################### EDIT_HERE
####################################### EDIT_HERE

# Windows-note: Make sure all slashes are unix style! / instead of \ 

set(LLVM_DIR "E:/weitere-Dokumente/Software/llvm-3.8.0.src")

set(LLVM_LIB_DIR "E:/weitere-Dokumente/Software/llvm-3.8.0.src/build/MinSizeRel/lib")

# If you followed the clang build tutorial step by step and also named your llvm build folder
# "build", then the lines below need no further adaption, but just LLVM_DIR above.
set(LLVM_GENERAL_INCLUDE_DIR  "${LLVM_DIR}/include")
set(CLANG_GENERAL_INCLUDE_DIR "${LLVM_DIR}/tools/clang/include")

# Path where your generated project files lay for the llvm suite.
set(LLVM_BUILD_INCLUDE_DIR  "${LLVM_DIR}/build/include")

# Path where your generated project files lay for the downloaded clang project.
set(CLANG_BUILD_INCLUDE_DIR "${LLVM_DIR}/build/tools/clang/include")

######################################## /EDIT_HERE
######################################## /EDIT_HERE


set(inexor_basedir "../..")
set(EXE_DIR "out") ## Must be defined before of add_app


list(INSERT CMAKE_LIBRARY_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR} ${LLVM_LIB_DIR})

declare_module(gluegen .)

find_libs(LLVM_LIBS LLVMCore LIB LIB LLVMOption LIB LLVMMC
 LIB LLVMSupport
 LIB LLVMMCParser
 LIB LLVMBitReader
 LIB clangAST
 LIB clangBasic
 LIB clangDriver
 LIB clangFormat
 LIB clangFrontend
 LIB clangTooling
 LIB clangSerialization
 LIB clangParse
 LIB clangSema
 LIB clangEdit
 LIB clangAnalysis
 LIB clangASTMatchers
 LIB clangToolingCore
 LIB clangRewrite
 LIB clangLex
)


add_app(gluecodegenerator ${GLUEGEN_MODULE_SOURCES} CONSOLE_APP)

require_boost_program_options(gluecodegenerator)
require_boost_regex(gluecodegenerator)

target_link_libs(gluecodegenerator ${LLVM_LIBS})
include_directories(
  ${LLVM_BUILD_INCLUDE_DIR}
  ${LLVM_GENERAL_INCLUDE_DIR}
  ${CLANG_BUILD_INCLUDE_DIR}
  ${CLANG_GENERAL_INCLUDE_DIR}
)
