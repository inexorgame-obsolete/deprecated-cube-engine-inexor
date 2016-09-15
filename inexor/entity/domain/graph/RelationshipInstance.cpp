/*
 * Relationship.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipInstance.hpp"
#include "EntityInstance.hpp"

namespace inexor {
namespace entity {

    RelationshipInstance::RelationshipInstance(
        TypeRefPtr<RelationshipType> type,
        InstanceRefPtr<EntityInstance> startNode,
        InstanceRefPtr<EntityInstance> endNode
    ) : InstanceBase(),
        alive(true),
        type(type)
    {
        // Type checks
        if (type->start_node_type == NULL || startNode->type->IsA(type->start_node_type)) {
            this->startNode = startNode;
        } else {
            logoutf("Start node not of expected type: (%s, %s)", type->start_node_type->name.c_str(), startNode->type->name.c_str());
        }
        if (type->end_node_type == NULL || endNode->type->IsA(type->end_node_type)) {
            this->endNode = endNode;
        } else {
            logoutf("End node not of expected type: (%s, %s)", type->end_node_type->name.c_str(), endNode->type->name.c_str());
        }
    }

    RelationshipInstance::RelationshipInstance(
        TypeRefPtr<RelationshipType> type,
        InstanceRefPtr<EntityInstance> startNode,
        InstanceRefPtr<EntityInstance> endNode,
        std::string uuid
    ) : InstanceBase(uuid),
        alive(true),
        type(type)
    {
        // Type checks
        if (type->start_node_type != NULL || startNode->type->IsA(type->start_node_type)) {
            this->startNode = startNode;
        } else {
            logoutf("Start node not of expected type: (%s, %s)", type->start_node_type->name.c_str(), startNode->type->name.c_str());
        }
        if (type->end_node_type != NULL || endNode->type->IsA(type->end_node_type)) {
            this->endNode = endNode;
        } else {
            logoutf("End node not of expected type: (%s, %s)", type->end_node_type->name.c_str(), endNode->type->name.c_str());
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
