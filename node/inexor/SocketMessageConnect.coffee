Long = require 'inexor/Long'
BufferBuilder = require 'inexor/BufferBuilder'

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

  constructor: (@con_para) ->

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


  onError: (a...) =>
    console.log a...
    @con_cache = null

  send: (buf) =>
    szbuf = Long.fromNumber(buf.length, true).toBufferLE()
    @con().write szbuf
    @con().write buf

  close: =>
    @con().end()
    @con_cache = null

module.exports = SocketMessageConnect
