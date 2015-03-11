# TODO: Unify flags and lib detection on ALL plattforms as much as possible
# TODO: Move functions to an extra file
# TODO: Automatically detect new modules
# TODO: Encapsulate all settings in a module
# TODO: Write a lib detector that does the following: Search for cmake definitions; search for pkg-cfg's; search for libs and headers; everyting may be specified multiple times

# Wrong folder: User attempted to generate from src instead of the main-inexor folder
if(NOT DEFINED PROJECT_ARCH)
    message(FATAL_ERROR "You are generating from the wrong folder! \"Where is the Source:\" (currently: ${MAINDIR}) should point to the Main directory (!) of Inexor")
endif()


# TODO: Write function fallback_find_package?
# TODO: We should stick to singular in all lib detection
find_package(ZLIB)
if(NOT ${ZLIB_FOUND})
  find_library(ZLIB_LIBRARY2 NAMES z zlib1)
  find_path(ZLIB_INCLUDE_DIR2 zlib.h)

  message(STATUS "ZLIB_LIBRARY2 = ${ZLIB_LIBRARY2}")
  message(STATUS "ZLIB_INCLUDE_DIR2 = ${ZLIB_INCLUDE_DIR2}")

  if (EXISTS ${ZLIB_LIBRARY} AND EXISTS ${ZLIB_INCLUDE_DIR})
    set(ZLIB_FOUND 1)
  else()
    message(ERROR "Could not find zlib")
  endif()
endif()

find_package(OpenGL)
find_package(PkgConfig)


# Allow disabling Server/Client-subproject
option(BUILD_CLIENT "Build the client" ${OPENGL_FOUND})
option(BUILD_SERVER "Build the server" ON)


message(STATUS "Detecting Libs...")

# Linux Libraries for Server AND Client
if(OS_LINUX)

    # SDL (crossplatform Library for anything general)
    if(NOT BUILD_SDL2_LOCAL AND PKG_CONFIG_FOUND)
        message(STATUS "Using pkg-config to detect SDL2...")
        pkg_check_modules(SDL2 QUIET sdl2)
        if(SDL2_FOUND)
            message(STATUS "Found SDL2.")
            message(STATUS "include: ${SDL2_INCLUDE_DIRS}")
        else()
            message(FATAL_ERROR "SDL2 not found.")
        endif()
    else()
        if(PKG_CONFIG_FOUND)
            message(STATUS "Using local SDL2.")
        else()
            message(STATUS "Using local SDL2. (could not find PKG_CONFIG)")
        endif()
        set(SDL2_LIBRARIES "SDL2")
    endif()
    set(SDL2_LIBRARIES "${SDL2_LIBRARIES};SDL2_image;SDL2_mixer")
    add_definitions(-D_REENTRANT -D_THREAD_SAFE)


    # ENet networking library
    if(NOT DEFINED ENET_LIBRARIES AND NOT DEFINED LOCAL_ENET)
        set(LOCAL_ENET 1 CACHE INTERNAL "Use local enet library")
    elseif(DEFINED LOCAL_ENET)
        set(LOCAL_ENET ${LOCAL_ENET} CACHE INTERNAL "Use local enet library")
    else()
        set(LOCAL_ENET 0 CACHE INTERNAL "Use local enet library")
    endif()

    if(${LOCAL_ENET})
        message(STATUS "Building local ENet")
        add_subdirectory(libraries/enet)
    endif()
endif()


# common MACOSX and Windows Libraries
if(OS_MACOSX OR OS_WINDOWS)
    find_library(ENET_LIBRARIES enet)
    find_path(ENET_INCLUDE_DIRS enet/enet.h)


    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_IMAGE_LIBRARY SDL2_image)
    find_library(SDL2_MIXER_LIBRARY SDL2_mixer)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY}
        ${SDL2_IMAGE_LIBRARY})

    find_path(SDL2_INCLUDE_DIR       SDL.h       PATH_SUFFIXES SDL2)
    find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h PATH_SUFFIXES SDL2)
    find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h PATH_SUFFIXES SDL2)
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
endif()

