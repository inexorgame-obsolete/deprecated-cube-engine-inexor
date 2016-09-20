/*
 * ParticleTypeFactory.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "ParticleTypeFactory.hpp"

namespace inexor {
namespace entity {
namespace particle {

    ParticleTypeFactory::ParticleTypeFactory(std::shared_ptr<EntityTypeManager> entity_type_manager)
        : EntityTypeFactory(PARTICLE_TYPE_FACTORY, PARTICLE_TYPE_FUNCTION_ATTRIBUTE_NAME, ENTTYPE_PREFIX_PARTICLE_TYPE, entity_type_manager)
    {
    }

    ParticleTypeFactory::~ParticleTypeFactory()
    {
    }

    TypeRefPtr<EntityType> ParticleTypeFactory::Create(std::string name_suffix, std::string renderer_instance_name)
    {
        std::string entity_type_name = entity_type_name_prefix + name_suffix;
        // Set the parent type, so that we know that the entity type is a particle emitter type.
        TypeRefPtr<EntityType> parent_emitter_type = entity_type_manager->Get(ENTTYPE_PARENT_PARTICLE_TYPE);
        TypeRefPtr<EntityType> particle_type = entity_type_manager->Create(entity_type_name, true, true, parent_emitter_type);
        particle_type[PARTICLE_TYPE_RENDERER_INSTANCE_ATTRIBUTE_NAME] = renderer_instance_name;
        return particle_type;
    }

}
}
}
