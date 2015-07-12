Long = require 'inexor/util/Long'
BufferBuilder = require 'inexor/util/BufferBuilder'

# Pendant of C++ MessageConnect, more specifically
# inexor::net::MCSocket.
#
# This basically takes an already established socket
# connection and hacks it into messages by sending on the
# socket:
# * First a# little endian 64bit unsigned integer as the size
# * and then a message with that size.
class SocketMessageConnect

  # [BufferBuilder] Buffer for reading messages and the message size.
  databuf: new BufferBuilder

  # [Int] How much data we need to read an entire size/message
  # TODO: We should actually use 64 bit numbers here
  dataneed: 8

  # [Bool] Are we reading a size or a message?
  readsize: true

  # Event called every time we red an entire message
  msg_listener: ->

  # @param [object] con_para – Either a socket to
  #   send/receive on (with `{connection: $socket}`), or
  #   parameters for creating a connection: Something you
  #   would pass to Socket as parameters
  # NOTE: We will register "date", "error" and "end" on the
  # socket, so those should not be already registered.
  constructor: (@con_para) ->

  # Getter for the connection
  #
  # If the connection was already used, returns that
  # connection.
  #
  # Otherwise it acquires a connection and registers the
  # data, error and end events on it.
  #
  # The connection is acquired by the following rules:
  # If a socket was passed to the constructor, returns that.
  # Otherwise creates a socket with the parameters passed to
  # the socket.
  con: ->
    return @con_cache if @con_cache

    if @con_para.connection
      @con_cache = con.connection
    else
      @con_cache = net.createConnection @con_para

    @con_cache.on "data", @onData
    @con_cache.on "error", @onError
    @con_cache.on "end", @close
    @con_cache

  # Called every time we read some data on the socket.
  #
  # This buffers the data and fires the msg_listener if an
  # entire message was red.
  onData: (buf) =>
    if @dataneed == 0
      throw new Error "SocketMessageConnect: @dataneed can never be 0"

    # TODO: Save data in cases we no not actually need the
    # second buffer, or in cases we need not copy
    bufpt = 0
    avail = buf.length
    while bufpt < buf.length
      avail = buf.length - bufpt
      ncpy = Math.min @dataneed, avail
      @databuf.append buf.slice bufpt, bufpt + ncpy
      bufpt += ncpy
      @dataneed -= ncpy

      # Need Moar data
      if @dataneed > 0
        continue

      # Got one size
      if @readsize
        @readsize = false
        @dataneed = Long.fromBufferLE(@databuf.finalize()).toNumber()
        @databuf = new BufferBuilder

      # Got one message
      else
        @msg_listener @databuf.finalize()
        @readsize = true
        @dataneed = 8
        @databuf = new BufferBuilder


  # Something bad happened on the socket. Log it.
  onError: (a...) =>
    console.log a...

  # Send a message wit it's size
  send: (buf) =>
    szbuf = Long.fromNumber(buf.length, true).toBufferLE()
    @con().write szbuf
    @con().write buf

  # Close the underlying socket
  close: =>
    @con().end()
    @con_cache = null

module.exports = SocketMessageConnect
