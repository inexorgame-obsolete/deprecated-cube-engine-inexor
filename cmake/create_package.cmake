# Create a package using CPack.
# CPack just uses everything done with "install()". so we "install()" all stuff we normally wouldn't but need for a complete package.

# Wrapper around install(FILES) to preserve subdirectories.
#
# A normal install(FILES tool/create_visual_studio_project.bat DESTINATION "directoryname") would copy the file directly to "directoryname",
# but we want it in "directoryname/tool".
function(install_file_hierarchy DESTINATION_FOLDER)
  foreach (file ${ARGN} )
    get_filename_component(dir ${file} DIRECTORY )
    install( FILES ${file} DESTINATION ${DESTINATION_FOLDER}/${dir} )
  endforeach()
endfunction()

# Normal game bundle

set(INSTALL_FILES changelog.md contributing.md readme.md credits.md license.md)
install_file_hierarchy("./" ${INSTALL_FILES})

set(INSTALL_FOLDERS dist)
install(DIRECTORY ${INSTALL_FOLDERS} DESTINATION "./")

set(DEPENDENCY_LIST_FILE "dependencies.md" CACHE STRING "If DEPENDENCY_LIST_FILE is specified we will save all dependencies including their licenses to this file.")
if(DEPENDENCY_LIST_FILE)
  include(cmake/get_conan_dependency_list.cmake)
  get_conan_dependency_list(${MAINDIR} 1 1 DEPENDENCY_LIST)
  file(WRITE ${DEPENDENCY_LIST_FILE} "${DEPENDENCY_LIST}")
  message(STATUS "Created DEPENDENCY_LIST_FILE: ${DEPENDENCY_LIST_FILE}")
  install_file_hierarchy("./" ${DEPENDENCY_LIST_FILE})
endif()

# Developer files bundle

option(PACK_DEV_FILES "Bundle development files with the package" OFF)

if(PACK_DEV_FILES)
  set(INSTALL_FILES_DEV CMakeLists.txt conanfile.py doxygen.conf tool/create_visual_studio2015_project.bat tool/create_visual_studio2017_project.bat)
  set(INSTALL_FOLDERS_DEV cmake inexor)
  install_file_hierarchy("./" ${INSTALL_FILES_DEV})
  install(DIRECTORY ${INSTALL_FOLDERS_DEV} DESTINATION "./")

  # Generate the documentation using doxygen.
  install(CODE "execute_process(COMMAND doxygen doxygen.conf WORKING_DIRECTORY ${MAINDIR})")
  install(DIRECTORY "${MAINDIR}/doc/" DESTINATION "doc")
endif()


set(PACKAGE_GENERATORS_DEFAULT ZIP)

set(CPACK_GENERATOR ${PACKAGE_GENERATORS_DEFAULT} CACHE STRING "List of CPack Generators which will be created by the 'PACKAGE' target. Default: ZIP")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${MAINDIR}/readme.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Inexor nightly package")
set(CPACK_RESOURCE_FILE_LICENSE "${MAINDIR}/license.md")

## versioning and name of the file

# we do not use the path level number
set(ENV_VERSION "$ENV{INEXOR_VERSION}") # e.g. the git tag "0.3.1-alpha"
if(NOT ENV_VERSION)
  set(CPACK_PACKAGE_VERSION "0.0.0-alpha" CACHE STRING "Complete version of the created package.")
else()
  set(CPACK_PACKAGE_VERSION "${ENV_VERSION}" CACHE STRING "Complete version of the created package.")
endif()


set(CPACK_PACKAGE_INSTALL_DIRECTORY "Inexor")
set(CPACK_ARCHIVE_COMPONENT_INSTALL OFF)
set(CPACK_MONOLITHIC_INSTALL ON)

set(CPACK_PACKAGE_FILE_NAME "inexor-core-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}${PROJECT_ARCH}")

include(CPack)

add_custom_target(package_debug
              COMMAND ${CMAKE_CPACK_COMMAND} --debug --config CPackConfig.cmake
              COMMENTS "Build package with debug and verbose output")
