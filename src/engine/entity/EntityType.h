/*
 * EntityType.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYTYPE_H_
#define SRC_ENGINE_ENTITY_ENTITYTYPE_H_

#include <string>
#include <map>

#include "EntitySystem.h"

#include "EntityAttribute.h"
#include "EntityAction.h"

class EntityType
{
    public:
        EntityType(std::string name, bool persist, bool synchronize);
        virtual ~EntityType();

    private:

        /**
         * The unique identifier of this entity type.
         */
        std::string uuid;

        /**
         * The name of the entity type.
         */
        std::string name;

        /**
         * Entity instances of this type should be persisted.
         */
        bool persist;

        /**
         * Entity instances of this type should be synchronized.
         */
        bool synchronize;

        /**
         * The attributes of the entity type.
         */
        std::map<std::string, CefRefPtr<EntityAttribute> > attributes;

        /**
         * The actions which are available on entity instances of this entity type.
         */
        std::map<std::string, CefRefPtr<EntityAction> > actions;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityType);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYTYPE_H_ */
