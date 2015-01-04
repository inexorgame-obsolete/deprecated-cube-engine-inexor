#include <uuid/uuid.h>

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
}
}
