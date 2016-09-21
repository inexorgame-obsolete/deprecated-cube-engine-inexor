#ifndef INEXOR_ENTITY_RENDERING_SUBSYSTEM_HEADER
#define INEXOR_ENTITY_RENDERING_SUBSYSTEM_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"

#define ENTITY_RENDERING_SUBSYSTEM "entity_rendering"

using namespace inexor::entity;

namespace inexor {
namespace entity {
namespace rendering {

    /**
     * This subsystems manages 3D visual scripting.
     */
    class EntityRenderingSubsystem : public SubsystemBase
    {
        public:

            EntityRenderingSubsystem();
            
            /**
             *
             */
            EntityRenderingSubsystem(std::shared_ptr<EntityTypeManager> entity_type_manager,
                             std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                             std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                             std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~EntityRenderingSubsystem();

            /**
            *
            */
            void Update(TimeStep time_step);

            /**
             *
             */
            void Cleanup();

            /**
             *
             */
            void Reset();

            /**
             * Renders the entities.
             */
            void RenderEntities();

            /**
             * Renders the relationships.
             */
            void RenderRelationships();

    };

}
}
}

#endif /* INEXOR_ENTITY_RENDERING_SUBSYSTEM_HEADER */
