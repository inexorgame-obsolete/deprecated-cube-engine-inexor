/*
 * EntitySystem.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_
#define SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_

#include "EntitySystemBase.h"
#include "domain/InstanceBase.h"
#include "domain/TypeBase.h"
#include "domain/graph/EntityInstance.h"
#include "domain/graph/EntityType.h"
#include "domain/graph/RelationshipType.h"
#include "domain/graph/RelationshipInstance.h"
#include "manager/EntityInstanceManager.h"
#include "manager/EntityTypeManager.h"
#include "manager/RelationshipInstanceManager.h"
#include "manager/RelationshipTypeManager.h"
#include "subsystem/TeleportSubsystem.h"
#include "subsystem/ParticleSubsystem.h"

class EntitySystem
{
    public:
        EntitySystem();
        virtual ~EntitySystem() {};

        CefRefPtr<EntityTypeManager> GetEntityTypeManager() { return entity_type_manager; };
        CefRefPtr<RelationshipTypeManager> GetRelationshipTypeManager() { return relationship_type_manager; };
        CefRefPtr<EntityInstanceManager> GetEntityInstanceManager() { return entity_instance_manager; };
        CefRefPtr<RelationshipInstanceManager> GetRelationshipInstanceManager() { return relationship_instance_manager; };

        void Save(std::string filename);

        void Load(std::string filename);

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
        std::map<std::string, CefRefPtr<SubsystemBase> > subsystems;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntitySystem);
};

#endif /* SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_ */
