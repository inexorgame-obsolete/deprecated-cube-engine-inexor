# TODO: Unify flags and lib detection on ALL plattforms as much as possible
# TODO: Move functions to an extra file
# TODO: Automatically detect new modules
# TODO: Encapsulate all settings in a module
# TODO: Write a lib detector that does the following: Search for cmake definitions; search for pkg-cfg's; search for libs and headers; everyting may be specified multiple times

# Wrong folder: User attempted to generate from src instead of the main-inexor folder
if(NOT DEFINED PROJECT_ARCH)
    message(FATAL_ERROR "You are generating from the wrong folder! \"Where is the Source:\" (currently: ${MAINDIR}) should point to the Main directory (!) of Inexor")
endif()


# TODO: Write function fallback_find_package?
# TODO: We should stick to singular in all lib detection
find_package(ZLIB)
if(NOT ${ZLIB_FOUND})
  find_library(ZLIB_LIBRARY2 NAMES z zlib1)
  find_path(ZLIB_INCLUDE_DIR2 zlib.h)

  message(STATUS "ZLIB_LIBRARY2 = ${ZLIB_LIBRARY2}")
  message(STATUS "ZLIB_INCLUDE_DIR2 = ${ZLIB_INCLUDE_DIR2}")

  if (EXISTS ${ZLIB_LIBRARY} AND EXISTS ${ZLIB_INCLUDE_DIR})
    set(ZLIB_FOUND 1)
  else()
    message(ERROR "Could not find zlib")
  endif()
endif()

find_package(OpenGL)
find_package(PkgConfig)

message(STATUS "Detecting Libs...")

# Linux Libraries for Server AND Client
if(OS_LINUX)

    # SDL (crossplatform Library for anything general)
    if(NOT BUILD_SDL2_LOCAL AND PKG_CONFIG_FOUND)
        message(STATUS "Using pkg-config to detect SDL2...")
        pkg_check_modules(SDL2 QUIET sdl2)
        if(SDL2_FOUND)
            message(STATUS "Found SDL2.")
            message(STATUS "include: ${SDL2_INCLUDE_DIRS}")
        else()
            message(FATAL_ERROR "SDL2 not found.")
        endif()
    else()
        if(PKG_CONFIG_FOUND)
            message(STATUS "Using local SDL2.")
        else()
            message(STATUS "Using local SDL2. (could not find PKG_CONFIG)")
        endif()
        set(SDL2_LIBRARIES "SDL2")
    endif()
    set(SDL2_LIBRARIES "${SDL2_LIBRARIES};SDL2_image;SDL2_mixer")
    add_definitions(-D_REENTRANT -D_THREAD_SAFE)


    # ENet networking library
    if(NOT DEFINED ENET_LIBRARIES AND NOT DEFINED LOCAL_ENET)
        set(LOCAL_ENET 1 CACHE INTERNAL "Use local enet library")
    elseif(DEFINED LOCAL_ENET)
        set(LOCAL_ENET ${LOCAL_ENET} CACHE INTERNAL "Use local enet library")
    else()
        set(LOCAL_ENET 0 CACHE INTERNAL "Use local enet library")
    endif()

    if(${LOCAL_ENET})
        message(STATUS "Building local ENet")
        add_subdirectory(libraries/enet)
    endif()
endif()


# common MACOSX and Windows Libraries
if(OS_MACOSX OR OS_WINDOWS)
    find_library(ENET_LIBRARIES enet)
    find_path(ENET_INCLUDE_DIRS enet/enet.h)


    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_IMAGE_LIBRARY SDL2_image)
    find_library(SDL2_MIXER_LIBRARY SDL2_mixer)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY}
        ${SDL2_IMAGE_LIBRARY})

    find_path(SDL2_INCLUDE_DIR       SDL.h       PATH_SUFFIXES SDL2)
    find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h PATH_SUFFIXES SDL2)
    find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h PATH_SUFFIXES SDL2)
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
endif()

# COCOA for SQL on OSX
if(OS_MACOSX)
  find_library(CORESERVICES_LIBRARY CoreServices)
  find_library(COCOA_LIBRARY Cocoa)
  list(APPEND SDL2_LIBRARIES
      ${CORESERVICES_LIBRARY} ${COCOA_LIBRARY})
endif()

# Windows Libraries for Server AND Client
if(OS_WINDOWS)
    if(NOT MSVC)
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} -static-libgcc -static-libstdc++)
    endif()
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} kernel32 ws2_32 winmm)
endif()

set(ALL_MODULES "" CACHE INTERNAL "")
set(ALL_HEADERS "" CACHE INTERNAL "")
set(OUTSOURCED_MODULES "" CACHE INTERNAL "")

