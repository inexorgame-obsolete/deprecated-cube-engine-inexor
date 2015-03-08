# ASIO LIB ################

message(STATUS "Detecting ASIO...")
find_path(ASIO_INCLUDE_DIRS asio.hpp)

# NET MODULE ##############

declare_module(net .)

add_library(inexor_net STATIC ${NET_MODULE_SOURCES})

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
    target_link_libraries_wrapper(${targ} inexor_net)

    if (WIN32)
      target_link_libraries_wrapper(${targ} ws2_32)
    endif()
  endif()
endfunction()
