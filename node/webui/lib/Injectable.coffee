define [
  "lodash",
  "util/requireOptional"
], (_, req_opt) ->

  # Curved Injectable - Basic tools to declare angular staff
  # in coffee script classes. And support for AMD.
  #
  # # Features
  #
  # * Framework for declaring controllers/directives/… in classes
  # * Injection of angular and requirejs modules with @inject
  # * Declaring the angular module this is in by name
  #
  # # Usage
  #
  # This is not to be used directly, rather it should be
  # used as means to wrap angular declaration functions like
  # .controller, .factory or .directive.
  #
  # In order to use Injectable, a class must be declared
  # that extends Injectable. The resulting class must then
  # be passed to Injectable.wrap, which calls requirejs'
  # define() and wraps the constructor to provide automatic
  # dependency injection.
  # Injectable.wrap also takes a callback; this callback
  # is given the resulting class and should be used to
  # actually call .controller or another of those functions.
  #
  # # Example
  #
  # See Component for a complex wrapper around .directive
  #
  # This quickly illustrates how a very simple wrapper
  # around .controller() could be created.
  #
  # `BaseController.coffee`
  # ```
  #   define ["Injectable"], (Injectable) ->
  #     class BaseController extends Injectable
  #       # Will provide @$scope and @underscore while the
  #       # object is alive
  #       @inject "$scope", "underscore"
  #
  #     # We need to use our own wrapper
  #     BaseController.wrap (name, clz) ->
  #       # define is called here
  #       Injectable.wrap clz, (new_clz) ->
  #
  #         # new_clz needs to be instantiated with new
  #         factory = (a...) -> new new_clz a...
  #         # The factory needs to have a the $inject
  #         # property for dependency injection to work
  #         factory.$inject = new_clz
  #
  #         new_clz.angular_module.controller name, factory
  #
  #     # Usually we should never move something into the
  #     # global namespace; except the main dependency
  #     # resolving mechanism; BaseController is our primary
  #     # dependency resolver in this case
  #     window.BaseController = BaseController
  #     window.defineBaseController = BaseController.wrap
  #
  #     return BaseController
  # ```
  #
  # `MyController.coffee`
  # ```
  #   defineBaseController 'MyController', class extends BaseController
  #     @inject "uuid", ["underscore"]
  #
  #     # The module this controller will be added to
  #     # Must be a string; it must be possible to require
  #     # 'my_application' with requirejs
  #     @mod "my_application"
  #
  #     constructor: ->
  #       @$scope.boat = "Titanic"
  # ```
  #
  class Injectable
    # A list of the dependencies added with @inject
    @dependencies: []

    # If a dependency has an alias, it's name
    @dependency_aliases: {}

    # Add a dependency to be provided by angular or requirejs
    #
    # Dependencies requested this way are accessible as
    # fields. `@inject 'foo'` -> `@foo`
    #
    # This takes strings, lists of strings and objects to
    # specify aliases:
    #
    # ```
    #   # Will be available as @async
    #   @inject "asyn"
    #
    #   # Will be available as @$ and @_
    #   @inject
    #     _: "underscore"
    #     $: "jQuery"
    # ```
    @inject: (args...) ->
      for x in args
        if (typeof x) == 'string'
          @dependencies.push x
        else if x instanceof Array
          @inject x...
        else if x instanceof Object
          _.merge @dependency_aliases, _.invert x
          @inject (_.values x)...
        else
          throw Error "Invalid argument #{x}"

    # Insert a dependency
    #
    # Should be called during instantiation by Injectable
    # only
    #
    # First resolves whether the dependency has an alias and
    # then sets the instance variable with the alias or the
    # name.
    #
    # @param name_ The name of the depnendency
    # @param mod   The actual module
    insert_dependency: (name_, mod) =>
      name = @clz.dependency_aliases[name_] || name_
      @[name] = mod

    # Set the angular module this is supposed to be added
    # to.
    # The argument must be the name of an amd-loadable
    # module.
    # Defaults to app.
    @mod: (mod) ->
      @angular_module_name = mod

    @mod "app"
    @inject []

    # The angular module instance this is supposed to be
    # added to. This is resolved by the wrapper from the
    # value set by @mod()
    @angular_module: null
    # The amd module; The wrapper is calling define(["module"])
    # automatically; this will contain information like the
    # file the wrapper is called in.
    @amd_module: null

    # A map {$name: $value} of resolved AMD dependencies.
    # This is filled by the wrapper.
    @amd_loaded: null

    # The usual angular $inject property. Dependencies that
    # could not be resolved by amd and that are now to be
    # resolved by the angular dependency injector on class
    # instantiation.
    # List of names; set by the wrapper.
    @$inject: null
  
  # The wrapper must be called on the class that extends
  # Injectable. (see the class doc for examples)
  #
  # * It calls define to make the whole class an AMD module
  # * It resolves AMD dependencies added with @inject
  # * It wraps the constructor so that angular dependencies
  #   are automatically added as fields.
  #
  # TODO: Get rid of Injectable.wrap
  #
  # @param clz [Class] The class this wraps
  # @param deps [Array<String>] Any number of AMD dependencies.
  #        Those are passed to the callback
  # @param cb - [Function] The callback. This is passed
  #        another class created by the wrapper and any deps
  #        resolved
  Injectable.wrap = (clz, deps..., cb) ->
    define [clz.angular_module_name, deps..., "module"], \
            (angular_module, resolved_deps..., amd_module) ->

      # We first try to load the @dependencies with AMD;
      # any dependencies that could not be loaded are then
      # injected as angular dependencies
      # This is a bit problematic because the amd_loader
      # should have a lower priority than the angular injector.
      #
      # TODO: Extend the angular injector to natively load
      #       amd modules as fallback. (amd is async;
      #       angular is sync - we need to bridge that).
      #       use https://oclazyload.readme.io/ ?
      req_opt clz.dependencies, (amd_injects...) ->

        # [[$dependency_name, $amd_resolved]]
        req_zip = _.chain(clz.dependencies).zip amd_injects
        class Wrapper extends clz
          # disable, otherwise this will be Injectable.wrap
          @wrap = null

          @angular_module: angular_module
          @amd_module: amd_module

          @amd_loaded =  req_zip
              .filter ([name, mod]) -> mod != null
              .object()
              .value()

          @$inject = req_zip
              .filter ([name, mod]) -> mod == null
              .map ([name]) -> name
              .value()

          constructor: (args...) ->
            @clz = Wrapper

            # Insert all the modules loaded by AMD
            for name, mod of @clz.amd_loaded
              @insert_dependency name, mod

            # Handle all the injected arguments by storing
            # them with the correct name ass a class
            # variable
            for dep,i in @clz.$inject
              @insert_dependency dep, args[i]

            # Call the class constructor, removing all the
            # injected arguments
            new_args = _.slice args, (@clz.$inject.length)
            super new_args...

        # end: class Wrapper
        cb Wrapper, resolved_deps

  # end Injectable.wrap
  return Injectable
