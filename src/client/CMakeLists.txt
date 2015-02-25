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

set(CLIENT_SOURCES ${CLIENT_SOURCES_ENGINE}
  ${CLIENT_SOURCES_FPSGAME} ${COMMON_SOURCES}
  CACHE INTERNAL "")

# Set Binary name
set(CLIENT_BINARY inexor CACHE INTERNAL "Client binary name.")

# Set Client definition
add_definitions(-DCLIENT)

# Linux Libraries and Configuration
if(OS_LINUX)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dl rt)
endif()

# MACOSX Libraries and Configuration
if(OS_MACOSX)
    set(CLIENT_SOURCES
        ${CLIENT_SOURCES}
        engine/macutils.mm)
endif()

# Windows Libraries and Configuration
if(OS_WINDOWS)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} opengl32)

    if(MSVC)
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dbghelp)
    else()
        add_definitions(-mwindows)
    endif()
endif()


# Assemble executable in specific mode
if(OS_WINDOWS)
  add_executable(${CLIENT_BINARY} WIN32 ${CLIENT_SOURCES}
      ${ALL_HEADERS})
elseif(OS_MACOSX)
    add_executable(${CLIENT_BINARY} MACOSX_BUNDLE ${CLIENT_SOURCES})
else()
    add_executable(${CLIENT_BINARY} ${CLIENT_SOURCES})
endif()

config_protoc(${CLIENT_BINARY})

set(CLIENT_LIBS ${COMMON_LIBS} ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES} ${ADDITIONAL_LIBRARIES} CACHE INTERNAL "")
target_link_libraries(${CLIENT_BINARY} ${CLIENT_LIBS})

# C++ Libraries depending on the stdlib are NOT binary compatible for different VS versions.
# Also a debug .lib is incompatible to Inexor in releasemode then.
if(MSVC)
    target_link_libraries(${CLIENT_BINARY} debug ${PROTOBUF_LIBRARIES_MSVC_DEBUG})
    target_link_libraries(${CLIENT_BINARY} optimized ${PROTOBUF_LIBRARIES_MSVC_RELEASE})
    add_definitions(-DPROTOBUF_USE_DLLS)
endif()

message(STATUS "CLIENT ENET_LIBRARIES:       ${ENET_LIBRARIES}")
message(STATUS "CLIENT SDL2_LIBRARIES:       ${SDL2_LIBRARIES}")
message(STATUS "CLIENT OPENGL_LIBRARIES:     ${OPENGL_LIBRARIES}")
message(STATUS "CLIENT ZLIB_LIBRARIES:       ${ZLIB_LIBRARIES}")
message(STATUS "CLIENT PROTOBUF_LIBRARIES:   ${PROTOBUF_LIBRARIES}")
message(STATUS "CLIENT ADDITIONAL_LIBRARIES: ${ADDITIONAL_LIBRARIES}")
message(STATUS "CLIENT INCLUDE DIRECTORIES:  ${INCLUDE_DIRECTORIES}")
if(MSVC)
    set_property(TARGET ${CLIENT_BINARY} PROPERTY FOLDER "executables")
endif()

# Install Binary
install(TARGETS ${CLIENT_BINARY}
        DESTINATION ${EXE_DIR})
