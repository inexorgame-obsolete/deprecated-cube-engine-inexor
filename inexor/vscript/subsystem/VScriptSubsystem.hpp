#ifndef INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER
#define INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/vscript/provider/MemoryEntityTypeProvider.hpp"
#include "inexor/vscript/event/TimerEvent.hpp"
#include "inexor/vscript/operator/IncreaseInteger.hpp"
#include "inexor/vscript/operator/DecreaseInteger.hpp"

#define VSCRIPT_SUBSYSTEM "vscript"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    /**
     * This subsystems manages 3D visual scripting.
     */
    class VScriptSubsystem : public SubsystemBase
    {
        public:

            VScriptSubsystem();
            
            /**
             *
             */
            VScriptSubsystem(std::shared_ptr<EntityTypeManager> entity_type_manager,
                             std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                             std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                             std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~VScriptSubsystem();

            /**
             * Updates all activations. Start point are all event entities.
             */
            void Update(TimeStep time_step);

            /**
             * Updates a single activation.
             */
            void Activate(TimeStep time_step, InstanceRefPtr<EntityInstance> source);

            /**
             * Calls the activation.
             */
            void Activate(TimeStep time_step, InstanceRefPtr<EntityInstance> source, InstanceRefPtr<EntityInstance> target, InstanceRefPtr<RelationshipInstance> activates);

            /**
             *
             */
            void Cleanup();

            /**
             *
             */
            void Reset();

            /**
             * Initializes the graph model for the particle system.
             * TODO: Move this to SubsystemBase
             */
            void InitializeModel();

            /**
             * Creates a event type.
             */
            TypeRefPtr<EntityType> CreateEventType(std::string name, InstanceRefPtr<EntityFunction> function);

            /**
             * Creates a memory type.
             */
            TypeRefPtr<EntityType> CreateMemoryType(std::string name);

            /**
             * Creates an event entity.
             */
            InstanceRefPtr<EntityInstance> CreateEvent(TypeRefPtr<EntityType> event_type, double x, double y, double z);

            /**
             * Creates a memory entity.
             */
            InstanceRefPtr<EntityInstance> CreateMemory(TypeRefPtr<EntityType> memory_type, double x, double y, double z, bool isConstant);

            /**
             * Creates an activation relationship between the given source
             * entity and the given target entity. During activation, the
             * target's entity function named "activation_function_name" is
             * called.
             *
             * It is possible to create multiple activations between the same
             * source and target with different activation functions.
             */
            InstanceRefPtr<RelationshipInstance> ConnectActivation(InstanceRefPtr<EntityInstance> source, InstanceRefPtr<EntityInstance> target, std::string activation_function_name);

            /**
             * Removes the given activation relationship.
             */
            void DisconnectActivation(InstanceRefPtr<RelationshipInstance> activation);

            /**
             * Removes all existing activations between the two given entities.
             */
            void DisconnectAllActivations(InstanceRefPtr<EntityInstance> source, InstanceRefPtr<EntityInstance> target);

            /**
             * Removes all outgoing activations of the given entity.
             */
            void DisconnectAllOutgoingActivations(InstanceRefPtr<EntityInstance> source);

            /**
             * Removes all incoming activations of the given entity.
             */
            void DisconnectAllIncomingActivations(InstanceRefPtr<EntityInstance> target);

            /**
             * Removes all outgoing and incoming activations.
             */
            void DisconnectAllActivations(InstanceRefPtr<EntityInstance> entity);

        private:

            /**
             * The base type for event types.
             */
            TypeRefPtr<EntityType> parent_event_type;

            /**
             * This map stores all event types.
             */
            std::unordered_map<std::string, TypeRefPtr<EntityType> > event_types;

            /**
             * The base type for memory types.
             */
            TypeRefPtr<EntityType> parent_memory_type;

            /**
             * This map stores all memory types.
             */
            std::unordered_map<std::string, TypeRefPtr<EntityType> > memory_types;

            /**
             * The list of event entity instances.
             */
            std::vector<InstanceRefPtr<EntityInstance>> event_instances;

            /**
             * The list of memory entity instances.
             */
            std::vector<InstanceRefPtr<EntityInstance>> memory_instances;


            // The main relationship types of the VScript subsystem.

            /**
             * Relationship type: The source entity activates the target entity.
             *
             * SOURCE_ENTITY--[activates]-->TARGET_ENTITY
             *
             */
            TypeRefPtr<RelationshipType> activates;

    };

}
}

/**
 * Provide the vscript subsystem as global reference.
 */
extern std::shared_ptr<inexor::vscript::VScriptSubsystem> vscript_subsystem;

#endif /* INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER */
