add_definitions(-DSERVER -DSTANDALONE)

if(${BUILD_TARGET_WINDOWS})
    set(EXTRA_LIBS ${EXTRA_LIBS} opengl32 ws2_32 winmm)
elseif(${BUILD_TARGET_WINDOWS})
    set(EXTRA_LIBS ${EXTRA_LIBS} dl -pthread)
elseif(${BUILD_TARGET_WINDOWS})
    set(EXTRA_LIBS ${EXTRA_LIBS} socket nsl)
endif()

set(SERVER_SOURCES_SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/crypto
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/geom
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/stream
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/tools
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/zip)

set(SERVER_HEADERS_SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/command
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/cube
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/ents
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/geom
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/iengine
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/igame
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/tools)

set(SERVER_SOURCES_ENGINE
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/server
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/command
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/worldio)

set(SERVER_HEADERS_ENGINE
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/world)

set(SERVER_SOURCES_FPSGAME
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/server
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/entities)

set(SERVER_HEADERS_FPSGAME
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/aiman
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/bomb
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/capture
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/collect
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/ctf
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/extinfo
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/game
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/hideandseek)

set(SERVER_SOURCES
    ${SERVER_SOURCES_SHARED}
    ${SERVER_SOURCES_ENGINE}
    ${SERVER_SOURCES_FPSGAME})

sb_msvc_build_source_groups(ENGINE engine fpsgame shared)

set(SB_SERVER_BINARY server CACHE INTERNAL "Server binary name.")

if(WIN32)
    add_executable(${SB_SERVER_BINARY} WIN32 ${SERVER_SOURCES})
elseif(APPLE)
    add_executable(${SB_SERVER_BINARY} MACOSX_BUNDLE ${SERVER_SOURCES})
else()
    add_executable(${SB_SERVER_BINARY} ${SERVER_SOURCES})
endif()

target_link_libraries(${SB_SERVER_BINARY}
    ${ENET_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${EXTRA_LIBS})
    
if(MSVC)
    set_property(TARGET ${SB_SERVER_BINARY} PROPERTY FOLDER "executables")
endif()

install(TARGETS
    ${SB_SERVER_BINARY}
    RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
    ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR})
