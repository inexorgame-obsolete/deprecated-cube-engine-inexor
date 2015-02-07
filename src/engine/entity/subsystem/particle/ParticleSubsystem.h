/*
 * ParticleSubsystem.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_

#include "ParticleModel.h"
#include "../SubsystemBase.h"
#include "worker/ParticleWorker.h"
#include "worker/EmitterWorker.h"
#include "worker/ModifierWorker.h"
#include "../../factory/ParticleTypeFactory.h"
#include "../../factory/ParticleEmitterTypeFactory.h"
#include "../../factory/ParticleInitializerTypeFactory.h"
#include "../../factory/ParticleModifierTypeFactory.h"

using namespace inexor::entity;

namespace inexor {
namespace entity {
namespace particle {

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

        void Update(TimeStep time_step);
        void Cleanup();
        void Reset();

        /**
         * Renders the faces.
         */
        void RenderFaces();

        /**
         * Renders the particles.
         */
        void RenderParticles();

        TypeRefPtr<EntityType> CreateParticleType(std::string particle_type_name, std::string renderer_instance_name);
        TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int batch_size, int lifetime, double mass, double density);
        TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, std::string particle_type_name, int rate, int batch_size, int lifetime, double mass, double density);
        TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int lifetime);
        TypeRefPtr<EntityType> CreateInitializerType(std::string initializer_type_name, FunctionRefPtr function);
        TypeRefPtr<EntityType> CreateModifierType(std::string modifier_type_name, FunctionRefPtr function);

        TypeRefPtr<EntityType> GetParticleType(std::string particle_type_name);
        TypeRefPtr<EntityType> GetEmitterType(std::string emitter_type_name);
        TypeRefPtr<EntityType> GetInitializerType(std::string initializer_type_name);
        TypeRefPtr<EntityType> GetModifierType(std::string modifier_type_name);

        TypeRefPtr<RelationshipType> GetRelationshipType(std::string relationship_type_name);
        void DeleteRelationship(InstanceRefPtr<RelationshipInstance> instance);

        InstanceRefPtr<EntityInstance> CreateEmitterInstance(std::string emitter_type_name, double x, double y, double z, double vx, double vy, double vz);
        InstanceRefPtr<EntityInstance> CreateEmitterInstance(TypeRefPtr<EntityType> emitter_type, double x, double y, double z, double vx, double vy, double vz);
        InstanceRefPtr<EntityInstance> CreateInitializerInstance(std::string initializer_type_name);
        InstanceRefPtr<EntityInstance> CreateInitializerInstance(TypeRefPtr<EntityType> initializer_type);
        InstanceRefPtr<EntityInstance> CreateModifierInstance(std::string modifier_type_name);
        InstanceRefPtr<EntityInstance> CreateModifierInstance(TypeRefPtr<EntityType> modifier_type);

        void DestroyEmitterInstance(std::string uuid);
        void DestroyEmitterInstance(InstanceRefPtr<EntityInstance> emitter_instance);
        void DestroyInitializerInstance(std::string uuid);
        void DestroyInitializerInstance(InstanceRefPtr<EntityInstance> initializer_instance);
        void DestroyModifierInstance(std::string uuid);
        void DestroyModifierInstance(InstanceRefPtr<EntityInstance> modifier_instance);

        InstanceRefPtr<RelationshipInstance> AddModifierToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> modifier_instance);
        InstanceRefPtr<RelationshipInstance> AddInitializerToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> initializer_instance);

        CefRefPtr<ParticleWorker> CreateParticleWorker(std::string name, FunctionRefPtr function);
        CefRefPtr<EmitterWorker> CreateEmitterWorker(std::string name, TypeRefPtr<EntityType> emitter_type, InstanceRefPtr<EntityInstance> emitter_instance);
        CefRefPtr<ModifierWorker> CreateModifierWorker(std::string name, TypeRefPtr<EntityType> modifier_type, InstanceRefPtr<EntityInstance> modifier_instance);

        void DestroyParticleWorker(std::string name);
        void DestroyParticleWorker(InstanceRefPtr<EntityInstance> entity_instance);
        void DestroyEmitterWorker(InstanceRefPtr<EntityInstance> emitter_instance);
        void DestroyModifierWorker(InstanceRefPtr<EntityInstance> modifier_instance);

    private:
        CefRefPtr<ParticleTypeFactory> particle_type_factory;
        CefRefPtr<ParticleEmitterTypeFactory> particle_emitter_type_factory;
        CefRefPtr<ParticleInitializerTypeFactory> particle_initializer_type_factory;
        CefRefPtr<ParticleModifierTypeFactory> particle_modifier_type_factory;

        std::map<std::string, TypeRefPtr<EntityType> > particle_types;
        std::map<std::string, TypeRefPtr<EntityType> > emitter_types;
        std::map<std::string, TypeRefPtr<EntityType> > initializer_types;
        std::map<std::string, TypeRefPtr<EntityType> > modifier_types;

        /**
         * The particle workers.
         */
        std::vector<CefRefPtr<ParticleWorker> > particle_workers;

        /**
         * The emitter workers.
         */
        std::vector<CefRefPtr<EmitterWorker> > emitter_workers;

        /**
         * The modifier workers.
         */
        std::vector<CefRefPtr<ModifierWorker> > modifier_workers;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleSubsystem);

};

}
}
}

/**
 * Provide the particle subsystem as global reference.
 */
extern CefRefPtr<inexor::entity::particle::ParticleSubsystem> particle_subsystem;

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_ */
