Express = require 'express'
Modmap = require 'modmap'
Assets = require 'connect-assets'
ServeStatic = require 'serve-static'
Browzerify = require 'browzerify'
_ = require 'lodash'
AssetManager = require 'asset-manager'

module.exports = ->
  App = new Express

  # Mount all the asset paths
  for path, dir of Modmap.web_assets
    App.use Assets _.merge {}, Modmap.connect_assets_cfg,
      paths: dir
      servePath: path
    App.use path, ServeStatic dir

  App.get '/require/:module', Browzerify.request_handler

  App.get '/list-assets', (req, res) ->
    res.json AssetManager.list()

  App
