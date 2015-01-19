/*
 * Relationship.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_

#include "EntitySystemBase.h"
#include "InstanceBase.h"

#include "EntityAttribute.h"
#include "RelationshipType.h"

class EntityInstance;

class RelationshipInstance : public InstanceBase
{
    public:
        RelationshipInstance(CefRefPtr<RelationshipType> type, CefRefPtr<EntityInstance> startNode, CefRefPtr<EntityInstance> endNode);
        virtual ~RelationshipInstance();

        CefRefPtr<RelationshipType> GetType() { return type; };

        CefRefPtr<EntityInstance> GetStartNode() { return startNode; };

        CefRefPtr<EntityInstance> GetEndNode() { return endNode; };

    protected:

        /**
         * The relationship type.
         */
        CefRefPtr<RelationshipType> type;

        /**
         * The start node (parent node) is an entity instance.
         */
        CefRefPtr<EntityInstance> startNode;

        /**
         * The end node (child node) is an entity instance.
         */
        CefRefPtr<EntityInstance> endNode;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipInstance);

};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_ */
