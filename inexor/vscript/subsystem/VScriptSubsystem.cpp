#include "VScriptSubsystem.hpp"

namespace inexor {
namespace vscript {

    VScriptSubsystem::VScriptSubsystem() : SubsystemBase(VSCRIPT_SUBSYSTEM)
    {
    }

    VScriptSubsystem::VScriptSubsystem(
        CefRefPtr<EntityTypeManager> entity_type_manager,
        CefRefPtr<EntityInstanceManager> entity_instance_manager,
        CefRefPtr<RelationshipTypeManager> relationship_type_manager,
        CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
    ) : SubsystemBase(VSCRIPT_SUBSYSTEM, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager)
    {

        // Create entity type providers
        CefRefPtr<EntityTypeProvider> memory_provider = new MemoryEntityTypeProvider();
        entity_type_manager->RegisterProvider(memory_provider);

        // Create relationship type providers
        // CefRefPtr<RelationshipTypeProvider> teleporting_provider = new TeleportingRelationshipTypeProvider(entity_type_manager);
        // relationship_type_manager->RegisterProvider(teleporting_provider);

    }

    VScriptSubsystem::~VScriptSubsystem()
    {
    }

    void VScriptSubsystem::Update(TimeStep time_step)
    {
        // logoutf("VScriptSubsystem::Update() elapsed_millis: %d time_factor: %2.3f time_unit: %4.1f", time_step.elapsed_millis, time_step.time_factor, time_step.time_unit);
    }

    void VScriptSubsystem::Cleanup()
    {
    }

    void VScriptSubsystem::Reset()
    {
    }

    InstanceRefPtr<EntityInstance> VScriptSubsystem::CreateMemory(double x, double y, double z)
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENT_MEMORY);
        // Let the entity instance manager create the instance
        InstanceRefPtr<EntityInstance> entity_instance = entity_instance_manager->Create(entity_type);
        entity_instance["x"] = x;
        entity_instance["y"] = y;
        entity_instance["z"] = z;
        entity_instance["constant"] = true;
        return entity_instance;
    }

/*
    InstanceRefPtr<RelationshipInstance> VScriptSubsystem::Connect(InstanceRefPtr<EntityInstance> teleport, InstanceRefPtr<EntityInstance> teledest)
    {
        TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(REL_TELEPORTING);
        if (relationship_type.get()) {
            InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(relationship_type, teleport, teledest);
            return relationship_instance;
        } else {
            return NULL;
        }
    }

    void VScriptSubsystem::Disconnect(InstanceRefPtr<RelationshipInstance> relationship_instance)
    {
        // TODO: check for start and end node for type safety!
        relationship_instance_manager->DeleteInstance(relationship_instance);
    }

    void VScriptSubsystem::DeleteAll()
    {
        DeleteAllTeleports();
        DeleteAllTeledests();
        DeleteAllConnections();
    }

    void VScriptSubsystem::DeleteAllTeleports()
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENT_TELEPORT);
        entity_instance_manager->DeleteAllInstances(entity_type);
    }

    void VScriptSubsystem::DeleteAllTeledests()
    {
        TypeRefPtr<EntityType> entity_type = entity_type_manager->Get(ENT_TELEDEST);
        entity_instance_manager->DeleteAllInstances(entity_type);
    }

    void VScriptSubsystem::DeleteAllConnections()
    {
        TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(REL_TELEPORTING);
        relationship_instance_manager->DeleteAllInstances(relationship_type);
    }
*/

}
}
