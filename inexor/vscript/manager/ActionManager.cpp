#include "ActionManager.hpp"

namespace inexor {
namespace vscript {

    ActionManager::ActionManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                               std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                               std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                               std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
      : entity_type_manager(entity_type_manager),
        entity_instance_manager(entity_instance_manager),
        relationship_type_manager(relationship_type_manager),
        relationship_instance_manager(relationship_instance_manager)
    {
        rel_executes = relationship_type_manager->Get(REL_TYPE_EXECUTES);

        parent_action_type = entity_type_manager->Create(ENT_TYPE_ACTION, true, true);

        FunctionRefPtr print_function = std::make_shared<PrintAction>();
        CreateActionType(ENT_TYPE_ACTION_PRINT, print_function);
    }

    ActionManager::~ActionManager()
    {
    }

    void ActionManager::Update(TimeStep time_step)
    {
        spdlog::get("global")->info() << "ActionManager::Update";
    }

    void ActionManager::Cleanup()
    {
        spdlog::get("global")->info() << "ActionManager::Cleanup";
    }

    void ActionManager::Reset()
    {
        spdlog::get("global")->info() << "ActionManager::Reset";
    }

    TypeRefPtr<EntityType> ActionManager::CreateActionType(std::string name, FunctionRefPtr action_function)
    {
        TypeRefPtr<EntityType> action_type = entity_type_manager->Create(name, true, true, parent_action_type);
        action_type[ENT_TYPE_ATTR_PROPAGATE]->functionVal = action_function;
        action_types[name] = action_type;
        return action_type;
    }

    InstanceRefPtr<EntityInstance> ActionManager::CreateAction(TypeRefPtr<EntityType> action_entity_type, double x, double y, double z)
    {
        InstanceRefPtr<EntityInstance> action_entity_instance = entity_instance_manager->Create(action_entity_type);
        action_entity_instance["x"] = x;
        action_entity_instance["y"] = y;
        action_entity_instance["z"] = z;
        action_instances.push_back(action_entity_instance);
        return action_entity_instance;
    }

    void ActionManager::RemoveAction(InstanceRefPtr<EntityInstance>)
    {
        // TODO: implement
        // Remove instance and all relationships
    }

    InstanceRefPtr<RelationshipInstance> ActionManager::Connect(InstanceRefPtr<EntityInstance> previous_action, InstanceRefPtr<EntityInstance> next_action)
    {
        return relationship_instance_manager->CreateInstance(rel_executes, previous_action, next_action);
    }

    void ActionManager::ExecuteAction(InstanceRefPtr<EntityInstance> action)
    {
        spdlog::get("global")->info() << "ExecuteAction uuid: " << action->uuid;

        // TODO: call all following
    }

}
}