# COCOA for SQL on OSX
if(OS_MACOSX)
  find_library(CORESERVICES_LIBRARY CoreServices)
  find_library(COCOA_LIBRARY Cocoa)
  list(APPEND SDL2_LIBRARIES
      ${CORESERVICES_LIBRARY} ${COCOA_LIBRARY})
endif()

# Windows Libraries for Server AND Client
if(OS_WINDOWS)
    if(NOT MSVC)
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} -static-libgcc -static-libstdc++)
    endif()
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} kernel32 ws2_32 winmm)
endif()

# USAGE: declare_module(<NAME> [PATH])
#
# Automatically search for headers and source files inside
# a module, export these and add a group for visual studio
# that contains all the sources.
#
# ARGUMENTS:
#   NAME – The name of the module
#   PATH – The relative path all the sources are inside
#
# SIDE EFFECTS:
#   * ${NAME}_MODULE_HEADERS – such a variable is created;
#     it contains a list of all headers in this module
#   * ${NAME}_MODULE_SOURCES – such a variable is created;
#     it contains a list of all source files in this module
#   * A VS source group is added with the name ${NAME}; it
#     contains all the headers and source files in this module

set(ALLMODULES "" CACHE INTERNAL "")
function(declare_module NAME PATH)
  get_filename_component(abs
    "${CMAKE_CURRENT_SOURCE_DIR}/${PATH}" REALPATH)
  string(TOUPPER "${NAME}" mod)
  message(STATUS "DECLARE MODULE(${NAME}, ${PATH}) -> ${mod} inside ${abs}")

  # Search headers
  file(GLOB_RECURSE headers ${abs}/**.h)
  set(${mod}_MODULE_HEADERS ${headers}
    CACHE INTERNAL "Headers of the ${NAME} module")

  # Search sources
  file(GLOB_RECURSE sources ${abs}/**.cpp)
  set(${mod}_MODULE_SOURCES ${sources}
    CACHE INTERNAL "Sources of the ${NAME} module")

  # Save for group_modules()
  set(ALLMODULES ${ALLMODULES} ${mod} CACHE INTERNAL "")
endfunction()

# USAGE: group_modules()
# 
# Set up Source_groups for VS/XCode
# Has to be called for every target
# 
function(group_modules)
    message(STATUS "allmodules ${ALLMODULES}")
    foreach(mod ${ALLMODULES})
        string(TOLOWER "${mod}" gname)
        source_group(${gname} FILES ${${mod}_MODULE_HEADERS} ${${mod}_MODULE_SOURCES})
        message(STATUS "set group ${gname} FILES ${${mod}_MODULE_HEADERS} ${${mod}_MODULE_SOURCES}")
    endforeach()
endfunction()

# USAGE: prepend(<VARIABLE> <PREP> [ARGS]...)
#
# Prepend ${PREP} to each element of ${ARGS} and save the
# result in VARIABLE.
#
# ARGUMENTS:
#   VARIABLE – The variable to save the sources in
#   PREP     – The string to prepend
#   ARGS...  – The strings to prepend to
# SIDE EFFECTS:
#   * Creates a variable named VARIABLE and writes our
#     result there.
#
function(prepend variable prep)
  set(res "")
  foreach(s ${ARGN})
    set(res ${res} "${prep}/${s}")
  endforeach()
  set(${variable} ${res} PARENT_SCOPE)
endfunction()

# Wrapper around find_library to autodetect _debug and _release versions of a library
# Reason see lib/readme
#
# Note: only effects msvc so far
# Usage: find_cpp_library(<RETURNVAR> <name>)
# Arguments:
#   Returnvar   -   Usually the <LibraryName>_LIBRARY, but can be set differently.
#                   It will contain the found lib afterwards.
#   name        -   the Library name
# Example: find_cpp_library(PROTOBUF_LIBRARIES protobuf)
#
function(find_cpp_library RETURNVAR LIBNAME)
    if(DEFINED HAS_FIND_LIBRARY_WRAPPER)
        definition_find_cpp_library(${RETURNVAR} ${LIBNAME})
        set(${RETURNVAR} ${${RETURNVAR}} CACHE INTERNAL "")
    else()
        find_library(${RETURNVAR} ${LIBNAME})
    endif()
endfunction()

# USAGE: target_link_libraries_wrapper( <BINARYNAME> [ARGS] )
#
# Wrapper around target_link libs to be able to set different libs for debug and release
# (Necessary for MSVC in combination with stdlib-dependend Libs)
#
# ARGUMENTS
#  BINARYNAME - The Name of the target to link the libraries to
#  ARGS...    - The Libraries
#
function(target_link_libraries_wrapper BINARYNAME)
    if(DEFINED HAS_FIND_LIBRARY_WRAPPER)

        set(C_LIBS "")   # No need to seperately link c-libs
        set(CPP_LIBS_DEBUG "")
        set(CPP_LIBS_RELEASE "")

        foreach(CURLIB ${ARGN})
            if(${CURLIB} MATCHES "(.*)_release(.*)")
                set(CPP_LIBS_RELEASE ${CURLIB})
            elseif(${CURLIB} MATCHES "(.*)_debug(.*)")
                set(CPP_LIBS_DEBUG ${CURLIB})
            else()
                set(C_LIBS ${C_LIBS} ${CURLIB})
            endif()
        endforeach()

        message(STATUS "${BINARYNAME} - General Libs: ${C_LIBS}")
        message(STATUS "${BINARYNAME} - Debug   Libs: ${CPP_LIBS_DEBUG}")
        message(STATUS "${BINARYNAME} - Release Libs: ${CPP_LIBS_RELEASE}")

        target_link_libraries(${BINARYNAME} ${C_LIBS})
        if(NOT ${CPP_LIBS_DEBUG} STREQUAL "")
            target_link_libraries(${BINARYNAME} debug ${CPP_LIBS_DEBUG})
        endif()
        if(NOT ${CPP_LIBS_RELEASE} STREQUAL "")
            target_link_libraries(${BINARYNAME} optimized ${CPP_LIBS_RELEASE})
        endif()

    else()
        # No need on Unix systems, because of binary compatibility between different configurations
        target_link_libraries(${BINARYNAME} ${ARGN})
    endif()
endfunction()

add_subdirectory(libraries) # muparser
declare_module(shared ./shared)
declare_module(engine ./engine)
declare_module(fpsgame ./fpsgame)
declare_module(util ./util)
add_subdirectory(rpc) # rpc module, protobuf lib
add_subdirectory(net) # net module, asio lib

include_directories(
    ${ENET_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${MUPARSER_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${RPC_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${SOURCE_DIR}
    ${SOURCE_DIR}/shared
    ${SOURCE_DIR}/engine
    ${SOURCE_DIR}/fpsgame)

# This should contain all sources in the project,
# TODO: Append every time we glob some headers
set(ALL_HEADERS ${MUPARSER_HEADERS} ${SHARED_MODULE_HEADERS}
  ${ENGINE_MODULE_HEADERS} ${FPSGAME_MODULE_HEADERS}
  ${UTIL_MODULE_HEADERS} ${RPC_MODULE_HEADERS}
  ${NET_MODULE_HEADERS} CACHE INTERNAL "")

# This should contain all sources that are used by all
# targets. This only excludes fpsgame/ and engine/
# TODO: Append every time we glob for sources
set(COMMON_SOURCES ${MUPARSER_SOURCES} ${SHARED_MODULE_SOURCES}
  ${UTIL_MODULE_SOURCES} ${NET_MODULE_SOURCES}
  ${RPC_MODULE_SOURCES} CACHE INTERNAL "")

# This contains the libraries that are used by all targets.
# Excludes OpenGL and SDL, because those are only used by
# the client.
set(COMMON_LIBS ${ENET_LIBRARIES} ${OPENGL_LIBRARIES}
  ${ZLIB_LIBRARIES} ${PROTOBUF_LIBRARIES}
  ${ADDITIONAL_LIBRARIES} CACHE INTERNAL "")

get_property(INCLUDE_DIRECTORIES DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

# Subprojects Client and Server
if(${BUILD_CLIENT})
    add_subdirectory(client)
else()
    message(STATUS "not building the client")
endif()

if(${BUILD_SERVER})
    add_subdirectory(server)
else()
    message(STATUS "not building the server")
endif()
