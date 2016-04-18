# @file this file overrides the find_path() and find_program() global function to remove its findings from the cmake-gui
# Since those paths do not really need to be in the gui, but in the cache.

function(find_path var)
  _find_path(${var} ${ARGN})
  set(${var} ${${var}} CACHE INTERNAL "")
endfunction()

function(find_program var)
  _find_program(${var} ${ARGN})
  set(${var} ${${var}} CACHE INTERNAL "")
endfunction()
