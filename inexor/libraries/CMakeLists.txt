# TODO: Write a lib detector that does the following: Search for cmake definitions; search for pkg-cfg's; search for libs and headers; everyting may be specified multiple times

include(ExternalProject)
find_package(PkgConfig)

set(pwd "${CMAKE_CURRENT_SOURCE_DIR}")

#### Debug

function(config_debug targ)
  message(STATUS "Configuring ${targ} with Cocoa")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    return()
  endif()

  if (MSVC)
    target_link_libs(${targ} dbghelp)
  endif()
endfunction()

#### Cocoa/OSX

function(config_cocoa targ)
  message(STATUS "Configuring ${targ} with Cocoa")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()


  if (OS_MACOSX)
    target_link_libs(${targ} CoreServices Cocoa ${NOLINK})
  endif()
endfunction()

#### Threads

if (NOT THREADAPI)
  find_package(Threads REQUIRED)
  
  if(WIN32 AND CMAKE_USE_WIN32_THREADS_INIT)
    set(THREADAPI "win32" CACHE INTERN "")
  elseif(CMAKE_USE_PTHREADS_INIT OR CMAKE_HP_PTHREADS_INIT)
    set(THREADAPI "pthreads" CACHE INTERN "")
  endif()
endif()

if (THREADAPI STREQUAL "pthreads")
  set(THREADAPI_PTHREADS 1 CACHE INTERN "")

  find_libs(PTHREADS_LIBS pthread pthreadGC2 winpthread)
  find_path(PTHREADS_INCLUDE_DIRS pthread.h)

elseif(THREADAPI STREQUAL "win32")
  set(THREADAPI_WIN32 1 CACHE INTERN "")
endif()

message(STATUS "THREADAPI : ${THREADAPI}")

function(config_threads targ)
  message(STATUS "Configuring ${targ} with Threads (${THREADAPI})")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  if (THREADAPI_PTHREADS)
    target_link_libs(${targ} ${PTHREADS_LIBS} ${NOLINK})
    include_directories(${PTHREADS_INCLUDE_DIRS})
  elseif(THREADAPI_WIN32)
    # pass
  else()
    message(SEND_ERROR "Unkown thread API: ${THREADAPI}")
  endif()

endfunction()

#### OpenGL

find_package(OpenGL)

set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} CACHE INTERN "")
set(OPENGL_LIBS ${OPENGL_gl_LIBRARY} CACHE INTERN "")

function(config_opengl targ)
  message(STATUS "Configuring ${targ} with OpenGL (${OPENGL_LIBS})")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  if (OPENGL_INCLUDE_DIRS)
    include_directories("${OPENGL_INCLUDE_DIRS}")
  endif()

  target_link_libs(${targ} ${OPENGL_LIBS} ${NOLINK})
endfunction()

#### SDL

find_libs(SDL2_LIBS SDL2 LIB SDL2_image LIB SDL2_mixer)

find_path(SDL2_BASE_INCLUDE_DIRS  SDL.h       PATH_SUFFIXES SDL2)
find_path(SDL2_IMAGE_INCLUDE_DIRS SDL_image.h PATH_SUFFIXES SDL2)
find_path(SDL2_MIXER_INCLUDE_DIRS SDL_mixer.h PATH_SUFFIXES SDL2)
set(SDL2_INCLUDE_DIRS
  ${SDL2_BASE_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_MIXER_INCLUDE_DIRS} CACHE INTERN "")

function(config_sdl targ)
  message(STATUS "Configuring ${targ} with SDL")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  include_directories(${SDL2_INCLUDE_DIRS})
  target_link_libs(${targ} ${SDL2_LIBS} ${NOLINK})

  if(OS_WINDOWS)
    target_link_libs(${targ} winmm ${NOLINK})
    if(NOT MSVC) 
      add_definitions(-mwindows) # This is GUI!
    endif()
  elseif(OS_POSIX)
    target_link_libs(${targ} dl rt ${NOLINK})
  endif()

  config_cocoa(${targ} ${NOLINK})
  config_opengl(${targ} ${NOLINK})
endfunction()

#### ZLIB

find_package(ZLIB)

if (${ZLIB_FOUND})
  set(ZLIB_LIBS ${ZLIB_LIBRARY} CACHE INTERN "")
  set(ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIR} CACHE INTERN "")
else()
  find_libs(ZLIB_LIBS z zlib1)
  find_path(ZLIB_INCLUDE_DIRS zlib.h)

  message(STATUS "ZLIB_LIBRARY2 = ${ZLIB_LIBRARY2}")
  message(STATUS "ZLIB_INCLUDE_DIR2 = ${ZLIB_INCLUDE_DIR2}")

  if (EXISTS ${ZLIB_LIBRARY} AND EXISTS ${ZLIB_INCLUDE_DIR})
    set(ZLIB_FOUND 1)
  else()
    message(ERROR "Could not find zlib")
  endif()
