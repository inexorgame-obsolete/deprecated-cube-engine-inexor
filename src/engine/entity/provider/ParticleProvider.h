/*
 * Teleporter.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_PARTICLEPROVIDER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_PARTICLEPROVIDER_H_

#include "EntityTypeProvider.h"
#include "RelationshipTypeProvider.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"

#define ENTTYPE_PARTICLE_EMITTER "particle_emitter"
#define ENTTYPE_PARTICLE_INITIALIZER "particle_initializer"
#define ENTTYPE_PARTICLE_MODIFIER "particle_modifier"
#define RELTYPE_APPLY_MODIFIER_ON_EMITTED_PARTICLES "apply_modifier_on_emitted_particles"
#define RELTYPE_APPLY_INITIALIZER_ON_EMITTED_PARTICLES "apply_initializer_on_emitted_particles"

class EntityTypeManager;

class EmitterTypeProvider : public EntityTypeProvider
{
    public:
        EmitterTypeProvider();
        virtual ~EmitterTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EmitterTypeProvider);

};

class InitializerTypeProvider : public EntityTypeProvider
{
    public:
        InitializerTypeProvider();
        virtual ~InitializerTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InitializerTypeProvider);

};

class ModifierTypeProvider : public EntityTypeProvider
{
    public:
        ModifierTypeProvider();
        virtual ~ModifierTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ModifierTypeProvider);

};

/**
 * Relationship between particle emitters and particle initializers.
 * Apply the parent emitter and initializer types instead of the concrete emitter and initializer types.
 */
class ApplyInitializerOnEmittedParticlesRelationshipTypeProvider : public RelationshipTypeProvider
{
    public:
        ApplyInitializerOnEmittedParticlesRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~ApplyInitializerOnEmittedParticlesRelationshipTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ApplyInitializerOnEmittedParticlesRelationshipTypeProvider);

};

/**
 * Relationship between particle emitters and particle modifiers.
 * Apply the parent emitter and modifier types instead of the concrete emitter and modifier types.
 */
class ApplyModifierOnEmittedParticlesRelationshipTypeProvider : public RelationshipTypeProvider
{
    public:
        ApplyModifierOnEmittedParticlesRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~ApplyModifierOnEmittedParticlesRelationshipTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ApplyModifierOnEmittedParticlesRelationshipTypeProvider);

};

#endif /* SRC_ENGINE_ENTITY_PROVIDER_PARTICLEPROVIDER_H_ */
