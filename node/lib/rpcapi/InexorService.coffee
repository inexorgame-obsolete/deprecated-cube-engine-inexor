Net = require 'net'
MProto = require 'inexor/rpcapi/MessageProto'
SocketMessageConnect = require 'inexor/rpcapi/SocketMessageConnect'
MCRpcClient = require 'inexor/rpcapi/MCRpcClient'

default_config = ->
  cfg =
    socket: path: "/tmp/inexor.socket"
    proto: "../../../inexor/rpc/inexor_service.proto"
  if process.platform.match /^win/
    cfg.socket = port: 56732
  cfg

# Low level interface for communication with inexor
#
# This creates the sockets, loads the protocol files and
# stitches it all together
InexorService = (config=default_config()) ->
  msg_con = new SocketMessageConnect config.socket

  protocol =  new MProto config.proto
  rpc_client = new MCRpcClient msg_con, protocol,
      protocol.inexor.rpc.ServiceCall

  messages = protocol.inexor.rpc

  R = new messages.InexorService rpc_client.rpc_send
  R.messages = messages
  R.msg_con = msg_con
  R.protocol = protocol
  R.rpc_client = rpc_client
  R

module.exports = InexorService
