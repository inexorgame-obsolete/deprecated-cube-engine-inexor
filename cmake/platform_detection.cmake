### @File:
# NOTE:  **This file needs to be included AFTER project()**

# * Set platform boolean OS_* (WINDOWS/LINUX/MACOS)
# * Set architecture booleans X32 and X64
# * Set architecture string PROJECT_ARCH ("64"/"32" or "x86"/"x86_64")
# * Set compiler booleans COMPILER_* (GNU/CLANG/MSVC)


# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  set(OS_MACOS 1)
  set(OS_POSIX 1)
  message(STATUS "Platform: macOS")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(OS_LINUX 1)
  set(OS_POSIX 1)
  message(STATUS "Platform: Linux")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(OS_WINDOWS 1)
  message(STATUS "Platform: Windows")
endif()

# Determine the project architecture.
if(NOT DEFINED PROJECT_ARCH)
  if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PROJECT_ARCH "64")
  else()
    set(PROJECT_ARCH "32")
  endif()
  message(STATUS "No PROJECT_ARCH value specified, using ${PROJECT_ARCH}")
endif()

if(PROJECT_ARCH STREQUAL "64")
  set(X64 1)
else()
  set(X32 1)
endif()

message(STATUS "PROJECT_ARCH: ${PROJECT_ARCH}")

# Determine the compiler.
if(CMAKE_CXX_COMPILER_ID     MATCHES "GNU")
  set(COMPILER_GCC 1)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(COMPILER_CLANG 1)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(COMPILER_MSVC 1)
  # Currently we only support VS 2015+ natively
  if(MSVC_VERSION LESS 1900)
    message(WARNING "Use Visual Studio 2017 or 2015 in order to compile Inexor. (Otherwise you would need to recompile the dependencies yourself)")
  endif()
else()
  message(FATAL_ERROR "Could not detect compiler, please get in contact with the devs.")
endif()

if(OS_WINDOWS AND NOT COMPILER_MSVC)
  message(FATAL_ERROR "On Windows we currently maintain only the Visual Studio toolchain. If that's not an option for you, you need to compile the C++ dependencies manually.")
endif()
