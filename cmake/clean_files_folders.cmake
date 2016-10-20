# This file removes all folders and files specified with the VARS PATHS_TO_REMOVE (taking both files and folders).
# The key point is that it can happen at runtime! (so e.g. always before a build):
# Therefore use the command:
# add_custom_target(<your_command_name_here> COMMAND ${CMAKE_COMMAND} -DPATHS_TO_REMOVE="<your_files_and_folders_here>" -P clean_files_folders.cmake)
# Note: its IMPORTANT that "-DPATHS_TO_REMOVE=" comes before "-P .."!
# PATHS_TO_REMOVE is a string, not a list! (separation by " " not ";")

# Convert the given PATHS_TO_REMOVE to being a list instead of an string
string(REPLACE " " ";" PATHS_LIST ${PATHS_TO_REMOVE})

foreach(cfile ${PATHS_LIST})
message(STATUS "Removing ${cfile}")
  if (EXISTS "${cfile}")
     file(REMOVE_RECURSE ${cfile})
  endif()
endforeach()
