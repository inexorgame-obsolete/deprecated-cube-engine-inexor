# (Node only requires)
Fs = try require?("fs")

is_node = GLOBAL?.process?

class ModmapNode
  # TODO: Config lib_dir and node_dir as root for node require
  lib_dir: __dirname? && __dirname
  node_dir: "#{@::lib_dir}/.."
  repo_root: "#{@::node_dir}/.."
  web_dir: "#{@::repo_root}/web"

  amd_node_cfg:
    nodeRequire: require

  # The default config for connect-assets; do not set
  # paths and servePath; see @web_assets
  connect_assets_cfg:
    precompile: []
    build: false
    compile: true
    compress: false
    fingerprinting: false

  # Asset directories to mount; "http prefix": "dir path"
  # Each of those has their static files and their assets
  # to compile (jade/coffeescript/sass) mounted.
  web_assets:
    "/":    @::web_dir
    "/lib": @::lib_dir

  # This map is used when the browser requests that a module
  # be browserified; By default browzerify below will return
  # a node module, but this map can be used to take specific
  # action for a specific module;
  # The map contains module names as keys and functions as
  # values; these function must either return the contents
  # of the module as string or a readable stream.
  rfile = (file) -> -> Fs.createReadStream file
  browserify_map:
    requirejs: rfile "node_modules/requirejs-browser/require.js"
    angularAMD: rfile "node_modules/angularAMD/dist/angularAMD.js"

class ModmapBrowser
  amd_browser_cfg:
    baseUrl: "/require/"
    paths:
      app: "/lib/angular-app"

class Modmap extends (is_node && ModmapNode || ModmapBrowser)
  # A list of assets types that are known; The data structure
  # represents file name conversion schemes:
  # [[$regex, $replacement], ...]
  #
  # TODO: We should infer this from the asset lib somehow
  dynamic_assets: do ->
    r = []
    $ = (k,v) -> r.push [k,v]; r

    $ /\.coffee$/, ".js"
    $ /\.html\.jade$/, ".html"
    $ /\.styl$/, ".css"

# INITIALIZE REQUIREJS #####################################
# (in the browser only)

modmap = new Modmap

# TODO: This goes in main.coffee
if window?
  requirejs.config modmap.amd_browser_cfg

# EXPORT BOILERPLATE #######################################

if not define? # Amdefine can not deal with the explicit name
  __def = require('amdefine')(module)
  def = (name, deps, f) -> __def deps, f
else
  def = define

def "modmap", [], -> modmap
