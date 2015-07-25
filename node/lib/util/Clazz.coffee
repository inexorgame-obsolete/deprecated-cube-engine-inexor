# Basis class for generic 'extensions' to the coffee script
# class syntax (e.g. mixins, accessors)
#
# At the moment basic accessors/getters/setters are
# supported, use them by extending Clazz then define your
# accessors with @get, @set or @acc and call
# registerAccessors on construction:
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
# x.foo # 0
# x.foo # 1
# x.foo = 23
# x.foo # 23
# x.foo # 24
#
# x.bang # "-cracy"
# x.bang = 22
# x.bang "22-crazy"
#
# ```
#
# TODO: Move the meta constructors used by Injectable/Component here
class Clazz
  # Create getters
  # The getter should return the desired value for the variable.
  # @param [Object] hash – An object with {name => getter pairs}
  @get: (hash) ->
    @getters ||= {}
    @getters[k] = v for k,v of hash

  # Create setters
  # The setter is passed the variable to be assigned.
  # @param [Object] hash – An object with {name => setter pairs}
  @set: (hash) ->
    @setters ||= {}
    @setters[k] = v for k,v of hash

  # Create both getters and setters from the same function
  # This just like calling @get and @set with the same
  # value.
  # If used as a setter, the first (value) variable will be
  # set. Otherwise it will be undefined.
  # @param [Object] hash – An object with {name => accessor pairs}
  @acc: (hash) ->
    @get hash
    @set hash

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
    @__defineGetter__ k, v for k,v of clz.getters || {}
    @__defineSetter__ k, v for k,v of clz.setters || {}

def = define? && define || require('amdefine') module
def -> Clazz
