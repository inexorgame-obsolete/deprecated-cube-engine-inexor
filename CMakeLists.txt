cmake_minimum_required(VERSION 3.1) 
include(cmake/functions.cmake)
include(cmake/glibc_cxx11_abi_detection.cmake)
include(cmake/silence_find_pathprogram.cmake)

### Different Configuration Types (Debug release)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# First choice is Debug
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE INTERN "")
endif()


message(STATUS "CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")

# Project Name and start working in project scope (some things just work until now, some just work after this command)
project(Inexor)

# Use solution folders.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

# Get compiler/os/architecture variables
include(cmake/platform_detection.cmake)

# Set compile flags and compile specific definitions
include(cmake/compile_flags_and_defs.cmake)

# We use a lot of thirdparty dependencies which we deliver in prebuilt form to cut down compile time: make cmake find them.
include(platform/add_platform_files.cmake)


#### Install paths ####

# Error if paths aren't set well
get_filename_component(MAINDIR "${CMAKE_SOURCE_DIR}" REALPATH)  # Main inexor folder
get_filename_component(BINDIR "${CMAKE_BINARY_DIR}" REALPATH)   # Where it generates the projects into
if(${MAINDIR} STREQUAL ${BINDIR})
    message(FATAL_ERROR "Keep your directories clean, don't generate the project-files in the main directory! ${MAINDIR} ${BINDIR}")
endif()

# Set the path to inexor/ explicitly to simplify some following definitions
set(SOURCE_DIR ${MAINDIR}/inexor)

# INSTALL_LOCALLY will surpress the installation into CMAKE_INSTALL_PREFIX which is by default some global system path.
option(INSTALL_LOCALLY "Install everything relative to this folder (${MAINDIR}). Not into some global system directories." ON)

if(INSTALL_LOCALLY)
  set(CMAKE_INSTALL_PREFIX ${MAINDIR} CACHE PATH "" FORCE)
  message(STATUS "Local installation chosen. No files will move outside this folder (${MAINDIR}). .. ${CMAKE_INSTALL_PREFIX}")
endif()

# Define where to move the binary by target 'install'
if(OS_LINUX)
  set(EXE_DIR "bin/linux/${PROJECT_ARCH}")
elseif(OS_MACOSX)
  set(EXE_DIR "bin/mac/${PROJECT_ARCH}")
elseif(OS_WINDOWS)
  set(EXE_DIR "bin/windows/${PROJECT_ARCH}")
endif()

set(INSTALL_RESOURCES_DIR "bin/all")

message(STATUS "Generating Project-Files to ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Resulting Executable goes to ${EXE_DIR}")

### Go for the subfolders.
add_subdirectory(vendor)
add_subdirectory(inexor)

install(FILES ${INSTALL_SHARED_LIBS} ${INSTALL_EXES} DESTINATION ${EXE_DIR})
install(FILES ${INSTALL_SHARED_LIBS_DEBUG}   CONFIGURATIONS Debug   DESTINATION ${EXE_DIR})
install(FILES ${INSTALL_SHARED_LIBS_RELEASE} CONFIGURATIONS Release DESTINATION ${EXE_DIR})
install(FILES ${INSTALL_RESOURCES} DESTINATION ${INSTALL_RESOURCES_DIR})
install(DIRECTORY ${INSTALL_RESOURCES_FOLDERS} DESTINATION ${INSTALL_RESOURCES_DIR})

# shipped portable stuff on win (dirty but temporarily)
if(OS_WINDOWS)
  install(DIRECTORY ${INSTALL_PORTABLE_DIR} DESTINATION "bin/windows/all")
endif()
