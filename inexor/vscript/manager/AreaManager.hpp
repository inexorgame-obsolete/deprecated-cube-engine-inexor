#ifndef INEXOR_VSCRIPT_MANAGER_AREA_MANAGER_HEADER
#define INEXOR_VSCRIPT_MANAGER_AREA_MANAGER_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class AreaManager
    {
        public:

            AreaManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                         std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                         std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                         std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~AreaManager();

            /**
             * Updates the areas.
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
             * Creates a area type.
             */
            TypeRefPtr<EntityType> CreateAreaType(std::string name, FunctionRefPtr propagation_function);

            /**
             * Creates an area entity.
             */
            InstanceRefPtr<EntityInstance> CreateArea(TypeRefPtr<EntityType> area_type, double x, double y, double z);

            /**
             * Removes an area entity.
             */
            void RemoveArea(InstanceRefPtr<EntityInstance>);

        private:

            /**
             * The base type for area types.
             */
            TypeRefPtr<EntityType> parent_area_type;

            /**
             * This map stores all area types.
             */
            std::unordered_map<std::string, TypeRefPtr<EntityType> > area_types;

            /**
             * The list of area entity instances.
             */
            std::vector<InstanceRefPtr<EntityInstance>> area_instances;

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

#endif /* INEXOR_VSCRIPT_MANAGER_AREA_MANAGER_HEADER */