# USAGE: declare_module(<NAME> [PATH])
#
# Automatically search for headers and source files inside
# a module, export these and add a group for visual studio
# that contains all the sources.
#
# ARGUMENTS:
#   NAME – The name of the module
#   PATH – The relative path all the sources are inside
#
# SIDE EFFECTS:
#   * ${NAME}_MODULE_HEADERS – such a variable is created;
#     it contains a list of all headers in this module
#   * ${NAME}_MODULE_SOURCES – such a variable is created;
#     it contains a list of all source files in this module
#   * A VS source group is added with the name ${NAME}; it
#     contains all the headers and source files in this module
function(declare_module NAME PATH)
  get_filename_component(abs
    "${CMAKE_CURRENT_SOURCE_DIR}/${PATH}" REALPATH)
  string(TOUPPER "${NAME}" mod)
  message(STATUS "DECLARE MODULE(${NAME}, ${PATH}) -> ${mod} inside ${abs}")

  # Search headers
  file(GLOB_RECURSE headers ${abs}/**.h)
  set(${mod}_MODULE_HEADERS ${headers}
    CACHE INTERNAL "Headers of the ${NAME} module")

  # Search sources
  file(GLOB_RECURSE sources ${abs}/**.cpp)
  set(${mod}_MODULE_SOURCES ${sources}
    CACHE INTERNAL "Sources of the ${NAME} module")

  # Save for group_modules()
  set(ALL_MODULES ${ALL_MODULES} ${mod} CACHE INTERNAL "")
  set(ALL_HEADERS ${ALL_HEADERS} ${headers} CACHE INTERNAL "")
endfunction()

# USAGE: group_modules()
#
# Set up Source_groups for VS/XCode.
# Does not need to be called normally, except you are not
# using add_app
#
function(group_modules)
  foreach(mod ${ALL_MODULES})
    # skip creating a source_group for outsourced_modules
    set(skip 0)
    foreach(not_mod ${OUTSOURCED_MODULES})
      string(COMPARE EQUAL ${mod} ${not_mod} skip)
      if(skip)
        break()
      endif()
    endforeach()

    if(NOT skip)
      string(TOLOWER "${mod}" gname)
      source_group(${gname} FILES ${${mod}_MODULE_HEADERS} ${${mod}_MODULE_SOURCES})
    endif()
  endforeach()
endfunction()

# USAGE: prepend(<VARIABLE> <PREP> [ARGS]...)
#
# Prepend ${PREP} to each element of ${ARGS} and save the
# result in VARIABLE.
#
# ARGUMENTS:
#   VARIABLE – The variable to save the sources in
#   PREP     – The string to prepend
#   ARGS...  – The strings to prepend to
# SIDE EFFECTS:
#   * Creates a variable named VARIABLE and writes our
#     result there.
#
function(prepend variable prep)
  set(res "")
  foreach(s ${ARGN})
    set(res ${res} "${prep}/${s}")
  endforeach()
  set(${variable} ${res} PARENT_SCOPE)
endfunction()

# Wrapper around find_library to autodetect _debug and _release versions of a library
# Reason see lib/readme
#
# Note: only effects msvc so far
# Usage: find_cpp_library(<RETURNVAR> <name>)
# Arguments:
#   Returnvar   -   Usually the <LibraryName>_LIBRARY, but can be set differently.
#                   It will contain the found lib afterwards.
#   name        -   the Library name
# Example: find_cpp_library(PROTOBUF_LIBRARIES protobuf)
#
function(find_cpp_library RETURNVAR LIBNAME)
    if(DEFINED HAS_FIND_LIBRARY_WRAPPER)
        definition_find_cpp_library(${RETURNVAR} ${LIBNAME})
    else()
        find_library(${RETURNVAR} ${LIBNAME})
    endif()
    set(${RETURNVAR} ${${RETURNVAR}} CACHE INTERN "")
endfunction()

# USAGE: target_link_libs( <BINARYNAME> [ARGS] )
#
# Wrapper around target_link libs to be able to set different libs for debug and release
# (Necessary for MSVC in combination with stdlib-dependend Libs)
#
# ARGUMENTS
#  BINARYNAME - The Name of the target to link the libraries to
#  ARGS...    - The Libraries
#
function(target_link_libs BINARYNAME)
    if(DEFINED HAS_FIND_LIBRARY_WRAPPER)
      set(C_LIBS "")   # No need to seperately link c-libs
      set(CPP_LIBS_DEBUG "")
      set(CPP_LIBS_RELEASE "")

      foreach(CURLIB ${ARGN})
        if(${CURLIB} MATCHES "(.*)_release(.*)")
          set(CPP_LIBS_RELEASE ${CURLIB})
        elseif(${CURLIB} MATCHES "(.*)_debug(.*)")
          set(CPP_LIBS_DEBUG ${CURLIB})
        else()
          set(C_LIBS ${C_LIBS} ${CURLIB})
        endif()
      endforeach()

      target_link_libraries(${BINARYNAME} ${C_LIBS})
      if(NOT ${CPP_LIBS_DEBUG} STREQUAL "")
        target_link_libraries(${BINARYNAME} debug ${CPP_LIBS_DEBUG})
      endif()
      if(NOT ${CPP_LIBS_RELEASE} STREQUAL "")
        target_link_libraries(${BINARYNAME} optimized ${CPP_LIBS_RELEASE})
      endif()

    else()
      # No need on Unix systems, because of binary compatibility between different configurations
      target_link_libraries(${BINARYNAME} ${ARGN})
    endif()
endfunction()

# USAGE: add_app(executable SOURCE_FILES [CONSOLE_APP])
#
# Set up an executable.
# First this function creates a platform specific
# executable. On windows it creates a WIN32 executable, on
# OSX it creates a bundle.
# If "CONSOLE_APP" is given within the arguments,
# it wont create a WIN32 but a console app on windows.
#
# The executable created is also installed: On windows we
# add it to the executables folder, and we have it installed
# in ${EXE_DIR}.
#
# see: add_executable
function(add_app exe )
  message(STATUS "Adding Application: ${exe}")

  # Remove "CONSOLE_APP" if specified
  set(sources "${ARGN}")
  list(REMOVE_ITEM sources "CONSOLE_APP")

  group_modules()

  if(OS_WINDOWS)
    if(";${ARGN};" MATCHES ";CONSOLE_APP;")
      add_executable(${exe} ${sources} ${ALL_HEADERS})
    else()
      add_executable(${exe} WIN32 ${sources} ${ALL_HEADERS})
    endif()
  elseif(OS_MACOSX)
    add_executable(${exe} MACOSX_BUNDLE ${sources})
  else()
    add_executable(${exe} ${sources})
  endif()

  if(MSVC)
    set_property(TARGET ${exe} PROPERTY FOLDER "executables")
  endif()

  install(TARGETS ${exe} DESTINATION ${EXE_DIR})
endfunction()

# USAGE: add_lib(modulename)
#
# Set up a STATIC LIB for the corresponding module.
# Used for solving source_group issues for some IDEs
# @example add_lib(net)
# @sideeffects creates a library called module_<modulname>.
#
# see add_library
function(add_lib module)
  string(TOUPPER ${module} mod)
  string(TOLOWER ${module} mod_lil)

  set(name module_${mod_lil})
  add_library(${name} STATIC ${${mod}_MODULE_SOURCES} ${${mod}_MODULE_HEADERS})

  set(OUTSOURCED_MODULES ${OUTSOURCED_MODULES} ${mod} CACHE INTERNAL "")
endfunction()

# USAGE: opt_subdir SUBDIR INITIAL
#
# Optionally include a sub directory.
# This adds an option called BUILD_${subdir} (all caps) and
# includes the named subdir if that option is ON.
function(opt_subdir subdir initial)
  string(TOUPPER "BUILD_${subdir}" option_name)
  option(${option_name} "Build ${subdir}" ${initial})

  if(${${option_name}})
      add_subdirectory(${subdir})
  else()
      message(WARNING "not building ${subdir}")
  endif()
endfunction()

set(CEF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/libraries/cef3")
include_directories(
    ${ENET_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${SOURCE_DIR}
    ${CEF_INCLUDE_DIRS}
    ${SOURCE_DIR}/shared
    ${SOURCE_DIR}/engine
    ${SOURCE_DIR}/fpsgame)

if(NOT DEFINED LIBCEF_DLL_LIBRARIES AND NOT DEFINED LOCAL_LIBCEF_DLL)
    set(LOCAL_LIBCEF_DLL 1 CACHE INTERNAL "Use local libcef_dll library")
elseif(DEFINED LOCAL_LIBCEF_DLL)
    set(LOCAL_LIBCEF_DLL ${LOCAL_LIBCEF_DLL} CACHE INTERNAL "Use local libcef_dll library")
else()
    set(LOCAL_LIBCEF_DLL 0 CACHE INTERNAL "Use local libcef_dll library")
endif()

if(${LOCAL_LIBCEF_DLL})
    message(STATUS "Building local libcef_dll")
    add_subdirectory(libraries/cef3/libcef_dll)
endif()

add_subdirectory(libraries) # muparser
declare_module(shared ./shared)
declare_module(engine ./engine)
declare_module(fpsgame ./fpsgame)
add_subdirectory(util)
add_subdirectory(net) # net module, asio lib
add_subdirectory(rpc) # rpc module, protobuf lib

# *sigh* We can't make shared a real module. Yet.
# It's too interdependant
set(COMMON_SOURCES ${SHARED_MODULE_SOURCES} CACHE INTERNAL "")

# This contains the libraries that are used by all targets.
# Excludes OpenGL and SDL, because those are only used by
# the client.
set(COMMON_LIBS
  ${ENET_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${ADDITIONAL_LIBRARIES} CACHE INTERNAL "")

# Actual targets
opt_subdir(client ${OPENGL_FOUND})
opt_subdir(server on)
opt_subdir(test   on)
