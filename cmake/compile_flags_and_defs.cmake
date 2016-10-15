#### @File Set Compiler and Linker flags for the different compilers and os-specific definitions ####
## Note: This file needs to be included **after** platform_detection.cmake.


## GCC and CLang 
list(APPEND GNU_OR_CLANG_COMPILER_FLAGS
  -fomit-frame-pointer            # Don't keep the frame pointer for functions that don't need one
  -fno-strict-aliasing            # Avoid assumptions regarding non-aliasing of objects of different types
  -fsigned-char                   # Let the type char be signed, like signed char.
  -pipe                           # Use pipes rather than temporary files for communication between build stages
  -Wall                           # Enable all warnings
  -Wno-switch                     # Execpt Warnings for missing switch cases
  -Wno-deprecated-declarations    # 
  -Wno-missing-braces             #
  -fdiagnostics-show-option       # Show Warning IDs
  -g                              # Generate debug information
)

list(APPEND GCC_OR_CLANG_C_COMPILER_FLAGS
  -std=c99                        # Use the C99 language standard
)
list(APPEND GCC_OR_CLANG_CXX_COMPILER_FLAGS
  -fno-threadsafe-statics         # Don't generate thread-safe statics
  -std=c++14                      # Use the C++14 language standard
)
list(APPEND GCC_OR_CLANG_COMPILER_FLAGS_DEBUG
  -O0                             # Disable optimizations.
  -D_DEBUG                        # Debug build
)
list(APPEND GCC_OR_CLANG_COMPILER_FLAGS_RELEASE
  -O3                             # Optimize for maximum speed
  -fdata-sections                 # Enable linker optimizations to improve locality of reference for data sections
  -ffunction-sections             # Enable linker optimizations to improve locality of reference for function sections
  -fno-ident                      # Ignore the #ident directive
  -DNDEBUG                        # Not a debug build
  -U_FORTIFY_SOURCE               # Undefine _FORTIFY_SOURCE in case it was previously defined
  -D_FORTIFY_SOURCE=1             # Add memory and string function protection (security feature)
)
list(APPEND GCC_OR_CLANG_LINKER_FLAGS
  -Wl,-rpath,.                    # Set rpath so that libraries can be placed next to the executable
)
list(APPEND GCC_OR_CLANG_LINKER_FLAGS_RELEASE
  -Wl,-O1                         # Enable linker optimizations
  -Wl,--as-needed                 # Only link libraries that export symbols used by the binary
  -Wl,--gc-sections               # Remove unused code resulting from -fdata-sections and -function-sections
)

if(X64)
    # 64-bit architecture.
    list(APPEND GCC_OR_CLANG_COMPILER_FLAGS        -m64 -march=x86-64)
    list(APPEND GCC_OR_CLANG_LINKER_FLAGS          -m64)
else()
    # 32-bit architecture.
    list(APPEND GCC_OR_CLANG_COMPILER_FLAGS        -msse2 -mfpmath=sse -mmmx -m32)
    list(APPEND GCC_OR_CLANG_LINKER_FLAGS          -m32)
endif()

# Ability to use your environment own cflags/ldflags.. as well
option(USE_ENVFLAGS "Enable or Disable Use of environment own Compiler/Linker-Flags (for GCC or clang)" ON)

if(USE_ENVFLAGS)
    list(APPEND GCC_OR_CLANG_C_COMPILER_FLAGS      $ENV{CFLAGS})
    list(APPEND GCC_OR_CLANG_CXX_COMPILER_FLAGS    $ENV{CXXFLAGS})
    list(APPEND GCC_OR_CLANG_LINKER_FLAGS          $ENV{LDFLAGS})
endif()


## MS Visual Studio

list(APPEND MSVC_COMPILER_FLAGS
  /MP                                   # Multiprocess compilation
  /Gy                                   # Enable function-level linking
  /Zi                                   # Enable program database
  /fp:fast                              # Calculate with less precise floating point values
  /EHsc                                 # assume extern C stuff never throws exceptions
  /W2                                   # Warning level 2
  /bigobj                               # Disable obj file size limitation to compile big files
  /wd4091                               # Ignore "typedef .. where no variable gets declared ingored" warning
  /wd4244                               # Ignore "conversion from 'int' to 'float', possible loss of data" warning
  /wd4251                               # Ignore "class 'type' needs to have dll-interface .." warning
  /wd4267                               # Ignore "conversion from 'size_t' to 'int', possible loss of data" warning
  /wd4305                               # Ignore "truncation from 'double' to 'float'" warning
  /wd4996                               # Ignore "Function call with parameters that may be unsafe" warning
  )
list(APPEND MSVC_COMPILER_FLAGS_DEBUG
  /MTd                                  # Multithreaded debug runtime
  /Od                                   # Disable optimizations
  /RTC1                                 # Enable basic run-time checks
  /D_DEBUG                              # Debug build
   )
list(APPEND MSVC_COMPILER_FLAGS_RELEASE
  /MT                                   # Multithreaded release runtime
  /O2                                   # Optimize for maximum speed
  /Ob2                                  # Inline any suitable function
  /GF                                   # Enable string pooling
  /D NDEBUG /D _NDEBUG                  # Not a debug build, skip code passages meant for debug.
  /GL                                   # Whole Program Optimization: further optimize the program in linker stage (but calling the compiler).
  )
