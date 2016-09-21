/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.hpp"
#include <time.h>
#include "inexor/shared/cube.hpp"

namespace inexor {
namespace entity {

    EntitySystem::EntitySystem()
    {
        // Reset the time calculation
        ResetTimer();

        // Create type managers
        entity_type_manager = std::make_shared<EntityTypeManager>();
        relationship_type_manager = std::make_shared<RelationshipTypeManager>(entity_type_manager);

        // Create instance managers
        entity_instance_manager = std::make_shared<EntityInstanceManager>(entity_type_manager);
        relationship_instance_manager = std::make_shared<RelationshipInstanceManager>(relationship_type_manager);

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
        subsystem_type_map.clear();
        // subsystemTypeMap.ObjectMap.clear();
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
        // spdlog::get("global")->info() << "EntitySystem::Update()";
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
        // TODO: activate renderers again
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

    std::shared_ptr<EntityTypeManager> EntitySystem::GetEntityTypeManager()
    {
        return entity_type_manager;
    }

    std::shared_ptr<RelationshipTypeManager> EntitySystem::GetRelationshipTypeManager()
    {
        return relationship_type_manager;
    }

    std::shared_ptr<EntityInstanceManager> EntitySystem::GetEntityInstanceManager()
    {
        return entity_instance_manager;
    }

    std::shared_ptr<RelationshipInstanceManager> EntitySystem::GetRelationshipInstanceManager()
    {
        return relationship_instance_manager;
    }


}
}
