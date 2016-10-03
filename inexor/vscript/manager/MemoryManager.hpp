#ifndef INEXOR_VSCRIPT_MANAGER_MEMORY_MANAGER_HEADER
#define INEXOR_VSCRIPT_MANAGER_MEMORY_MANAGER_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class MemoryManager
    {
        public:

            MemoryManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                         std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                         std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                         std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~MemoryManager();

            /**
             * Updates the memorys.
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
             * Creates a memory type.
             */
            TypeRefPtr<EntityType> CreateMemoryType(std::string name, FunctionRefPtr propagation_function);

            /**
             * Creates an memory entity.
             */
            InstanceRefPtr<EntityInstance> CreateMemory(TypeRefPtr<EntityType> memory_type, double x, double y, double z);

            /**
             * Removes an memory entity.
             */
            void RemoveMemory(InstanceRefPtr<EntityInstance>);

        private:

            /**
             * The base type for memory types.
             */
            TypeRefPtr<EntityType> parent_memory_type;

            /**
             * This map stores all memory types.
             */
            std::unordered_map<std::string, TypeRefPtr<EntityType> > memory_types;

            /**
             * The list of memory entity instances.
             */
            std::vector<InstanceRefPtr<EntityInstance>> memory_instances;

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

#endif /* INEXOR_VSCRIPT_MANAGER_MEMORY_MANAGER_HEADER */
