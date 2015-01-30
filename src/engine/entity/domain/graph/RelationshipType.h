/*
 * RelationshipType.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_

#include "../TypeBase.h"
#include "../TypeRefPtr.h"
#include "EntityType.h"

class RelationshipType : public TypeBase
{
    public:
        RelationshipType(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);
        virtual ~RelationshipType();

        CefRefPtr<EntityType> GetStartNodeType() { return this->startNodeType; };
        void SetStartNodeType(CefRefPtr<EntityType> startNodeType) { this->startNodeType = startNodeType; };
        CefRefPtr<EntityType> GetEndNodeType() { return this->endNodeType; };
        void SetEndNodeType(CefRefPtr<EntityType> startNodeType) { this->endNodeType = endNodeType; };

    private:

        /**
         * The entity type of the start node.
         */
        TypeRefPtr<EntityType> startNodeType;

        /**
         * The entity type of the end node.
         */
        TypeRefPtr<EntityType> endNodeType;

        void operator()(EntityInstance* inst);

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipType);
};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_ */
