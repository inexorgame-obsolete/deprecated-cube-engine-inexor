/*
 * ParticleProvider.cpp
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#include "ParticleProvider.h"

EmitterTypeProvider::EmitterTypeProvider() : EntityTypeProvider(ENTTYPE_PARTICLE_EMITTER)
{
    entity_type = new EntityType(ENTTYPE_PARTICLE_EMITTER, true, true);
}

EmitterTypeProvider::~EmitterTypeProvider()
{
}

InitializerTypeProvider::InitializerTypeProvider() : EntityTypeProvider(ENTTYPE_PARTICLE_INITIALIZER)
{
    entity_type = new EntityType(ENTTYPE_PARTICLE_INITIALIZER, true, true);
}

InitializerTypeProvider::~InitializerTypeProvider()
{
}

ModifierTypeProvider::ModifierTypeProvider() : EntityTypeProvider(ENTTYPE_PARTICLE_MODIFIER)
{
    entity_type = new EntityType(ENTTYPE_PARTICLE_MODIFIER, true, true);
}

ModifierTypeProvider::~ModifierTypeProvider()
{
}

ApplyInitializerOnEmittedParticlesRelationshipTypeProvider::ApplyInitializerOnEmittedParticlesRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager)
    : RelationshipTypeProvider(RELTYPE_APPLY_MODIFIER_ON_EMITTED_PARTICLES, entity_type_manager)
{
    // Define the relationship type
    relationship_type = new RelationshipType(
        RELTYPE_APPLY_INITIALIZER_ON_EMITTED_PARTICLES,
        true,
        true,
        entity_type_manager->Get(ENTTYPE_PARTICLE_EMITTER),
        entity_type_manager->Get(ENTTYPE_PARTICLE_INITIALIZER)
    );
}

ApplyInitializerOnEmittedParticlesRelationshipTypeProvider::~ApplyInitializerOnEmittedParticlesRelationshipTypeProvider()
{
}

ApplyModifierOnEmittedParticlesRelationshipTypeProvider::ApplyModifierOnEmittedParticlesRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager)
    : RelationshipTypeProvider(RELTYPE_APPLY_MODIFIER_ON_EMITTED_PARTICLES, entity_type_manager)
{
    // Define the relationship type
    relationship_type = new RelationshipType(
        RELTYPE_APPLY_MODIFIER_ON_EMITTED_PARTICLES,
        true,
        true,
        entity_type_manager->Get(ENTTYPE_PARTICLE_EMITTER),
        entity_type_manager->Get(ENTTYPE_PARTICLE_MODIFIER)
    );
}

ApplyModifierOnEmittedParticlesRelationshipTypeProvider::~ApplyModifierOnEmittedParticlesRelationshipTypeProvider()
{
}
