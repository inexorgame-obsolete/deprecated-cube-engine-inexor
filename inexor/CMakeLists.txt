# Wrong folder: User attempted to generate from src instead of the main-inexor folder
if(NOT DEFINED PROJECT_ARCH)
    message(FATAL_ERROR "You are generating from the wrong folder! \"Where is the Source:\" (currently: ${MAINDIR}) should point to the Main directory (!) of Inexor")
endif()

set(ALL_MODULES "" CACHE INTERNAL "")
set(ALL_HEADERS "" CACHE INTERNAL "")
set(OUTSOURCED_MODULES "" CACHE INTERNAL "")

include_directories(${MAINDIR})
include_directories(${CMAKE_INCLUDE_PATH})

# TODO: Automatically detect new modules
declare_module(shared ./shared)
declare_module(engine ./engine)
declare_module(fpsgame ./fpsgame)

add_subdirectory(util)
add_subdirectory(filesystem)
add_subdirectory(rpc) # rpc module, protobuf lib
add_subdirectory(ui)
add_subdirectory(cef_subprocess)
add_subdirectory(crashreporter)
add_subdirectory(texture)

# Actual targets
opt_subdir(client on)
opt_subdir(server off)
opt_subdir(master off)
opt_subdir(test   on)

 # This gets used only if invoked from our conan.io package InexorGlueGen. otherwise just used for testing.
opt_subdir(gluegen off)
