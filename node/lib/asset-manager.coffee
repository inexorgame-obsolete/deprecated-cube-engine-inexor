Dir = try require?("node-dir") # node only
Path = try require?("path")

# TODO: We need a good detection lib for this
is_browser = window?

def = define? && define || require('amdefine')(module)
def ["modmap", "async", "lodash", "jquery"], (Modmap, Async, _, $) ->

  class AssetManager
    transformName: (name, map=Modmap.dynamic_assets) =>
      for [re, s] in map when name.match re
        return Array (name.replace re, s), true
      return Array name, false

    # List all assets that are static files;
    # the result is passed to the callback as array
    #
    # TODO: Caching
    listStatic: (cb) =>
      dirs = _.pairs Modmap.web_assets

      itr = ([prefix, dir], cb_) -> # Effectively iterates over dirs
        Dir.files dir, (err, files) ->
          return cb_ err, null if err
          cb_ null, _.map files, (f) ->
            Path.join prefix, (Path.relative dir, f)

            # The paths are all relative to the current
            # directory; make them relative to dir and
            # prepend the prefix

      Async.map dirs, itr, (err, res) ->
        return cb err, null if err
        cb null, _.flatten res

    # List all the dynamically compiled assets
    listDynamic: (cb) =>
      @listStatic (err, assets) =>
        return cb err if err
        cb null, _.compact _.map assets, (a) =>
          [name, changed] = @transformName a
          changed && name

    # List *all* assets; dynamically compiled ones + static
    # ones
    list: (cb) =>
      Async.parallel [@listDynamic, @listStatic], (err, [dyn, stat]) =>
        return cb err if err
        cb null, dyn.concat(stat)

  # TODO: Add decorators for browser/node only
  # TODO: Add decorators that implicitly call server
  #       methods on the client
  # TODO: Add a generic wrapper for doing API calls
  if is_browser
    AssetManager::listStatic = (cb) ->
      req = $.getJSON "/api/0.0.1/asset-manager/listStatic"
      req.success (data) -> cb null, data
      req.fail (err) -> cb err, null

  return new AssetManager
