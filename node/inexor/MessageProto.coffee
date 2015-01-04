Uuid = require 'uuid'
Protobuf = require 'protobufjs'
Long = require 'inexor/Long'

# NOTE: This is an abstract MessagProtocol, the actual
#       instance can be found in InexorService.MessageProtocol

module.exports = (file) ->
  builder = Protobuf.loadProtoFile file

  MessageProto = builder.build()
  MessageProto.file = file
  MessageProto.reflect = builder.lookup()

  MessageProto
