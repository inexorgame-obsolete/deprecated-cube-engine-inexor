/*
 * RelationshipInstanceManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipInstanceManager.h"

InstanceRefPtr<RelationshipInstance> RelationshipInstanceManager::CreateInstance(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node)
{
    InstanceRefPtr<RelationshipInstance> relationship_instance = new RelationshipInstance(relationship_type, start_node, end_node);
    relationship_instances[relationship_instance->GetUuid()] = relationship_instance;
    return relationship_instance;
}

InstanceRefPtr<RelationshipInstance> RelationshipInstanceManager::CreateInstance(std::string relationship_type_name, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node)
{
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(relationship_type_name);
    return CreateInstance(relationship_type, start_node, end_node);
}

bool RelationshipInstanceManager::Exists(std::string uuid)
{
    return relationship_instances.count(uuid);
}

InstanceRefPtr<RelationshipInstance> RelationshipInstanceManager::Get(std::string uuid)
{
    return relationship_instances[uuid];
}

std::list<InstanceRefPtr<RelationshipInstance> > RelationshipInstanceManager::GetAll(TypeRefPtr<RelationshipType> relationship_type)
{
    // TODO: implement
    // Iterate through all instances and check type (costly)
}

std::list<InstanceRefPtr<RelationshipInstance> > RelationshipInstanceManager::GetAll(std::string relationship_type_name)
{
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(relationship_type_name);
    return GetAll(relationship_type);
}


void RelationshipInstanceManager::DeleteInstance(InstanceRefPtr<RelationshipInstance> instance)
{
    relationship_instances.erase(instance->GetUuid());
}

void RelationshipInstanceManager::DeleteInstance(std::string uuid)
{
    relationship_instances.erase(uuid);
}


void RelationshipInstanceManager::DeleteAllInstances()
{
    relationship_instances.clear();
}

void RelationshipInstanceManager::DeleteAllInstances(TypeRefPtr<RelationshipType> relationship_type)
{
    // TODO: implement
    // Iterate through all instances and check type (costly), then remove instance
}

int RelationshipInstanceManager::Size() {
    return relationship_instances.size();
}
