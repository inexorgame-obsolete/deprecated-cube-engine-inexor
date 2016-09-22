#ifndef INEXOR_ENTITY_RENDERING_SUBSYSTEM_HEADER
#define INEXOR_ENTITY_RENDERING_SUBSYSTEM_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/model/EntityModel.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/entityrendering/model/EntityRenderingModel.hpp"

using namespace inexor::entity;

namespace inexor {
namespace entity {
namespace rendering {

    /**
     * This subsystems manages the entity rendering.
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
             * Initializes the entity rendering graph model.
             */
            void InitializeModel();

            /**
             *
             */
            void Cleanup();

            /**
             *
             */
            void Reset();

            /**
             * Creates a entity renderer instance of the given renderer type.
             * For example, create a blue box renderer of type ColouredBoxRenderer.
             */
            void CreateEntityRenderer(TypeRefPtr<EntityType> renderer_type);
            void ConnectEntityRenderer(InstanceRefPtr<EntityInstance> entity_renderer_instance, InstanceRefPtr<EntityInstance> entity_instance);

            /**
             * Renders the entities.
             */
            void RenderEntities();

            /**
             * Renders the relationships.
             */
            void RenderRelationships();

        private:

            /**
             * The entity renderers.
             */
            std::vector<InstanceRefPtr<EntityInstance> > entity_renderers;

            /**
             * The relationship renderers.
             */
            std::vector<InstanceRefPtr<EntityInstance> > relationship_renderers;

            /**
             * The relationship type which connects an entity renderer instance
             * with another entity instance which shall be rendered by the renderer
             * instance.
             */
            TypeRefPtr<RelationshipType> renders_entity;

    };

}
}
}

#endif /* INEXOR_ENTITY_RENDERING_SUBSYSTEM_HEADER */
