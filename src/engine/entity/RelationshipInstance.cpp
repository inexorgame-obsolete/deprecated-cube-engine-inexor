/*
 * Relationship.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipInstance.h"
#include "EntityInstance.h"

RelationshipInstance::RelationshipInstance(
    TypeRefPtr<RelationshipType> type,
    InstanceRefPtr<EntityInstance> startNode,
    InstanceRefPtr<EntityInstance> endNode
) : type(type),
    InstanceBase()
{
    // Type checks
    if (startNode->GetType()->GetUuid() == type->GetStartNodeType()->GetUuid()) {
        this->startNode = startNode;
    }
    if (endNode->GetType()->GetUuid() == type->GetEndNodeType()->GetUuid()) {
        this->endNode = endNode;
    }
}

RelationshipInstance::RelationshipInstance(
    TypeRefPtr<RelationshipType> type,
    InstanceRefPtr<EntityInstance> startNode,
    InstanceRefPtr<EntityInstance> endNode,
    std::string uuid
) : type(type),
    InstanceBase(uuid)
{
    // Type checks
    if (startNode->GetType()->GetUuid() == type->GetStartNodeType()->GetUuid()) {
        this->startNode = startNode;
    }
    if (endNode->GetType()->GetUuid() == type->GetEndNodeType()->GetUuid()) {
        this->endNode = endNode;
    }
}
