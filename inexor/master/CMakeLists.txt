prepend(MASTER_SOURCES_ENGINE ${SOURCE_DIR}/engine
    master.cpp command.cpp)

#prepend(MASTER_SOURCES_FPSGAME ${SOURCE_DIR}/fpsgame
#    entities.cpp)

set(MASTER_SOURCES
  ${SHARED_MODULE_SOURCES}
  #${MASTER_SOURCES_FPSGAME}
  ${MASTER_SOURCES_ENGINE}
  CACHE INTERNAL "")

# Set Binary name
set(MASTER_BINARY master CACHE INTERNAL "Master binary name.")

add_definitions(-DSERVER -DSTANDALONE)

add_app(${MASTER_BINARY} ${MASTER_SOURCES} CONSOLE_APP)

require_threads(${MASTER_BINARY})
require_zlib(${MASTER_BINARY})
require_enet(${MASTER_BINARY})
require_util(${MASTER_BINARY})
require_crashreporter(${MASTER_BINARY})
require_filesystem(${MASTER_BINARY})
