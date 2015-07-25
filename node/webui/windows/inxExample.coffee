defineComponent 'inxExample', class extends Component
  @scope:
    say: '='

  constructor: ->
    console.log "Template URL", @constructor.templateUrl
    console.log "Template", @constructor.template
    console.log "ATTRS", @$attrs
    console.log "SAYING", @$attrs.say
    console.log "SAYING (class scope)", @say
    console.log "GOT JQUERY", @$
    console.log "GOT UNDERSCORE: ", @_
    console.log "GOT THE ELEMENT: ", @elem.html()
    console.log "GOT INSTANCE: ", @
    console.log "GOT CLASS: ", @constructor

  @on "click", (ev) -> console.log "CLICK: ", ev

  @on "#open-another", "click", ->
    WM.open "inx-example"

