Browserify = require "browserify"
Modmap = require "modmap"

# Format modules for use in the browser
#
# This is a tiny wrapper around Browserify; the difference
# is, that this can also serve modules from lib/ (for
# convenience) and this function can be configured to take
# specific actions with the map parameter (by default
# configured in Modmap.browserify_map).
#
# @see Browzerify.request_handler A handler suitable for
#      use with express
#
# @return
#   JS code suitable for the browser, either as string or
#   as readable stream.
#
# @param what [string] The module to browserify
# @param map [Object] This map can be used to configure
#   specific modules; it contains an association of
#   {$module_name: $loader, ....}; where loader is
#   a function that returns JS code suitable for the
#   browser either as readable stream or as string;
#   By default configured in Modmap.browserify_map
module.exports = InstantBrowserify = (what, map=Modmap.browserify_map) ->
  map[what]?() || InstantBrowserify.node_module what

# Browserify a module
InstantBrowserify.node_module = (mod) ->
  b = new Browserify
    fullPaths: true
    bundleExternal: false
    standalone: mod
  b.require mod
  b.bundle()

# Handler for HTTP requests that can be used to browserify
# things;
#
# Takes a :module parameter.
InstantBrowserify.request_handler = (req, res) ->
  mod = req.params.module.replace /\.js$/, ""
  str = InstantBrowserify mod

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
