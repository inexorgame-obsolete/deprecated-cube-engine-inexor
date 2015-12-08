prepend(CLIENT_SOURCES_ENGINE ${SOURCE_DIR}/engine
    3dgui.cpp
    bih.cpp
    blend.cpp
    client.cpp
    command.cpp
    console.cpp
    decal.cpp
    dynlight.cpp
    glemu.cpp
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
  ${SHARED_MODULE_SOURCES}
  ${CLIENT_SOURCES_ENGINE}
  ${CLIENT_SOURCES_FPSGAME} CACHE INTERNAL "")

if(OS_MACOSX)
  list(APPEND CLIENT_SOURCES engine/macutils.mm)
endif()

# Set Binary name
set(CLIENT_BINARY inexor CACHE INTERNAL "Client binary name.")

add_definitions(-DCLIENT)

add_app(${CLIENT_BINARY} ${CLIENT_SOURCES})

config_threads(${CLIENT_BINARY})
config_cocoa(${CLIENT_BINARY}) # For rendering the initial window
config_crashreporter(${CLIENT_BINARY})
config_sdl(${CLIENT_BINARY})
config_zlib(${CLIENT_BINARY})
config_enet(${CLIENT_BINARY})
config_net(${CLIENT_BINARY})
config_rpc(${CLIENT_BINARY})
config_util(${CLIENT_BINARY})
config_ui(${CLIENT_BINARY})
config_muparser(${CLIENT_BINARY})
