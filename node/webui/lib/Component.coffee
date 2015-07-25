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
    #
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

    # Specialized accessors
    # TODO: modularize this; use mixins; Accessors
    _parse_accessors = (targ, args...) ->
      _.map args, (a) ->
        if _.isArray a
          _parse_accessors targ, a...
        else if _.isString a
          targ[a] = a
        else if _.isObject a
          _.merge targ, a

    # Create a getter that proxies to a scope variable
    # @param a – Any number of arguments: Each one being
    #    either a list of nested elements, the name of
    #    a variable in @$scope to proxy or a hash of
    #    {$component_name -> $scope_name} if you want
    #    a different name in the scope than in the Component
    @scopeGet: (a...) ->
      @scopeGetters ||= {}
      _parse_accessors @scopeGetters, a...
    # Create a setter that proxies to a scope variable
    # @param a – Any number of arguments: Each one being
    #    either a list of nested elements, the name of
    #    a variable in @$scope to proxy or a hash of
    #    {$component_name -> $scope_name} if you want
    #    a different name in the scope than in the Component
    @scopeSet: (a...) ->
      @scopeSetters ||= {}
      _parse_accessors @scopeSetters, a...
    # Create an accessor (getter and setter) that proxies 
    # to a scope variable.
    # @param a – Any number of arguments: Each one being
    #    either a list of nested elements, the name of
    #    a variable in @$scope to proxy or a hash of
    #    {$component_name -> $scope_name} if you want
    #    a different name in the scope than in the Component
    @scopeAcc: (a...) ->
      @scopeGet a...
      @scopeSet a...

    registerAccessors: ->
      clz = @constructor
      _.forIn clz.scopeGetters || {}, (name, attr) =>
        @__defineGetter__ name, => @$scope[attr]
      _.forIn clz.scopeSetters || {}, (name, attr) =>
        @__defineSetter__ name, (v) =>
          @$scope[attr] = v
          @$timeout => @$scope.$apply()


      super()


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

  return Component
