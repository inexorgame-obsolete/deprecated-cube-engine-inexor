delay = (t,f) -> setTimeout f,t

require ["InxComponent", "angular"], (InxComponent, Angular) ->
  window.InxComponent = InxComponent
  window.defineInxComponent = InxComponent.wrap

  require ["/components/inxExample"], ->
    # TODO: The delay is shitty; we need this because
    # InxComponent returns before the component is added,
    # but do something better
    delay 1000, ->
      console.log "BOOT"
      Angular.bootstrap document, ["inexor_web_app"]
