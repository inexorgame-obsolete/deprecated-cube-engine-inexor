/*
 * Entity.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_
#define SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_

#include <string>
#include <map>
#include <list>

#include "EntitySystem.h"

#include "EntityAttribute.h"
#include "EntityType.h"
// #include "RelationshipInstance.h"

class RelationshipInstance;

class EntityInstance
{
    public:
        EntityInstance();
        virtual ~EntityInstance();

    private:
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
         * The attributes of this entity instance.
         */
        std::map<std::string, CefRefPtr<EntityAttribute> > attributes;

        /**
         * The relationships.
         */
        std::list<CefRefPtr<RelationshipInstance> > relationships;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityInstance);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_ */
