## This is the CMake file for the gluegen standalone tool.
##
## Its used for generating reflection boilerplate code and hence gets
## shipped precompiled as tool which is integrated in the build-process on every platform.
## It does need Doxygen for parsing the source and providing us with an AST (which inform us about Shared Declarations).

find_path(MUSTACHE_INCLUDE_DIR kainjow/mustache.hpp)

declare_module(gluegen .)
add_app(gluecodegenerator ${GLUEGEN_MODULE_SOURCES} CONSOLE_APP)

require_boost_program_options(gluecodegenerator)
require_boost_regex(gluecodegenerator)
require_threads(gluecodegenerator)
require_pugixml(gluecodegenerator)

require_filesystem(gluecodegenerator)

include_directories(${MUSTACHE_INCLUDE_DIR})
