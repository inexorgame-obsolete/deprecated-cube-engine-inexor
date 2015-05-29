delay = (t,f) -> setTimeout f,t

# We need to have some sort of requirejs config since we
# need to load the base config from another module
requirejs.config
  baseUrl: "/lib/"
  paths:
      # Courtesy to  the AssetManager; it requires these,
      # but the asset manager will only later be able to
      # tell us where they are
      async: "/require/async"
      lodash: "/require/lodash"
      jquery: "/require/jquery"

# Load base config; including static module paths
require ["modmap", "asset-manager"], (Modmap, AssetManager) ->

  AssetManager.listNodeModules (err, mods) ->
    throw err if err

    # Statically configure what node-modules we have
    Modmap.amd_browser_cfg.paths ||= {}
    for m in mods
      Modmap.amd_browser_cfg.paths[m] ||= "/require/#{m}"

    requirejs.config Modmap.amd_browser_cfg

    require ["angular", "InxComponent"], (Angular, InxComponent) ->
      window.InxComponent = InxComponent
      window.defineInxComponent = InxComponent.wrap

      # Load all our actual components
      require ["/components/inxExample"], ->
        # TODO: The delay is shitty; we need this because
        # InxComponent returns before the component is added,
        # but do something better
        delay 1000, ->
          console.log "BOOT"
          Angular.bootstrap document, ["inexor_web_app"]
