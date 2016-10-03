#ifndef INEXOR_VSCRIPT_MANAGER_OPERATOR_MANAGER_HEADER
#define INEXOR_VSCRIPT_MANAGER_OPERATOR_MANAGER_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class OperatorManager
    {
        public:

            OperatorManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                         std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                         std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                         std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~OperatorManager();

            /**
             * Updates the operators.
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
             * Creates a operator type.
             */
            TypeRefPtr<EntityType> CreateOperatorType(std::string name, FunctionRefPtr propagation_function);

            /**
             * Creates an operator entity.
             */
            InstanceRefPtr<EntityInstance> CreateOperator(TypeRefPtr<EntityType> operator_type, double x, double y, double z);

            /**
             * Removes an operator entity.
             */
            void RemoveOperator(InstanceRefPtr<EntityInstance>);

        private:

            /**
             * The base type for operator types.
             */
            TypeRefPtr<EntityType> parent_operator_type;

            /**
             * This map stores all operator types.
             */
            std::unordered_map<std::string, TypeRefPtr<EntityType> > operator_types;

            /**
             * The list of operator entity instances.
             */
            std::vector<InstanceRefPtr<EntityInstance>> operator_instances;

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

    };

}
}

#endif /* INEXOR_VSCRIPT_MANAGER_OPERATOR_MANAGER_HEADER */
