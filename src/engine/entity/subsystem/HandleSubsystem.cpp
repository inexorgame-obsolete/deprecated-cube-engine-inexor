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
    CefRefPtr<EntityTypeProvider> handle_renderer_provider = new HandleRendererEntityTypeProvider();
    entity_type_manager->RegisterProvider(handle_renderer_provider);

    // Create relationship type providers
    CefRefPtr<RelationshipTypeProvider> handles_provider = new HandlesRelationshipTypeProvider(entity_type_manager);
    relationship_type_manager->RegisterProvider(handles_provider);
    CefRefPtr<RelationshipTypeProvider> renders_handle_provider = new RendersHandleRelationshipTypeProvider(entity_type_manager);
    relationship_type_manager->RegisterProvider(renders_handle_provider);

    FunctionRefPtr handle_renderer_box = new Box();
    CreateHandleRenderer("box", handle_renderer_box);
}

HandleSubsystem::~HandleSubsystem()
{
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance)
{
    return CreateHandle(entity_instance, HANDLE_POINT, vec(entity_instance[POS]->vec3Val), vec(0.0f, 0.0f, 0.0f), vec(4.0f, 4.0f, 4.0f));
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance, std::string handle_renderer_name, vec pos, vec dir, vec dim)
{
	return CreateHandle(entity_instance, renderers[handle_renderer_name], pos, dir, dim);
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance, InstanceRefPtr<EntityInstance> handle_renderer, vec pos, vec dir, vec dim)
{
    InstanceRefPtr<EntityInstance> handle = entity_instance_manager->Create(ENT_HANDLE);
    handle[TYPE] = type;
    handle[POS] = pos;
    handle[DIR] = dir;
    handle[DIM] = dim;
    relationship_instance_manager->CreateInstance(REL_HANDLES, handle, entity_instance);
    relationship_instance_manager->CreateInstance(REL_RENDERS_HANDLE, handle_renderer, handle);
    return handle;
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandleRenderer(std::string name, FunctionRefPtr function)
{
	InstanceRefPtr<EntityInstance> handle_renderer = entity_instance_manager->CreateInstance(entity_type_manager->Get(ENT_HANDLE_RENDERER));
	handle_renderer[FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME] = function;
	renderers[name] = handle_renderer;
	return handle_renderer;
}

void HandleSubsystem::RenderHandles()
{
    TimeStep time_step(0, 1000);
    std::unordered_map<std::string, InstanceRefPtr<EntityInstance> >::iterator it = renderers.begin();
    while(it != renderers.end())
    {
        std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = (*it)->second->outgoing[REL_RENDERS_HANDLE].begin();
        while (it2 != (*it)->second->outgoing[REL_RENDERS_HANDLE].end())
        {
        	(*it2)->endNode[FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME]->Execute(time_step, (*it), (*it2));
            ++it2;
        }
        ++it;
    }
    // render3dbox((*it).second[POS]->vec3Val, 1.0f, 1.0f, 1.0f, 0);
}

void HandleSubsystem::Update(TimeStep time_step)
{
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
