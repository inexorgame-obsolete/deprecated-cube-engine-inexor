/*
 * Teleporter.cpp
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#include "TeleportEntityTypeProvider.h"

TeleportEntityTypeProvider::TeleportEntityTypeProvider() : EntityTypeProvider(ENTTYPE_TELEPORT)
{
    entity_type = new EntityType(ENTTYPE_TELEPORT, true, true);
}

TeleportEntityTypeProvider::~TeleportEntityTypeProvider()
{
}

TeledestEntityTypeProvider::TeledestEntityTypeProvider() : EntityTypeProvider(ENTTYPE_TELEDEST)
{
    entity_type = new EntityType(ENTTYPE_TELEDEST, true, true);
    FunctionRefPtr on_teleported = new EntityFunction("on_teleported");
    entity_type["on_teleported"] = on_teleported;
}

TeledestEntityTypeProvider::~TeledestEntityTypeProvider()
{
}

TeleportingRelationshipTypeProvider::TeleportingRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager)
    : RelationshipTypeProvider(RELTYPE_TELEPORTING, entity_type_manager)
{
    // Define the relationship type
    relationship_type = new RelationshipType(
        RELTYPE_TELEPORTING,
        true,
        true,
        entity_type_manager->Get(ENTTYPE_TELEPORT),
        entity_type_manager->Get(ENTTYPE_TELEDEST)
    );
}

TeleportingRelationshipTypeProvider::~TeleportingRelationshipTypeProvider()
{
}
