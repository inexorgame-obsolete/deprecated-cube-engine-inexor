def = define? && define || require('amdefine') module
def ["lodash", "underscore.string"], (_, _s) ->
  # Basis class for generic 'extensions' to the coffee script
  # class syntax (e.g. mixins, accessors)
  #
  # At the moment basic accessors/getters/setters are
  # supported, use them by extending Clazz then define your
  # accessors with @get, @set or @acc and call
  # registerAccessors on construction. See below for an
  # example.
  #
  # We also support defining accessor-types that quickly let
  # you define a bunch of getters and setters that all do
  # the same (e.g. log accesses or proxy to another object).
  # In fact, the standard accessors are just an accesor-type
  # with empty name that simply calls the function it was
  # given as an argument.
  # Set the customAccessorType documentation.
  #
  # TODO: Move the meta constructors used by Injectable/Component here
  class Clazz

    # Second-order function for registering families of
    # accessors
    #
    # Generalization of getters where specific types of
    # getters/setters are useful: The Comonent class in
    # webui – that one that encapsulates angular
    # directives – uses this mechanism to provide accessors
    # that access attributes `@attrAcc $field: $dom-attr`,
    # ones that acess jquery elements `@elemAcc $field: $css-selector`
    # and ones that access dom elements as other components
    # `@componentAcc $field: $css-selector`.
    #
    # @param [object] hash – A hash containing accessor
    #   type specifications:
    #   ```
    #   {$name: $accessor}
    #       WHERE $name is a string
    #       WHERE $accessor is
    #           EITHER an object {get: $getter, set: $setter}
    #               WHERE $getter and $setter are functions
    #           OR a function that is $setter AND $getter
    #   ```
    #
    # For each type of accessor `cat`, this will extend the
    # class DSL with the following methods and fields:
    # * @catGet – function that generates cat-type getters
    # * @catSet – function that generates cat-type setters
    # * @catAcc – function that generates cat-type getters and setters
    # * @catGetters – A hash with the defined getters; red
    #   by register accessors
    # * @catSetters – A hash with the defined setters; red
    #   by register accessors
    #
    # The generated accessors originally take one object
    # object as parameter, where each key specifies a field
    # to define a getter for and each value can be used as
    # an extra argument for the accessor-type function.
    #
    # ```
    # accessor_function = (field, param, value) ->
    # @customAccessorType cat: accessor_function
    # @catAcc foo: "bar"
    # ```
    #
    # This would create a property foo on an object `O`;
    # `O.foo` would invoke `accessor_function` with
    # `{"foo", "bar", undefined}`;
    # `O.foo = "xxx"` would invoke it with `{"foo", "bar", "xxx"}`
    #
    # To make calling the accessors a bit easier, we also
    # support strings as arguments:
    # `@catAcc "whiskers"` is equivalent to `@catAcc "whiskers": "whiskers"`
    # And we also support an arbitrary number of strings and
    # hashes and even nested in array; so you could specify:
    # `@catAcc "foo", "bar", ["baz", {my: "thy"}]` and it
    # would still works
    #
    # # Example
    #
    # You could register a special type of accessor that
    # creates accessors that proxies to another object.
    #
    # Code:
    # ```
    # class Meta extends Clazz
    #   shadow_values:
    #   @customAccessorType shade:
    #       get: (field, shadow) ->
    #         v = shadow_values[shadow]
    #         console.log "GET: #{field} (#{shadow}) `#{v}`"a
    #         v
    #       set: (field, shadow, val) ->
    #         console.log "SET: #{field} (#{shadow}) `#{shadow_values[shadow]}` = val"
    #         shadow_values[shadow] = val
    #
    #       @shadeGet "foo", "bar",
    #         bang: "cannon"
    #
    # inst = new Meta
    #
    # inst.foo       # => undefined
    # inst.foo = 22  # => 22
    # inst.foo       #=> 22
    # inst.shadow_values.foo # => 22
    #
    # inst.bang      # => undefined
    # inst.bang = 42 # => 42
    # inst.bang      # => 42
    # inst.shadow_values.bang # => undefined
    # inst.shadow_values.cannon # => 42
    # ```
    #
    # Output:
    # ```
    # GET: foo (foo) `undefined`
    # SET: foo (foo) `undefined` = 22
    # GET: foo (foo) `22`
    # GET: bang (cannon) `undefined`
    # SET: bang (cannon) `undefined` = 42
    # GET: bang (cannon) `42`
    # ```
    #
    @customAccessorType: (hash) ->
      _.forIn hash, (v, name) =>
        # Parse args
        if _.isFunction v
          get = set = v
        else
          {get, set} = v

        # Register the specific meta getter/setter
        (@accessorTypes ||= {})[name] = [get, set]

        # Parse the arguments for setters/getters
        #
        # The argument list is variadic, we parse it by the
        # following rules:
        #
        # * If the argument is a list, parse each element of
        #   the list as arguments
        # * If the argument is a hash, copy that hash into
        #   the target
        # * If the argument is a string `S`, transform into
        #   `{S: S}` and copy into the target
        #
        # @param targ The target hash we finally store the
        #   parsed getter/setter specifications in
        # @param args The arguments passed to the
        #   getter/setter
        parse_accessors = (targ, args) ->
          _.map args, (a) ->
            if _.isArray a
              _parse_accessors targ, a...
            else if _.isString a
              targ[a] = a
            else if _.isObject a
              _.merge targ, a

        # Register the new DSL; fooGet fooSet fooAcc
        cm = (s) -> _s.camelize _s.trim s
        getF = cm "#{name} get"
        getO = cm "#{name} getters"
        setF = cm "#{name} set"
        setO = cm "#{name} setters"
        accF = cm "#{name} acc"
        @[getF] = (a...) -> parse_accessors (@[getO] ||= {}), a
        @[setF] = (a...) -> parse_accessors (@[setO] ||= {}), a
        @[accF] = (a...) ->
          @[getF] a...
          @[setF] a...

    # Most basic accessor type;
    #
    # Registers a plain getter/setter with a name and
    # a custom function. The function is called to set/get
    # the value.
    #
    # ```
    # @get $prop: () -> ...
    # @set $prop: (val) -> ...
    # @acc $prop: (val) -> ...
    # ```
    #
    # # Example
    #
    # ```
    # class Myclass extends Clazz
    #   foo_ = 0
    #   @get foo: -> foo_++
    #   @set foo: (v) -> foo_ = v*2
    #
    #   bang_ = ""
    #   @acc bang: (v) ->
    #     bang_ = v.toString() if v
    #     bang_ + "-crazy"
    #
    #   constructor: ->
    #     @registerAccessors()
    #
    # x = new Myclass
    #
    # x.foo # => 0
    # x.foo # => 1
    # x.foo = 23
    # x.foo # => 23
    # x.foo # => 24
    #
    # x.bang # => "-cracy"
    # x.bang = 22
    # x.bang # => "22-crazy"
    #
    # ```
    @customAccessorType "": (name, f, val) ->
      f.call @, val

    # Register all the accessors defined for this class with
    # the instance
    #
    # The call to this function is necessary: Ordinarily you
    # would expect we just use the constructor. Unfortunately
    # though we need access to the THIS value of the
    # subclass-instance and the subclass constructor/class
    # variable itself (which we can get from the
    # subclass-instance).
    #
    # This function get's the correct values when it's called
    # from the subclass constructor. Our own constructor
    # however only gets our own this with our own class
    # variable.
    registerAccessors: ->
      clz = @constructor
      cm = _s.camelize

      _.forIn clz.accessorTypes, ([fget, fset], name) =>
        _.forIn clz[cm "#{name} getters"] || {}, (para, field) =>
          @__defineGetter__ field, => fget.call @, field, para

        _.forIn clz[cm "#{name} setters"] || {}, (para, field) =>
          @__defineSetter__ field, (val) => fset.call @, field, para, val
