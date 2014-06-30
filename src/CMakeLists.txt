find_package(ZLIB REQUIRED)

find_package(OpenGL)
find_package(PkgConfig)

option(BUILD_CLIENT "Build the client" ${OPENGL_FOUND})
option(BUILD_SERVER "Build the server" 1)

if(${BUILD_TARGET_WINDOWS} AND ${CMAKE_C_COMPILER} MATCHES "mingw")
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} -static-libgcc)
endif()

message(STATUS "Detecting SDL...")
if(NOT ${BUILD_TARGET_WINDOWS} AND NOT ${BUILD_TARGET_OSX})
    if(NOT BUILD_SDL_LOCAL AND PKG_CONFIG_FOUND)
        message(STATUS "Using pkg-config to detect SDL...")
        pkg_check_modules(SDL QUIET sdl)
        if(SDL_FOUND)
            message(STATUS "Found SDL.")
            message(STATUS "include: ${SDL_INCLUDE_DIRS}")
        else()
            message(FATAL_ERROR "SDL not found.")
        endif()
    else()
        if(PKG_CONFIG_FOUND)
            message(STATUS "Using local SDL.")
        else()
            message(STATUS "Using local SDL. (could not find PKG_CONFIG)")
        endif()
        set(SDL_LIBRARIES "SDL")
    endif()
    set(SDL_LIBRARIES "${SDL_LIBRARIES};SDL_image;SDL_mixer")
    add_definitions(-D_REENTRANT -D_THREAD_SAFE)
elseif(${BUILD_TARGET_OSX})
    find_library(SDL_LIBRARY SDL)
    find_library(SDL_IMAGE_LIBRARY SDL_image)
    find_library(SDL_MIXER_LIBRARY SDL_mixer)

    find_path(SDL_INCLUDE_DIR SDL.h)
    find_path(SDL_IMAGE_INCLUDE_DIR SDL_image.h)
    find_path(SDL_MIXER_INCLUDE_DIR SDL_mixer.h)
    set(SDL_INCLUDE_DIRS "${SDL_INCLUDE_DIR};${SDL_IMAGE_INCLUDE_DIR};${SDL_MIXER_INCLUDE_DIR}")
endif()

if(NOT DEFINED ENET_LIBRARIES)
    add_subdirectory(libraries/enet)
endif()

include_directories(
    ${ENET_INCLUDE_DIRS}
    ${SDL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/game
)

if(${BUILD_CLIENT})
    add_subdirectory(client)
else()
    message(WARNING "not building the client")
endif()

if(${BUILD_SERVER})
    add_subdirectory(server)
else()
    message(WARNING "not building the server")
endif()
