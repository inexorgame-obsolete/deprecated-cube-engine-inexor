# This file removes all folders and files specified with the VARS PATHS_TO_REMOVE (taking both files and folders).
# The key point is that it can happen at runtime! (so e.g. always before a build):
# Therefore use the command:
# add_custom_target(<your_command_name_here> COMMAND ${CMAKE_COMMAND} -P clean_files_folders.cmake -DPATHS_TO_REMOVE=<your_files_and_folders_here>)

foreach(file ${PATHS_TO_REMOVE})
  if (EXISTS ${file})
     file(REMOVE_RECURSE ${file})
  endif()
endforeach(file)
