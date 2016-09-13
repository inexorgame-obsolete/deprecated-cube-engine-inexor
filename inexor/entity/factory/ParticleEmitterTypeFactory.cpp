/*
 * ParticleProvider.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "ParticleEmitterTypeFactory.hpp"

namespace inexor {
namespace entity {
namespace particle {

ParticleEmitterTypeFactory::ParticleEmitterTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager)
    : EntityTypeFactory(PARTICLE_EMITTER_TYPE_FACTORY, PARTICLE_EMITTER_FUNCTION_ATTRIBUTE_NAME, ENTTYPE_PREFIX_PARTICLE_EMITTER_TYPE, entity_type_manager)
{
}

ParticleEmitterTypeFactory::~ParticleEmitterTypeFactory()
{
}

TypeRefPtr<EntityType> ParticleEmitterTypeFactory::Create(std::string name_suffix, FunctionRefPtr function, std::string particle_type_name, int rate, int batch_size, int lifetime, double mass, double density)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    // Set the parent type, so that we know that the entity type is a particle emitter type.
    TypeRefPtr<EntityType> parent_emitter_type = entity_type_manager->Get(ENTTYPE_PARENT_EMITTER_TYPE);
    TypeRefPtr<EntityType> particle_emitter_type = entity_type_manager->Create(entity_type_name, true, true, parent_emitter_type);
    particle_emitter_type[function_attribute_name] = function;
    particle_emitter_type["particle_type"] = particle_type_name;
    particle_emitter_type["rate"] = rate;
    particle_emitter_type["batch_size"] = batch_size;
    particle_emitter_type["lifetime"] = lifetime;
    particle_emitter_type["mass"] = mass;
    particle_emitter_type["density"] = density;
    return particle_emitter_type;
}

}
}
}
