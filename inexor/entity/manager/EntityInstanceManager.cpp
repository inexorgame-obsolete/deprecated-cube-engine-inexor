/*
 * EntityInstanceManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "EntityInstanceManager.hpp"

namespace inexor {
namespace entity {

    InstanceRefPtr<EntityInstance> EntityInstanceManager::Create(TypeRefPtr<EntityType> entity_type)
    {
        InstanceRefPtr<EntityInstance> entity_instance = std::make_shared<EntityInstance>(entity_type);
        entity_instances[entity_instance->uuid] = entity_instance;
        return entity_instance;
    }

    InstanceRefPtr<EntityInstance> EntityInstanceManager::Create(std::string entity_type_name)
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(entity_type_name);
        InstanceRefPtr<EntityInstance> entity_instance = std::make_shared<EntityInstance>(entity_type);
        return entity_instance;
    }

    InstanceRefPtr<EntityInstance> EntityInstanceManager::Create(InstanceRefPtr<EntityInstance> entity_instance)
    {
        entity_instances[entity_instance->uuid] = entity_instance;
        return entity_instance;
    }

    InstanceRefPtr<EntityInstance> EntityInstanceManager::CreateUnmanagedInstance(TypeRefPtr<EntityType> entity_type)
    {
        InstanceRefPtr<EntityInstance> entity_instance = std::make_shared<EntityInstance>(entity_type);
        return entity_instance;
    }

    bool EntityInstanceManager::Exists(std::string uuid)
    {
        return entity_instances.count(uuid);
    }

    InstanceRefPtr<EntityInstance> EntityInstanceManager::Get(std::string uuid)
    {
        return entity_instances[uuid];
    }

    /*
    std::list<InstanceRefPtr<EntityInstance> > EntityInstanceManager::GetAll(TypeRefPtr<EntityType> entity_type)
    {
        // TODO: implement
        // Iterate through all instances and check type (costly)
    }
    */

    /*
    std::list<InstanceRefPtr<EntityInstance> > EntityInstanceManager::GetAll(std::string entity_type_name)
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(entity_type_name);
        return GetAll(entity_type);
    }
    */

    void EntityInstanceManager::DeleteInstance(InstanceRefPtr<EntityInstance> instance)
    {
        entity_instances.erase(instance->uuid);
    }

    void EntityInstanceManager::DeleteInstance(std::string uuid)
    {
        entity_instances.erase(uuid);
    }

    void EntityInstanceManager::DeleteAllInstances()
    {
        entity_instances.clear();
    }

    void EntityInstanceManager::DeleteAllInstances(TypeRefPtr<EntityType> entity_type)
    {
        auto it = entity_instances.begin();
        while (it != entity_instances.end())
        {
            // This check removes an instance if the entity type equals the given
            // entity type or it's parent entity_type.
            if (it->second->GetType()->IsA(entity_type))
            {
                it = entity_instances.erase(it);
            } else {
                ++it;
            }
        }
    }

    int EntityInstanceManager::Size()
    {
        return entity_instances.size();
    }

}
}
