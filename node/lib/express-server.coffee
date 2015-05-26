RJs = require 'requirejs'
Modmap = require 'modmap'
Express = require 'express'
Assets = require 'connect-assets'
ServeStatic = require 'serve-static'
Browzerify = require 'browzerify'
_ = require 'lodash'

# Configure requirejs for node #############################


RJs.config Modmap.amd_node_cfg


# Export/compile our assets ################################

module.exports = App = new Express

assetsv = []

# Mount all the asset paths
for path, dir of Modmap.web_assets
  a = Assets _.merge {}, Modmap.connect_assets_cfg,
    paths: dir
    servePath: path
  assetsv.push a
  App.use a
  App.use path, ServeStatic dir


# Load node_modules in the browser #########################

App.get '/require/:module', Browzerify.request_handler assetsv
