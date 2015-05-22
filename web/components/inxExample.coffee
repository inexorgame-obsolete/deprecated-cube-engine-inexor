defineInxComponent 'inxExample', class extends InxComponent
  @inject "_"
  @scope:
    say: '='

  constructor: ->
    console.log "Template URL", @clz.templateUrl
    console.log "Template", @clz.template
    console.log "ATTRS", @attrs
    console.log "SAYING", @attrs.say
    console.log "SAYING (class scope)", @say
    console.log "GOT JQUERY", @$
    console.log "GOT UNDERSCORE: ", @_
    console.log "GOT THE ELEMENT: ", @elem.html()
    console.log "GOT INSTANCE: ", @
    console.log "GOT CLASS: ", @clz

    @elem.css
      width: 200
      height: 200
      background: "yellow"
      display: "block"

  @on "click", (ev) -> console.log "CLICK: ", ev

