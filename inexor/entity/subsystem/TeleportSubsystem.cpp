/*
 * TeleportSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "TeleportSubsystem.hpp"

namespace inexor {
namespace entity {

    TeleportSubsystem::TeleportSubsystem() : SubsystemBase(TELEPORT_SUBSYSTEM)
    {
    }

    TeleportSubsystem::TeleportSubsystem(
        std::shared_ptr<EntityTypeManager> entity_type_manager,
        std::shared_ptr<EntityInstanceManager> entity_instance_manager,
        std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
        std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager
    ) : SubsystemBase(TELEPORT_SUBSYSTEM, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager)
    {

        // Create entity type providers
        std::shared_ptr<EntityTypeProvider> teleport_provider = std::make_shared<TeleportEntityTypeProvider>();
        std::shared_ptr<EntityTypeProvider> teledest_provider = std::make_shared<TeledestEntityTypeProvider>();
        entity_type_manager->RegisterProvider(teleport_provider);
        entity_type_manager->RegisterProvider(teledest_provider);

        // Create relationship type providers
        std::shared_ptr<RelationshipTypeProvider> teleporting_provider = std::make_shared<TeleportingRelationshipTypeProvider>(entity_type_manager);
        relationship_type_manager->RegisterProvider(teleporting_provider);

    }

    TeleportSubsystem::~TeleportSubsystem()
    {
    }

    void TeleportSubsystem::Update(TimeStep time_step)
    {
        // logoutf("TeleportSubsystem::Update() elapsed_millis: %d time_factor: %2.3f time_unit: %4.1f", time_step.elapsed_millis, time_step.time_factor, time_step.time_unit);
    }

    void TeleportSubsystem::Cleanup()
    {
    }

    void TeleportSubsystem::Reset()
    {
    }

    InstanceRefPtr<EntityInstance> TeleportSubsystem::CreateTeleport(double x, double y, double z)
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENT_TELEPORT);
        // Let the entity instance manager create the instance
        InstanceRefPtr<EntityInstance> entity_instance = entity_instance_manager->Create(entity_type);
        entity_instance["x"] = x;
        entity_instance["y"] = y;
        entity_instance["z"] = z;
        return entity_instance;
    }

    InstanceRefPtr<EntityInstance> TeleportSubsystem::CreateTeledest(double x, double y, double z)
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENT_TELEDEST);
        InstanceRefPtr<EntityInstance> entity_instance = entity_instance_manager->Create(entity_type);
        entity_instance["x"] = x;
        entity_instance["y"] = y;
        entity_instance["z"] = z;
        return entity_instance;
    }

    InstanceRefPtr<RelationshipInstance> TeleportSubsystem::Connect(InstanceRefPtr<EntityInstance> teleport, InstanceRefPtr<EntityInstance> teledest)
    {
        TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(REL_TELEPORTING);
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
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENT_TELEPORT);
        entity_instance_manager->DeleteAllInstances(entity_type);
    }

    void TeleportSubsystem::DeleteAllTeledests()
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENT_TELEDEST);
        entity_instance_manager->DeleteAllInstances(entity_type);
    }

    void TeleportSubsystem::DeleteAllConnections()
    {
        TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(REL_TELEPORTING);
        relationship_instance_manager->DeleteAllInstances(relationship_type);
    }

}
}
