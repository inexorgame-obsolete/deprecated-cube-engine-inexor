Net = require 'net'
MProto = require 'inexor/MessageProto'
SocketMessageConnect = require 'inexor/SocketMessageConnect'
MCRpcClient = require 'inexor/MCRpcClient'


# Low level interface for communication with inexor
#
# This creates the sockets, loads the protocol files and
# stitches it all together
InexorService = ->
  if process.platform.match /^win/
    soco = port: 56732
  else
    soco = path: "/tmp/inexor.socket"

  msg_con = new SocketMessageConnect soco

  protocol =  new MProto "../inexor/rpc/inexor_service.proto"
  rpc_client = new MCRpcClient msg_con, protocol,
      protocol.inexor.rpc.ServiceCall

  msg_con.msg_listener = rpc_client.rpc_recv

  messages = protocol.inexor.rpc

  R = new messages.InexorService rpc_client.rpc_send
  R.messages = messages
  R.msg_con = msg_con
  R.protocol = protocol
  R.rpc_client = rpc_client
  R

module.exports = InexorService
