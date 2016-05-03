#### @File Set Compiler and Linker flags for the different compilers and os-specific definitions ####
## Note: This file needs to be included **after** platform_detection.cmake.

if(COMPILER_CLANG OR COMPILER_GNU)
    set(I_LIBTYPE                 SHARED)
    # -fomit-frame-pointer            = Don't keep the frame pointer for functions that don't need one
    # -fno-strict-aliasing            = Avoid assumptions regarding non-aliasing of objects of different types
    # -fsigned-char                   = Let the type char be signed, like signed char.
    # -pipe                           = Use pipes rather than temporary files for communication between build stages
    # -Wall                           = Enable all warnings
    # -Wno-switch                     = Execpt Warnings for missing switch cases
    # -fdiagnostics-show-option       = Show Warning IDs
    # -g                              = Generate debug information
    set(I_COMPILER_FLAGS          "-fomit-frame-pointer -fno-strict-aliasing -fsigned-char -pipe -Wall -Wno-switch -Wno-deprecated-declarations -g -Wno-missing-braces -fdiagnostics-show-option")
    # -std=c99                        = Use the C99 language standard
    set(I_C_COMPILER_FLAGS        "-std=c99")
    # -fno-threadsafe-statics         = Don't generate thread-safe statics
    # -std=c++11                      = Use the C++11 language standard
    set(I_CXX_COMPILER_FLAGS      "-fno-threadsafe-statics -std=c++14")
    # -O0                             = No optimization
    # -D_DEBUG                        = Debug build
    set(I_COMPILER_FLAGS_DEBUG    "-O0 -D_DEBUG")
    # -O3                             = Optimize for maximum speed
    # -fdata-sections                 = Enable linker optimizations to improve locality of reference for data sections
    # -ffunction-sections             = Enable linker optimizations to improve locality of reference for function sections
    # -fno-ident                      = Ignore the #ident directive
    # -DNDEBUG                        = Not a debug build
    # -U_FORTIFY_SOURCE               = Undefine _FORTIFY_SOURCE in case it was previously defined
    # -D_FORTIFY_SOURCE=1             = Add memory and string function protection (security feature)
    set(I_COMPILER_FLAGS_RELEASE  "-O3 -fdata-sections -ffunction-sections -fno-ident -DNDEBUG -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1")
    # -Wl,-rpath,.                    = Set rpath so that libraries can be placed next to the executable
    set(I_LINKER_FLAGS            "-Wl,-rpath,.")
    # -Wl,-O1                         = Enable linker optimizations
    # -Wl,--as-needed                 = Only link libraries that export symbols used by the binary
    # -Wl,--gc-sections               = Remove unused code resulting from -fdata-sections and -function-sections
    set(I_LINKER_FLAGS_RELEASE    "-Wl,-O1 -Wl,--as-needed -Wl,--gc-sections")

    if(X64)
        # 64-bit architecture.
        set(I_COMPILER_FLAGS        "${I_COMPILER_FLAGS} -m64 -march=x86-64")
        set(I_LINKER_FLAGS          "${I_LINKER_FLAGS} -m64")
    else()
        # 32-bit architecture.
        set(I_COMPILER_FLAGS        "${I_COMPILER_FLAGS} -msse2 -mfpmath=sse -mmmx -m32")
        set(I_LINKER_FLAGS          "${I_LINKER_FLAGS} -m32")
    endif()

	# Ability to use your environment own cflags/ldflags.. as well
    option( USE_ENVFLAGS "Enable or Disable Use of environment own Compiler/Linker-Flags" ON)

    if(USE_ENVFLAGS)
        set(I_C_COMPILER_FLAGS      "${I_C_COMPILER_FLAGS} $ENV{CFLAGS}")
        set(I_CXX_COMPILER_FLAGS    "${I_CXX_COMPILER_FLAGS} $ENV{CXXFLAGS}")
        set(I_LINKER_FLAGS          "${I_LINKER_FLAGS} $ENV{LDFLAGS}")
    endif()
endif()


