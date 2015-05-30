Dir = try require?("node-dir") # node only
Path = try require?("path")
Fs = try require? "fs"

# TODO: We need a good detection lib for this
is_browser = window?

# If this module requires node_modules, they need to be
# statically defined in main, because this module is
# required for configuring the node modules
def = define? && define || require('amdefine') module
def ["modmap", "lodash", "jquery"], (Modmap, _, $) ->

  # TODO: Move to a dedicated module
  findSync = (dir) ->
    fv = Fs.readdirSync dir
    _.flatten _.map fv, (f) ->
      path = "#{dir}/#{f}"
      if Fs.statSync(path).isDirectory()
        findSync path
      else
        path

  # The AssetManager provides reflection on the available
  # assets.
  #
  # We can print the entire tree, check which modules are
  # compiled, which ones are static and can list which node
  # modules are available.
  #
  # NOTE: This class is synchronous; it was async in the
  # beginning but that is to terrible to work with;
  # Now that it is sync, stuff complains.
  # The bes way of dealing with this would be to do our
  # async requests is before the amd module is defined, but
  # that does not seem to work on node.
  #
  # TODO: Async? This is slow...
  # TODO: Cache invaldidation
  # TODO: Can we generate this from require/connect-assets/serve-static?
  class AssetManager
    constructor: ->
      @listNodeModules = _.memoize @listNodeModules
      @listRequire = _.memoize @listRequire
      @listStatic = _.memoize @listStatic
      @listDynamic = _.memoize @listDynamic
      @list = _.memoize @list

    # List all the node modules that can be loaded via
    # require/, without the require prefix
    #
    # @return [Array(String)] A list of node module names
    listNodeModules: =>
      mod_dir = "#{Modmap.node_dir}/node_modules"
      fv = Fs.readdirSync mod_dir

      _.filter fv, (f) ->
        return false if f.match /^\./
        Fs.statSync("#{mod_dir}/#{f}").isDirectory()

    # List all static assets
    #
    # @return [Array(String)] a list with all static assets
    listStatic: =>
      _.flatten \
        _.map (_.pairs Modmap.web_assets), ([prefix,dir]) ->
          _.map (findSync dir), (f) ->
            Path.join prefix, (Path.relative dir, f)

    # Get the name an asset could be compiled to
    #
    # ```
    # $ transformName "foo.styl" # ==> "foo.css"
    # ```
    #
    # What kinds of transformations are possible is defined
    # in Modmap.dynamic_assets.
    #
    # @param name [String] The name to get the compiled name for
    # @param map [ Array(Array(Regex|String, String)) ]
    #        A mapping of possible name transformations, see
    #        Modmap.dynamic_assets.
    # @return [Array(String, boolean)] A tuple with the
    #        first element being the transformed name and
    #        the second indicating whether any
    #        transformation actually happened.
    transformName: (name, map=Modmap.dynamic_assets) =>
      for [re, s] in map when name.match re
        return Array (name.replace re, s), true
      return Array name, false

    # Lists everything that can be loaded via require/ with
    # the require/ prefix:
    #
    # @return [Array(String)] list of paths under /require/
    listRequire: =>
      _.map @listNodeModules(), (m) -> "/require/#{m}"

    # List all the dynamically compiled assets
    # @return [Array(String)]
    listDynamic: =>
      _.compact _.map @listStatic(), (a) =>
        [name, changed] = @transformName a
        changed && name

    # List *all* assets; dynamically compiled ones + static
    # ones
    # @return [Array(string)]
    list: =>
      _.flatten [@listDynamic(), @listStatic(), @listRequire()]

  # TODO: Add decorators for browser/node only
  # TODO: Add decorators that implicitly call server
  #       methods on the client
  # TODO: Add a generic wrapper for doing API calls
  if is_browser
    AssetManager::listStatic = (cb) ->
      # TODO: Jquery says 
      req = $.ajax
        async: false
        dataType: "json"
        url: "/api/0.0.1/asset-manager/listStatic"
      JSON.parse req.responseText

    AssetManager::listNodeModules = (cb) ->
      req = $.ajax
        async: false
        dataType: "json"
        url: "/api/0.0.1/asset-manager/listNodeModules"
      JSON.parse req.responseText

  new AssetManager
