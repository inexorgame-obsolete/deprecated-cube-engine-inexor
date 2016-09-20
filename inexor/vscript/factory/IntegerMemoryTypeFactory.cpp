#include "IntegerMemoryTypeFactory.hpp"

namespace inexor {
namespace vscript {

    IntegerMemoryTypeFactory::IntegerMemoryTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager)
        : EntityTypeFactory(INTEGER_MEMORY_TYPE_FACTORY,
                            INTEGER_MEMORY_FUNCTION_ATTRIBUTE_NAME,
                            ENTTYPE_PREFIX_ENT_INTEGER_MEMORY_TYPE,
                            entity_type_manager)
    {
    }

    IntegerMemoryTypeFactory::~IntegerMemoryTypeFactory()
    {
    }

    TypeRefPtr<EntityType> IntegerMemoryTypeFactory::Create(std::string name_suffix, int value)
    {
        std::string entity_type_name = entity_type_name_prefix + name_suffix;
        // Set the parent type: memory.
        TypeRefPtr<EntityType> parent_type = entity_type_manager->Get(ENT_MEMORY);
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Create(ENT_INTEGER_MEMORY, true, true, parent_type);
        entity_type["value"] = value;
        return entity_type;
    }

}
}