list(APPEND MSVC_LINKER_FLAGS
  /DEBUG                                # Generate debug information (even for release builds for our stackwalker)
  /MANIFEST:NO                          # No default manifest
  /SAFESEH:NO                           # Do Not Create a table of safe exception handlers (binary incompatible)
  )
list(APPEND MSVC_LINKER_FLAGS_RELEASE
  /OPT:REF                              # Eliminate Unreferenced Data (to revert changes to the binary caused by /DEBUG)
  /OPT:ICF                              # Remove Redundant COMDATs (to revert changes to the binary caused by /DEBUG)
  /INCREMENTAL:NO                       # Linking incremental (faster) does not work anymore with the previous two optimizations
  /LTCG                                 # Link-time Code Generation: further optimisations in the linker stage.
  )



# Just merge compiler/linker flags (specific to the used compiler)
# We do save separate compiler specific flags, since we need them in our reflection pass which builds upon clang
# (and hence always needs clang flags)
if(COMPILER_GCC OR COMPILER_CLANG)
  set(VAR_PREPART "GCC_OR_CLANG")
elseif(COMPILER_MSVC)
  set(VAR_PREPART "MSVC")
endif()

set(CMAKE_C_FLAGS                     ${${VAR_PREPART}_COMPILER_FLAGS}          ${${VAR_PREPART}_C_COMPILER_FLAGS})
set(CMAKE_CXX_FLAGS                   ${${VAR_PREPART}_COMPILER_FLAGS}          ${${VAR_PREPART}_CXX_COMPILER_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG             ${${VAR_PREPART}_COMPILER_FLAGS_DEBUG}    ${${VAR_PREPART}_CXX_COMPILER_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE           ${${VAR_PREPART}_COMPILER_FLAGS_RELEASE}  ${${VAR_PREPART}_CXX_COMPILER_FLAGS_RELEASE})
set(CMAKE_EXE_LINKER_FLAGS            ${${VAR_PREPART}_LINKER_FLAGS}            ${${VAR_PREPART}_EXE_LINKER_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS_DEBUG      ${${VAR_PREPART}_LINKER_FLAGS_DEBUG}      ${${VAR_PREPART}_EXE_LINKER_FLAGS_DEBUG})
set(CMAKE_EXE_LINKER_FLAGS_RELEASE    ${${VAR_PREPART}_LINKER_FLAGS_RELEASE}    ${${VAR_PREPART}_EXE_LINKER_FLAGS_RELEASE})

# Fix CMake having no easy workaround to change between cmake lists (separated by ;) and cmake strings (separated by " ")
# TODO remove this fix by using target_add_compile flags or sth which can handle a cmake list.
string(REPLACE ";" " " CMAKE_C_FLAGS                        "${CMAKE_C_FLAGS}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS                      "${CMAKE_CXX_FLAGS}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS_DEBUG                "${CMAKE_CXX_FLAGS_DEBUG}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS_RELEASE              "${CMAKE_CXX_FLAGS_RELEASE}")
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS               "${CMAKE_EXE_LINKER_FLAGS}")
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS_DEBUG         "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS_RELEASE       "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")

message(STATUS "Current mode:                   ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler:                       ${CMAKE_CXX_COMPILER_ID}")

message(STATUS "C_FLAGS:                        ${CMAKE_C_FLAGS}")
message(STATUS "CXX_FLAGS:                      ${CMAKE_CXX_FLAGS}")
message(STATUS "CXX_FLAGS_DEBUG:                ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CXX_FLAGS_RELEASE:              ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "EXE_LINKER_FLAGS:               ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "EXE_LINKER_FLAGS_DEBUG:         ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(STATUS "EXE_LINKER_FLAGS_RELEASE:       ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")


#### Platform specific definitions ####

# Allow C++ programs to use stdint.h macros specified in the C99 standard that
# aren't in the C++ standard (e.g. UINT8_MAX, INT64_MIN, etc).
add_definitions(-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS)

if(OS_POSIX)
  # Allow the Large File Support (LFS) interface to replace the old interface.
  add_definitions(-D_FILE_OFFSET_BITS=64)
endif()

if(OS_WINDOWS)
  # -DWIN32 -D_WIN32 -D_WINDOWS           = Windows platform
  # -DNOMINMAX                            = Use the standard's templated min/max
  # -D_WIN32_WINNT=0x0600                 = Target is Windows Vista
  # -D_MATH_DEFINES_DEFINED               = We define our own math constants (PI, ln(2)...) this fixes warnings when including math.h
  # -DWIN32_LEAN_AND_MEAN               = Skip deprecated windows.h parts (which will for sure cause troubles)
  add_definitions(-DWIN32 -D_WIN32 -D_WINDOWS -DWINDOWS -DNOMINMAX -D_WIN32_WINNT=0x0600 -D_MATH_DEFINES_DEFINED -DWIN32_LEAN_AND_MEAN )
  if(X64)
    add_definitions(-DWIN64)
  endif()	
endif()

get_directory_property(DEFINITIONS              COMPILE_DEFINITIONS)
message(STATUS "Platform definitions:           ${DEFINITIONS}")

