#include "EventManager.hpp"

namespace inexor {
namespace vscript {

    EventManager::EventManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                               std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                               std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                               std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager,
                               std::shared_ptr<ActionManager> action_manager)
      : entity_type_manager(entity_type_manager),
        entity_instance_manager(entity_instance_manager),
        relationship_type_manager(relationship_type_manager),
        relationship_instance_manager(relationship_instance_manager),
        action_manager(action_manager)
    {
        rel_executes = relationship_type_manager->Get(REL_TYPE_EXECUTES);

        parent_event_type = entity_type_manager->Create(ENT_TYPE_EVENT, true, true);

        FunctionRefPtr on_memory_changed_function = std::make_shared<OnMemoryChangedEvent>();
        CreateEventType(ENT_TYPE_EVENT_ON_MEMORY_CHANGED, on_memory_changed_function);
    }

    EventManager::~EventManager()
    {
    }

    void EventManager::Update(TimeStep time_step)
    {
        // spdlog::get("global")->info() << "EventManager::Update";
        // Iterates over all events
        // spdlog::get("global")->info() << "events: " << event_instances.size();
        std::vector<InstanceRefPtr<EntityInstance> >::iterator it = event_instances.begin();
        while (it != event_instances.end())
        {
            spdlog::get("global")->info() << "Check event " << (*it)->uuid;

            // First check if event fires
            FunctionRefPtr execute_function = (*it)->GetAttribute(ENT_FUNC_EVENT_CHECK)->functionVal;
            if(execute_function)
            {
                AttributeRefPtr return_value = execute_function->Execute(time_step, (*it));
                if (return_value->GetBool()) {

                    // The event fires, which means we follow all outgoing relationships of type executes.
                    /*
                    std::list<InstanceRefPtr<RelationshipInstance> > outgoing = (*it)->GetAllOutgoingRelationshipsOfType(rel_executes);
                    std::vector<InstanceRefPtr<RelationshipInstance> >::iterator it2 = outgoing.begin();
                    while (it2 != (*it)->outgoing.end())
                    {
                        action_manager->ExecuteAction(*it);
                        ++it2;
                    }
                    */
                }
            }
            ++it;

        }
    }

    void EventManager::Cleanup()
    {
        spdlog::get("global")->info() << "EventManager::Cleanup";
    }

    void EventManager::Reset()
    {
        spdlog::get("global")->info() << "EventManager::Reset";
    }

    TypeRefPtr<EntityType> EventManager::CreateEventType(std::string name, FunctionRefPtr check_function)
    {
        TypeRefPtr<EntityType> event_type = entity_type_manager->Create(name, true, true, parent_event_type);
        event_type[ENT_FUNC_EVENT_CHECK]->functionVal = check_function;
        event_types[name] = event_type;
        return event_type;
    }

    InstanceRefPtr<EntityInstance> EventManager::CreateEvent(TypeRefPtr<EntityType> event_entity_type, double x, double y, double z)
    {
        InstanceRefPtr<EntityInstance> event_entity_instance = entity_instance_manager->Create(event_entity_type);
        event_entity_instance["x"] = x;
        event_entity_instance["y"] = y;
        event_entity_instance["z"] = z;
        event_instances.push_back(event_entity_instance);
        return event_entity_instance;
    }

    void EventManager::RemoveEvent(InstanceRefPtr<EntityInstance>)
    {
        // TODO: implement
        // Remove instance and all relationships
    }

    InstanceRefPtr<RelationshipInstance> EventManager::Connect(InstanceRefPtr<EntityInstance> event, InstanceRefPtr<EntityInstance> action)
    {
        return relationship_instance_manager->CreateInstance(rel_executes, event, action);
    }

}
}
