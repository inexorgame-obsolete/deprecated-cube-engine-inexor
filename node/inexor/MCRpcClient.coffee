MProto = global.InexorMessageProtocol
Uuid = require 'uuid'
_ = require 'lodash'

class JSServiceCall
  constructor: (@name, @payload, @callback,
      @uuid=Uuid(), @type = "CALL") ->

  @fromProtobuf: (d) ->
    new JSServiceCall \
        d.function_name,
        d.payload,
        null,
        d.call_uuid,
        d.type

  @fromBuffer: (msg_codr, buf) ->
    JSServiceCall.fromProtobuf msg_codr.decode buf

  toProtobuf: (msg_codr) =>
    new msg_codr
      function_name: @name
      call_uuid: @uuid
      type: @type
      payload: @payload.toBuffer()

  toBuffer: (msg_codr) =>
    @toProtobuf(msg_codr).toBuffer()

class MCRpcClient
  constructor: (@con, @protocol, @msg_coder) ->
    @calls = {}

  rpc_send: (full_name, msg, cb=->) =>
    call = new JSServiceCall full_name, msg, cb
    @con.send call.toBuffer @msg_coder
    @calls[call.uuid] = call

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
