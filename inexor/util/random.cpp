#include "inexor/util/random.hpp"

namespace inexor {
namespace util {

namespace random {
    thread_local auto_seeded<rng_engine> generator;
    thread_local rng_engine deterministic_generator;
}

}
}
