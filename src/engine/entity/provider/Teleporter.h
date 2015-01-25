/*
 * Teleporter.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_TELEPORTER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_TELEPORTER_H_

#include "../EntityFunction.h"
#include "../EntityType.h"
#include "../RelationshipType.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/RelationshipTypeManager.h"
#include "EntityTypeProvider.h"
#include "RelationshipTypeProvider.h"

#define ENTTYPE_TELEPORT "teleport"
#define ENTTYPE_TELEDEST "teledest"
#define RELTYPE_TELEPORTING "teleporting"

/**
 * Defines the teleport source entity type.
 */
class TeleportEntityTypeProvider : public EntityTypeProvider
{
    public:
        TeleportEntityTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager) : EntityTypeProvider(ENTTYPE_TELEPORT, entity_type_manager) {
            entity_type = new EntityType(ENTTYPE_TELEPORT, true, true);
        };
        virtual ~TeleportEntityTypeProvider() {};

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(TeleportEntityTypeProvider);

};

/**
 * Defines the teleport destination entity type.
 */
class TeledestEntityTypeProvider : public EntityTypeProvider
{
    public:
        TeledestEntityTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager) : EntityTypeProvider(ENTTYPE_TELEDEST, entity_type_manager) {
            entity_type = new EntityType(ENTTYPE_TELEDEST, true, true);
            FunctionRefPtr on_teleported = new EntityFunction("on_teleported");
            entity_type["on_teleported"] = on_teleported;
        };
        virtual ~TeledestEntityTypeProvider() {};

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(TeledestEntityTypeProvider);

};

/**
 * Defines the teleporting relationship type.
 */
class TeleportingRelationshipTypeProvider : public RelationshipTypeProvider
{
    public:
        TeleportingRelationshipTypeProvider(
            CefRefPtr<RelationshipTypeManager> relationship_type_manager,
            CefRefPtr<EntityTypeManager> entity_type_manager
        ) : RelationshipTypeProvider(RELTYPE_TELEPORTING, relationship_type_manager, entity_type_manager) {
            // Define the relationship type
            relationship_type = new RelationshipType(
                RELTYPE_TELEPORTING,
                true,
                true,
                entity_type_manager->Get(ENTTYPE_TELEPORT),
                entity_type_manager->Get(ENTTYPE_TELEDEST)
            );
        };
        virtual ~TeleportingRelationshipTypeProvider() {};

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(TeleportingRelationshipTypeProvider);

};

#endif /* SRC_ENGINE_ENTITY_PROVIDER_TELEPORTER_H_ */
