Dir = try require?("node-dir") # node only
Path = try require?("path")
Fs = try require? "fs"

# TODO: We need a good detection lib for this
is_browser = window?

# If this module requires node_modules, they need to be
# statically defined in main, because this module is
# required for configuring the node modules
def = define? && define || require('amdefine')(module)
def ["modmap", "async", "lodash", "jquery"], (Modmap, Async, _, $) ->

  class AssetManager
    constructor: ->
      # TODO: Cache invalidation
      @list = Async.memoize @list
      @listStatic = Async.memoize @listStatic
      @listDynamic = Async.memoize @listDynamic
      @listNodeModules = Async.memoize @listNodeModules
      @listRequire = Async.memoize @listRequire

    transformName: (name, map=Modmap.dynamic_assets) =>
      for [re, s] in map when name.match re
        return Array (name.replace re, s), true
      return Array name, false

    # List all the node modules that can be loaded via
    # require/, without the require prefix
    #
    # ```
    #   $ listNodeModules console.log
    #   null, ["async", "lodash"]
    # ```
    listNodeModules: (cb) =>
      mod_dir = "#{Modmap.node_dir}/node_modules"

      isModule = (f, cb) ->
        return cb null, false if f.match /^\./
        Fs.stat "#{mod_dir}/#{f}", (err, stat) ->
          throw err if err # *sigh* async does not support errors
          cb stat.isDirectory()

      Fs.readdir mod_dir, (err, fv) ->
        return cb err if err
        Async.filter fv, isModule, (res) -> cb null, res

    # Lists everything that can be loaded via require/ with
    # the require/ prefix:
    #
    # ```
    #   $ listRequire console.log
    #   null, ["/require/async", "/require/lodash"]
    # ```
    listRequire: (cb) =>
      @listNodeModules (err, mods) ->
        return cb err if err
        cb null, _.map mods, (m) -> "/require/#{m}"

    # List all assets that are static files;
    # the result is passed to the callback as array
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
      parts = Array @listDynamic, @listStatic, @listRequire
      Async.parallel parts, (err, res) =>
        return cb err if err
        cb null, _.flatten res

  # TODO: Add decorators for browser/node only
  # TODO: Add decorators that implicitly call server
  #       methods on the client
  # TODO: Add a generic wrapper for doing API calls
  if is_browser
    AssetManager::listStatic = (cb) ->
      req = $.getJSON "/api/0.0.1/asset-manager/listStatic"
      req.success (data) -> cb null, data
      req.fail (err) -> cb err, null

    AssetManager::listNodeModules = (cb) ->
      req = $.getJSON "/api/0.0.1/asset-manager/listNodeModules"
      req.success (data) -> cb null, data
      req.fail (err) -> cb err, null

  return new AssetManager
