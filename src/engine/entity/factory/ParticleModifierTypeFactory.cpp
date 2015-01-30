/*
 * ParticleModifierTypeFactory.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "ParticleModifierTypeFactory.h"

TypeRefPtr<EntityType> ParticleModifierTypeFactory::Create(std::string name_suffix)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    // The parent type is the generic modifier type
    TypeRefPtr<EntityType> parent_modifier_type = entity_type_manager->Get(ENTTYPE_PARTICLE_MODIFIER);
    TypeRefPtr<EntityType> particle_modifier_type = entity_type_manager->Create(entity_type_name, true, true, parent_modifier_type);
    particle_modifier_type["name_suffix"] = name_suffix;
    return particle_modifier_type;
}
