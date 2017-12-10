# Otherwise we can't access the path of this directory anyhow
set(DIR_OF_FUNCTIONS_CMAKE ${CMAKE_CURRENT_LIST_DIR})

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
  file(GLOB_RECURSE headers ${abs}/**.hpp)
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

# USAGE: group_sources(file1 file2 file3)
#
# Set up source groups (for better browsing inside IDEs) for the provided list of source files.
# Filenames can be absolute or relative to SOURCE_DIR.
# Group names get created based on that path.
function(group_sources)
    foreach(FILE ${ARGN})
      # Get the directory of the source file
      get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

      # Remove common directory prefix to make the group
      string(REPLACE "${SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

      if(OS_WINDOWS)
        # Make sure we are using windows slashes
        string(REPLACE "/" "\\" GROUP "${GROUP}")
      endif()

      source_group("${GROUP}" FILES "${FILE}")
    endforeach()
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
      group_sources("${${mod}_MODULE_HEADERS} ${${mod}_MODULE_SOURCES}")
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

# Wrapper around find_library to autodetect debug and
# release versions of a library.
#
# This is necessary when building on Windows in VS (ABI conflicts between MT and MTd).
#
# Note: only effects msvc so far
# Usage: find_cpp_library(<RETURNVAR> <LIBNAME> [NOCACHE])
# Arguments:
#   VAR        –   Output variable
#   LIB        -   the Library name
# Example: find_cpp_library(PROTOBUF_LIBRARIES protobuf)
#
function(find_cpp_library VAR LIB)
  if(DEFINED HAS_FIND_LIBRARY_WRAPPER)
    definition_find_cpp_library(tmp ${LIB})
    if(NOT tmp)
      find_library(tmp ${LIB})
    endif()
  else()
    find_library(tmp ${LIB})
  endif()

  if (ARGN STREQUAL "NOCACHE")
    set(${VAR} "${tmp}" PARENT_SCOPE)
  else()
    set(${VAR} "${tmp}" CACHE INTERNAL "")
  endif()

  unset(tmp CACHE)
endfunction()

# Search for multiple libraries with multiple possible names
#
# This is be useful, when a module requires multiple libs or
# when a lib can have multiple names.
#
# Wrapper around find_cpp_library, so libs with debug and
# release versions are supported, which in turn is a wrapper
# around find library, so you can omit /^lib/ and the usual
# suffixes (.dll/.so/.o/.obj/.a)
#
# USAGE: find_libs(<OUTVAR> lib1_names...
#     [LIB libN_names... ]... NOCACHE)
#
# EXAMPLE:
#     You are working on module `cuteness` module cuteness;
#     cuteness depends on two libraries: libkittens.so and
#     libdog.a; libdog.a might however also be called libpuppy.so.
#     You could use the following command:
#
#     find_libs(CUTENESS_LIBS kittens LIB dog puppy)
function(find_libs)
  set(out "")
  set(found "")
  set(outvar "")
  set(nocache "")
  set(attempts "")

  ## READING ARGS

  foreach(arg ${ARGN})

    if(${arg} STREQUAL "NOCACHE")
      set(nocache true)

    elseif(${arg} STREQUAL "LIB")
      if (NOT found AND NOT attempts STREQUAL "")
        message(SEND_ERROR "Could not find a lib for ${attempts} !")
      endif()
      set(found "")
      set(attempts "")

    elseif(NOT outvar) # First real arg: OUTVAR
      set(outvar "${arg}")

    elseif(NOT found) # Real arg: lib name
      find_cpp_library(lib "${arg}" NOCACHE)
      if (lib)
        set(found true)
        list(APPEND out "${lib}")
      else()
        list(APPEND attempts "${arg}")
      endif()

    endif()
  endforeach()

  ## RETURN

  if (out AND nocache)
    set(${outvar} ${out} PARENT_SCOPE)
  elseif(out)
    set(${outvar} ${out} CACHE INTERNAL "")
  endif()
endfunction()

function(add_windows_manifest target)
  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND "mt.exe" -nologo
            -manifest \"${DIR_OF_FUNCTIONS_CMAKE}/windows.manifest.xml\"
            -outputresource:"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.exe"\;\#1
    COMMENT "Adding manifest..."
    )
endfunction()

# USAGE: add_app(executable SOURCE_FILES [CONSOLE_APP])
#
# Set up an executable.
# First this function creates a platform specific
# executable. On windows it creates a WIN32 executable, on
# macOS it creates a bundle.
# If "CONSOLE_APP" is given within the arguments,
# it wont create a WIN32 but a console app on windows.
#
# The executable created is also installed: On windows we
# add it to the executables folder, and we have it installed
# in ${EXE_DIR}.
#
# see: add_executable
function(add_app exe)
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
    add_windows_manifest(${exe})
  elseif(OS_MACOS)
    add_executable(${exe} MACOS_BUNDLE ${sources})
  else()
    add_executable(${exe} ${sources})
  endif()

  if(MSVC)
    set_property(TARGET ${exe} PROPERTY FOLDER "executables")
  endif()

  target_link_libraries(${exe} ${CONAN_LIBS})
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

  if(NOT DEFINED BUILD_ALL)
    option(${option_name} "Build ${subdir}" ${initial})
  endif()

  if(DEFINED BUILD_ALL)
      add_subdirectory(${subdir})
  elseif(${${option_name}})
      add_subdirectory(${subdir})
  else()
      message(STATUS "not building ${subdir}")
  endif()
endfunction()

# USAGE: pragma_once(net_module server_target)
# Servers as include guard alternative, since its sets the variable ALREADY_INCLUDED
# in its parents scope.
function(pragma_once VAR1 VAR2)

  # GET_PROPERTY and SET_PROPERTY is a workaround for having global variables in cmake.
  # Cached strings would not work, since they'd stay for the next configuring as well..
  GET_PROPERTY(LOCAL_REGISTRY GLOBAL PROPERTY GLOBAL_PRAGMA_REGISTRY)

  if(";${LOCAL_REGISTRY};" MATCHES "Pragma_${VAR1}_${VAR2}")
    set(ALREADY_INCLUDED 1 PARENT_SCOPE)
    return()
  endif()
  set(LOCAL_REGISTRY "${LOCAL_REGISTRY} Pragma_${VAR1}_${VAR2}")
  SET_PROPERTY(GLOBAL PROPERTY GLOBAL_PRAGMA_REGISTRY ${LOCAL_REGISTRY})

  set(ALREADY_INCLUDED 0 PARENT_SCOPE)
endfunction()
