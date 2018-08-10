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

  target_link_libraries(${targ} Threads::Threads)
endfunction()

#### OpenGL
find_package(OpenGL)

set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} CACHE INTERNAL "")
set(OPENGL_LIBS ${OPENGL_gl_LIBRARY} CACHE INTERNAL "")

function(require_opengl targ)
  message(STATUS "Configuring ${targ} with OpenGL (${OPENGL_LIBS})")

  if (OPENGL_INCLUDE_DIRS)
    include_directories("${OPENGL_INCLUDE_DIRS}")
  endif()

  target_link_libraries(${targ} ${OPENGL_LIBS})
endfunction()

set(BOOST_ROOT ${CONAN_BOOST_ROOT})
set(BOOST_LIBRARYDIR ${CONAN_LIB_DIRS_BOOST})
set(BOOST_INCLUDEDIR ${CONAN_INCLUDE_DIRS_BOOST})

#set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_NO_SYSTEM_PATHS ON)

# Use the same threading as we found out from find_package(Threads)
add_definitions(-DBOOST_ALL_NO_LIB ${CONAN_DEFINES_BOOST})
if (CMAKE_USE_PTHREADS_INIT)
  set(Boost_THREADAPI "pthread")
  add_definitions(-DBOOST_THREAD_PTHREAD -DBOOST_THREAD_POSIX)
elseif(CMAKE_USE_WIN32_THREADS_INIT)
  add_definitions(-DBOOST_THREAD_WIN32)
  set(Boost_THREADAPI "win32")
endif()
# conan: we can override FindBoost
# include("${CONAN_BOOST_ROOT}/FindBoost.cmake") disable it until we have our runtime chosen.

find_package(Boost REQUIRED
  COMPONENTS
  thread
  random
  filesystem
  regex
  program_options
  system
)

# This macro lets us create a require_boost_XY for all other libs. name is the canonical name without spaces, e.g. "program_options"
# additional defines can be listed, but WITHOUT "-D" and in quotes, followed by additional **boost lib requirements** e.g. "system thread"
macro(add_require_boost_lib_function name defines requirements)
  function(require_boost_${name} TARG)
    message(STATUS "Configuring ${TARG} with library Boost ${name}")

    string(TOUPPER ${name} NAME_UPPER) # we want PROGRAM_OPTIONS as variable

    string(REPLACE " " ";" DEFINES_LIST "${defines}") # string to list
    string(REPLACE " " ";" REQUIREMENTS_LIST "${requirements}") # string to list, we just add those libs
    target_compile_definitions(${TARG} PUBLIC ${CONAN_DEFINES_BOOST} ${defines})
    target_include_directories(${TARG} PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(${TARG} ${Boost_${NAME_UPPER}_LIBRARY})
    foreach(REQ ${REQUIREMENTS_LIST})
      string(TOUPPER ${REQ} REQ_UPPER)
      target_link_libraries(${TARG} ${Boost_${REQ_UPPER}_LIBRARY})
    endforeach()
  endfunction()
endmacro()

add_require_boost_lib_function(random "" "system")
add_require_boost_lib_function(filesystem "BOOST_FILESYSTEM_NO_DEPRECATED" "system")
add_require_boost_lib_function(thread "BOOST_THREAD_LIB" "")
add_require_boost_lib_function(regex "" "")
add_require_boost_lib_function(program_options "" "")

# This macro lets us create a require_xy (with XY being the name of the library) without code duplication
# but just the name of the library (as it can be found in conan).
# require_xy is all lower case. LIMITATION: lib name ("XY") is not allowed to contain "-".
macro(add_require_conan_lib_function name)
  string(TOLOWER ${name} name_lower)
  string(REPLACE "-" "_" name_lower_alphanumeric ${name_lower})
  function(require_${name_lower_alphanumeric} targ)
    target_link_libraries(${targ} CONAN_PKG::${name})
  endfunction()
endmacro()

# Google test (unit testing framework)
add_require_conan_lib_function(gtest)

# PugiXML (xml parser, used for our gluecode generator)
add_require_conan_lib_function(pugixml)

# kainjow-mustache (a template engine, used for our gluecode generator)
add_require_conan_lib_function(kainjow-mustache)

# ZLIB (fast file compression)
add_require_conan_lib_function(zlib)

# ENet (reliable UDP networking lib)
add_require_conan_lib_function(enet)

# Protobuf (XML or JSON like serialization format but in binary, so it needs an compiler)
set(protobuf_MODULE_COMPATIBLE ON)
add_require_conan_lib_function(protobuf)
find_program(PROTOBUF_PROTOC_EXECUTABLE protoc PATHS ${CONAN_BIN_DIRS_PROTOBUF} NO_CMAKE_ENVIRONMENT_PATH  NO_CMAKE_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH )

# gRPC (googles remote procedure call framework, used for Inexors networking and scripting binding)
add_require_conan_lib_function(grpc)
find_program(GRPC_GRPC_CPP_PLUGIN grpc_cpp_plugin PATHS ${CONAN_BIN_DIRS_GRPC} NO_CMAKE_ENVIRONMENT_PATH  NO_CMAKE_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH )

# spdlog (fast logging library)
add_require_conan_lib_function(spdlog)

# fmt (fast and convenient formatting library)
add_require_conan_lib_function(fmt)

# CEF Chromium Embedded Framework (Embedded Browser used for the UI)
add_require_conan_lib_function(CEF)

# sdl2 (input output framework)
add_require_conan_lib_function(sdl2)

# sdl2_image (image loader library)
add_require_conan_lib_function(sdl2_image)

# libjpeg turbo a dependency of sdl2_image
add_require_conan_lib_function(libjpeg-turbo)

# libpng a dependency of sdl2_image
add_require_conan_lib_function(libpng)

# sdl2_mixer (sound library)
# add_require_conan_lib_function(sdl2_mixer)

## Wrapper for all SDL libs (you usually want all of them)
function(require_sdl targ)
  message(STATUS "Configuring ${targ} with SDL2")

  require_sdl2(${targ})
  require_libjpeg_turbo(${targ})
  require_libpng(${targ})
  require_sdl2_image(${targ})
  # require_sdl2_mixer(${targ})
  require_opengl(${targ})
endfunction()
