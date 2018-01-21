cmake_minimum_required(VERSION 3.4)
include(cmake/functions.cmake)
include(cmake/silence_find_pathprogram.cmake)
include(cmake/get_conan_build_type.cmake)

### Different Configuration Types (Debug release)

get_conan_build_type(BUILD_TYPE)
message(STATUS "BUILD_TYPE: ${BUILD_TYPE}")

# Only generate the single build type (Debug vs Release) we have our dependencies built for, since our prior step is to run conan.
set(CMAKE_CONFIGURATION_TYPES ${BUILD_TYPE})
set(CMAKE_BUILD_TYPE ${BUILD_TYPE} CACHE INTERN "")


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

# Add conan dependencies (our c++ dependency manager)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# And we split them accordingly into different require_XY() functions
include(cmake/require_thirdparty_libs.cmake)


## Path Variables

# Error if paths aren't set well
get_filename_component(MAINDIR "${CMAKE_SOURCE_DIR}" REALPATH)  # Main inexor folder
get_filename_component(BINDIR "${CMAKE_BINARY_DIR}" REALPATH)   # Where it generates the projects into
if(${MAINDIR} STREQUAL ${BINDIR})
    message(FATAL_ERROR "Keep your directories clean, don't generate the project-files in the main directory! ${MAINDIR} ${BINDIR}")
endif()

# Set the path to inexor/ explicitly to simplify some following definitions
set(SOURCE_DIR ${MAINDIR}/inexor)


## Installation

# INSTALL_LOCALLY will surpress the installation into CMAKE_INSTALL_PREFIX which is by default some global system path.
option(INSTALL_LOCALLY "Install everything relative to this folder (${MAINDIR}). Not into some global system directories." ON)

if(INSTALL_LOCALLY)
  set(CMAKE_INSTALL_PREFIX ${MAINDIR} CACHE PATH "" FORCE)
  message(STATUS "Local installation chosen. No files will move outside this folder (${MAINDIR}). .. ${CMAKE_INSTALL_PREFIX}")
endif()

set(EXE_DIR "bin" CACHE STRING "The directory you want to install your executables to. Use target 'install'.")
install(DIRECTORY "${CMAKE_BINARY_DIR}/bin/" DESTINATION "${EXE_DIR}" USE_SOURCE_PERMISSIONS) # Trailing '/' before the DIRECTORY is significant. Without it bin would be installed to bin/bin.
message(STATUS "Generating Project-Files to ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Resulting Executable goes to ${EXE_DIR}")

# We have the .exe suffix on all platforms, to ease our startup manager and possible future uses.
set(CMAKE_EXECUTABLE_SUFFIX ".exe")

option(CREATE_PACKAGE "If enabled we can create a distributable package by building the target \"PACKAGE\"" OFF)
if(CREATE_PACKAGE)
  include(cmake/create_package.cmake)
endif()

## Go for the source subfolder.
add_subdirectory(inexor)
