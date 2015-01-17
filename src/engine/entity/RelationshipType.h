/*
 * RelationshipType.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_

#include "EntitySystemBase.h"

#include "EntityAction.h"
#include "EntityAttribute.h"
#include "EntityType.h"

class RelationshipType
{
    public:
        RelationshipType(std::string name, bool persist, bool synchronize);
        virtual ~RelationshipType();

    private:

        /**
         * The unique identifier of this relationship type.
         */
        std::string uuid;

        /**
         * The name of the relationship type.
         */
        std::string name;

        /**
         * Relationship instances of this type should be persisted.
         */
        bool persist;

        /**
         * Relationship instances of this type should be synchronized.
         */
        bool synchronize;

        /**
         * The attributes of the relationship type.
         */
        std::map<std::string, CefRefPtr<EntityAttribute> > attributes;

        /**
         * The actions which are available on relationship instances of this relationship type.
         */
        std::map<std::string, CefRefPtr<EntityAction> > actions;

        /**
         * The entity type of the start node.
         */
        CefRefPtr<EntityType> startNodeType;

        /**
         * The entity type of the end node.
         */
        CefRefPtr<EntityType> endNodeType;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipType);
};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_ */
