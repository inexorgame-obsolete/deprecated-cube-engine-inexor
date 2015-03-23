# ASIO LIB ################

message(STATUS "Detecting ASIO...")
find_path(ASIO_INCLUDE_DIRS asio.hpp)

# NET MODULE ##############

declare_module(net .)

include_directories(${ASIO_INCLUDE_DIRS})
add_lib(net)

if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  message(STATUS "Using ASIO in standalone mode")
  add_definitions(-DASIO_STANDALONE)
else()
  message(STATUS "Using ASIO with boost. Detecting Boost...")
endif()

function(config_net targ)
  message(STATUS "Configuring ${targ} with net")

  if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_definitions(-DASIO_STANDALONE)
  endif()

  include_directories(${ASIO_INCLUDE_DIRS})
  if (NOT ";${ARGN};" MATCHES ";NOLINK;")
    target_link_libs(${targ} module_net)
    if (WIN32)
      target_link_libs(${targ} ws2_32)
    endif()
  endif()
endfunction()
