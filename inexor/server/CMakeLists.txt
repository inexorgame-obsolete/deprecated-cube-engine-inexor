prepend(SERVER_SOURCES_ENGINE ${SOURCE_DIR}/engine
    server.cpp command.cpp worldio.cpp)

prepend(SERVER_SOURCES_FPSGAME ${SOURCE_DIR}/fpsgame
    server.cpp entities.cpp)

set(SERVER_SOURCES
  ${SHARED_MODULE_SOURCES}
  ${SERVER_SOURCES_FPSGAME}
  ${SERVER_SOURCES_ENGINE}
  CACHE INTERNAL "")

# Set Binary name
set(SERVER_BINARY server CACHE INTERNAL "Server binary name.")

add_definitions(-DSERVER -DSTANDALONE)

add_app(${SERVER_BINARY} ${SERVER_SOURCES})

config_threads(${SERVER_BINARY})
config_zlib(${SERVER_BINARY})
config_enet(${SERVER_BINARY})
config_net(${SERVER_BINARY})
config_rpc(${SERVER_BINARY})
config_util(${SERVER_BINARY})
config_muparser(${SERVER_BINARY})
config_crashreporter(${SERVER_BINARY})
