/*
 * Relationship.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_

#include "EntitySystemBase.h"
#include "EntityInstance.h"
#include "EntityAttribute.h"
#include "InstanceBase.h"
#include "RelationshipType.h"

class EntityInstance;

class RelationshipInstance : public InstanceBase
{
    public:
        RelationshipInstance(TypeRefPtr<RelationshipType> type, InstanceRefPtr<EntityInstance> startNode, InstanceRefPtr<EntityInstance> endNode);
        RelationshipInstance(TypeRefPtr<RelationshipType> type, InstanceRefPtr<EntityInstance> startNode, InstanceRefPtr<EntityInstance> endNode, std::string uuid);
        virtual ~RelationshipInstance() {};

        TypeRefPtr<RelationshipType> GetType() { return type; };

        InstanceRefPtr<EntityInstance> GetStartNode() { return startNode; };

        InstanceRefPtr<EntityInstance> GetEndNode() { return endNode; };

    protected:

        /**
         * The relationship type.
         */
        TypeRefPtr<RelationshipType> type;

        /**
         * The start node (parent node) is an entity instance.
         */
        InstanceRefPtr<EntityInstance> startNode;

        /**
         * The end node (child node) is an entity instance.
         */
        InstanceRefPtr<EntityInstance> endNode;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipInstance);

};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_ */
