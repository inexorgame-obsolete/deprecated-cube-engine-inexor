/*
 * Relationship.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipInstance.h"
#include "EntityInstance.h"

RelationshipInstance::RelationshipInstance(CefRefPtr<RelationshipType> type, CefRefPtr<EntityInstance> startNode, CefRefPtr<EntityInstance> endNode)
    : type(type)
{
    // Type checks
    if (startNode->GetType()->GetUuid() == type->GetStartNodeType()->GetUuid()) {
        this->startNode = startNode;
    }
    if (endNode->GetType()->GetUuid() == type->GetEndNodeType()->GetUuid()) {
        this->endNode = endNode;
    }
}

RelationshipInstance::~RelationshipInstance()
{
}

