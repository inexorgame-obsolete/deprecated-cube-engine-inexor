find_package(ZLIB REQUIRED)

find_package(OpenGL)
find_package(PkgConfig)

option(BUILD_CLIENT "Build the client" ${OPENGL_FOUND})
option(BUILD_SERVER "Build the server" 1)

if(${BUILD_TARGET_WINDOWS} AND ${CMAKE_C_COMPILER} MATCHES "mingw")
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} -static-libgcc)
endif()

message(STATUS "Detecting SDL2...")
if(NOT ${BUILD_TARGET_WINDOWS} AND NOT ${BUILD_TARGET_OSX})
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
elseif(${BUILD_TARGET_OSX})
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
    #include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
endif()

# TODO: This should go insted net/
message(STATUS "Detecting ASIO...")
find_path(ASIO_INCLUDE_DIRS asio.hpp)
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

# TODO: This should go inside rpc/
if (NOT DEFINED PROTOC_EXE)
  set(PROTOC_EXE "protoc")
endif()
add_custom_command(
  OUTPUT rpc/inexor_service.pb.h rpc/inexor_service.pb.cc
  COMMAND ${PROTOC_EXE} --proto_path=${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${CMAKE_BINARY_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/rpc/inexor_service.proto
  DEPENDS rpc/inexor_service.proto
)
add_custom_target(inexor_rpc_protobuf DEPENDS
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.h
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc)

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

set(MUPARSER_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/libraries/muparser/include")
set(CEF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/libraries/cef3")

include_directories(
    ${ENET_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${MUPARSER_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${CEF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_BINARY_DIR}/src/
)

# Builds source groups for MSVC
function(sb_msvc_build_source_groups TARGET)
    if(MSVC)
        message(STATUS "Setting up source groups.")

        string(TOUPPER "${TARGET}" TARGET)
        string(TOUPPER "${ARGN}" GROUPS)

        foreach(GROUP ${GROUPS})
            set(SOURCE_GROUP_${GROUP} "")
            foreach(FILE "${${TARGET}_SOURCES_${GROUP}};${${TARGET}_HEADERS_${GROUP}}")
                set(SOURCE_GROUP_${GROUP}
                    ${SOURCE_GROUP_${GROUP}}
                    ${FILE}.cpp
                    ${FILE}.h)
                message(STATUS "Adding ${TARGET}_{SOURCES,HEADERS}_${GROUP} -> ${FILE}")
            endforeach(FILE)
            string(SUBSTRING ${GROUP} 0 1 GROUPNAME1)
            string(TOLOWER ${GROUP} GROUPNAME)
            if(GROUP_NAME_CAMEL_CASE)
                string(REGEX REPLACE "^.(.*)" "${GROUPNAME1}\\1" GROUPNAME "${GROUPNAME}")
            endif()
            source_group(${GROUPNAME} FILES ${SOURCE_GROUP_${GROUP}}})
        endforeach(GROUP)
    endif()
endfunction()

if(NOT DEFINED LIBCEF_DLL_LIBRARIES AND NOT DEFINED LOCAL_LIBCEF_DLL)
    set(LOCAL_LIBCEF_DLL 1 CACHE INTERNAL "Use local libcef_dll library")
elseif(DEFINED LOCAL_LIBCEF_DLL)
    set(LOCAL_LIBCEF_DLL ${LOCAL_LIBCEF_DLL} CACHE INTERNAL "Use local libcef_dll library")
else()
    set(LOCAL_LIBCEF_DLL 0 CACHE INTERNAL "Use local libcef_dll library")
endif()

if(${LOCAL_LIBCEF_DLL})
    message(STATUS "Building local libcef_dll")
    add_subdirectory(libraries/cef3/libcef_dll)
endif()

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
