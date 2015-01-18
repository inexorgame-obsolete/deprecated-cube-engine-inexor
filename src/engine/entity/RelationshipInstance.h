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
        RelationshipInstance();
        virtual ~RelationshipInstance();

        CefRefPtr<RelationshipType> GetType() { return type; };

        CefRefPtr<EntityInstance> Parent() { return parent; };

        CefRefPtr<EntityInstance> Child() { return child; };

    protected:

        /**
         * The relationship type.
         */
        CefRefPtr<RelationshipType> type;

        /**
         * The start node is an entity instance.
         */
        CefRefPtr<EntityInstance> parent;

        /**
         * The end node is an entity instance.
         */
        CefRefPtr<EntityInstance> child;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipInstance);

};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_ */
