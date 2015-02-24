## Definitions for both the Client and the Server
## Mainly detecting Libs is done here


# Wrong folder: User attempted to generate from src instead of the main-inexor folder
if(NOT DEFINED PROJECT_ARCH)
    message(FATAL_ERROR "You are generating from the wrong folder! \"Where is the Source:\" (currently: ${MAINDIR}) should point to the Main directory (!) of Inexor")
endif()


# Core Libs
find_package(ZLIB REQUIRED)

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


# MACOSX Libraries for Server AND Client
if(OS_MACOSX)
    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_IMAGE_LIBRARY SDL2_image)
    find_library(SDL2_MIXER_LIBRARY SDL2_mixer)

    find_library(CORESERVICES_LIBRARY CoreServices)
    find_library(COCOA_LIBRARY Cocoa)

    set(SDL2_LIBRARIES "${SDL2_LIBRARY};${SDL2_MIXER_LIBRARY};${SDL2_IMAGE_LIBRARY};${CORESERVICES_LIBRARY};${COCOA_LIBRARY}")

    find_path(SDL2_INCLUDE_DIR SDL.h)
    find_path(SDL2_IMAGE_INCLUDE_DIR SDL2_image.h)
    find_path(SDL2_MIXER_INCLUDE_DIR SDL2_mixer.h)
    set(SDL2_INCLUDE_DIRS "${SDL2_INCLUDE_DIR};${SDL2_IMAGE_INCLUDE_DIR};${SDL2_MIXER_INCLUDE_DIR}")
endif()


# POSIX Libraries
if(OS_MACOSX OR OS_LINUX)

    # ASIO package detection     TODO: This should go inside net/
    message(STATUS "Detecting ASIO...")
    find_path(ASIO_INCLUDE_DIRS asio.hpp)

    # Clang + ASIO require boost
    if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      message(STATUS "Using ASIO in standalone mode")
      add_definitions(-DASIO_STANDALONE)
    else()
      message(STATUS "Using ASIO with boost. Detecting Boost...")
    endif()

    # TODO: This should go inside rpc/
    message(STATUS "Detecting Protobuf...")
    find_library(PROTOBUF_LIBRARIES protobuf)
    find_PATH(PROTOBUF_INCLUDE_DIRS google/protobuf/service.h)
endif()


# Windows Libraries for Server AND Client
if(OS_WINDOWS)
    if(NOT MSVC)
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} -static-libgcc -static-libstdc++)
    endif()
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} kernel32 ws2_32 winmm)

    add_definitions(-DASIO_STANDALONE)
endif()


# Generate protobuf-Headers from its general definition file (.proto -> .h and .c)
if (NOT DEFINED PROTOC_EXE)
  set(PROTOC_EXE "protoc")
endif()

execute_process(COMMAND ${PROTOC_EXE} -I=${SOURCE_DIR}/rpc/ --cpp_out=${SOURCE_DIR}/rpc/ ${SOURCE_DIR}/rpc/inexor_service.proto
               WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(
  OUTPUT rpc/inexor_service.pb.h rpc/inexor_service.pb.cc
  COMMAND ${PROTOC_EXE} --proto_path=${SOURCE_DIR}/rpc/ --cpp_out=${SOURCE_DIR}/rpc/ ${SOURCE_DIR}/rpc/inexor_service.proto
  DEPENDS rpc/inexor_service.proto
)

add_custom_target(inexor_rpc_protobuf DEPENDS
    ${SOURCE_DIR}/rpc/inexor_service.pb.h
    ${SOURCE_DIR}/rpc/inexor_service.pb.cc)

# MuParser Lib for parsing mathematical expressions
set(MUPARSER_INCLUDE_DIRS "${SOURCE_DIR}/libraries/muparser/include")


include_directories(
    ${ENET_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${MUPARSER_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${SOURCE_DIR}
    ${SOURCE_DIR}/shared
    ${SOURCE_DIR}/engine
    ${SOURCE_DIR}/fpsgame
)


# Set names of Source Files (prepend correct path)
function(create_names TARGET)
    message(STATUS "Appending names")
    string(TOUPPER "${TARGET}" TARGET)
    string(TOUPPER "${ARGN}" GROUPS)

    foreach(GROUP ${GROUPS})

        # Sources:
        set(SOURCE_GROUP_${GROUP} "")
        foreach(FILE ${${TARGET}_SOURCES_${GROUP}})
            set(SOURCE_GROUP_${GROUP}
                ${SOURCE_GROUP_${GROUP}}
                ${SOURCE_DIR}/${FILE})
            #message(STATUS "Prepend path for ${FILE} (becoming ${SOURCE_DIR}/${FILE})")
        endforeach(FILE)

        # Replace old Source Array
        set(${TARGET}_SOURCES_${GROUP} ${SOURCE_GROUP_${GROUP}} PARENT_SCOPE)

        # For Visual Studio create filter groups as well
        if(MSVC)
            message(STATUS "Setting up Filter group ${GROUP}")

            # We want the Header files in our Solution Explorer as well:
            set(HEADER_GROUP_${GROUP} "")
            foreach(FILE ${${TARGET}_HEADERS_${GROUP}})
                set(HEADER_GROUP_${GROUP}
                    ${HEADER_GROUP_${GROUP}}
                    ${SOURCE_DIR}/${FILE})
            endforeach(FILE)

            # Replace old Header Array
            set(${TARGET}_HEADERS_${GROUP} ${HEADER_GROUP_${GROUP}} PARENT_SCOPE)

            # Create filter:
            string(TOLOWER ${GROUP} GROUPNAME)
            source_group(${GROUPNAME} FILES ${SOURCE_GROUP_${GROUP}} ${HEADER_GROUP_${GROUP}})
        endif()

    endforeach(GROUP)
endfunction()

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
