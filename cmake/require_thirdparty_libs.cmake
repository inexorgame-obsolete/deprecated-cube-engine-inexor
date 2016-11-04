# Adding third-party libs is a three step procedure:
# 1) Add it to conanfile.txt
# 2) Add a require_XY() to this file
# 3) Use the require_XY() in the places you need


# NOTE: Locally built dependencies need to go to the bottom
# so all the others are available and the GLIBC C++11 ABI detection
# works (it needs a list of libraries to check whether they use the new ABI)

include(ExternalProject)
find_package(PkgConfig)

set(pwd "${CMAKE_CURRENT_SOURCE_DIR}")

#### Threads

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

function(require_threads targ)
  if(NOT CMAKE_THREAD_LIBS_INIT)
    return()
  endif()
  message(STATUS "Configuring ${targ} with system threads (API: ${CMAKE_THREAD_LIBS_INIT})")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libraries(${targ} Threads::Threads)
endfunction()

#### OpenGL
find_package(OpenGL)

set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} CACHE INTERNAL "")
set(OPENGL_LIBS ${OPENGL_gl_LIBRARY} CACHE INTERNAL "")
register_possible_dependency(${OPENGL_LIBs})

function(require_opengl targ)
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
register_possible_dependency(${SDL2_LIBS})

find_path(SDL2_BASE_INCLUDE_DIRS  SDL.h       PATH_SUFFIXES SDL2)
find_path(SDL2_IMAGE_INCLUDE_DIRS SDL_image.h PATH_SUFFIXES SDL2)
find_path(SDL2_MIXER_INCLUDE_DIRS SDL_mixer.h PATH_SUFFIXES SDL2)
set(SDL2_INCLUDE_DIRS
  ${SDL2_BASE_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_MIXER_INCLUDE_DIRS} CACHE INTERNAL "")

function(require_sdl targ)
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

  require_opengl(${targ} ${NOLINK})
endfunction()

#### BOOST (System)

find_libs(BOOST_SYSTEM_LIBS boost_system)
find_path(BOOST_SYSTEM_INCLUDE_DIRS boost/system/config.hpp)

register_possible_dependency(${BOOST_SYSTEM_LIBS})

function(require_boost_system targ)
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

register_possible_dependency(${BOOST_THREAD_LIBS})

function(require_boost_thread targ)
  message(STATUS "Configuring ${targ} with Boost Thread")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  require_boost_system(${targ} ${NOLINK})
  require_threads(${targ} ${NOLINK})

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

register_possible_dependency(${BOOST_RANDOM_LIBS})

function(require_boost_random targ)
  message(STATUS "Configuring ${targ} with Boost Random")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  require_boost_system(${targ} ${NOLINK})

  include_directories(${BOOST_RANDOM_INCLUDE_DIRS})
  target_link_libs(${targ} ${BOOST_RANDOM_LIBS} ${NOLINK})
endfunction()

#### BOOST (ASIO)

find_path(ASIO_INCLUDE_DIRS boost/asio.hpp)

function(require_asio targ)
  message(STATUS "Configuring ${targ} with Boost Asio")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()
  
  add_definitions(-DBOOST_ASIO_HAS_STD_CHRONO)
  include_directories(${ASIO_INCLUDE_DIRS})

  if (WIN32)
    target_link_libs(${targ} ws2_32 ${NOLINK})
  endif()

  require_boost_system(${targ})
endfunction()

function(require_boost_asio)
  require_asio(${ARGN})
endfunction()

#### BOOST (Filesystem)

find_libs(BOOST_FILESYSTEM_LIBS boost_filesystem)
find_path(BOOST_FILESYSTEM_INCLUDE_DIRS boost/filesystem.hpp)

register_possible_dependency(${BOOST_FILESYSTEM_LIBS})

function(require_boost_filesystem targ)
  message(STATUS "Configuring ${targ} with Boost Filesystem")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
  target_link_libs(${targ} ${BOOST_FILESYSTEM_LIBS} ${NOLINK})
  target_include_directories(${targ} PUBLIC ${BOOST_FILESYSTEM_INCLUDE_DIRS})

  require_boost_system(${targ} ${NOLINK})
endfunction()

#### BOOST (Regex)

find_libs(BOOST_REGEX_LIBS boost_regex)
find_path(BOOST_REGEX_INCLUDE_DIRS boost/regex.hpp)

register_possible_dependency(${BOOST_REGEX_LIBS})

