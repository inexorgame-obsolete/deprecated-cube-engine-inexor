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
    shader.cpp
    sound.cpp
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
    movable.cpp
    render.cpp
    scoreboard.cpp
    waypoint.cpp
    weapon.cpp)

# generate source file list of this folder
declare_module(client .)

set(CLIENT_SOURCES
  ${SHARED_MODULE_SOURCES}
  ${CLIENT_MODULE_SOURCES}
  ${CLIENT_SOURCES_ENGINE}
  ${CLIENT_SOURCES_FPSGAME} CACHE INTERNAL "")

# Set Binary name
set(CLIENT_BINARY inexor CACHE INTERNAL "Client binary name.")

add_definitions(-DCLIENT)

add_app(${CLIENT_BINARY} ${CLIENT_SOURCES})

require_threads(${CLIENT_BINARY})
require_crashreporter(${CLIENT_BINARY})
require_sdl(${CLIENT_BINARY})
require_zlib(${CLIENT_BINARY})
require_network(${CLIENT_BINARY} "CLIENT NOT_STANDALONE")
require_util(${CLIENT_BINARY})
require_ui(${CLIENT_BINARY})
require_texture(${CLIENT_BINARY})
require_filesystem(${CLIENT_BINARY})
require_gamemode(${CLIENT_BINARY})
