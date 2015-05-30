defineInxComponent 'inxExample', class extends InxComponent
  @inject
    _: "lodash"
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

    if @attrs.bg
      @elem.css background: @attrs.bg

  @on "click", (ev) -> console.log "CLICK: ", ev

