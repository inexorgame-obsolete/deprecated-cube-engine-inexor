/*
 * ParticleModifierTypeFactory.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "ParticleModifierTypeFactory.hpp"

namespace inexor {
namespace entity {
namespace particle {

    ParticleModifierTypeFactory::ParticleModifierTypeFactory(std::shared_ptr<EntityTypeManager> entity_type_manager)
        : EntityTypeFactory(PARTICLE_MODIFIER_TYPE_FACTORY, PARTICLE_MODIFIER_FUNCTION_ATTRIBUTE_NAME, ENTTYPE_PREFIX_PARTICLE_MODIFIER_TYPE, entity_type_manager)
    {
    }

    ParticleModifierTypeFactory::~ParticleModifierTypeFactory()
    {
    }

    TypeRefPtr<EntityType> ParticleModifierTypeFactory::Create(std::string name_suffix, FunctionRefPtr function)
    {
        std::string entity_type_name = entity_type_name_prefix + name_suffix;
        // Set the parent type, so that we know that the entity type is a particle modifier type.
        TypeRefPtr<EntityType> parent_modifier_type = entity_type_manager->Get(ENTTYPE_PARENT_MODIFIER_TYPE);
        TypeRefPtr<EntityType> particle_modifier_type = entity_type_manager->Create(entity_type_name, true, true, parent_modifier_type);
        particle_modifier_type[function_attribute_name] = function;
        return particle_modifier_type;
    }

}
}
}
