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
# 6. Load the InxComponent and inject into the global
#    namespace (it wraps define for the components)
# 7. Load angular modules (window manager)
# 8. List the available components
# 9. require them with requirejs; They will also be added to
#    angular as directives
# 10. (wait a bit to give the components time to really load)
# 11. Initialize angular

# TODO: Put into some util module
delay = (t,f) -> setTimeout f,t

# We need to have some sort of requirejs config since we
# need to load the base config from another module
requirejs.config
  baseUrl: "/lib/"
  paths:
      # Courtesy to  the AssetManager; it requires these,
      # but the asset manager will only later be able to
      # tell us where they are
      lodash: "/require/lodash"
      jquery: "/require/jquery"

# Load base config; including static module paths
# Modmap has the base amd config; AssetManager provides the
# list of node-modules
require ["modmap", "asset-manager"], (Modmap, AssetManager) ->
  assets = AssetManager.list()

  # Inject all the node modules into the amd configuration
  Modmap.amd_browser_cfg.paths ||= {}
  for m in assets when m.match /^\/require\/./
    name = m.replace "/require/", ""
    Modmap.amd_browser_cfg.paths[name] ||= m

  # Load the proper amd config
  requirejs.config Modmap.amd_browser_cfg


  require ["angular", "InxComponent", "async", "lodash", "app", "jquery"], \
          (Angular, InxComponent, Async, _, app, $) ->

    # The components use this as loader
    window.InxComponent = InxComponent
    window.defineInxComponent = InxComponent.wrap

    # Load angular modules (window manager)
    # TODO: Add a generic css/js tag routine
    # TODO: We should load those at a better place, in here
    #       does not scale and it should not be necessary to
    #       require the modules in bootstrap below
    window.Angular = window.angular = Angular
    $("head").append $("<link/>").attr
      href: "/require/css_wmwindow"
      rel: "stylesheet"
    $.getScript "/require/wmwindow"

    # Component files to load
    components = _.filter assets, (f) ->
        f.match /^\/components\/.*\.js$/

    # Load all our actual components
    __load = (m, cb) -> require [m], cb
    Async.map components, __load, (loaded) ->
      # TODO: The delay is shitty; we need this for the
      # angular modules and because InxComponent returns
      # before the component is added, but do something
      # better
      delay 1000, ->
        Angular.bootstrap document, ["inexor_web_app", "ngWindowManager"]
