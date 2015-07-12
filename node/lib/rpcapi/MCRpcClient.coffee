MProto = global.InexorMessageProtocol
Uuid = require 'uuid'
_ = require 'lodash'

# JS Abstraction of the ServiceCall message type
#
# ServiceCall encapsulates a function call and contains the
# name of the rpc message called, the call UUID, the call
# type (call/callback) and the payload: Either the argument
# or the return value message
class JSServiceCall
  # Create a Service call
  #
  # @param [string] name – The name of the rpc function to call
  # @param [bytes] payload – The not encode parameter/return
  #   value to send (must support .toBuffer())
  # @param [function] callback – The callback to call as
  #   soon as we get the return value
  # @param [uuid] uuid – The calls UUID. Normally you can
  #   leave this blank; for returning from a function, the
  #   uuid of the initial call must be passed.
  # @param [either "CALL" or "RESPONSE"] type – Whether this
  #   is an initial call or whether we return from a called
  #   function
  constructor: (@name, @payload, @callback,
      @uuid=Uuid(), @type = "CALL") ->

  # Construct a JSServiceCall from an already decoded
  # protobuf message
  @fromProtobuf: (d) ->
    new JSServiceCall \
        d.function_name,
        d.payload,
        null,
        d.call_uuid,
        d.type

  # Construct a JSServiceCall from an encoded protobuf
  # message
  #
  # @param msg_codr – The protobuf Message type of
  #   ServiceCall
  # @param [bytes] – The raw bytes of a service call
  @fromBuffer: (msg_codr, buf) ->
    JSServiceCall.fromProtobuf msg_codr.decode buf

  # Encode this JSServiceCall as a protobuf message
  #
  # @param msg_codr – The protobuf Message type of
  #   ServiceCall
  toProtobuf: (msg_codr) =>
    new msg_codr
      function_name: @name
      call_uuid: @uuid
      type: @type
      payload: @payload.toBuffer()

  # Encode thsis JSServiceCall to bytes
  #
  # @param msg_codr – The protobuf Message type of
  #   ServiceCall
  toBuffer: (msg_codr) =>
    @toProtobuf(msg_codr).toBuffer()

# Pendant of C++ MCRpcServer
#
# This takes lets you call RPC function given their
# unencoded argument message and the function name to call.
class MCRpcClient

  # NOTE: This registers `@con.msg_listener = @rpc_recv` on
  # initialization
  #
  # @param [SocketMessageConnect] con – An already opened
  #   socket to send calls on
  # @param protocol – The protobuf protocol description
  # @param msg_coder – The type of the protobuf ServiceCall
  #   message
  constructor: (@con, @protocol, @msg_coder) ->
    @con.msg_listener = @rpc_recv
    @calls = {}

  # Start an RPC call
  #
  # @param [string] full_name – The full, canonical name of
  #   the rpc function to call
  # @param msg – The protobuf message argument
  # @param cb – The callback to call as soon as the call
  #   returns
  rpc_send: (full_name, msg, cb=->) =>
    call = new JSServiceCall full_name, msg, cb
    @con.send call.toBuffer @msg_coder
    @calls[call.uuid] = call

  # Receive a message.
  #
  # Takes
  rpc_recv: (buf) =>
    call = JSServiceCall.fromBuffer @msg_coder, buf

    msg_type = # Find the msg type and decode the message
      @protocol.reflect.resolve(call.name)
          .resolvedResponseType.clazz
    msg = msg_type.decode call.payload

    cb = @calls[call.uuid].callback # Get & Delete CB
    delete @calls[call.uuid]

    cb msg, call

module.exports = MCRpcClient
module.exports.JSServiceCall = JSServiceCall
