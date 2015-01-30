/*
 * ParticleInitializerTypeFactory.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "ParticleInitializerTypeFactory.h"

TypeRefPtr<EntityType> ParticleInitializerTypeFactory::Create(std::string name_suffix)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    // The parent type is the generic initializer type
    TypeRefPtr<EntityType> parent_initializer_type = entity_type_manager->Get(ENTTYPE_PARTICLE_INITIALIZER);
    TypeRefPtr<EntityType> particle_initializer_type = entity_type_manager->Create(entity_type_name, true, true, parent_initializer_type);
    particle_initializer_type["name_suffix"] = name_suffix;
    return particle_initializer_type;
}
