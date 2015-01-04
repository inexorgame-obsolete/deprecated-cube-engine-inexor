prepend(CLIENT_SOURCES_ENGINE ${SOURCE_DIR}/engine
    3dgui.cpp
    bih.cpp
    blend.cpp
    client.cpp
    command.cpp
    console.cpp
    decal.cpp
    dynlight.cpp
    grass.cpp
    main.cpp
    material.cpp
    menus.cpp
    movie.cpp
    normal.cpp
    octa.cpp
    octaedit.cpp
    octarender.cpp
    physics.cpp
    pvs.cpp
    rendergl.cpp
    rendermodel.cpp
    renderparticles.cpp
    rendersky.cpp
    rendertext.cpp
    renderva.cpp
    server.cpp
    shader.cpp
    sound.cpp
    texture.cpp
    water.cpp
    world.cpp
    worldio.cpp
    serverbrowser.cpp
    shadowmap.cpp
    lightmap.cpp
    glare.cpp
    blob.cpp)

prepend(CLIENT_SOURCES_FPSGAME ${SOURCE_DIR}/fpsgame
    ai.cpp
    client.cpp
    entities.cpp
    fps.cpp
    monster.cpp
    movable.cpp
    render.cpp
    scoreboard.cpp
    server.cpp
    waypoint.cpp
    weapon.cpp)

set(CLIENT_SOURCES_CEFDLL
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/cef3/libcef_dll
)

set(CLIENT_SOURCES
  ${CLIENT_SOURCES_CEFDLL}
  ${CLIENT_SOURCES_ENGINE}
  ${CLIENT_SOURCES_FPSGAME}
  ${COMMON_SOURCES} CACHE INTERNAL "")

# Set Binary name
set(CLIENT_BINARY inexor CACHE INTERNAL "Client binary name.")

add_definitions(-DCLIENT)

if(OS_LINUX)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dl rt)
elseif(OS_MACOSX)
  set(CLIENT_SOURCES ${CLIENT_SOURCES} engine/macutils.mm)
elseif(OS_WINDOWS)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} opengl32)

    if(MSVC)
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dbghelp)
    else()
        add_definitions(-mwindows)
    endif()
endif()

if(BUILD_TARGET_LINUX)
    if(BUILD_TARGET_X86)
        set(CEF_LIBRARIES "${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/linux/bin_x86/libcef.so;${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/linux/bin_x86/libffmpegsumo.so")
    else()
        set(CEF_LIBRARIES "${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/linux/bin_x86_64/libcef.so;${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/linux/bin_x86_64/libffmpegsumo.so")
    endif()
elseif(BUILD_TARGET_WINDOWS)
    if(BUILD_TARGET_X86)
        set(CEF_LIBRARIES "${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/windows/lib32/libcef.lib;${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/windows/lib32/cef_sandbox.lib")
    else()
        set(CEF_LIBRARIES "${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/windows/lib64/libcef.lib;${PROJECT_SOURCE_DIR}/src/libraries/cef3/cef_bin/windows/lib64/cef_sandbox.lib")
    endif()
endif()
if(CEF_LIBRARIES)
    set(CEF_LIBRARIES "${CEF_LIBRARIES};libcef_dll_wrapper")
endif()

add_app(${CLIENT_BINARY} ${CLIENT_SOURCES})
target_link_libs(${CLIENT_BINARY}
  ${COMMON_LIBS}
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${ADDITIONAL_LIBRARIES}
  ${CEF_LIBRARIES})

config_net(${CLIENT_BINARY})
config_rpc(${CLIENT_BINARY})
config_util(${CLIENT_BINARY})
config_muparser(${CLIENT_BINARY})
