/*
 * Relationship.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_

#include "EntitySystemBase.h"

#include "EntityAttribute.h"
// #include "EntityInstance.h"
#include "RelationshipType.h"

class EntityInstance;

class RelationshipInstance
{
    public:
        RelationshipInstance();
        virtual ~RelationshipInstance();

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

        /**
         * The attributes of
         */
        std::map<std::string, CefRefPtr<EntityAttribute> > attributes;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipInstance);

};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_ */
