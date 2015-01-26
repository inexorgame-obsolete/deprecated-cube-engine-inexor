/*
 * ParticleSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "ParticleSubsystem.h"

ParticleSubsystem::ParticleSubsystem() : SubsystemBase(PARTICLE_SUBSYSTEM)
{
}

ParticleSubsystem::ParticleSubsystem(
    CefRefPtr<EntityTypeManager> entity_type_manager,
    CefRefPtr<EntityInstanceManager> entity_instance_manager,
    CefRefPtr<RelationshipTypeManager> relationship_type_manager,
    CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
) : SubsystemBase(PARTICLE_SUBSYSTEM, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager)
{
    // Create entity type factories
    particle_type_factory = new ParticleTypeFactory(entity_type_manager);
    particle_emitter_type_factory = new ParticleEmitterTypeFactory(entity_type_manager);

    // Register entity type factories
    entity_type_manager->RegisterFactory(particle_type_factory);
    entity_type_manager->RegisterFactory(particle_emitter_type_factory);
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateParticleType(std::string particle_type_name)
{
    return particle_type_factory->Create(particle_type_name);
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateParticleEmitterType(std::string particle_emitter_type_name)
{
    return particle_emitter_type_factory->Create(particle_emitter_type_name);
}
