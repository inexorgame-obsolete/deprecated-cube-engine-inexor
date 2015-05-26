# (Node only requires)
Browserify = try require?("browserify")
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

class ModmapBrowser
  amd_browser_cfg:
    baseUrl: "/require/"
    paths:
      app: "/lib/angular-app"

class Modmap extends (is_node && ModmapNode || ModmapBrowser)

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
