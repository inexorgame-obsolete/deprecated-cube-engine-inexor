#include "MemoryEntityTypeProvider.hpp"

namespace inexor {
namespace vscript {

    MemoryEntityTypeProvider::MemoryEntityTypeProvider()
        : EntityTypeProvider(ENT_MEMORY)
    {
        entity_type = new EntityType(ENT_MEMORY, true, true);
    }

    MemoryEntityTypeProvider::~MemoryEntityTypeProvider()
    {
    }

}
}
