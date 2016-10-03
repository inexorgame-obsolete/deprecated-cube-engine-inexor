#ifndef INEXOR_VSCRIPT_MANAGER_EVENT_MANAGER_HEADER
#define INEXOR_VSCRIPT_MANAGER_EVENT_MANAGER_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/vscript/event/OnMemoryChangedEvent.hpp"
#include "inexor/vscript/manager/ActionManager.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class EventManager
    {
        public:

            EventManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                         std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                         std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                         std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager,
                         std::shared_ptr<ActionManager> action_manager);
            virtual ~EventManager();

            /**
             * Updates the events.
             */
            void Update(TimeStep time_step);

            /**
             * Cleanup the visual scripting subsystem.
             */
            void Cleanup();

            /**
             * Resets the visual scripting subsystem.
             */
            void Reset();

            /**
             * Creates a event type.
             */
            TypeRefPtr<EntityType> CreateEventType(std::string name, FunctionRefPtr propagation_function);

            /**
             * Creates an event entity.
             */
            InstanceRefPtr<EntityInstance> CreateEvent(TypeRefPtr<EntityType> event_type, double x, double y, double z);

            /**
             * Removes an event entity.
             */
            void RemoveEvent(InstanceRefPtr<EntityInstance> event);

            /**
             * Connects an event with a action.
             */
            InstanceRefPtr<RelationshipInstance> Connect(InstanceRefPtr<EntityInstance> event, InstanceRefPtr<EntityInstance> action);

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
             * The list of event entity instances.
             */
            std::vector<InstanceRefPtr<EntityInstance>> event_instances;

            /**
             * The local reference of the entity type manager.
             */
            std::shared_ptr<EntityTypeManager> entity_type_manager;

            /**
             * The local reference of the entity instance manager.
             */
            std::shared_ptr<EntityInstanceManager> entity_instance_manager;

            /**
             * The local reference of the relationship type manager.
             */
            std::shared_ptr<RelationshipTypeManager> relationship_type_manager;

            /**
             * The local reference of the relationship instance manager.
             */
            std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager;

            /**
             * The local reference of the action manager.
             */
            std::shared_ptr<ActionManager> action_manager;

            /**
             * Relationship type: executes.
             */
            TypeRefPtr<RelationshipType> rel_executes;

    };

}
}

#endif /* INEXOR_VSCRIPT_MANAGER_EVENT_MANAGER_HEADER */
