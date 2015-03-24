#ifndef INEXOR_TEST_NET_HELPERS_HEADER
#define INEXOR_TEST_NET_HELPERS_HEADER

#include "test/helpers.h"
#include "net/net.h"

typedef inexor::net::bytes bytes;

/// Create a message connect message with random content.
///
/// Actually just a long, random string.
///
/// The message will be between 16 and 1k bytes long.
///
/// @param len The length of the message to generate
/// @return The random message
extern bytes mkpkg();

/// Encode a MessageConnect message like MCByteBuffer would.
///
/// @return The encoded message.
extern bytes mcbytebuffer_encode(bytes &msg);

#endif
