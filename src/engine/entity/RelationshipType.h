/*
 * RelationshipType.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_

#include "TypeBase.h"
#include "EntityType.h"

class RelationshipType : public TypeBase
{
    public:
        RelationshipType(std::string name, bool persist, bool synchronize);
        virtual ~RelationshipType();

    private:

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
