/*
 * HandleSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "HandleSubsystem.h"

namespace inexor {
namespace entity {

HandleSubsystem::HandleSubsystem() : SubsystemBase(SYS_HANDLE)
{
}

HandleSubsystem::HandleSubsystem(
    CefRefPtr<EntityTypeManager> entity_type_manager,
    CefRefPtr<EntityInstanceManager> entity_instance_manager,
    CefRefPtr<RelationshipTypeManager> relationship_type_manager,
    CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
) : SubsystemBase(SYS_HANDLE, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager)
{

    // Create entity type providers
    CefRefPtr<EntityTypeProvider> handle_provider = new HandleEntityTypeProvider();
    entity_type_manager->RegisterProvider(handle_provider);

    // Create relationship type providers
    CefRefPtr<RelationshipTypeProvider> handles_provider = new HandlesRelationshipTypeProvider(entity_type_manager);
    relationship_type_manager->RegisterProvider(handles_provider);

}

HandleSubsystem::~HandleSubsystem()
{
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance)
{
    return CreateHandle(entity_instance, HANDLE_POINT, vec(entity_instance[POS]->vec3Val), vec(0.0f, 0.0f, 0.0f), vec(4.0f, 4.0f, 4.0f));
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance, int type, vec pos, vec dir, vec dim)
{
    InstanceRefPtr<EntityInstance> handle = entity_instance_manager->Create(ENT_HANDLE);
    handle[TYPE] = type;
    handle[POS] = pos;
    handle[DIR] = dir;
    handle[DIM] = dim;
    handles[handle->uuid] = handle;
    relationship_instance_manager->CreateInstance(REL_HANDLES, handle, entity_instance);
    return handle;
}

void HandleSubsystem::RenderHandles()
{
    std::unordered_map<std::string, InstanceRefPtr<EntityInstance> >::iterator it = handles.begin();
    while(it != handles.end())
    {

        // TODO: call handle renderer for type
        // TODO: Handle-Tracker (*it)->outgoing

        render3dbox((*it).second[POS]->vec3Val, 1.0f, 1.0f, 1.0f, 0);
        ++it;
    }
}

void HandleSubsystem::Update(TimeStep time_step)
{
    // logoutf("HandleSubsystem::Update() elapsed_millis: %d time_factor: %2.3f time_unit: %4.1f", time_step.elapsed_millis, time_step.time_factor, time_step.time_unit);
}

void HandleSubsystem::Cleanup()
{
}

void HandleSubsystem::Reset()
{
}

void HandleSubsystem::DeleteAll()
{
}

}
}
