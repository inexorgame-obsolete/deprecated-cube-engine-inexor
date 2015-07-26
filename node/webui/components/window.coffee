# Directive representing a window.
#
# A window normally resides in a window manager under
# WM.windows(); WM is the default manager which is available
# globally.
#
# Opening a window can also be achieved by using the window
# manager. See wm::open.
defineComponent 'window', class extends Component
  ## DIRECTIVE ##

  @restrict: "E"
  @transclude: true

  @inject "uuid"

  ## ACCESSORS ##

  # The title of this window
  @scopeAcc "title"

  # Position accessors: Use to set and receive the location
  # and size of the window
  @acc
    width: (v) ->
      @elem.css "width", "#{v}px" if v
      @elem.width()
    height: (v) ->
      @elem.css "height", "#{v}px" if v
      @elem.height()
    X: (v) ->
      @elem.css "left", "#{v}px" if v
      @elem.position().left
    Y: (v) ->
      @elem.css "top", "#{v}px" if v
      @elem.position().top

  # UI: The Component of the UI in this window.
  @componentAcc ui: ".win-content > *"

  # TODO: Can we use an attr accessor with a sort of filter?
  # Or with a list of states {true => null, false => ""}
  # Whether this window should be decorated.
  # This adds an "not-decorated" attribute to the window tag
  # if decorated == false.
  @get decorated: ->
    not @elem.attr("not-decorated")?
  @set decorated: (v) ->
    @elem.attr "not-decorated", (if v then "" else null)

  ## FUNCTIONS ##

  constructor: ->
    # TODO: Use a better way to process attribute
    # parameters; provide attribute accessors? provide an
    # automatic attribute-sync-to-value service? something
    # like attributes: {"X": "X"} or a tag for accessors
    # "This is an attr argument".
    @_.map ["X", "Y", "width", "height", "title"], (attr) =>
      val = @$attrs[attr.toLowerCase()]
      if val
        @[attr] = val

  # Get the window manager holding this window.
  wm: => Component.componentFor @elem.parents("wm").get(0)

  move: (@x, @y, @width=@width, @heigt=@heigh) =>
  resize: (@width, @height) =>

  # Close this window
  close: => @elem.remove()

  # Put this window to the top of the stack
  toTop: =>
    par = @$ @elem.parent()
    @elem.detach()
    par.append @elem


  ## EVENT MANAGEMENT ##

  # TODO: We should register this on mousedown, but then
  # clicking buttons stops working??
  @on "click", -> @toTop() if @decorated

  # TODO: Set events by function name?
  @on ".win-closebtn", "click", -> @close()

  # TODO: Put into it's own function
  delay = (t, f) -> setTimeout f, t

  @on ".win-resizebtn", "mousedown", (ev0) ->
    # TODO: Provide a better mechanism for
    # registering/deregistering scoped events
    uuid = @uuid()
    w0 = @width
    h0 = @height

    @document.on "mousemove.#{uuid}", (ev1) =>
      @width  = Math.max 0, w0 + (ev1.screenX - ev0.screenX)
      @height = Math.max 0, h0 + (ev1.screenY - ev0.screenY)

    @document.on "mouseup.#{uuid}", =>
      @document.off "mousemove.#{uuid}"
      @document.off "mouseup.#{uuid}"

  @on ".win-topbar", "mousedown", (ev0) ->
    uuid = @uuid()
    x0 = @X
    y0 = @Y

    @document.on "mousemove.#{uuid}", (ev1) =>
      @X = Math.max 0, x0 + (ev1.screenX - ev0.screenX)
      @Y = Math.max 0, y0 + (ev1.screenY - ev0.screenY)

    @document.on "mouseup.#{uuid}", =>
      @document.off "mousemove.#{uuid}"
      @document.off "mouseup.#{uuid}"
