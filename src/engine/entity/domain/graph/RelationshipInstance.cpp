/*
 * Relationship.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipInstance.h"
#include "EntityInstance.h"

namespace inexor {
namespace entity {

RelationshipInstance::RelationshipInstance(
    TypeRefPtr<RelationshipType> type,
    InstanceRefPtr<EntityInstance> startNode,
    InstanceRefPtr<EntityInstance> endNode
) : InstanceBase(),
    type(type)
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
) : InstanceBase(uuid),
    type(type)
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

RelationshipInstance::~RelationshipInstance()
{
}

TypeRefPtr<RelationshipType> RelationshipInstance::GetType()
{
    return type;
}

InstanceRefPtr<EntityInstance> RelationshipInstance::GetStartNode()
{
    return startNode;
}

InstanceRefPtr<EntityInstance> RelationshipInstance::GetEndNode()
{
    return endNode;
}

}
}
