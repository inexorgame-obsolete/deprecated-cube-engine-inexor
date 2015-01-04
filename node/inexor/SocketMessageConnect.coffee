Long = require 'inexor/Long'
BufferBuilder = require 'inexor/BufferBuilder'

class SocketMessageConnect
  constructor: (@con_para) ->
    
    # Buffer for reading messages and the message size.
    # If datalen=null we are in 'size-reading' state
    @databuf = new BufferBuilder
    @datalen =  null

    @msg_listener = ->

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
    @databuf.append buf

    # We got the entire message size
    if @datalen == null && @databuf.len >= 8
      szbuf = Long.fromBufferLE @databuf.buf
      @datalen = szbuf.toNumber()
      @databuf.sliceThis 8

    # We got the message itself
    if @databuf.len == @datalen
      dat = @databuf.finalize()
      @databuf = new BufferBuilder
      @datalen = null

      @msg_listener dat

  onError: (a...) =>
    console.log a...
    @con_cache = null

  lis: => @msg_listener

  send: (buf) =>
    szbuf = Long.fromNumber(buf.length, true).toBufferLE()
    @con().write szbuf
    @con().write buf

  close: =>
    @con().end()
    @con_cache = null

module.exports = SocketMessageConnect
