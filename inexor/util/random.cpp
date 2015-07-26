#include "inexor/util/random.h"

#include <chrono>

namespace inexor {
namespace util {

namespace random {
    thread_local_ptr<auto_seeded<rng_engine>> generator;
    thread_local_ptr<rng_engine> deterministic_generator;
}

}
}
