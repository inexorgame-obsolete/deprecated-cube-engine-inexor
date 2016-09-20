#include "IntegerMemoryEntityTypeProvider.hpp"

namespace inexor {
namespace vscript {

    IntegerMemoryEntityTypeProvider::IntegerMemoryEntityTypeProvider()
        : EntityTypeProvider(ENT_BOOL_MEMORY)
    {
        entity_type = new EntityType(ENT_INTEGER_MEMORY, true, true);
    }

    IntegerMemoryEntityTypeProvider::~IntegerMemoryEntityTypeProvider()
    {
    }

}
}
