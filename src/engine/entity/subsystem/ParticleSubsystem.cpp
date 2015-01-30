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
    // Create entity type providers
    CefRefPtr<EntityTypeProvider> emitter_type_provider = new EmitterTypeProvider();
    CefRefPtr<EntityTypeProvider> initializer_type_provider = new InitializerTypeProvider();
    CefRefPtr<EntityTypeProvider> modifier_type_provider = new ModifierTypeProvider();
    entity_type_manager->RegisterProvider(emitter_type_provider);
    entity_type_manager->RegisterProvider(initializer_type_provider);
    entity_type_manager->RegisterProvider(modifier_type_provider);

    // Create relationship type providers
    CefRefPtr<RelationshipTypeProvider> apply_initializer_on_emitted_particles_relationship_type_provider = new ApplyInitializerOnEmittedParticlesRelationshipTypeProvider(entity_type_manager);
    CefRefPtr<RelationshipTypeProvider> apply_modifier_on_emitted_particles_relationship_type_provider = new ApplyModifierOnEmittedParticlesRelationshipTypeProvider(entity_type_manager);
    relationship_type_manager->RegisterProvider(apply_initializer_on_emitted_particles_relationship_type_provider);
    relationship_type_manager->RegisterProvider(apply_modifier_on_emitted_particles_relationship_type_provider);

    // Create entity type factories
    particle_type_factory = new ParticleTypeFactory(entity_type_manager);
    particle_emitter_type_factory = new ParticleEmitterTypeFactory(entity_type_manager);
    particle_initializer_type_factory = new ParticleInitializerTypeFactory(entity_type_manager);
    particle_modifier_type_factory = new ParticleModifierTypeFactory(entity_type_manager);

    // Register entity type factories
    entity_type_manager->RegisterFactory(particle_type_factory);
    entity_type_manager->RegisterFactory(particle_emitter_type_factory);
    entity_type_manager->RegisterFactory(particle_initializer_type_factory);
    entity_type_manager->RegisterFactory(particle_modifier_type_factory);
}

ParticleSubsystem::~ParticleSubsystem()
{
}

void ParticleSubsystem::RenderFaces()
{
    // TODO: Implement
}

void ParticleSubsystem::RenderParticles()
{
    // TODO: Implement
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateParticleType(std::string particle_type_name)
{
    return particle_type_factory->Create(particle_type_name);
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateEmitterType(std::string emitter_type_name)
{
    return particle_emitter_type_factory->Create(emitter_type_name);
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateInitializerType(std::string initializer_type_name)
{
    return particle_initializer_type_factory->Create(initializer_type_name);
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateModifierType(std::string modifier_type_name)
{
    return particle_modifier_type_factory->Create(modifier_type_name);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateEmitterInstance(std::string emitter_type_name, double x, double y, double z)
{
    TypeRefPtr<EntityType> emitter_type = entity_type_manager->Get(emitter_type_name);
    return CreateEmitterInstance(emitter_type, x, y, z);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateEmitterInstance(TypeRefPtr<EntityType> emitter_type, double x, double y, double z)
{
    InstanceRefPtr<EntityInstance> emitter_instance = entity_instance_manager->Create(emitter_type);
    emitter_instance["x"] = x;
    emitter_instance["y"] = y;
    emitter_instance["z"] = z;
    return emitter_instance;
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateInitializerInstance(std::string initializer_type_name)
{
    TypeRefPtr<EntityType> initializer_type = entity_type_manager->Get(initializer_type_name);
    return CreateInitializerInstance(initializer_type);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateInitializerInstance(TypeRefPtr<EntityType> initializer_type)
{
    InstanceRefPtr<EntityInstance> initializer_instance = entity_instance_manager->Create(initializer_type);
    return initializer_instance;
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateModifierInstance(std::string modifier_type_name)
{
    TypeRefPtr<EntityType> modifier_type = entity_type_manager->Get(modifier_type_name);
    return CreateModifierInstance(modifier_type);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateModifierInstance(TypeRefPtr<EntityType> modifier_type)
{
    InstanceRefPtr<EntityInstance> modifier_instance = entity_instance_manager->Create(modifier_type);
    return modifier_instance;
}

InstanceRefPtr<RelationshipInstance> ParticleSubsystem::AddModifierToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> modifier_instance)
{
    TypeRefPtr<RelationshipType> apply_modifier_type = relationship_type_manager->Get(RELTYPE_APPLY_MODIFIER_ON_EMITTED_PARTICLES);
    if (apply_modifier_type.get()) {
        InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(apply_modifier_type, emitter_instance, modifier_instance);
        return relationship_instance;
    } else {
        return NULL;
    }
}

InstanceRefPtr<RelationshipInstance> ParticleSubsystem::AddInitializerToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> initializer_instance)
{
    TypeRefPtr<RelationshipType> apply_initializer_type = relationship_type_manager->Get(RELTYPE_APPLY_INITIALIZER_ON_EMITTED_PARTICLES);
    if (apply_initializer_type.get()) {
        InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(apply_initializer_type, emitter_instance, initializer_instance);
        return relationship_instance;
    } else {
        return NULL;
    }
}
