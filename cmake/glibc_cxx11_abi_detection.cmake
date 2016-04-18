# USAGE: register_possible_dependency(lib...)
#
# Used to register any dependencies we might need.
# Will just store the given libraries in the cached variable
# DEPENDENCY_REGISTRY
function(register_possible_dependency)
  set(tmp "${DEPENDENCY_REGISTRY}")
  unset(DEPENDENCY_REGISTRY CACHE)

  foreach(dep "${ARGN}")
    if (NOT "${dep}" STREQUAL "")
      message(STATUS "Registrig lib dependency: ${dep}")
      list(APPEND tmp "${dep}")
    endif()
  endforeach()

  set(DEPENDENCY_REGISTRY "${tmp}" CACHE INTERNAL "List of all libraries inexor may depend on.")
endfunction()

# USAGE: lib_requires_GLIBC_CXX11_ABI(LIBRARY_PATH, OUTPUT_VARIABLE)
#
# Checks if the given library depends on the new GLIBC C++11 ABI.
# The given variable will be defined with "yes" if the library needs
# the new ABI or with "no" if the library doesn't need the new ABI.
function(lib_requires_GLIBC_CXX11_ABI lib var)
  execute_process( COMMAND sh -c "readelf -Ws \"$0\" | c++filt | grep -qF cxx11" "${lib}" RESULT_VARIABLE return_code)

  if ("${return_code}" EQUAL 0)
    set("${var}" yes PARENT_SCOPE)
  else()
    set("${var}" no PARENT_SCOPE)
  endif()
endfunction()

# Check whether the new GLIBC CXX11 ABI should be used.
# Will store 1 or 0 in _GLIBCXX_USE_CXX11_ABI
#
# The call to this needs to be deferred until all dependencies are found.
function(check_GLIBC_CXX11_AB1)
  if (NOT DEFINED _GLIBCXX_USE_CXX11_ABI)
    if(MSVC)
      message(STATUS "Not on clang or gcc. Skipping GLIBC C++11 ABI check.")
      set(_GLIBCXX_USE_CXX11_ABI 0 CACHE INTERN "")
      return()
    endif()

    set(need no)

    foreach(lib ${DEPENDENCY_REGISTRY})
      lib_requires_GLIBC_CXX11_ABI("${lib}" thisneed)
      message(STATUS "${lib} requires new GLIBC C++11 ABI: ${thisneed}")

      if ("${thisneed}" STREQUAL "yes")
        set(need "yes")
      endif()
    endforeach()
    
    message(STATUS "Compiling with new GLIBC C++11 ABI: ${need}")
    if ("${need}" STREQUAL "yes")
      set(_GLIBCXX_USE_CXX11_ABI 1 CACHE INTERN "")
    else()
      set(_GLIBCXX_USE_CXX11_ABI 0 CACHE INTERN "")
    endif()
  endif()
endfunction()

# Automatically defines -D_GLIBCXX_USE_CXX11_ABI with the correct values.
# Essentially this iterates over each known library dependency and checks
# whether that library requires the new or the old ABI.
#
# This should be used by any module compiling c++ code.
#
# This is using require_ style because we need to defer this
# until all dependencies are found.
#
# TODO: Detect pure C libraries as requiring no specific ABI. At the moment those are detected to use the old abi.
# TODO: Add support for GNU LD scripts
function(require_cxx11_abi targ)
  check_GLIBC_CXX11_AB1()
  add_definitions(-D_GLIBCXX_USE_CXX11_ABI=${_GLIBCXX_USE_CXX11_ABI})
endfunction()
