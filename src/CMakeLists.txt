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

    find_libs(ENET_LIBRARIES enet)
    find_path(ENET_INCLUDE_DIRS enet/enet.h)

    find_libs(SDL2_LIBRARIES SDL2 LIB SDL2_image LIB SDL2_mixer)

    find_path(SDL2_INCLUDE_DIR       SDL.h       PATH_SUFFIXES SDL2)
    find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h PATH_SUFFIXES SDL2)
    find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h PATH_SUFFIXES SDL2)
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
endif()

# COCOA for SQL on OSX
if(OS_MACOSX)
  find_libs(osx_libs CoreServices LIB Cocoa NOCACHE)
  list(APPEND SDL2_LIBRARIES ${osx_libs})
endif()

# Windows Libraries for Server AND Client
if(OS_WINDOWS)
    if(NOT MSVC)
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} -static-libgcc -static-libstdc++)
    endif()
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} kernel32 ws2_32 winmm)
endif()

set(ALL_MODULES "" CACHE INTERNAL "")
set(ALL_HEADERS "" CACHE INTERNAL "")
set(OUTSOURCED_MODULES "" CACHE INTERNAL "")

# TODO: use proper config in libraries/
include_directories(
    ${ENET_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${SOURCE_DIR}
    ${SOURCE_DIR}/shared
    ${SOURCE_DIR}/engine
    ${SOURCE_DIR}/fpsgame)

add_subdirectory(libraries) # muparser
declare_module(shared ./shared)
declare_module(engine ./engine)
declare_module(fpsgame ./fpsgame)
add_subdirectory(util)
add_subdirectory(net) # net module, asio lib
add_subdirectory(rpc) # rpc module, protobuf lib
add_subdirectory(ui)

# *sigh* We can't make shared a real module. Yet.
# It's too interdependant
set(COMMON_SOURCES ${SHARED_MODULE_SOURCES} CACHE INTERNAL "")

# This contains the libraries that are used by all targets.
# Excludes OpenGL and SDL, because those are only used by
# the client.
set(COMMON_LIBS
  ${ENET_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${ADDITIONAL_LIBRARIES} CACHE INTERNAL "")

# Actual targets
opt_subdir(client ${OPENGL_FOUND})
opt_subdir(server on)
opt_subdir(test   on)
