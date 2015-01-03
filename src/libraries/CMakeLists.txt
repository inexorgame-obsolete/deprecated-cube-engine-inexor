# MUPARSER
set(muparser_dir "${CMAKE_CURRENT_SOURCE_DIR}/muparser")

file(GLOB_RECURSE headers ${muparser_dir}/include/*.h)
set(MUPARSER_HEADERS ${headers} CACHE INTERNAL "")

prepend(sources ${muparser_dir}/src/ muParser muParserBase
  muParserBytecode muParserCallback muParserError
  muParserInt muParserTokenReader)
set(MUPARSER_SOURCES ${sources} CACHE INTERNAL "")

source_group(muparser FILES ${headers} ${sources})
set(MUPARSER_INCLUDE_DIRS "${muparser_dir}/include" CACHE INTERNAL "")

# CEF Lib for Rendering HTML ingame
find_library(CEF_LIBRARIES "libcef")
set(CEF_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cef3")
set(CEF_WRAPPER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cef3/libcef_dll")
set(CEF_INCLUDE_DIRS ${CEF_DIR} ${CEF_WRAPPER_DIR} CACHE INTERNAL "")

# We need to do this before add_subdirectory because the cmakefile sucks in there
include_directories(${CEF_INCLUDE_DIRS})
add_subdirectory(${CEF_WRAPPER_DIR})
