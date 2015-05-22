Express = require 'express'
Assets = require "connect-assets"
ServeStatic = require 'serve-static'
RequireJS = require 'requirejs'
Browserify = require 'browserify'
Fs = require 'fs'

assets = Assets
  paths: "../web"
  servePath: "/"
  precompile: []
  build: false
  compile: true
  compress: false
  fingerprinting: false

App = new Express
App.use ServeStatic "../web"
App.use assets


RequireJS.config
  nodeRequire: require

class Broz
  @node_module: (mod) ->
    b = new Browserify
      fullPaths: true
      bundleExternal: false
      standalone: mod
    b.require mod
    b.bundle()

  @lib: (mod) ->
    assets.environment.findAsset("lib/#{mod}.js")?.__source__

  rnode = (mod) -> -> Broz.node_module mod
  rfile = (file) -> -> Fs.createReadStream file
  @Modmap:
    requirejs: rfile "node_modules/requirejs-browser/require.js"
    angularAMD: rfile "node_modules/angularAMD/dist/angularAMD.js"

  @require: (what) ->
    @Modmap[what]?() || @lib(what) || @node_module what

# Used by requirejs to load node.js modules
#
# see Broz; this is a wrapper around it.
App.get '/require/:module', (req, res) ->
  mod = req.params.module.replace /\.js$/, ""
  str = Broz.require mod

  res.contentType "application/javascript"

  if (typeof str) == "string"
    res.send(str)
    return

  str.on 'error', (err) ->
    return if res.finished
    res.contentType "text/plain"
    res.status(404).send """
      Error 404: Could not bundle  "#{mod}"!

      #{err.stack}
    """

  str.on 'data', (chunk) -> res.write chunk
  str.on 'end', -> res.end()

App.listen 8000, "localhost"
