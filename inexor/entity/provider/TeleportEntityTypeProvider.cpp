/*
 * Teleporter.cpp
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#include "TeleportEntityTypeProvider.hpp"

namespace inexor {
namespace entity {


TeleportEntityTypeProvider::TeleportEntityTypeProvider()
    : EntityTypeProvider(ENT_TELEPORT)
{
    entity_type = new EntityType(ENT_TELEPORT, true, true);
}

TeleportEntityTypeProvider::~TeleportEntityTypeProvider()
{
}

TeledestEntityTypeProvider::TeledestEntityTypeProvider()
    : EntityTypeProvider(ENT_TELEDEST)
{
    entity_type = new EntityType(ENT_TELEDEST, true, true);
    FunctionRefPtr teleported = new EntityFunction(FUNC_TELEPORTED);
    // TODO: implement teleported event
    entity_type[FUNC_TELEPORTED] = teleported;
}

TeledestEntityTypeProvider::~TeledestEntityTypeProvider()
{
}

TeleportingRelationshipTypeProvider::TeleportingRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager)
    : RelationshipTypeProvider(REL_TELEPORTING, entity_type_manager)
{
    // Define the relationship type
    relationship_type = new RelationshipType(
        REL_TELEPORTING,
        true,
        true,
        entity_type_manager->Get(ENT_TELEPORT),
        entity_type_manager->Get(ENT_TELEDEST)
    );
}

TeleportingRelationshipTypeProvider::~TeleportingRelationshipTypeProvider()
{
}

}
}
