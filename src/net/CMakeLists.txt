# ASIO LIB ################

message(STATUS "Detecting ASIO...")
find_path(ASIO_INCLUDE_DIRS asio.hpp)

function(config_net targ)
  if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Using ASIO in standalone mode")
    add_definitions(-DASIO_STANDALONE)
  else()
    message(STATUS "Using ASIO with boost. Detecting Boost...")
  endif()
endfunction()

declare_module(net .)
