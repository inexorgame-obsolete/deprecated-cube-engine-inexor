/*
 * EntityInstanceManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "EntityInstanceManager.h"

InstanceRefPtr<EntityInstance> EntityInstanceManager::Create(TypeRefPtr<EntityType> entity_type)
{
    InstanceRefPtr<EntityInstance> entity_instance = new EntityInstance(entity_type);
    entity_instances[entity_instance->GetUuid()] = entity_instance;
    return entity_instance;
}

InstanceRefPtr<EntityInstance> EntityInstanceManager::Create(std::string entity_type_name)
{
    TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(entity_type_name);
    InstanceRefPtr<EntityInstance> entity_instance = new EntityInstance(entity_type);
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

std::list<InstanceRefPtr<EntityInstance> > EntityInstanceManager::GetAll(TypeRefPtr<EntityType> entity_type)
{
    // TODO: implement
    // Iterate through all instances and check type (costly)
}

std::list<InstanceRefPtr<EntityInstance> > EntityInstanceManager::GetAll(std::string entity_type_name)
{
    TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(entity_type_name);
    return GetAll(entity_type);
}

void EntityInstanceManager::DeleteInstance(InstanceRefPtr<EntityInstance> instance)
{
    entity_instances.erase(instance->GetUuid());
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
    // TODO: implement
    // Iterate through all instances and check type (costly), then remove instance
}

int EntityInstanceManager::Size() {
    return entity_instances.size();
}
