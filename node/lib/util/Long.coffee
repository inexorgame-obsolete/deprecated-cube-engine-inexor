BasicLong = require 'long'

class Long extends BasicLong
  # Generate a new Long from a buffer
  @fromBufferLE: (buf) ->
    new Long \
      buf.readUInt32LE(0),
      buf.readUInt32LE(4),
      true

  @fromBufferBE: (buf) ->
    new Long \
        buf.readUInt32BE(4),
        buf.readUInt32BE(0),
        true

  @fromObj: (o) ->
    Long.fromBits o.low, o.high, o.unsigned

  @fromBits:   (a...) -> new Long super a...
  @fromInt:    (a...) -> new Long super a...
  @fromNumber: (a...) -> new Long super a...
  @fromString: (a...) -> new Long super a...
  @fromValue:  (a...) -> new Long super a...

  writeToBufferLE: (b, ofs=0) =>
    b.writeUInt32LE @low,  0+ofs
    b.writeUInt32LE @high, 4+ofs
    b

  writeToBufferBE: (b, ofs=0) =>
    b.writeUInt32BE @high, 0+ofs
    b.writeUInt32BE @low,  4+ofs
    b

  toBufferLE: =>
    @writeToBufferLE new Buffer 8

  toBufferBE: =>
    @writeToBufferBE new Buffer 8

module.exports = Long
