RJs = require 'requirejs'
Modmap = require 'modmap'
Express = require 'express'
Assets = require 'connect-assets'
ServeStatic = require 'serve-static'
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


App.get '/require/:module', (req, res) ->
  mod = req.params.module.replace /\.js$/, ""
  str = Modmap.Broz.require mod, assetsv

  res.contentType "application/javascript"

  if (typeof str) == "string"
    res.send(str)
    return

  # TODO: Does express have native stream handling?
  str.on 'error', (err) ->
    return if res.finished
    res.contentType "text/plain"
    res.status(404).send """
      Error 404: Could not bundle  "#{mod}"!

      #{err.stack}
    """

  str.on 'data', (chunk) -> res.write chunk
  str.on 'end', -> res.end()
