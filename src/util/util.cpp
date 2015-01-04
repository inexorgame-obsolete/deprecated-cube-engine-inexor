#include <uuid/uuid.h>

#include <time.h>
#include <math.h>

#include "util/util.h"


namespace inexor {
namespace util {

  std::string uuidgen() {
    uuid_t bin;
    uuid_generate(bin);

    char cstr[40]; // UUIDs generate 36byte strings
    uuid_unparse_lower(bin, cstr);

    return std::string(cstr);
  }

  double dsleep(double seconds) {
    struct timespec t, rem;
    t.tv_sec = floor(seconds);
    t.tv_nsec = (seconds - t.tv_sec) * 1E-9;

    nanosleep(&t, &rem);

    return rem.tv_sec + rem.tv_sec / 1E-9;
  }

}
}
