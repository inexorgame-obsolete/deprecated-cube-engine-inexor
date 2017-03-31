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

# Generate the documentation using doxygen.
install(CODE "execute_process(COMMAND doxygen doxygen.conf WORKING_DIRECTORY ${MAINDIR})")
install(DIRECTORY "${MAINDIR}/doc/" DESTINATION "doc")

# Update the node.js package.
set(NODE_DIR "${MAINDIR}/flex/")
install(CODE "execute_process(COMMAND npm install WORKING_DIRECTORY ${NODE_DIR})")
install(DIRECTORY ${NODE_DIR} DESTINATION "flex")

# Install the media folders only if specified.
option(PACKAGE_INCLUDE_MEDIA "If enabled we include the media folders in the package created." OFF)
if(PACKAGE_INCLUDE_MEDIA)
  configure_file("${MAINDIR}/cmake/update_media_folders.cmake.in" "${CMAKE_BINARY_DIR}/update_media_folders.cmake")
  install(SCRIPT "${CMAKE_BINARY_DIR}/update_media_folders.cmake")
  install(DIRECTORY "${MAINDIR}/media/core" "${MAINDIR}/media/additional" DESTINATION "media") # "${MAINDIR}/media/playground"  is left out atm
endif()

set(INSTALL_FILES changelog.md contributing.md readme.md credits.md license.md master.cfg server-init.cfg media/readme.md)
if(OS_WINDOWS)
  set(INSTALL_FILES_STARTUP inexor.bat server.bat) # used as links in the startmenu
elseif(OS_LINUX)
  set(INSTALL_FILES_STARTUP inexor_unix) # used as links in the startmenu
  list(APPEND INSTALL_FILES ${INSTALL_FILES_STARTUP})
endif()

set(INSTALL_FILES_DEV CMakeLists.txt dependencies.py conanfile.py doxygen.conf tool/create_visual_studio_project.bat)
set(INSTALL_FOLDERS_DEV cmake inexor)

install_file_hierarchy("./" ${INSTALL_FILES})
install_file_hierarchy("./" ${INSTALL_FILES_DEV})
install(DIRECTORY ${INSTALL_FOLDERS_DEV} DESTINATION "./")

set(DEPENDENCY_LIST_FILE "dependencies.md" CACHE STRING "If DEPENDENCY_LIST_FILE is specified we will save all dependencies including their licenses to this file.")
if(DEPENDENCY_LIST_FILE)
  include(cmake/get_conan_dependency_list.cmake)
  get_conan_dependency_list(${MAINDIR} 1 1 DEPENDENCY_LIST)
  file(WRITE ${DEPENDENCY_LIST_FILE} "${DEPENDENCY_LIST}")
  message(STATUS "Created DEPENDENCY_LIST_FILE: ${DEPENDENCY_LIST_FILE}")
  install_file_hierarchy("./" ${DEPENDENCY_LIST_FILE})
endif()

if(OS_WINDOWS)
  set(PACKAGE_GENERATORS_DEFAULT 7Z)
else()
  set(PACKAGE_GENERATORS_DEFAULT TGZ)
endif()

set(CPACK_GENERATOR ${PACKAGE_GENERATORS_DEFAULT} CACHE STRING "List of CPack Generators which will be created by the 'PACKAGE' target. Default: 7Z (WIN), TGZ (UNIX)")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${MAINDIR}/readme.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Inexor nightly package")
set(CPACK_RESOURCE_FILE_LICENSE "${MAINDIR}/license.md")
set(CPACK_PACKAGE_EXECUTABLES ${INSTALL_FILES_STARTUP})
set(CPACK_PACKAGE_VERSION_MAJOR "0" CACHE STRING "MAJOR VERSION NUMBER")
set(CPACK_PACKAGE_VERSION_MINOR "9" CACHE STRING "MINOR VERSION NUMBER")
set(CPACK_PACKAGE_VERSION_PATCH "0" CACHE STRING "PATH LEVEL NUMBER")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-alpha" CACHE STRING "Complete version of the created package.")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "Inexor")
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

include(CPack)
