
# Returns if conan is configured for Debug or Release
function(get_conan_build_type BUILD_TYPE)
    MESSAGE(STATUS "Current conanbuildinfo.cmake directory: " ${CMAKE_BINARY_DIR})
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/conaninfo.txt)
        message(FATAL_ERROR "conaninfo.txt not found. Run conan prior to cmake!")
        return()
    endif()

    file (READ "${CMAKE_BINARY_DIR}/conaninfo.txt" CONANINFO)

    string(REGEX MATCH "build_type=([A-Za-z0-9_ ]+)" _MATCHED ${CONANINFO})
    if(DEFINED CMAKE_MATCH_1)
        string(STRIP ${CMAKE_MATCH_1} CO_BUILD_TYPE)
        set(${BUILD_TYPE} ${CO_BUILD_TYPE} PARENT_SCOPE)
    endif()
endfunction()
