/*
 * SubsystemBase.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "SubsystemBase.hpp"

namespace inexor {
namespace entity {

    SubsystemBase::SubsystemBase(std::string name)
      : name(name),
        paused(false)
    {
    }

    SubsystemBase::SubsystemBase(std::string name,
                                 std::shared_ptr<EntityTypeManager> entity_type_manager,
                                 std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                                 std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                                 std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
      : name(name),
        paused(false),
        entity_type_manager(entity_type_manager),
        entity_instance_manager(entity_instance_manager),
        relationship_type_manager(relationship_type_manager),
        relationship_instance_manager(relationship_instance_manager)
    {
    }

    void SubsystemBase::Update(TimeStep time_step)
    {
        spdlog::get("global")->debug() << "SubsystemBase::Update() elapsed_millis: %d time_factor: %2.3f time_unit: %4.1f", time_step.elapsed_millis, time_step.time_factor, time_step.time_unit;
    }

    void SubsystemBase::Cleanup()
    {
    }

    void SubsystemBase::Reset()
    {
    }

    std::string SubsystemBase::GetName()
    {
        return name;
    }

    void SubsystemBase::SetName(std::string)
    {
        this->name = name;
    }

    void SubsystemBase::SetEntityTypeManager(std::shared_ptr<EntityTypeManager> entity_type_manager)
    {
        this->entity_type_manager = entity_type_manager;
    }

    void SubsystemBase::SetEntityInstanceManager(std::shared_ptr<EntityInstanceManager> entity_instance_manager)
    {
        this->entity_instance_manager = entity_instance_manager;
    }

    void SubsystemBase::SetRelationshipTypeManager(std::shared_ptr<RelationshipTypeManager> relationship_type_manager)
    {
        this->relationship_type_manager = relationship_type_manager; 
    }

    void SubsystemBase::SetRelationshipInstanceManager(std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
    {
        this->relationship_instance_manager = relationship_instance_manager;
    }

}
}
