# Window Manager
#
# By default there is always a window manager, it can be
# accessed though the global variable `WM` which is set by
# /main.coffee
defineComponent 'wm', class extends Component
  @restrict: "E"
  @transclude: true

  @inject "$compile"

  delay = (t, f) -> setTimeout f, t

  # Open a new window
  #
  # TODO: We should have an interface more like new Window(args, new InxExample(args), WM=wm)
  #
  # @params [string] ui – The name of the directive to
  # display inside the window.
  # @params [object] window_params – The properties to set
  # on the window
  # @params [object] ui_params – The properties to set on
  # the directive inside the window
  open: (ui, window_params={}, ui_params={}) =>
    el = @$compile("<window><#{ui}></#{ui}></window>")(@$scope)

    @elem.prepend el
    # TODO: Get rid of the delay
    delay 30, =>
      window = Component.componentFor el
      window.title ||= ui
      @_.merge window, window_params
      @_.merge window.ui, ui_params

    return window

  # Get the list of windows in this WM
  # TODO: Should this be an accessor
  windows: =>
    @_.map @elem.find("> window"), Component.componentFor
