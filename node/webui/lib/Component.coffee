# TODO: Simplify this code
define [
    "Injectable",
    "lodash",
    "underscore.string",
    "jquery",
    "AssetManager"
], (Injectable, _, _s, $, AssetManager) ->
  # Component - Object oriented directive definition
  #
  # This is based on Injectable.
  #
  # # Features
  #
  # * Declare directives as classes
  # * Declare directive configuration as class variables
  # * Event declaration during class definition with @on
  # * Automatic template loading
  # * Automatically provides jQuery (@$), the jquery element (@elem),
  #   the element attributes (@$attrs) the transclude
  #   function (@$transclude), the document as a jquery
  #   variable (@document) and the scope (@$scope)
  # * Dependeny injection with @inject
  # * Accessors for scope variables so we can access
  #   variables in the scope as variables in the Component
  #
  # # Default values
  #
  # This changes the default values for directives:
  #
  # * templateUrl - is automatically resolved so a template
  #   with the same name as the component is used.
  # * scope: {}
  # * bindToController: true
  # * controller – Is automatically set so the entire class
  #   acts as acontroller
  #
  # # Usage
  #
  # Declare a class that extends Component; wrap it using
  # Component.wrap $name, ...
  #
  # See Injectable on why the wrapper is necessary.
  #
  # Note that Component should be available globally and
  # Component.wrap should be available as
  # defineComponent.
  #
  # # Example
  #
  # `components/inxFnord.coffee`
  # ```
  #   defineComponent 'inxFnord', class extends Component
  #     @inject "underscore"
  #
  #     @scope:
  #       sex: "=doMe"
  #
  #     constructor: ->
  #       console.log "Element: ", @elem
  #       console.log "sex", @$attrs.sex
  #
  #     @on "click", (event) ->
  #       console.log "I have been clicked"
  # ```
  #
  # `components/inxFnord.html.jade`
  # ```
  #   h1 This is 23 template
  #
  #   p It will be automagically loaded as the themplate of inxFnord.
  # ```
  #
  class Component extends Injectable
    # TODO: Use jQuery rather than jQlite for $element
    @inject "$transclude", "$element", "$scope", "$attrs", "$timeout"
    @inject
      $: "jquery"
      _: "lodash"

    # Register an event on the element; this automatically
    # creates a onEvent function in the class.
    #
    # @param target [String] OPTIONAL! The css selector of
    # the subelement to regsiter the event on
    # @param event [String] The name of the event
    # @param f [Function] The function to call
    @on: (args...) ->
      @req_queue ||= []
      switch args.length
        when 2 then [event, f] = args
        when 3 then [targ, event, f] = args
        else        throw new Error "Expected two or three args"
      @req_queue.push [targ, event, f]

    # Registers @scopeGet, @scopeSet and @scopeAcc that
    # proxy to fields in @$scope
    @customAccessorType scope:
      get: (name, alias)      ->
        @$scope[alias]
      set: (name, alias, val) ->
        @$scope[alias] = val
        # TODO: For some reason, this is necessary to
        # apply the scope. WHY?!?!
        @$timeout ->

    # Generate accessors for element attributes
    @customAccessorType attr:
      get: (field, attr) -> @elem.attr attr
      set: (field, attr, v) -> @elem.attr attr, v

    # Generate accessors for boolean-type element attributes
    # (they are either set or unset)
    @customAccessorType boolAttr:
      get: (field, attr) ->
        !! @elem.attr(attr)
      set: (field, attr, val) ->
        @elem.attr attr, (if val then "" else null)

    # Generate accessors for dom elements
    @customAccessorType dom: (field, selector, v) ->
      targ = @elem.find selector
      targ.replaceWith v if v
      targ

    # Generate accessors for sub components
    @customAccessorType component: (field, selector, v) ->
      targ = Component.componentFor @elem.find selector
      targ.elem.replaceWith v.elem if v
      targ

  # The wrapper must be called on the class that extends
  # Component. (see the class doc for examples)
  #
  # It does everything Injectable.wrap does, but also
  # handles event registration, resolves the template and
  # controller, and calls .directive() to register the
  # directive.
  #
  # TODO: Get rid of the wrapper
  # TODO: Can we maybe define the wrapper constructor in
  # some sort of queue/array with special accessors
  #
  # @param name [String] The name of the directive
  # @param clz  [Class] The directive class
  # @param cb   [Function] an optional callback that is
  #        called after directive() and is passed the
  #        wrapper class.
  Component.wrap = (name, clz, cb=->) ->
    # We register a wrapper between the Injectable wrapper
    # and the class; the hierarchy looks something like:
    #
    # (From top to bottom)
    # Injectable's wrapper -> this wrapper -> clz -> Component -> Injectable
    class __constructor_wrapper extends clz
      constructor: (a...) ->
        # Make sure we're using full jQuery (not jqlite)
        @elem = @$ @$element

        @document = @$ document

        # Register this object in the scope so we can
        # retrieve it with componentFor
        @$scope.js_component = @

        # Autoload the CSS
        cssf = "#{@constructor.component_prefix}.css"
        if cssf in AssetManager.list()
          @$("head").append @$("<link/>").attr
            href: cssf
            rel: "stylesheet"

        # Register all events
        _.map @constructor.req_queue, ([targ, ev, f]) =>
          fname = _s.camelize "on_#{targ || ""}_#{ev}"
          targ = if targ then @elem.find targ else @elem
          @[fname] = f
          targ.on ev, (a...) => @[fname] a...

        super a...

    #  This is where define is called
    Injectable.wrap __constructor_wrapper, (Nu) ->
      # We can not just register Nu as controller, because
      # angular does not call new
      ctrl_factory = (a...) ->
        new Nu a...
      # ctrl_factory is passed as controller; what is passed
      # as controller needs the $inject property for angular
      # di to work
      ctrl_factory.$inject = Nu.$inject

      Nu.component_prefix = Nu.amd_module.uri.replace /\.js$/, ""
      Nu.scope ||= {}
      Nu.bindToController ||= true
      Nu.controllerAs ||= "C"
      Nu.controller ||= ctrl_factory

      htmlf = "#{Nu.component_prefix}.html"
      if htmlf in AssetManager.list()
        Nu.templateUrl ||= htmlf

      Nu.angular_module.directive name, ->
        # This is the actual directive factory; angular
        # won't act correctly if the result of this is
        # a function, so we copy all the class attributes
        # into a new object
        _.merge {}, Nu

      cb Nu

  # Retrieve the angular scope for a DOM element, if there
  # is a scope
  #
  # @param elem – A single dom element. Can be a Plain DOM,
  #   or a jquery element
  Component.isolateScopeFor = (elem) ->
    plainv = $(elem).get()

    if plainv.length != 1
      throw new Error "Component.scopeFor takes a single " +
          "dom element; #{elem} given instead"

    angular.element(plainv[0]).isolateScope()

  # Retrieve the Component for a DOM element.
  Component.componentFor = (elem) ->
    Component.isolateScopeFor(elem)?.js_component

  return Component
