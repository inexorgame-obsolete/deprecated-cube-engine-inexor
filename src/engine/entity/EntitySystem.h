/*
 * EntitySystem.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_
#define SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_

#include "EntitySystemBase.h"
#include "InstanceBase.h"
#include "TypeBase.h"
#include "EntityInstance.h"
#include "EntityType.h"
#include "RelationshipType.h"
#include "RelationshipInstance.h"
#include "manager/EntityInstanceManager.h"
#include "manager/EntityTypeManager.h"
#include "manager/RelationshipInstanceManager.h"
#include "manager/RelationshipTypeManager.h"
#include "subsystem/TeleportSubsystem.h"

class EntitySystem
{
    public:
        EntitySystem();
        virtual ~EntitySystem() {};

    private:

        /**
         * The entity type manager.
         */
        CefRefPtr<EntityTypeManager> entity_type_manager;

        /**
         * The relationship type manager.
         */
        CefRefPtr<RelationshipTypeManager> relationship_type_manager;

        /**
         * The entity instance manager.
         */
        CefRefPtr<EntityInstanceManager> entity_instance_manager;

        /**
         * The relationship instance manager.
         */
        CefRefPtr<RelationshipInstanceManager> relationship_instance_manager;

        /**
         * The subsystems.
         */
        std::map<std::string, CefRefPtr<Subsystem> > subsystems;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntitySystem);
};

#endif /* SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_ */
