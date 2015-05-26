# Optionally load requirejs modules
#
# This is a wrapper around requirejs that does not throw
# errors when a module can not be found, but rather returns
# null in this case.
#
# TODO: Suppress HTTP error messages on the console when
#       a module is not found
def = define? && define || require('amdefine')(module)
def ["async"], (async) -> (mods, cb) ->
  if (typeof mods) == 'string'
    return try require mod

  f = (m, cb_) ->
    try
      suc = (i) -> cb_ null, i
      err = -> cb_ null, null
      require [m], suc, err
    catch er
      cb_ null, null
  async.map mods, f, (err, insts) -> cb insts...
