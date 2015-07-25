# INITIALIZATION
#
# Any global variables should be set here.
#
# 1. Activate minimal requirejs configuration
# 2. Retrieve the real requirejs configuration from Modmap
# 3. List the available node-modules with the asset manager;
#    inject them statically in the requirejs config
# 4. Load the new configuration into requirejs
# 5. Activate the real requirejs configuration
# 6. Load the Component and inject into the global
#    namespace (it wraps define for the components)
# 7. Load angular modules (window manager)
# 8. List the available components
# 9. require them with requirejs; They will also be added to
#    angular as directives
# 10. (wait a bit to give the components time to really load)
# 11. Initialize angular

# TODO: Put into some util module
delay = (t,f) -> setTimeout f,t

config =
  requirejs:
    baseUrl: "/lib/"
    paths:
      jquery: "/require/jquery"
      "underscore.string": "/require/underscore.string"
  requirejs_pseudopaths: Array "/require"

main = ->
  # Configure amd
  requirejs.config config.requirejs

  do reconfig

reconfig = -> require [
    "AssetManager",
    "underscore.string"
], (AssetManager, _s) ->
  # Inject all static prefixes into the requirejs paths
  # This enables us to simulate multiple roots
  for prefix in config.requirejs_pseudopaths
    for file in AssetManager.list() when _s.startsWith file, prefix
      name = file.replace(prefix, "").replace(/^\//, "")
      config.requirejs.paths[name] = file

  # Reconfigure amd with the new paths
  requirejs.config config.requirejs

  do bootstrap

bootstrap = -> require [
    "angular",
    "Component",
    "async",
    "lodash",
    "app",
    "jquery",
    "AssetManager"
], (Angular, Component, Async, _, app, $, AssetManager) ->

  # Handle focus; Make sure CEF looses focus and Inexor
  # gains it, when we click on the background
  if inexor?
    $("body, html").on "click", -> inexor.releaseFocus()
  else
    console.warn "Not registering focus handlers. Not in inexor?"

  # The components use this as loader
  window.Component = Component
  window.defineComponent = Component.wrap

  # Component files to load
  components = _.filter AssetManager.list(), (f) ->
      f.match /^\/(components|windows)\/.*\.js$/

  # Load all our actual components
  __load = (m, cb) -> require [m], cb
  Async.map components, __load, (loaded) ->
    # TODO: The delay is shitty; we need this for the
    # angular modules and because Component returns
    # before the component is added, but do something
    # better
    delay 300, ->
      Angular.bootstrap document, ["inexor_web_app"]

      # Initialize the window manager
      window.WM = Component.componentFor $ "wm#masterWM"

      WM.open "inx-example"

do main
