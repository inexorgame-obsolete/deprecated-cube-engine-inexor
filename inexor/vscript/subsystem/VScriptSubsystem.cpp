#include "VScriptSubsystem.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    VScriptSubsystem::VScriptSubsystem()
        : SubsystemBase(SUBSYSTEM_VSCRIPT)
    {
    }

    VScriptSubsystem::VScriptSubsystem(std::shared_ptr<EntityTypeManager> entity_type_manager,
                                       std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                                       std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                                       std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
      : SubsystemBase(SUBSYSTEM_VSCRIPT,
                      entity_type_manager,
                      entity_instance_manager,
                      relationship_type_manager,
                      relationship_instance_manager)
    {
        action_manager = std::make_shared<ActionManager>(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
        area_manager = std::make_shared<AreaManager>(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
        event_manager = std::make_shared<EventManager>(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager, action_manager);
        memory_manager = std::make_shared<MemoryManager>(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
        operator_manager = std::make_shared<OperatorManager>(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);

        relationship_type_manager->Create(REL_TYPE_EXECUTES, ENT_ANY, ENT_TYPE_ACTION);
    }

    VScriptSubsystem::~VScriptSubsystem()
    {
    }

    void VScriptSubsystem::Update(TimeStep time_step)
    {
        event_manager->Update(time_step);
    }

    void VScriptSubsystem::Cleanup()
    {
        action_manager->Cleanup();
        area_manager->Cleanup();
        event_manager->Cleanup();
        memory_manager->Cleanup();
        operator_manager->Cleanup();
    }

    void VScriptSubsystem::Reset()
    {
        action_manager->Reset();
        area_manager->Reset();
        event_manager->Reset();
        memory_manager->Reset();
        operator_manager->Reset();
    }

    std::shared_ptr<ActionManager> VScriptSubsystem::GetActionManager()
    {
        return action_manager;
    }

    std::shared_ptr<AreaManager> VScriptSubsystem::GetAreaManager()
    {
        return area_manager;
    }

    std::shared_ptr<EventManager> VScriptSubsystem::GetEventManager()
    {
        return event_manager;
    }

    std::shared_ptr<MemoryManager> VScriptSubsystem::GetMemoryManager()
    {
        return memory_manager;
    }

    std::shared_ptr<OperatorManager> VScriptSubsystem::GetOperatorManager()
    {
        return operator_manager;
    }

}
}
