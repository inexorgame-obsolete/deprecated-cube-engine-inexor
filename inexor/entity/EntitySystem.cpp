/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.hpp"
#include <time.h>
#include "inexor/shared/cube.hpp"

using namespace inexor::entity::particle;

namespace inexor {
namespace entity {

    EntitySystem::EntitySystem()
    {
        // Reset the time calculation
        ResetTimer();

        // Create type managers
        entity_type_manager = new EntityTypeManager();
        relationship_type_manager = new RelationshipTypeManager(entity_type_manager);

        // Create instance managers
        entity_instance_manager = new EntityInstanceManager(entity_type_manager);
        relationship_instance_manager = new RelationshipInstanceManager(relationship_type_manager);

        InitProviders();
        InitSubsystems();

        // Start worker threads
        // Doesn't work in multithreading! Conflicts with renderer!
        // relationship_instance_manager->Start();
    }

    EntitySystem::~EntitySystem()
    {
        // Stop worker threads
        relationship_instance_manager->Stop();

        Cleanup();
        subsystems.clear();
        subsystemTypeMap.ObjectMap.clear();
    }

    void EntitySystem::InitProviders()
    {
    /*
        // Create entity type providers
        CefRefPtr<EntityTypeProvider> handle_provider = new HandleEntityTypeProvider();
        entity_type_manager->RegisterProvider(handle_provider);

        // Create relationship type providers
        CefRefPtr<RelationshipTypeProvider> handles_provider = new HandlesRelationshipTypeProvider(entity_type_manager);
        relationship_type_manager->RegisterProvider(handles_provider);
    */
    }

    void EntitySystem::InitSubsystems()
    {
        // Create subsystem instances
        handle_subsystem = new HandleSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
        teleport_subsystem = new TeleportSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
        // vscript_subsystem = new TeleportSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
        particle_subsystem = new ParticleSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);

        // Store the subsystems and it's type(!) in the subsystem type map, so that
        // the concrete subsystem can be retrieved instead of only as SubsystemBase
        //
        // ex: CefRefPtr<TeleportSubsystem> teleport_subsystem = entity_system->GetSubsystem<TeleportSubsystem>();
        //
        subsystemTypeMap.Set<HandleSubsystem>(handle_subsystem.get());
        subsystemTypeMap.Set<TeleportSubsystem>(teleport_subsystem.get());
        // subsystemTypeMap.Set<VScriptSubsystem>(vscript_subsystem.get());
        subsystemTypeMap.Set<ParticleSubsystem>(particle_subsystem.get());

        // Store all subsystems in a vector:
        subsystems.push_back(handle_subsystem);
        subsystems.push_back(teleport_subsystem);
        // subsystems.push_back(vscript_subsystem);
        subsystems.push_back(particle_subsystem);
    }

    /**
     * This happens in the main thread.
     */
    void EntitySystem::Update()
    {
        // Calculate the time step
        frame_millis = SDL_GetTicks();
        elapsed_millis = frame_millis - frame_last_millis;
        TimeStep time_step(elapsed_millis, time_unit);
        for (unsigned int i = 0; i < subsystems.size(); i++)
        {
            subsystems[i]->Update(time_step);
        }
        // Cleanup invalidated relationships
        relationship_instance_manager->InvalidateInstances();
        relationship_instance_manager->DequeInstances();
        frame_last_millis = frame_millis;
    }

    void EntitySystem::Cleanup()
    {
        for (unsigned int i = 0; i < subsystems.size(); i++)
        {
            subsystems[i]->Cleanup();
        }
        // Cleanup all instances
        relationship_instance_manager->DeleteAllInstances();
        entity_instance_manager->DeleteAllInstances();
        // Cleanup all types
        relationship_type_manager->DeleteAllTypes();
        entity_type_manager->DeleteAllTypes();
    }

    void EntitySystem::Reset()
    {
        // TODO: cleanup entities, temporarily stop renderers
        for (unsigned int i = 0; i < subsystems.size(); i++)
        {
            subsystems[i]->Reset();
        }
    }

    void EntitySystem::Save(std::string filename)
    {
    }

    void EntitySystem::Load(std::string filename)
    {
    }

    void EntitySystem::ResetTimer()
    {
        frame_millis = frame_last_millis = SDL_GetTicks();
        elapsed_millis = 0;
        time_unit = 1000.0;
    }

    void EntitySystem::SetTimeUnit(double time_unit)
    {
        this->time_unit = time_unit;
    }

    CefRefPtr<EntityTypeManager> EntitySystem::GetEntityTypeManager()
    {
        return entity_type_manager;
    }

    CefRefPtr<RelationshipTypeManager> EntitySystem::GetRelationshipTypeManager()
    {
        return relationship_type_manager;
    }

    CefRefPtr<EntityInstanceManager> EntitySystem::GetEntityInstanceManager()
    {
        return entity_instance_manager;
    }

    CefRefPtr<RelationshipInstanceManager> EntitySystem::GetRelationshipInstanceManager()
    {
        return relationship_instance_manager;
    }


}
}
