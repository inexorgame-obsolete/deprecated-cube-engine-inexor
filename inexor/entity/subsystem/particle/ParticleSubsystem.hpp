/*
 * ParticleSubsystem.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_

#include "ParticleModel.hpp"
#include "../SubsystemBase.hpp"
#include "../HandleSubsystem.hpp"
#include "worker/ParticleWorker.hpp"
#include "worker/EmitterWorker.hpp"
#include "worker/ModifierWorker.hpp"
#include "../../factory/ParticleTypeFactory.hpp"
#include "../../factory/ParticleEmitterTypeFactory.hpp"
#include "../../factory/ParticleInitializerTypeFactory.hpp"
#include "../../factory/ParticleModifierTypeFactory.hpp"
#include "../../factory/ParticleRendererTypeFactory.hpp"

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

        /**
         * Updates the particle system by the given time step.
         */
        void Update(TimeStep time_step);

        /**
         * Initializes the graph model for the particle system.
         */
        void InitializeModel();

        /**
         * Shutdown.
         */
        void Cleanup();

        /**
         * TODO
         */
        void Reset();

        /**
         * Renders the faces.
         */
        void RenderFaces();

        /**
         * Renders the particles. This method is called in the main thread.
         */
        void RenderParticles();

        TypeRefPtr<EntityType> CreateParticleType(std::string particle_type_name, std::string renderer_instance_name);
        TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int batch_size, int lifetime, double mass, double density);
        TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, std::string particle_type_name, int rate, int batch_size, int lifetime, double mass, double density);
        TypeRefPtr<EntityType> CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int lifetime);
        TypeRefPtr<EntityType> CreateInitializerType(std::string initializer_type_name, FunctionRefPtr function);
        TypeRefPtr<EntityType> CreateModifierType(std::string modifier_type_name, FunctionRefPtr function);
        TypeRefPtr<EntityType> CreateRendererType(std::string renderer_type_name, FunctionRefPtr function);

        TypeRefPtr<EntityType> GetParticleType(std::string particle_type_name);
        TypeRefPtr<EntityType> GetEmitterType(std::string emitter_type_name);
        TypeRefPtr<EntityType> GetInitializerType(std::string initializer_type_name);
        TypeRefPtr<EntityType> GetModifierType(std::string modifier_type_name);
        TypeRefPtr<EntityType> GetRendererType(std::string renderer_type_name);

        TypeRefPtr<RelationshipType> GetRelationshipType(std::string relationship_type_name);

        InstanceRefPtr<EntityInstance> CreateEmitterInstance(std::string emitter_type_name, double x, double y, double z, double vx, double vy, double vz);
        InstanceRefPtr<EntityInstance> CreateEmitterInstance(TypeRefPtr<EntityType> emitter_type, double x, double y, double z, double vx, double vy, double vz);
        InstanceRefPtr<EntityInstance> CreateInitializerInstance(std::string initializer_type_name);
        InstanceRefPtr<EntityInstance> CreateInitializerInstance(TypeRefPtr<EntityType> initializer_type);
        InstanceRefPtr<EntityInstance> CreateModifierInstance(std::string modifier_type_name);
        InstanceRefPtr<EntityInstance> CreateModifierInstance(TypeRefPtr<EntityType> modifier_type);
        InstanceRefPtr<EntityInstance> CreateRendererInstance(std::string renderer_type_name, std::string model, vec offset);
        InstanceRefPtr<EntityInstance> CreateRendererInstance(std::string renderer_type_name, std::string shader, std::string texture, float size);
        InstanceRefPtr<EntityInstance> CreateRendererInstance(TypeRefPtr<EntityType> renderer_type, std::string model, vec offset);
        InstanceRefPtr<EntityInstance> CreateRendererInstance(TypeRefPtr<EntityType> renderer_type, std::string shader, std::string texture, float size);

        void DestroyEmitterInstance(std::string uuid);
        void DestroyEmitterInstance(InstanceRefPtr<EntityInstance> emitter_instance);
        void DestroyInitializerInstance(std::string uuid);
        void DestroyInitializerInstance(InstanceRefPtr<EntityInstance> initializer_instance);
        void DestroyModifierInstance(std::string uuid);
        void DestroyModifierInstance(InstanceRefPtr<EntityInstance> modifier_instance);
        void DestroyRendererInstance(std::string uuid);
        void DestroyRendererInstance(InstanceRefPtr<EntityInstance> renderer_instance);

        InstanceRefPtr<RelationshipInstance> AddModifierToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> modifier_instance);
        InstanceRefPtr<RelationshipInstance> AddInitializerToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> initializer_instance);
        InstanceRefPtr<RelationshipInstance> AddRendererToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> renderer_instance);

        CefRefPtr<ParticleWorker> CreateParticleWorker(std::string name, FunctionRefPtr function);
        CefRefPtr<ParticleWorker> CreateParticleWorker(std::string name, FunctionRefPtr function, int maxfps);
        CefRefPtr<EmitterWorker> CreateEmitterWorker(TypeRefPtr<EntityType> emitter_type, InstanceRefPtr<EntityInstance> emitter_instance);
        CefRefPtr<EmitterWorker> CreateEmitterWorker(TypeRefPtr<EntityType> emitter_type, InstanceRefPtr<EntityInstance> emitter_instance, int maxfps);
        CefRefPtr<ModifierWorker> CreateModifierWorker(TypeRefPtr<EntityType> modifier_type, InstanceRefPtr<EntityInstance> modifier_instance);
        CefRefPtr<ModifierWorker> CreateModifierWorker(TypeRefPtr<EntityType> modifier_type, InstanceRefPtr<EntityInstance> modifier_instance, int maxfps);

        void DestroyParticleWorker(std::string name);
        void DestroyParticleWorker(InstanceRefPtr<EntityInstance> entity_instance);
        void DestroyEmitterWorker(InstanceRefPtr<EntityInstance> emitter_instance);
        void DestroyModifierWorker(InstanceRefPtr<EntityInstance> modifier_instance);

    private:

        /**
         * The maximum frames per second.
         */
        int maxfps;

        CefRefPtr<ParticleTypeFactory> particle_type_factory;
        CefRefPtr<ParticleEmitterTypeFactory> particle_emitter_type_factory;
        CefRefPtr<ParticleInitializerTypeFactory> particle_initializer_type_factory;
        CefRefPtr<ParticleModifierTypeFactory> particle_modifier_type_factory;
        CefRefPtr<ParticleRendererTypeFactory> particle_renderer_type_factory;

        std::unordered_map<std::string, TypeRefPtr<EntityType> > particle_types;
        std::unordered_map<std::string, TypeRefPtr<EntityType> > emitter_types;
        std::unordered_map<std::string, TypeRefPtr<EntityType> > initializer_types;
        std::unordered_map<std::string, TypeRefPtr<EntityType> > modifier_types;
        std::unordered_map<std::string, TypeRefPtr<EntityType> > renderer_types;

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

        /**
         * The modifier workers.
         */
        std::vector<InstanceRefPtr<EntityInstance> > renderers;

        TypeRefPtr<RelationshipType> emitted_by;
        TypeRefPtr<RelationshipType> modifies;
        TypeRefPtr<RelationshipType> renders;
        TypeRefPtr<RelationshipType> apply_initializer;
        TypeRefPtr<RelationshipType> apply_modifier;
        TypeRefPtr<RelationshipType> apply_renderer;

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
