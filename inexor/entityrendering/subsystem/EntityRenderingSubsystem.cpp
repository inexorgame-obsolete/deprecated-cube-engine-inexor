#include "EntityRenderingSubsystem.hpp"

namespace inexor {
namespace entity {
namespace rendering {

    EntityRenderingSubsystem::EntityRenderingSubsystem() : SubsystemBase(ENTITY_RENDERING_SUBSYSTEM)
    {
    }

    EntityRenderingSubsystem::EntityRenderingSubsystem(std::shared_ptr<EntityTypeManager> entity_type_manager,
                                       std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                                       std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                                       std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
        : SubsystemBase(ENTITY_RENDERING_SUBSYSTEM,
                        entity_type_manager,
                        entity_instance_manager,
                        relationship_type_manager,
                        relationship_instance_manager)
    {
    }

    EntityRenderingSubsystem::~EntityRenderingSubsystem()
    {
    }

    void EntityRenderingSubsystem::Update(TimeStep time_step)
    {
        // logoutf("EntityRenderingSubsystem::Update() elapsed_millis: %d time_factor: %2.3f time_unit: %4.1f", time_step.elapsed_millis, time_step.time_factor, time_step.time_unit);
    }

    void EntityRenderingSubsystem::InitializeModel()
    {
        renders_entity = relationship_type_manager->Create(REL_RENDERS_ENTITY, true, true, ENT_ANY, ENT_ANY);
        spdlog::get("global")->debug() << "Entity rendering subsystem graph model initialized";
    }

    void EntityRenderingSubsystem::Cleanup()
    {
    }

    void EntityRenderingSubsystem::Reset()
    {
    }

    void EntityRenderingSubsystem::CreateEntityRenderer(TypeRefPtr<EntityType> renderer_type)
    {
        InstanceRefPtr<EntityInstance> entity_renderer_instance = entity_instance_manager->Create(renderer_type);
        entity_renderers.push_back(entity_renderer_instance);
        // TODO: configure the entity renderer instance
    }

    void EntityRenderingSubsystem::ConnectEntityRenderer(InstanceRefPtr<EntityInstance> entity_renderer_instance, InstanceRefPtr<EntityInstance> entity_instance)
    {
        // TODO: connect the renderer instance with another entity instance which shall be rendered
    }

    // EntityRenderer --[renders_entity]--> EntityOfAnyType
    void EntityRenderingSubsystem::RenderEntities()
    {
        std::vector<InstanceRefPtr<EntityInstance> >::iterator it = entity_renderers.begin();
        while (it != entity_renderers.end())
        {
            std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = (*it)->outgoing[renders_entity->uuid].begin();
            TimeStep time_step(0.0, 1000.0);
            FunctionRefPtr function = (*it)->GetType()[FUNC_RENDERS_ENTITY_ATTRIBUTE_NAME]->functionVal;
            function->Before(time_step, (*it));
            while (it2 != (*it)->outgoing[renders_entity->uuid].end())
            {
                // This calls the actual entity renderer code; which is an
                // EntityFunction, for example BoxRenderer::Execute()
                function->Execute(time_step, (*it), (*it2)->endNode);
                ++it2;
            }
            function->After(time_step, (*it));
            ++it;
        }
    }

    void EntityRenderingSubsystem::RenderRelationships()
    {

    }

}
}
}
