prepend(SERVER_SOURCES_ENGINE ${SOURCE_DIR}/engine
    server.cpp command.cpp worldio.cpp)

prepend(SERVER_SOURCES_FPSGAME ${SOURCE_DIR}/fpsgame
    server.cpp entities.cpp)

# generate source file list from files in this folder
declare_module(server .)

set(SERVER_SOURCES
  ${SHARED_MODULE_SOURCES}
  ${SERVER_MODULE_SOURCES} # files from this folder
  ${SERVER_SOURCES_FPSGAME}
  ${SERVER_SOURCES_ENGINE}
  CACHE INTERNAL "")

# Set Binary name
set(SERVER_BINARY server CACHE INTERNAL "Server binary name.")

add_definitions(-DSERVER -DSTANDALONE)

add_app(${SERVER_BINARY} ${SERVER_SOURCES})

require_threads(${SERVER_BINARY})
require_zlib(${SERVER_BINARY})
require_network(${SERVER_BINARY} "SERVER STANDALONE SERVMODE")
require_util(${SERVER_BINARY})
require_crashreporter(${SERVER_BINARY})
require_filesystem(${SERVER_BINARY})
require_gamemode(${SERVER_BINARY})
