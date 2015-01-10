add_definitions(-DCLIENT)

if(${BUILD_TARGET_WINDOWS})
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} ws2_32 winmm)
    if(GNU)
        add_definitions(-mwindows)
    elseif(MSVC)
        set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} dbghelp)
    endif()
elseif(${BUILD_TARGET_LINUX})
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} dl rt)
elseif(${BUILD_TARGET_SOLARIS})
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} socket nsl)
endif()

set(CLIENT_SOURCES_SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/crypto
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/geom
	${CMAKE_CURRENT_SOURCE_DIR}/../shared/json
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/stream
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/tools
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/zip)

# Only used for MSVC
set(CLIENT_HEADERS_SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/command
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/cube
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/ents
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/geom
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/iengine
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/igame
	${CMAKE_CURRENT_SOURCE_DIR}/../shared/json
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/tools)

set(CLIENT_SOURCES_ENGINE
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/3dgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/bih
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/blend
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/client
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/command
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/console
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/decal
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/dynlight
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/grass
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/main
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/material
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/menus
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/movie
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/normal
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/octa
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/octaedit
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/octarender
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/physics
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/pvs
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/rendergl
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/rendermodel
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/renderparticles
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/rendersky
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/rendertext
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/renderva
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/server
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/shader
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/sound
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/texture
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/water
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/world
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/worldio
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/serverbrowser
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/shadowmap
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/lightmap
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/glare
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/blob)

set(CLIENT_HEADERS_ENGINE
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/animmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/bih
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/depthfx
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/explosion
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/iqm
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/lensflare
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/lightmap
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/lightning
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/md2
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/md3
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/md5
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/model
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/mpr
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/obj
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/octa
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/ragdoll
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/rendertarget
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/scale
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/skelmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/smd
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/textedit
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/texture
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/varray
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/vertmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/world)
    
set(CLIENT_SOURCES_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefapp
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefclienthandler
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefconsole
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefcontextmanager
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefcontextprovider
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefdebug
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefevent
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefeventmanager
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefkeyboard
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/ceflayer
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/ceflayermanager
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefmenu
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefmouse
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefrenderhandler
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/cefrequestcontexthandler
)

set(CLIENT_SOURCES_CEFDLL
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/cef3/libcef_dll
)

set(CLIENT_SOURCES_FPSGAME
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/ai
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/client
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/fps
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/monster
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/movable
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/render
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/scoreboard
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/server
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/waypoint
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/weapon)

set(CLIENT_SOURCES_RPC
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../rpc/InexorServiceImpl
    ${CMAKE_CURRENT_SOURCE_DIR}/../rpc/MCRpcServer
    ${CMAKE_CURRENT_SOURCE_DIR}/../rpc/rpc)

set_source_files_properties(
    ${CMAKE_BINARY_DIR}/src/rpc/inexor_service.pb.cc
    PROPERTIES GENERATED TRUE)

set(CLIENT_SOURCES_NET
  ${CMAKE_CURRENT_SOURCE_DIR}/../net/MCHub
  ${CMAKE_CURRENT_SOURCE_DIR}/../net/MCByteBuffer)

set(CLIENT_HEADERS_FPSGAME
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/ai
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/aiman
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/bomb
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/capture
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/collect
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/ctf
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/extinfo
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/hideandseek)

set(CLIENT_SOURCES_MUPARSER
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/muparser/src/muParser
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/muparser/src/muParserBase
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/muparser/src/muParserBytecode
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/muparser/src/muParserCallback
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/muparser/src/muParserError
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/muparser/src/muParserInt
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/muparser/src/muParserTokenReader
)

set(CLIENT_SOURCES
    ${CLIENT_SOURCES_SHARED}
    ${CLIENT_SOURCES_ENGINE}
    ${CLIENT_SOURCES_UI}
    ${CLIENT_SOURCES_CEFDLL}
    ${CLIENT_SOURCES_FPSGAME}
    ${CLIENT_SOURCES_MUPARSER}
    ${CLIENT_SOURCES_NET}
    ${CLIENT_SOURCES_RPC})

