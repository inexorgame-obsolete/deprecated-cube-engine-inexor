include(ExternalProject)
set(pwd "${CMAKE_CURRENT_SOURCE_DIR}")

#### MUPARSER

set(muparser_dir "${pwd}/muparser")

file(GLOB_RECURSE headers ${muparser_dir}/include/*.h)
set(MUPARSER_HEADERS ${headers} CACHE INTERNAL "")

prepend(sources ${muparser_dir}/src/ muParser muParserBase
  muParserBytecode muParserCallback muParserError
  muParserInt muParserTokenReader)
set(MUPARSER_SOURCES ${sources} CACHE INTERNAL "")

source_group(muparser FILES ${headers} ${sources})
set(MUPARSER_INCLUDE_DIRS "${muparser_dir}/include" CACHE INTERNAL "")

include_directories(${MUPARSER_INCLUDE_DIRS})
add_library(module_muparser STATIC ${MUPARSER_SOURCES} ${headers})

function(config_muparser targ)
  message(STATUS "Configuring ${targ} with muparser")

  include_directories(${MUPARSER_INCLUDE_DIRS})
  target_link_libs(${targ} module_muparser)
endfunction()

#### Googletest

set(GTEST_DIR "${pwd}/googletest" CACHE INTERNAL "")
set(GTEST_INCLUDE_DIRS "${GTEST_DIR}/include"
  CACHE INTERNAL "")

set(gtest_args
      -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -Dgtest_disable_pthreads=true)
if (CMAKE_TOOLCHAIN_FILE)
  list(APPEND gtest_args
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
endif()

ExternalProject_Add(build_gtest
  SOURCE_DIR "${GTEST_DIR}"
  INSTALL_COMMAND ""
  CMAKE_ARGS ${gtest_args})

# This is a it of a hack to find the actual location of the
# built library
ExternalProject_Get_Property(build_gtest BINARY_DIR)
set(GTEST_LIB_DIR ${BINARY_DIR} CACHE INTERN "")

function(config_gtest targ)
  message(STATUS "Configuring ${targ} with google test")

  add_dependencies(${targ} build_gtest)
  include_directories(${GTEST_INCLUDE_DIRS})
  target_link_libs(${targ} gtest)
endfunction()