if(COMPILER_MSVC)
    # /MP                                   = Multiprocess compilation
    # /Gy                                   = Enable function-level linking
    # /Zi                                   = Enable program database
    # /fp:fast                              = Calculate with less precise floating point values
    # /EHsc                                 = assume extern C stuff never throws exceptions
    # /W2                                   = Warning level 2
    # /wd"4091"                             = Ignore "typedef .. where no variable gets declared ingored" warning
    # /wd"4244"                             = Ignore "conversion from 'int' to 'float', possible loss of data" warning
    # /wd"4251"                             = Ignore "class 'type' needs to have dll-interface .." warning
    # /wd"4267"                             = Ignore "conversion from 'size_t' to 'int', possible loss of data" warning
    # /wd"4305"                             = Ignore "truncation from 'double' to 'float'" warning
    # /wd"4996"                             = Ignore "Function call with parameters that may be unsafe" warning
  set(I_COMPILER_FLAGS          "-MP -Gy -Zi -fp:fast -EHsc -W2 -wd\"4091\"  -wd\"4244\" -wd\"4251\" -wd\"4267\" -wd\"4305\" -wd\"4996\"")
    # /MTd                                  = Multithreaded debug runtime
    # /Od                                   = Disable optimizations
    # /RTC1                                 = Enable basic run-time checks
    # -D_DEBUG                              = Debug build
  set(I_COMPILER_FLAGS_DEBUG    "-MTd -RTC1 -Od -D_DEBUG")
    # /MT                                   = Multithreaded release runtime
    # /O2                                   = Optimize for maximum speed
    # /Ob2                                  = Inline any suitable function
    # /GF                                   = Enable string pooling
    # /D NDEBUG /D _NDEBUG                  = Not a debug build, skip code passages meant for debug.
    # /GL                                   = Whole Program Optimization: further optimize the program in linker stage (but calling the compiler).
  set(I_COMPILER_FLAGS_RELEASE  "-MT -O2 -Ob2 -GF -DNDEBUG -D_NDEBUG -GL")
    # /DEBUG                                = Generate debug information (even for release builds for our stackwalker)
    # /MANIFEST:NO                          = No default manifest
    # /SAFESEH:NO                           = Do Not Create a table of safe exception handlers (binary incompatible)
  set(I_LINKER_FLAGS            "-MANIFEST:NO -SAFESEH:NO -DEBUG ")
    # /OPT:REF                              = Eliminate Unreferenced Data (to revert changes to the binary caused by /DEBUG)
    # /OPT:ICF                              = Remove Redundant COMDATs (to revert changes to the binary caused by /DEBUG)
    # /INCREMENTAL:NO                       = Linking incremental (faster) does not work anymore with the previous two optimizations
    # /LTCG                                 = Link-time Code Generation: further optimisations in the linker stage.
  set(I_LINKER_FLAGS_RELEASE    "-LTCG -OPT:REF -OPT:ICF -INCREMENTAL:NO")

  # Add the library path as well
  foreach(dir ${CMAKE_LIBRARY_PATH}) # We need to do this seperately since LIBPATH does not accept more than one dir at once
    set(I_EXE_LINKER_FLAGS "${I_EXE_LINKER_FLAGS} -LIBPATH:${dir}")
  endforeach()
endif()

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
  add_definitions(-DWIN32 -D_WIN32 -D_WINDOWS -DWINDOWS -DNOMINMAX -D_WIN32_WINNT=0x0600 -D_MATH_DEFINES_DEFINED)
  if(X64)
    add_definitions(-DWIN64)
  endif()	
endif()


# Merge compiler/linker flags.
set(CMAKE_C_FLAGS                     "${I_COMPILER_FLAGS} ${I_C_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS                   "${I_COMPILER_FLAGS} ${I_CXX_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG             "${I_COMPILER_FLAGS_DEBUG} ${I_CXX_COMPILER_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE           "${I_COMPILER_FLAGS_RELEASE} ${I_CXX_COMPILER_FLAGS_RELEASE}")
set(CMAKE_EXE_LINKER_FLAGS            "${I_LINKER_FLAGS} ${I_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG      "${I_LINKER_FLAGS_DEBUG} ${I_EXE_LINKER_FLAGS_DEBUG}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE    "${I_LINKER_FLAGS_RELEASE} ${I_EXE_LINKER_FLAGS_RELEASE}")

message(STATUS "Current mode:                   ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler:                       ${CMAKE_CXX_COMPILER_ID}")
get_directory_property(DEFINITIONS              COMPILE_DEFINITIONS)
message(STATUS "Compiler definitions:           ${DEFINITIONS}")

message(STATUS "C_FLAGS:                        ${CMAKE_C_FLAGS}")
message(STATUS "CXX_FLAGS:                      ${CMAKE_CXX_FLAGS}")
message(STATUS "CXX_FLAGS_DEBUG:                ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CXX_FLAGS_RELEASE:              ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "EXE_LINKER_FLAGS:               ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "EXE_LINKER_FLAGS_DEBUG:         ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(STATUS "EXE_LINKER_FLAGS_RELEASE:       ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
