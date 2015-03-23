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

set(CLIENT_SOURCES
  ${CLIENT_SOURCES_ENGINE}
  ${CLIENT_SOURCES_FPSGAME}
  ${COMMON_SOURCES} CACHE INTERNAL "")

group_modules()

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

add_app(${CLIENT_BINARY} ${CLIENT_SOURCES})
target_link_libs(${CLIENT_BINARY}
  ${COMMON_LIBS}
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${ADDITIONAL_LIBRARIES})

config_net(${CLIENT_BINARY})
config_rpc(${CLIENT_BINARY})
config_util(${CLIENT_BINARY})
config_muparser(${CLIENT_BINARY})
