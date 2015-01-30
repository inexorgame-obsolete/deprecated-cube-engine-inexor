/*
 * ParticleSubsystem.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_

#include "SubsystemBase.h"
#include "../factory/ParticleTypeFactory.h"
#include "../factory/ParticleEmitterTypeFactory.h"
#include "../factory/ParticleInitializerTypeFactory.h"
#include "../factory/ParticleModifierTypeFactory.h"
#include "../provider/ParticleProvider.h"

#define PARTICLE_SUBSYSTEM "particle"

class ParticleSubsystem : public SubsystemBase
{
    public:
        ParticleSubsystem();
        ParticleSubsystem(
            CefRefPtr<EntityTypeManager> entity_type_manager,
            CefRefPtr<EntityInstanceManager> entity_instance_manager,
            CefRefPtr<RelationshipTypeManager> relationship_type_manager,
            CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
        );
        virtual ~ParticleSubsystem();

        void RenderFaces();
        void RenderParticles();

        TypeRefPtr<EntityType> CreateParticleType(std::string particle_type_name);
        TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name);
        TypeRefPtr<EntityType> CreateInitializerType(std::string initializer_type_name);
        TypeRefPtr<EntityType> CreateModifierType(std::string modifier_type_name);

        InstanceRefPtr<EntityInstance> CreateEmitterInstance(std::string emitter_type_name, double x, double y, double z);
        InstanceRefPtr<EntityInstance> CreateEmitterInstance(TypeRefPtr<EntityType> emitter_type, double x, double y, double z);
        InstanceRefPtr<EntityInstance> CreateInitializerInstance(std::string initializer_type_name);
        InstanceRefPtr<EntityInstance> CreateInitializerInstance(TypeRefPtr<EntityType> initializer_type);
        InstanceRefPtr<EntityInstance> CreateModifierInstance(std::string modifier_type_name);
        InstanceRefPtr<EntityInstance> CreateModifierInstance(TypeRefPtr<EntityType> modifier_type);

        InstanceRefPtr<RelationshipInstance> AddModifierToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> modifier_instance);
        InstanceRefPtr<RelationshipInstance> AddInitializerToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> initializer_instance);

    private:
        CefRefPtr<EntityTypeFactory> particle_type_factory;
        CefRefPtr<ParticleEmitterTypeFactory> particle_emitter_type_factory;
        CefRefPtr<ParticleInitializerTypeFactory> particle_initializer_type_factory;
        CefRefPtr<ParticleModifierTypeFactory> particle_modifier_type_factory;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleSubsystem);

};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_ */
