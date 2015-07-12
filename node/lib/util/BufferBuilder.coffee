# TODO: Browser support

# Build Buffers; in case you don't know the size of the
# buffer you want to create
class BufferBuilder
  # [Int] Block size
  #
  # When the data needs to be resized, we will always
  # allocate the new buffer with a multiple of the block
  # size as size.
  bs: null

  # [Int] The size of the currently allocated buffer
  alloc: null

  # [Int] The amount of data used in the current buffer
  len: null

  # [Buffer] The underlying primitive buffer
  buf: null

  # Create a new BufferBuilder
  #
  # @param [Object] opts; default: {}
  # @option [Int] bs The block size to use; default: 1024
  # @option [Buffer] Buf, The buffer to initialize this with
  constructor: (opts={}) ->
    @bs  = opts.bs || 1024
    @alloc = @bs
    @buf =  new Buffer @alloc
    @len = 0

    if opts.buf
      @append opts.buf

  # Resize the buffer to a certain size
  #
  # Will cut off data of the end, size < @len
  #
  # @param [Int] size New size of the buffer
  resize: (size) =>
    old = @buf
    @alloc = @bs * Math.ceil(size/@bs)
    @len = Math.min @len, @alloc
    @buf = new Buffer @alloc
    old.copy @buf, 0, 0, @len

  # Ensure that this buffer at least as large as the given
  # size
  #
  # @param [Int] size
  ensureSize: (size) =>
    if size < @alloc
      @resize size

  # Ensure that there is at least a given amount of data
  # unused in the buffer
  #
  # @param [Int] size
  ensureFree: (size) =>
    @ensureSize @len + size

  # Append another buffer to the end of this
  #
  # @param [Buffer] buf The buffer to append
  append: (buf) =>
    @ensureFree buf.length
    buf.copy @buf, @len
    @len += buf.length

  # Shrink the buffer at both ends by the given size
  #
  # @param [Int] start The new starting position
  # @param [Int] end The new end position; default: @len
  sliceThis: (start, end=@len) =>
    bad = start < 0 || start > @len || end < 0 \
        || end > @len || start > end
    if bad
      throw new Error "That's not a sane buffer range"

    # Take from the end
    @len = end
  
    # Take from the start
    @buf = @buf.slice start
    @len -= start
    @alloc -= start

  # Generate a new buffer that contains a copy of the
  # actually used data
  #
  # @return [Buffer] The new buffer
  toBuffer: =>
    out = new Buffer @len
    @buf.copy out, 0, 0, @len
    out

  # Make this a proper buffer
  #
  # Like toBuffer, but will not copy the buffer.
  #
  # The BufferBuilder should not be used after calling this
  # function.
  #
  # @return [Buffer] The finally generated buffer
  finalize: =>
    @buf.slice 0, @len

module.exports = BufferBuilder
