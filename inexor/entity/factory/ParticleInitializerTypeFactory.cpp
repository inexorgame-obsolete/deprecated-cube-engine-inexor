/*
 * ParticleInitializerTypeFactory.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "ParticleInitializerTypeFactory.hpp"

namespace inexor {
namespace entity {
namespace particle {

ParticleInitializerTypeFactory::ParticleInitializerTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager)
    : EntityTypeFactory(PARTICLE_INITIALIZER_TYPE_FACTORY, PARTICLE_INITIALIZER_FUNCTION_ATTRIBUTE_NAME, ENTTYPE_PREFIX_PARTICLE_INITIALIZER_TYPE, entity_type_manager)
{
}

ParticleInitializerTypeFactory::~ParticleInitializerTypeFactory()
{
}

TypeRefPtr<EntityType> ParticleInitializerTypeFactory::Create(std::string name_suffix, FunctionRefPtr function)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    // Set the parent type, so that we know that the entity type is a particle initializer type.
    TypeRefPtr<EntityType> parent_initializer_type = entity_type_manager->Get(ENTTYPE_PARENT_INITIALIZER_TYPE);
    TypeRefPtr<EntityType> particle_initializer_type = entity_type_manager->Create(entity_type_name, true, true, parent_initializer_type);
    particle_initializer_type[function_attribute_name] = function;
    return particle_initializer_type;
}

}
}
}
