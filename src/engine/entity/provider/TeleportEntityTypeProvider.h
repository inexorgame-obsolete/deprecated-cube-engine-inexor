/*
 * Teleporter.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_TELEPORTENTITYTYPEPROVIDER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_TELEPORTENTITYTYPEPROVIDER_H_

#include "../EntityFunction.h"
#include "../EntityType.h"
#include "../RelationshipType.h"
#include "EntityTypeProvider.h"
#include "RelationshipTypeProvider.h"

#define ENTTYPE_TELEPORT "teleport"
#define ENTTYPE_TELEDEST "teledest"
#define RELTYPE_TELEPORTING "teleporting"

class EntityTypeManager;

/**
 * Defines the teleport source entity type.
 */
class TeleportEntityTypeProvider : public EntityTypeProvider
{
    public:
        TeleportEntityTypeProvider();
        virtual ~TeleportEntityTypeProvider();

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
        TeledestEntityTypeProvider();
        virtual ~TeledestEntityTypeProvider();

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
        TeleportingRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~TeleportingRelationshipTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(TeleportingRelationshipTypeProvider);

};

#endif /* SRC_ENGINE_ENTITY_PROVIDER_TELEPORTENTITYTYPEPROVIDER_H_ */
