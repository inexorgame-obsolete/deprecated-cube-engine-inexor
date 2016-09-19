#include "BoolMemoryEntityTypeProvider.hpp"

namespace inexor {
namespace vscript {

    BoolMemoryEntityTypeProvider::BoolMemoryEntityTypeProvider()
        : EntityTypeProvider(ENT_BOOL_MEMORY)
    {
        entity_type = new EntityType(ENT_BOOL_MEMORY, true, true);
    }

    BoolMemoryEntityTypeProvider::~BoolMemoryEntityTypeProvider()
    {
    }

}
}
