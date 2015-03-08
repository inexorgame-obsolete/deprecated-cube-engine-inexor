set(pwd "${CMAKE_CURRENT_SOURCE_DIR}")

#### MUPARSER

set(muparser_dir "${pwd}/muparser")

file(GLOB_RECURSE headers ${muparser_dir}/include/*.h)
set(MUPARSER_HEADERS ${headers} CACHE INTERNAL "")

prepend(sources ${muparser_dir}/src/ muParser muParserBase
  muParserBytecode muParserCallback muParserError
  muParserInt muParserTokenReader)
set(MUPARSER_SOURCES ${sources} CACHE INTERNAL "")

source_group(muparser FILES ${headers} ${sources})
set(MUPARSER_INCLUDE_DIRS "${muparser_dir}/include" CACHE INTERNAL "")

include_directories(${MUPARSER_INCLUDE_DIRS})
add_library(inexor_muparser STATIC ${MUPARSER_SOURCES})

function(config_muparser targ)
  message(STATUS "Configuring ${targ} with muparser")

  include_directories(${MUPARSER_INCLUDE_DIRS})
  target_link_libraries_wrapper(${targ} inexor_muparser)
endfunction()
