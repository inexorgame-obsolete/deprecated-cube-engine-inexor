/*
 * HandleSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "HandleSubsystem.h"
#include "renderer/Box.h"

// extern physent *camera1 = NULL;

namespace inexor {
namespace entity {
namespace handle {

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
    CreateHandleRenderer(FUNC_BOX_HANDLE_RENDERER, handle_renderer_box);

    handles = relationship_type_manager->Get(REL_HANDLES);
    renders_handle = relationship_type_manager->Get(REL_RENDERS_HANDLE);
}

HandleSubsystem::~HandleSubsystem()
{
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance)
{
    return CreateHandle(entity_instance, FUNC_BOX_HANDLE_RENDERER, vec(entity_instance[POS]->vec3Val), vec(0.0f, 0.0f, 0.0f), vec(2.0f, 2.0f, 2.0f));
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance, std::string handle_renderer_name, vec pos, vec dir, vec dim)
{
	return CreateHandle(entity_instance, renderers[handle_renderer_name], pos, dir, dim);
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandle(InstanceRefPtr<EntityInstance> entity_instance, InstanceRefPtr<EntityInstance> handle_renderer, vec pos, vec dir, vec dim)
{
    InstanceRefPtr<EntityInstance> handle = entity_instance_manager->Create(ENT_HANDLE);
    handle[POS] = pos;
    handle[DIR] = dir;
    handle[DIM] = dim;
    handle[SELECTED] = false;
    handle[HOVERED] = false;
    relationship_instance_manager->CreateInstance(handles, handle, entity_instance);
    relationship_instance_manager->CreateInstance(renders_handle, handle_renderer, handle);
    return handle;
}

InstanceRefPtr<EntityInstance> HandleSubsystem::CreateHandleRenderer(std::string name, FunctionRefPtr function)
{
    TypeRefPtr<EntityType> handle_renderer_type = entity_type_manager->Get(ENT_HANDLE_RENDERER);
	InstanceRefPtr<EntityInstance> handle_renderer = entity_instance_manager->Create(handle_renderer_type);
	handle_renderer[FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME] = function;
	renderers[name] = handle_renderer;
	return handle_renderer;
}

// extern float rayent(const vec &o, const vec &ray, float radius, int mode, int size, int &orient, int &ent);
// extern bool rayboxintersect(const vec &b, const vec &s, const vec &o, const vec &ray, float &dist, int &orient);

void HandleSubsystem::RenderHandles(vec camdir)
{
    if (editmode)
    {
        TimeStep time_step(0, 1000);
        std::unordered_map<std::string, InstanceRefPtr<EntityInstance> >::iterator it = renderers.begin();
        while(it != renderers.end())
        {
            InstanceRefPtr<EntityInstance> handle_renderer = it->second;
            FunctionRefPtr func = handle_renderer[FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME]->functionVal;
            func->Before(time_step, handle_renderer.get());
            std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = handle_renderer->outgoing[renders_handle->uuid].begin();
            while (it2 != handle_renderer->outgoing[renders_handle->uuid].end())
            {
                InstanceRefPtr<RelationshipInstance> renders_handle = (*it2);
                if (renders_handle->alive)
                {

                    /*
                    vec pmin(pos);
                    vec pmax(pmin);
                    pmin.sub(dim);
                    pmax.add(dim);
                    */


                    func->Execute(time_step, renders_handle.get());

                } else {
                    renders_handle->endNode[HOVERED] = false;
                }

                /*
                float wdist = rayent(player->o, camdir, 1e16f,
                                       (editmode && showmat ? RAY_EDITMAT : 0)   // select cubes first
                                       | (!dragging && entediting ? RAY_ENTS : 0)
                                       | RAY_SKIPFIRST
                                       | (passthroughcube==1 ? RAY_PASS : 0), gridsize, entorient, ent);
*/



                ++it2;
            }
            func->After(time_step, handle_renderer.get());
            ++it;
        }
    }
    // render3dbox((*it).second[POS]->vec3Val, 1.0f, 1.0f, 1.0f, 0);
}

/*
float rayent(const vec &o, const vec &ray, float radius, int mode, int size, int &orient, int &ent)
{
    hitent = -1;
    hitentdist = radius;
    hitorient = -1;
    float dist = raycube(o, ray, radius, mode, size);
    if((mode&RAY_ENTS) == RAY_ENTS)
    {
        float dent = disttooutsideent(o, ray, dist < 0 ? 1e16f : dist, mode, NULL);
        if(dent < 1e15f && (dist < 0 || dent < dist)) dist = dent;
    }
    orient = hitorient;
    ent = hitentdist == dist ? hitent : -1;
    return dist;
}
*/

bool HandleSubsystem::HitHandle(const vec &o, const vec &ray, InstanceRefPtr<EntityInstance> handle)
{

}

void HandleSubsystem::Drag(vec camdir)
{
    logoutf("drag (%2.2f, %2.2f, %2.2f)", camdir.x, camdir.y, camdir.z);
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
}
