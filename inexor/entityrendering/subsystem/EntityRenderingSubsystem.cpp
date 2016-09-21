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

    void EntityRenderingSubsystem::Cleanup()
    {
    }

    void EntityRenderingSubsystem::Reset()
    {
    }

    void EntityRenderingSubsystem::RenderEntities()
    {

    }

    void EntityRenderingSubsystem::RenderRelationships()
    {

    }

}
}
}
