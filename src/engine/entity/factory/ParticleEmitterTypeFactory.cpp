/*
 * ParticleProvider.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "ParticleEmitterTypeFactory.h"

TypeRefPtr<EntityType> ParticleEmitterTypeFactory::Create(std::string name_suffix)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    TypeRefPtr<EntityType> particle_emitter_type = entity_type_manager->Create(entity_type_name, true, true);
    particle_emitter_type["rate"] = 4;
    particle_emitter_type["lifetime"] = 0.0;
    particle_emitter_type["mass"] = 0.1;
    particle_emitter_type["density"] = 1.0;
    particle_emitter_type["vel_x"] = 1.0;
    particle_emitter_type["vel_y"] = 0.0;
    particle_emitter_type["vel_z"] = 0.0;
    return particle_emitter_type;
}
