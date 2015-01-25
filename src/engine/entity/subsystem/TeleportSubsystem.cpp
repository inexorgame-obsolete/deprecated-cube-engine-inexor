/*
 * TeleportSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "TeleportSubsystem.h"

TeleportSubsystem::TeleportSubsystem() : SubsystemBase(TELEPORT_SUBSYSTEM)
{
}

TeleportSubsystem::TeleportSubsystem(
    CefRefPtr<EntityTypeManager> entity_type_manager,
    CefRefPtr<EntityInstanceManager> entity_instance_manager,
    CefRefPtr<RelationshipTypeManager> relationship_type_manager,
    CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
) : SubsystemBase(TELEPORT_SUBSYSTEM, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager)
{
}

InstanceRefPtr<EntityInstance> TeleportSubsystem::CreateTeleport(double x, double y, double z)
{
    TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENTTYPE_TELEPORT);
    // Let the entity instance manager create the instance
    InstanceRefPtr<EntityInstance> entity_instance = entity_instance_manager->Create(entity_type);
    entity_instance["x"] = x;
    entity_instance["y"] = y;
    entity_instance["z"] = z;
    return entity_instance;
}

InstanceRefPtr<EntityInstance> TeleportSubsystem::CreateTeledest(double x, double y, double z)
{
    TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENTTYPE_TELEDEST);
    InstanceRefPtr<EntityInstance> entity_instance = entity_instance_manager->Create(entity_type);
    entity_instance["x"] = x;
    entity_instance["y"] = y;
    entity_instance["z"] = z;
    return entity_instance;
}

InstanceRefPtr<RelationshipInstance> TeleportSubsystem::Connect(InstanceRefPtr<EntityInstance> teleport, InstanceRefPtr<EntityInstance> teledest)
{
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(RELTYPE_TELEPORTING);
    if (relationship_type.get()) {
        InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(relationship_type, teleport, teledest);
        return relationship_instance;
    } else {
        return NULL;
    }
}

void TeleportSubsystem::Disconnect(InstanceRefPtr<RelationshipInstance> relationship_instance)
{
    // TODO: check for start and end node for type safety!
    relationship_instance_manager->DeleteInstance(relationship_instance);
}

void TeleportSubsystem::DeleteAll()
{
    DeleteAllTeleports();
    DeleteAllTeledests();
    DeleteAllConnections();
}

void TeleportSubsystem::DeleteAllTeleports()
{
    TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENTTYPE_TELEPORT);
    entity_instance_manager->DeleteAllInstances(entity_type);
}

void TeleportSubsystem::DeleteAllTeledests()
{
    TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENTTYPE_TELEDEST);
    entity_instance_manager->DeleteAllInstances(entity_type);
}

void TeleportSubsystem::DeleteAllConnections()
{
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(RELTYPE_TELEPORTING);
    relationship_instance_manager->DeleteAllInstances(relationship_type);
}

