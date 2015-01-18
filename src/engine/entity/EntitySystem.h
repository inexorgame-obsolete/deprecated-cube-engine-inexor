/*
 * EntitySystem.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_
#define SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_

#include "InstanceBase.h"
#include "TypeBase.h"
#include "EntitySystemBase.h"
#include "EntityType.h"
#include "EntityInstance.h"
#include "RelationshipType.h"
#include "RelationshipInstance.h"

class EntitySystem
{
    public:
        EntitySystem();
        virtual ~EntitySystem();

        /**
         * Creates an entity type.
         */
        CefRefPtr<EntityType> CreateEntityType(std::string name, bool persist, bool synchronize);

        /**
         * Creates an relationship type.
         */
        CefRefPtr<RelationshipType> CreateRelationshipType(std::string name, bool persist, bool synchronize);

        /**
         * Returns the entity type with the given name.
         */
        CefRefPtr<EntityType> GetEntityType(std::string name);

        /**
         * Returns the relationship type with the given name.
         */
        CefRefPtr<RelationshipType> GetRelationshipType(std::string name);

    private:

        /**
         * The entity types by name.
         */
        std::map<std::string, CefRefPtr<EntityType> > entity_types;

        /**
         * The relationship types by name.
         */
        std::map<std::string, CefRefPtr<RelationshipType> > relationship_types;

        /**
         * The entity instances.
         */
        std::list<CefRefPtr<EntityInstance> > entity_instances;

        /**
         * The relationship instances.
         */
        std::list<CefRefPtr<RelationshipInstance> > relationship_instances;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntitySystem);
};

#endif /* SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_ */
