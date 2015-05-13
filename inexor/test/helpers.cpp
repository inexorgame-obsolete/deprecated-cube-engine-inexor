#include "inexor/test/helpers.h"

#include <cstring>

using namespace std;

default_random_engine trand;

void rndcopy(void *dst, size_t len) {
  typedef default_random_engine::result_type rt;
  size_t x=0, rts = sizeof(rt);

  unsigned char *dstc = (unsigned char*) dst;
  for (size_t x=0; x <= len-1-rts; x+=rts)
    dstc[x] = trand();

  rt last = trand();
  memcpy(dst, (void*)&last, len - x);
}
