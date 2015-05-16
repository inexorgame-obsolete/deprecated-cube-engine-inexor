Express = require 'express'
Assets = require "connect-assets"
ServeStatic = require 'serve-static'
RequireJS = require 'requirejs'
Browserify = require 'browserify'
Fs = require 'fs'

App = new Express

App.use ServeStatic "../web"
App.use Assets
  paths: "../web"
  servePath: "/"
  precompile: []
  build: false
  compile: true
  compress: false
  fingerprinting: false

RequireJS.config
  nodeRequire: require

App.get '/node/:module', (req, res) ->
  mod = req.params.module.replace /\.js$/, ""
  if mod == 'requirejs'
    # Requirejs is a special case; for this lib we just cat
    # the script
    str = Fs.createReadStream \
      "node_modules/requirejs-browser/require.js"
  else
    b = new Browserify
      fullPaths: true
      bundleExternal: false
      standalone: mod
    b.require mod

    str = b.bundle()

  str.on 'error', (err) ->
    return if res.finished
    res.status(404).send """
      Error 404: Could not bundle  "#{mod}"!
      
      #{err.stack}
    """

  res.contentType "application/javascript"
  str.on 'data', (chunk) -> res.write chunk
  str.on 'end', -> res.end()

App.listen 8000, "localhost"
