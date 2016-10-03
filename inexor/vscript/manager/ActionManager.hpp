#ifndef INEXOR_VSCRIPT_MANAGER_ACTION_MANAGER_HEADER
#define INEXOR_VSCRIPT_MANAGER_ACTION_MANAGER_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/vscript/action/PrintAction.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class ActionManager
    {
        public:

            ActionManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                         std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                         std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                         std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~ActionManager();

            /**
             * Updates the actions.
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
             * Creates a action type.
             */
            TypeRefPtr<EntityType> CreateActionType(std::string name, FunctionRefPtr propagation_function);

            /**
             * Creates an action entity.
             */
            InstanceRefPtr<EntityInstance> CreateAction(TypeRefPtr<EntityType> action_type, double x, double y, double z);

            /**
             * Removes an action entity.
             */
            void RemoveAction(InstanceRefPtr<EntityInstance> action);

            /**
             * Connects an event with a action.
             */
            InstanceRefPtr<RelationshipInstance> Connect(InstanceRefPtr<EntityInstance> previous_action, InstanceRefPtr<EntityInstance> next_action);

            /**
             * Executes the action.
             */
            void ExecuteAction(InstanceRefPtr<EntityInstance> action);

        private:

            /**
             * The base type for action types.
             */
            TypeRefPtr<EntityType> parent_action_type;

            /**
             * This map stores all action types.
             */
            std::unordered_map<std::string, TypeRefPtr<EntityType> > action_types;

            /**
             * The list of action entity instances.
             */
            std::vector<InstanceRefPtr<EntityInstance>> action_instances;

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
             * Relationship type: executes.
             */
            TypeRefPtr<RelationshipType> rel_executes;

    };

}
}

#endif /* INEXOR_VSCRIPT_MANAGER_ACTION_MANAGER_HEADER */
