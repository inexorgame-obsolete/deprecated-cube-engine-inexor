InexorService = require 'inexor/InexorService'

# High Level interface for communicating with Inexor
#
# The module always exposes the singleton value
class Inexor
  # The singleton value;
  #
  # @see @getSingleton
  # @return [Inexor]
  @singleton_value: null

  # Get or create the singleton instance
  #
  # This is what the module exposes
  #
  # @return [Inexor] The singleton value
  @getSingleton: ->
    Inexor.singleton_value ||= new Inexor

  # The underlying InexorService
  #
  # @return [InexorService]
  service: null

  # The messages; taken from @service.messages
  #
  # TODO: Type?
  messages: null
  
  # Create one
  #
  # @param [InexorService] @service The underlying service
  constructor: (@service = new InexorService) ->
    @messages = @service.messages

  # Evaluate some cubescript in inexor
  #
  # @param [string] code The code to evaluate
  # @return [Int/Float/String/Null] The return value of the
  #   cubescript executed
  eval: (code, cb=->) ->
    msg = new @messages.Cubescript code: code
    @service.EvalCubescript msg, (a...) ->
      m = a[0]

      cb(m) if m instanceof Error

      data = m.s || m.i || m.f
      cb data, a...

module.exports = Inexor.getSingleton()
