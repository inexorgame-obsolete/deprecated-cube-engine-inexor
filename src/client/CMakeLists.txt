add_definitions(-DCLIENT)

if(${BUILD_TARGET_WINDOWS})
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} opengl32 ws2_32 winmm)
    add_definitions(-mwindows)
elseif(${BUILD_TARGET_LINUX})
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} dl rt)
elseif(${BUILD_TARGET_SOLARIS})
    set(BUILD_EXTRA_LIBS ${BUILD_EXTRA_LIBS} socket nsl)
endif()

set(CLIENT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/crypto
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/io
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/geom
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/stream
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/tools
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/zip

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
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/massspring
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/menus
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/movie
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/normal
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/octa
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/octaedit
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/octarender
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/particles
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
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/velocity
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/water
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/world
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/worldio
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/serverbrowser
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/shadowmap
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/lightmap
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/glare
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/blob
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/osd

    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/ai
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/client       
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/fps
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/hud
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/monster
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/movable
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/render
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/scoreboard
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/server
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/waypoint
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/weapon
)

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

set(SB_CLIENT_BINARY client_${BUILD_PLATFORM_BIN}_${BUILD_TARGET_ARCH} CACHE INTERNAL "Client binary name.")
add_executable(${SB_CLIENT_BINARY} ${CLIENT_SOURCES})
target_link_libraries(${SB_CLIENT_BINARY}
    ${ENET_LIBRARIES}
    ${SDL_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${BUILD_EXTRA_LIBS}
)

install(TARGETS
    ${SB_CLIENT_BINARY}
    RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
    ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR})
