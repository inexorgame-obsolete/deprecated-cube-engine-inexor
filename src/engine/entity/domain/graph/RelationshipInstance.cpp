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
    if (startNode->GetType()->IsA(type->GetStartNodeType())) {
        this->startNode = startNode;
    } else {
        logoutf("Start node not of expected type: (%s, %s)", type->GetStartNodeType()->GetName().c_str(), startNode->GetType()->GetName().c_str());
    }
    if (endNode->GetType()->IsA(type->GetEndNodeType())) {
        this->endNode = endNode;
    } else {
        logoutf("End node not of expected type: (%s, %s)", type->GetEndNodeType()->GetName().c_str(), endNode->GetType()->GetName().c_str());
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
    if (startNode->GetType()->IsA(type->GetStartNodeType())) {
        this->startNode = startNode;
    } else {
        logoutf("Start node not of expected type: (%s, %s)", type->GetStartNodeType()->GetName().c_str(), startNode->GetType()->GetName().c_str());
    }
    if (endNode->GetType()->IsA(type->GetEndNodeType())) {
        this->endNode = endNode;
    } else {
        logoutf("End node not of expected type: (%s, %s)", type->GetEndNodeType()->GetName().c_str(), endNode->GetType()->GetName().c_str());
    }
}
