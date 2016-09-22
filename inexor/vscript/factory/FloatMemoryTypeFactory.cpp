#include "FloatMemoryTypeFactory.hpp"

namespace inexor {
namespace vscript {

    FloatMemoryTypeFactory::FloatMemoryTypeFactory(std::shared_ptr<EntityTypeManager> entity_type_manager)
        : EntityTypeFactory(BOOL_MEMORY_TYPE_FACTORY,
                            BOOL_MEMORY_FUNCTION_ATTRIBUTE_NAME,
                            ENTTYPE_PREFIX_FLOAT_MEMORY_TYPE,
                            entity_type_manager)
    {
    }

    FloatMemoryTypeFactory::~FloatMemoryTypeFactory()
    {
    }

    TypeRefPtr<EntityType> FloatMemoryTypeFactory::Create(std::string name_suffix, float value)
    {
        std::string entity_type_name = entity_type_name_prefix + name_suffix;
        // Set the parent type: memory.
        TypeRefPtr<EntityType> parent_type = entity_type_manager->Get(ENT_MEMORY);
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Create(ENT_FLOAT_MEMORY, true, true, parent_type);
        entity_type["value"] = value;
        return entity_type;
    }

}
}
