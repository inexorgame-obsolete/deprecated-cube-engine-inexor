/// @file Set of containers (vector,hashset,buffer,stream) and tools for developing
/// @warning Try to avoid using these containers for new code.

#pragma once


#include "inexor/shared/cube_types.hpp"
#include "inexor/shared/cube_loops.hpp"
#include "inexor/shared/cube_tools.hpp"
#include "inexor/shared/cube_endian.hpp"
#include "inexor/shared/cube_formatting.hpp"
#include "inexor/shared/cube_hash.hpp"
#include "inexor/network/legacy/cube_network.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/stream.hpp"
#include "inexor/shared/cube_unicode.hpp"

#include <new>
#include <cstddef>
#include <algorithm>

#include <boost/algorithm/clamp.hpp>

#include "inexor/util/random.hpp"
#include "inexor/network/SharedTree.hpp"
#include "inexor/util.hpp"
// TODO:
// Replace swap in sources
// Replace rnd in sources (+ friends)
// Remove stringslice (replace with std::string methods)
// Move top level headers (inexor/util.hpp) to their moduls again.

using std::swap;
using std::min;
using std::max;

using boost::algorithm::clamp;

/// Search the mask data from least significant bit(LSB) to the most significant bit(MSB) for a set bit(1).
/// @return the position of first set bit (1) found.
#ifdef __GNUC__
#define bitscan(mask) (__builtin_ffs(mask)-1)
#else
#ifdef WIN32
#pragma intrinsic(_BitScanForward)
static inline int bitscan(uint mask)
{
    ulong i;
    return _BitScanForward(&i, mask) ? i : -1;
}
#else
static inline int bitscan(uint mask)
{
    if(!mask) return -1;
    int i = 1;
    if(!(mask&0xFFFF)) { i += 16; mask >>= 16; }
    if(!(mask&0xFF)) { i += 8; mask >>= 8; }
    if(!(mask&0xF)) { i += 4; mask >>= 4; }
    if(!(mask&3)) { i += 2; mask >>= 2; }
    return i - (mask&1);
}
#endif
#endif

INEXOR_FUNCTION_ALIAS(rnd, inexor::util::rnd<int>);
INEXOR_FUNCTION_ALIAS(rndscale, inexor::util::rnd<float>);
INEXOR_FUNCTION_ALIAS(detrnd, inexor::util::deterministic_rnd<int>);


