/*
 * ParticleTypeFactory.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "ParticleTypeFactory.h"

ParticleTypeFactory::ParticleTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager)
    : EntityTypeFactory(PARTICLE_TYPE_FACTORY, ENTTYPE_PREFIX_PARTICLE_TYPE, entity_type_manager)
{
}

ParticleTypeFactory::~ParticleTypeFactory()
{
}

TypeRefPtr<EntityType> ParticleTypeFactory::Create(std::string name_suffix)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    TypeRefPtr<EntityType> particle_type = entity_type_manager->Create(entity_type_name, true, true);
    particle_type["renderer_instance"] = "default_renderer";
    return particle_type;
}