endif()

function(config_zlib targ)
  message(STATUS "Configuring ${targ} with ZLIB")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} ${ZLIB_LIBS} ${NOLINK})
  include_directories(${ZLIB_INCLUDE_DIRS})
endfunction()

#### ENET

find_libs(ENET_LIBS enet)
find_path(ENET_INCLUDE_DIRS enet/enet.h)

function(config_enet targ)
  message(STATUS "Configuring ${targ} with ENET")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  include_directories(${ENET_INCLUDE_DIRS})
  target_link_libs(${targ} ${ENET_LIBS} ${NOLINK})
  if (OS_WINDOWS)
    # Why does enet need winmm
    target_link_libs(${targ} ws2_32 winmm ${NOLINK})
  endif()
endfunction()

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
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  include_directories(${MUPARSER_INCLUDE_DIRS})
  target_link_libs(${targ} module_muparser ${NOLINK})
endfunction()

#### Googletest

set(GTEST_DIR "${pwd}/googletest" CACHE INTERNAL "")
set(GTEST_INCLUDE_DIRS "${GTEST_DIR}/include"
  CACHE INTERNAL "")

# NOTE: For some reason compiling with pthreads fails for win32;
# can we fix this?
set(gtest_args
      -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -Dgtest_disable_pthreads=true)

# GCC 5.1 Introduces a new C++11 ABI; see the root CMakeLists
# TODO: Can we implicitly add that definition?
if (OS_WINDOWS AND NOT MSVC)
  list(APPEND gtest_args -DCMAKE_CXX_FLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 )
endif()

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
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  add_dependencies(${targ} build_gtest)
  include_directories(${GTEST_INCLUDE_DIRS})
  target_link_libs(${targ} gtest ${NOLINK})
endfunction()

#### BOOST (System)

find_libs(BOOST_SYSTEM_LIBS boost_system)
find_path(BOOST_SYSTEM_INCLUDE_DIRS boost/system/config.hpp)

function(config_boost_system targ)
  message(STATUS "Configuring ${targ} with Boost System")

  target_link_libs(${targ} ${BOOST_SYSTEM_LIBS})
  target_include_directories(${targ} PUBLIC ${BOOST_SYSTEM_INCLUDE_DIRS})
endfunction()

#### BOOST (Thread)

find_path(BOOST_THREAD_INCLUDE_DIRS boost/thread.hpp)

if (THREADAPI_WIN32)
  find_libs(BOOST_THREAD_LIBS boost_thread_win32 boost_thread)
else()
  find_libs(BOOST_THREAD_LIBS boost_thread)
endif()

function(config_boost_thread targ)
  message(STATUS "Configuring ${targ} with Boost Thread")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  config_boost_system(${targ} ${NOLINK})
  config_threads(${targ} ${NOLINK})

  add_definitions(-DBOOST_THREAD_LIB)

  if (THREADAPI_PTHREADS)
    add_definitions(-DBOOST_THREAD_PTHREAD -DBOOST_THREAD_POSIX)
  elseif(THREADAPI_WIN32)
    #add_definitions(-DBOOST_THREAD_WIN32) # redundant
  endif()

  target_link_libs(${targ} ${BOOST_THREAD_LIBS} ${NOLINK})
  target_include_directories(${targ} PUBLIC ${BOOST_THREAD_INCLUDE_DIRS})
endfunction()

#### BOOST (Random)

find_libs(BOOST_RANDOM_LIBS boost_random)
find_path(BOOST_RANDOM_INCLUDE_DIRS boost/random.hpp)

function(config_boost_random targ)
  message(STATUS "Configuring ${targ} with Boost Random")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  config_boost_system(${targ} ${NOLINK})

  include_directories(${BOOST_RANDOM_INCLUDE_DIRS})
  target_link_libs(${targ} ${BOOST_RANDOM_LIBS} ${NOLINK})
endfunction()

#### BOOST (ASIO)

find_path(ASIO_INCLUDE_DIRS boost/asio.hpp)

function(config_asio targ)
  message(STATUS "Configuring ${targ} with Boost Asio")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  include_directories(${ASIO_INCLUDE_DIRS})

  if (WIN32)
    target_link_libs(${targ} ws2_32 ${NOLINK})
  endif()

  config_boost_system(${targ})
endfunction()

function(config_boost_asio)
  config_asio(${ARGN})
endfunction()
