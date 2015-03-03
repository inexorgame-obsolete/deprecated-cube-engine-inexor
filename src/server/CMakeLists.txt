prepend(SERVER_SOURCES_ENGINE ${SOURCE_DIR}/engine
    server.cpp command.cpp worldio.cpp)

prepend(SERVER_SOURCES_FPSGAME ${SOURCE_DIR}/fpsgame
    server.cpp entities.cpp)

set(SERVER_SOURCES ${SERVER_SOURCES_FPSGAME}
  ${SERVER_SOURCES_ENGINE} ${COMMON_SOURCES}
  CACHE INTERNAL "")

# Set Binary name
set(SERVER_BINARY server CACHE INTERNAL "Server binary name.")

# Set Server Definition
add_definitions(-DSERVER -DSTANDALONE)

# Linux Libraries and Configuration
if(OS_LINUX)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dl -pthread)
endif()

# Assemble executable in specific mode
if(OS_WINDOWS)
    add_executable(${SERVER_BINARY} WIN32 ${SERVER_SOURCES} ${SERVER_HEADERS})
elseif(OS_MACOSX)
    add_executable(${SERVER_BINARY} MACOSX_BUNDLE ${SERVER_SOURCES})
else()
    add_executable(${SERVER_BINARY} ${SERVER_SOURCES})
endif()

target_link_libraries(${SERVER_BINARY} ${COMMON_LIBS}
  ${ADDITIONAL_LIBRARIES})

config_net(${SERVER_BINARY})
config_rpc(${SERVER_BINARY})

message(STATUS "SERVER ENET_LIBRARIES:       ${ENET_LIBRARIES}")
message(STATUS "SERVER SDL2_LIBRARIES:       ${SDL2_LIBRARIES}")
message(STATUS "SERVER OPENGL_LIBRARIES:     ${OPENGL_LIBRARIES}")
message(STATUS "SERVER ZLIB_LIBRARIES:       ${ZLIB_LIBRARIES}")
message(STATUS "SERVER PROTOBUF_LIBRARIES:   ${PROTOBUF_LIBRARIES}")
message(STATUS "SERVER ADDITIONAL_LIBRARIES: ${ADDITIONAL_LIBRARIES}")
message(STATUS "SERVER INCLUDE DIRECTORIES:  ${INCLUDE_DIRECTORIES}")

if(MSVC)
    set_property(TARGET ${SERVER_BINARY} PROPERTY FOLDER "executables")
endif()

# Install Binary
install(TARGETS ${SERVER_BINARY}
        DESTINATION ${EXE_DIR})
