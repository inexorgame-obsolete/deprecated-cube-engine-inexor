#include <boost/thread/thread.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread/mutex.hpp>

#include <array>
#include <unordered_map>
#include <unordered_set>

#include "inexor/util.hpp"
#include "inexor/util/random.hpp"

#include "gtest/gtest.h"

#include "inexor/test/helpers.hpp"

using namespace std;
using namespace boost;
using namespace inexor::util;

class range {
public:
    int a, // minimum of the range
        z, // maximum of the range
        tries, // Statistical tries
        same_compares; // Number of checks, whether the deterministic
};

// Seeds for the deterministic rng
array<int, 24> seeds = {
    0,       -2000,      1,     -1,
    -2000000,  999,    256,  -1024,
    12516,    9124,    882,   8843,
    23619,   17610,   3270,  19176,
    21357,    8158,   7774,  19288,
    2382,     1890,  22445,   5097
};

array<range, 5> ranges {
    range({0, 2, 10, 20}),
    range({-10, 10, 100, 2}),
    range({-30000, -29900, 100, 1}),
    range({5000, 7000, 100, 1}),
    range({300,302, 4, 20})
};

TEST(DeterministicRandom, XToYRange) {
    for (range &r : ranges) {

        // Here we check with different seeds and try if we
        // stay within the given range
        for (int seed : seeds) {
            int r1, r0 = deterministic_rnd(seed, r.a, r.z);

            // Here we check whether the same seed and range
            // produces the same result.
            for (int i=1; i<r.same_compares; i++) {
                r1 = deterministic_rnd(seed, r.a, r.z);
                EXPECT_EQ(r0, r1) << "Expected the"
                  "deterministic RNG to provide the same "
                  "result for the same seed.";

                r0 = r1;
            }

            EXPECT_GE(r0, r.a) << "Expected "
              "deterministic_ rnd(" << seed << ", "
              << r.a << ", " << r.z << ") = " << r0 <<
              "to produce values x >= " << r.a << ".";
            EXPECT_LE(r0, r.z) << "Expected "
              "deterministic_rnd(" << seed << ", "
              << r.a << ", " << r.z << ") = " << r0 <<
              "to produce values x <= " << r.z << ".";
        }

    }
}

TEST(PseudoRandom, XToYRange) {
    for (range &r : ranges) {
        int r0 = rnd(r.a, r.z);
        bool diff = false;
        for (int i=0; i<15; i++) {
            if (rnd(r.a, r.z) != r0) {
                diff = true;
                break;
            }
        }

        EXPECT_TRUE(diff) << "Expected at least one of ten random "
            "numbers to be different when calling rnd("
            << r.a << ", " << r.z << ") = " << r0;

        // Here we check with different seeds and try if we
        // stay within the given range
        for (int i=0; i<r.tries; i++) {
            int r0 = rnd(r.a, r.z);

            EXPECT_GE(r0, r.a) << "Expected "
              "rnd(" << r.a << ", " << r.z << ") "
              "to produce values x >= " << r.a << ".";
            EXPECT_LT(r0, r.z) << "Expected "
              "rnd(" << r.a << ", " << r.z << ") "
              "to produce values x < " << r.z << ".";
        }

    }
}

TEST(PseudoRandom, TypeFullRange) {
    typedef unsigned char uchar;

    unordered_set<uchar> dist;

    for (int i=0; i<200000; i++)
        dist.insert(rnd_raw<uchar>());

    EXPECT_EQ((unsigned int)255, dist.size()) << "Expected "
        "20000 random  unsigned chars to contain every "
        "possible uchar but could find only "
        << dist.size() << " values";
}

TEST(PseudoRandom, NumbersDifferAmongThreads) {
    typedef std::default_random_engine::result_type rand_type;
    const static int threadno = 200;

    array<rand_type, threadno> first_numbers;
    array<thread, threadno> threads;

    // Start $threadno threads; generate one number and save
    // in first_numbers; no locking because each thread owns
    // one slot in first_numbers
    for (int i=0; i<threadno; i++) {
        threads[i] = thread([i, &first_numbers](){
            first_numbers[i] =
                (inexor::util::random::generator)();
        });
    }

    // Wait for all threads to finish
    for (thread& t : threads) t.join();

    // Compute the distribution of numbers: number -> frequency
    unordered_map<rand_type, int> res(threadno*10);
    for (rand_type n : first_numbers) {
        bool has_key = res.find(n) == res.end();
        res[n] = (has_key ? res[n] : 0) + 1;
    }

    // And now check if there is any number whose frequency != 1
    // (usually will use uint_fast_32, so the collision
    // probability is OK, but not good)
    // TODO:  Check the seeds directly
    for (auto &cont : res)
        EXPECT_EQ(1, cont.second) << "Expcting random numbers"
          "to be uniq in a set of " << threadno << "threads, "
          "but random number " << cont.first << " occurred "
          << cont.second << " times.";
}
