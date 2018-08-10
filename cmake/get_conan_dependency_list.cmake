# This function executes conan to get a list of all dependencies ("conan info" but stripped).
# conanfile_py_folder is the path to the folder the conanfile.py lies in.
# if STRIP_CHANNELS is true the output in the form of boost/1.66.0@conan/stable becomes boost/1.66.0
# if SHOW_LICENSE is true it will also display license info.
function(get_conan_dependency_list CONANFILE_PY_FOLDER SHOW_LICENSE STRIP_CHANNELS OUTPUT_VAR)

  message(STATUS "executing conan info")
  if(SHOW_LICENSE)
    execute_process(COMMAND conan info . --only=license OUTPUT_VARIABLE TEMP_OUTPUT_VAR WORKING_DIRECTORY ${CONANFILE_PY_FOLDER})
  else()
    execute_process(COMMAND conan info . --only=stringwhichclearlywillnevermatch OUTPUT_VARIABLE TEMP_OUTPUT_VAR WORKING_DIRECTORY ${CONANFILE_PY_FOLDER})
  endif()

  # Strip any log appearing before the actual list (probably coming form the configure() commands):
  string(REGEX REPLACE "(.*)PROJECT" "Inexor" TEMP_OUTPUT_VAR ${TEMP_OUTPUT_VAR})

  if(STRIP_CHANNELS)
    string(REGEX REPLACE "@([a-zA-Z_]+)/([a-zA-Z_]+)" "" TEMP_OUTPUT_VAR ${TEMP_OUTPUT_VAR})
  endif()
  set(${OUTPUT_VAR} "${TEMP_OUTPUT_VAR}" PARENT_SCOPE)
endfunction()