if(${BUILD_TARGET_OSX})
    set(CLIENT_SOURCES
        ${CLIENT_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/../engine/macutils.mm)
elseif(${BUILD_TARGET_WINDOWS})
    option(CLIENT_USE_WINDRES "Add icon to executable." 0)

    if(${CLIENT_USE_WINDRES})
        set(CLIENT_SOURCES
            ${CLIENT_SOURCES}
            ${CMAKE_CURRENT_SOURCE_DIR}/../vcpp/rr.rc
        )

        set(CMAKE_RC_COMPILER_INIT windres)
        ENABLE_LANGUAGE(RC)
        SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> -O coff -I ${CMAKE_CURRENT_SOURCE_DIR}/.. -i <SOURCE> -o <OBJECT>")
    endif()
endif()


set(SB_CLIENT_BINARY inexor CACHE INTERNAL "Client binary name.")
sb_msvc_build_source_groups(CLIENT engine fpsgame shared)

if(WIN32)
    add_executable(${SB_CLIENT_BINARY} WIN32 ${CLIENT_SOURCES})
elseif(APPLE)
    add_executable(${SB_CLIENT_BINARY} MACOSX_BUNDLE ${CLIENT_SOURCES})
else()
    add_executable(${SB_CLIENT_BINARY} ${CLIENT_SOURCES})
endif()

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CEF_DLL_LIBRARY "libcef_dll_wrapper")
set(CEF_BASE_DIR "${PROJECT_SOURCE_DIR}/src/libraries/cef3")
set(ICUDTL_DAT "${CEF_BASE_DIR}/Resources/icudtl.dat")
if(BUILD_TARGET_LINUX)
    set(CEF_LINUX_DIR "${CEF_BASE_DIR}/cef_bin/linux")
    if(BUILD_TARGET_X86)
        set(CEF_LINUX_X86_DIR "${CEF_LINUX_DIR}/bin_x86")
        set(UDEV_LIBRARY "${CEF_LINUX_X86_DIR}/libudev.so")
        set(CEF_LIBRARY "${CEF_LINUX_X86_DIR}/libcef.so")
        set(FFMPEGSUMO_LIBRARY "${CEF_LINUX_X86_DIR}/libffmpegsumo.so")
        set(CHROME_SANDBOX_BIN "${CEF_LINUX_X86_DIR}/chrome-sandbox")
    else()
        set(CEF_LINUX_X86_64_DIR "${CEF_LINUX_DIR}/bin_x86_64")
        set(UDEV_LIBRARY "${CEF_LINUX_X86_64_DIR}/libudev.so")
        set(CEF_LIBRARY "${CEF_LINUX_X86_64_DIR}/libcef.so")
        set(FFMPEGSUMO_LIBRARY "${CEF_LINUX_X86_64_DIR}/libffmpegsumo.so")
        set(CHROME_SANDBOX_BIN "${CEF_LINUX_X86_64_DIR}/chrome-sandbox")
    endif()
elseif(BUILD_TARGET_WINDOWS)
    if(BUILD_TARGET_X86)
        set(CEF_LIBRARY "${CEF_BASE_DIR}/cef_bin/windows/lib32/libcef.lib")
    else()
        set(CEF_LIBRARY "${CEF_BASE_DIR}/cef_bin/windows/lib64/libcef.lib")
    endif()
endif()
set(CEF_LIBRARIES "${CEF_DLL_LIBRARY};-Wl,-rpath,. ${CEF_LIBRARY};-Wl,-rpath,. ${UDEV_LIBRARY}")

target_link_libraries(${SB_CLIENT_BINARY}
    ${ENET_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${CEF_LIBRARIES}
    ${BUILD_EXTRA_LIBS}
    ${PROTOBUF_LIBRARIES}
)

if(MSVC)
    set_property(TARGET ${SB_CLIENT_BINARY} PROPERTY FOLDER "executables")
endif()

add_dependencies(${SB_CLIENT_BINARY} inexor_rpc_protobuf)

install(TARGETS
    ${SB_CLIENT_BINARY}
    RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
    ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR})

message(STATUS "UDEV_LIBRARY ${UDEV_LIBRARY}")

file(COPY ${UDEV_LIBRARY} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${CEF_LIBRARY} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${FFMPEGSUMO_LIBRARY} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${CHROME_SANDBOX_BIN} DESTINATION ${INSTALL_RUNTIME_DIR})
file(COPY ${ICUDTL_DAT} DESTINATION ${INSTALL_RUNTIME_DIR})
