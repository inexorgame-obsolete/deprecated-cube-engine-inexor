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

set(SERVER_SOURCES_ENGINE
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/server
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/command
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/worldio)

set(SERVER_SOURCES_FPSGAME
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/server
    ${CMAKE_CURRENT_SOURCE_DIR}/../fpsgame/entities)

set(SERVER_SOURCES
    ${SERVER_SOURCES_SHARED}
    ${SERVER_SOURCES_ENGINE}
    ${SERVER_SOURCES_FPSGAME})

if(MSVC)
    message(STATUS "Setting up source groups.")
    
    foreach(GROUP SHARED ENGINE FPSGAME)
        set(SOURCE_GROUP_${GROUP} "")
        foreach(FILE ${SERVER_SOURCES_${GROUP}})
            set(SOURCE_GROUP_${GROUP}
                ${SOURCE_GROUP_${GROUP}}
                ${FILE}.cpp
                ${FILE}.h)
        endforeach(FILE)
        string(SUBSTRING ${GROUP} 0 1 GROUPNAME1)
        string(TOLOWER ${GROUP} GROUPNAME)
        if(GROUP_NAME_CAMEL_CASE)
            string(REGEX REPLACE "^.(.*)" "${GROUPNAME1}\\1" GROUPNAME "${GROUPNAME}")
        endif()
        source_group(${GROUPNAME} FILES ${SOURCE_GROUP_${GROUP}}})
    endforeach(GROUP)
endif()

set(SB_SERVER_BINARY server_${BUILD_PLATFORM_BIN}_${BUILD_TARGET_ARCH} CACHE INTERNAL "Server binary name.")

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
