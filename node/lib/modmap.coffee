# (Node only requires)
Browserify = try require?("browserify")
Fs = try require?("fs")

is_node = GLOBAL?.process?

class Modmap
  # TODO: Config lib_dir and node_dir as root for node require
  if is_node
    @lib_dir = __dirname
    @node_dir = "#{@lib_dir}/.."
    @repo_root = "#{@node_dir}/.."
    @web_dir = "#{@repo_root}/web"

  # AMD Config for use in node.js
  @amd_node_cfg:
    nodeRequire: require

  # AMD Config for use in the browser
  @amd_browser_cfg:
    baseUrl: "/require/"

  # The default config for connect-assets; do not set
  # paths and servePath; see @web_assets
  @connect_assets_cfg:
    precompile: []
    build: false
    compile: true
    compress: false
    fingerprinting: false

  # Asset directories to mount; "http prefix": "dir path"
  # Each of those has their static files and their assets
  # to compile (jade/coffeescript/sass) mounted.
  @web_assets:
    "/":    @web_dir
    "/lib": @lib_dir

  # Browserify node_modules for use in the server
  if is_node
    class @Broz
      @node_module: (mod) ->
        b = new Browserify
          fullPaths: true
          bundleExternal: false
          standalone: mod
        b.require mod
        b.bundle()

      @lib: (mod, assetsv) ->
        for man in assetsv
          i = man.environment.findAsset("#{mod}.js")?.__source__
          return i if i

      rnode = (mod) -> -> Broz.node_module mod
      rfile = (file) -> -> Fs.createReadStream file
      @map:
        requirejs: rfile "node_modules/requirejs-browser/require.js"
        angularAMD: rfile "node_modules/angularAMD/dist/angularAMD.js"

      @require: (what, assetsv) ->
        @map[what]?() || @lib(what, assetsv) || @node_module what

# INITIALIZE REQUIREJS #####################################
# (in the browser only)

modmap = new Modmap
if window?
  requirejs.config modmap.amd_browser_cfg

# EXPORT BOILERPLATE #######################################

if not define? # Amdefine can not deal with the explicit name
  __def = require('amdefine')(module)
  def = (name, deps, f) -> __def deps, f
else
  def = define

def "modmap", [], -> modmap