function(require_boost_regex targ)
  message(STATUS "Configuring ${targ} with Boost Regex")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} ${BOOST_REGEX_LIBS} ${NOLINK})
  target_include_directories(${targ} PUBLIC ${BOOST_REGEX_INCLUDE_DIRS})

endfunction()

#### BOOST (program options)

find_libs(BOOST_PROGRAM_OPTS_LIBS boost_program_options)
find_path(BOOST_PROGRAM_OPTS_INCLUDE_DIRS boost/program_options.hpp)

register_possible_dependency(${BOOST_PROGRAM_OPTS_LIBS})

function(require_boost_program_options targ)
  message(STATUS "Configuring ${targ} with Boost program options")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} ${BOOST_PROGRAM_OPTS_LIBS} ${NOLINK})
  target_include_directories(${targ} PUBLIC ${BOOST_PROGRAM_OPTS_INCLUDE_DIRS})

endfunction()

#### Protobuf

find_libs(PROTOBUF_LIBRARIES protobuf)
find_path(PROTOBUF_INCLUDE_DIRS google/protobuf/service.h)

register_possible_dependency(${PROTOBUF_LIBRARIES})

if (NOT DEFINED PROTOC_EXE)
  find_program(PROTOC_EXE protoc NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH )
  # grpc and protoc make problems if versions arent matching.
  # and since grpc is beta its not shipped for most linux distros
  # and we pack it prebuilt into the platform repo
endif()

function(require_protobuf targ)
  message(STATUS "Configuring ${targ} with protobuf")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  add_definitions(-DPROTOBUF_USE_DLLS)
  include_directories(${PROTOBUF_INCLUDE_DIRS})
  target_link_libs(${targ} ${NOLINK} ${PROTOBUF_LIBRARIES})
endfunction()

#### gRPC

find_libs(GRPC_LIBRARIES gpr LIB grpc_unsecure LIB grpc++_unsecure)
find_path(GRPC_INCLUDE_DIRS grpc/grpc.h)
find_path(GRPCPP_INCLUDE_DIRS grpc++/grpc++.h)


register_possible_dependency(${GRPC_LIBRARIES})

if (NOT DEFINED GRPC_EXE)
  find_program(GRPC_EXE grpc_cpp_plugin NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH )
  # grpc and protoc make problems if versions arent matching.
  # and since grpc is beta its not shipped for most linux distros
  # and we pack it prebuilt into the platform repo
endif()

function(require_grpc targ)
  message(STATUS "Configuring ${targ} with gRPC")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  include_directories(${GRPC_INCLUDE_DIRS} ${GRPCPP_INCLUDE_DIRS})
  target_link_libs(${targ} ${NOLINK} ${GRPC_LIBRARIES})

  require_protobuf(${targ} ${NOLINK})
endfunction()

# This macro lets us create a require_XY (with XY beeing the name of the library) without code dublication
# but just the name of the library (as it can be found in conan).
# Additional defines can be put last (e.g. "-DWINDOWS=0 -DDEFINENOSTATICS"), in case conanfile.txt don't provide the necessary arguments for them.
macro(add_require_conan_lib_function name)
  string(TOLOWER ${name} name_lower) # Tow different scopes for name_lower and NAME_UPPER: this a macro which does simple text replacement.
  function(require_${name_lower} targ)
    message(STATUS "Configuring ${targ} with library ${name}")
    if (";${ARGN};" MATCHES ";NOLINK;")
      set(NOLINK "NOLINK")
    endif()

    # This is a macro so the name_lower will have been overridden by other add_require_conan_lib_function invocations in the main time.
    string(TOUPPER ${name} NAME_UPPER)
    target_compile_definitions(${targ} PUBLIC ${CONAN_DEFINES_${NAME_UPPER}} ${ARGN})
    target_include_directories(${targ} PUBLIC ${CONAN_INCLUDE_DIRS_${NAME_UPPER}})
    target_link_libs(${targ} ${CONAN_LIBS_${NAME_UPPER}} ${NOLINK})
  endfunction()
endmacro()

# Google test (unit testing framework)
add_require_conan_lib_function(gtest)

# PugiXML (xml parser, used for our gluecode generator)
add_require_conan_lib_function(pugixml)

# Rapidjson (JSON parser)
add_require_conan_lib_function(RapidJSON "-DRAPIDJSON_SSE2")

# ZLIB (fast file compression)
add_require_conan_lib_function(zlib)

# ENet (reliable UDP networking lib)
add_require_conan_lib_function(enet)

# spdlog (fast logging library)
add_require_conan_lib_function(spdlog)
