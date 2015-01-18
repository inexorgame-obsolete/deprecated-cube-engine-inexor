/*
 * Entity.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_
#define SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_

#include "EntitySystemBase.h"
#include "InstanceBase.h"

#include "EntityAttribute.h"
#include "EntityType.h"

class RelationshipInstance;

class EntityInstance : public InstanceBase
{
    public:
        EntityInstance(CefRefPtr<EntityType> type);
        virtual ~EntityInstance();

        CefRefPtr<EntityType> GetType() { return type; };
        std::list<CefRefPtr<RelationshipInstance> > GetRelationships() { return relationships; };

    protected:
        /**
        std::string type;
        bool persist;
        float x, y, z;
        */

        /**
         * The entity type.
         */
        CefRefPtr<EntityType> type;

        /**
         * The relationships.
         */
        std::list<CefRefPtr<RelationshipInstance> > relationships;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityInstance);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_ */
