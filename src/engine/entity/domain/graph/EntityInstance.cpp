/*
 * Entity.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityInstance.h"
#include "RelationshipInstance.h"

EntityInstance::EntityInstance(TypeRefPtr<EntityType> type) : type(type), InstanceBase()
{
}

EntityInstance::EntityInstance(TypeRefPtr<EntityType> type, std::string uuid) : type(type), InstanceBase(uuid)
{
}

EntityInstance::~EntityInstance()
{
}

/*
AttributeRefPtr EntityInstance::operator[](std::string key) const
{
    return attributes[key];
}

AttributeRefPtr & EntityInstance::operator[](std::string key)
{
    return attributes[key];
}
*/

void EntityInstance::AddOutgoingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance)
{
    // TODO: check first for key and create key if not exists!
    this->outgoing[relationship_type].push_back(relationship_instance);
}

void EntityInstance::AddIncomingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance)
{
    // TODO: check first for key and create key if not exists!
    this->incoming[relationship_type].push_back(relationship_instance);
}

std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetAllRelationships()
{
    // TODO: implement
}

std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type)
{
    // TODO: implement
}

std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetAllOutgoingRelationships()
{
    // TODO: implement
}

std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetAllOutgoingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type)
{
    // TODO: implement
}

std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetAllIncomingRelationships()
{
    // TODO: implement
}

std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetAllIncomingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type)
{
    // TODO: implement
}
