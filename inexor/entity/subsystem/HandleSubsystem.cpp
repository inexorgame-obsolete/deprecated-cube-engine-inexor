/*
 * HandleSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "HandleSubsystem.hpp"
#include "handle/renderer/Box.hpp"

namespace inexor {
namespace entity {

    HandleSubsystem::HandleSubsystem() : SubsystemBase(SYS_HANDLE)
    {
    }

    HandleSubsystem::HandleSubsystem(
        std::shared_ptr<EntityTypeManager> entity_type_manager,
        std::shared_ptr<EntityInstanceManager> entity_instance_manager,
        std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
        std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager
    ) : SubsystemBase(SYS_HANDLE, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager)
    {

        // Create entity type providers
        std::shared_ptr<EntityTypeProvider> handle_provider = std::make_shared<HandleEntityTypeProvider>();
        entity_type_manager->RegisterProvider(handle_provider);
        std::shared_ptr<EntityTypeProvider> handle_renderer_provider = std::make_shared<HandleRendererEntityTypeProvider>();
        entity_type_manager->RegisterProvider(handle_renderer_provider);

        // Create relationship type providers
        std::shared_ptr<RelationshipTypeProvider> handles_provider = std::make_shared<HandlesRelationshipTypeProvider>(entity_type_manager);
        relationship_type_manager->RegisterProvider(handles_provider);
        std::shared_ptr<RelationshipTypeProvider> renders_handle_provider = std::make_shared<RendersHandleRelationshipTypeProvider>(entity_type_manager);
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
        return CreateHandle(entity_instance, FUNC_BOX_HANDLE_RENDERER, vec(entity_instance[POS]->vec3Val), vec(0.0f, 0.0f, 0.0f), vec(4.0f, 4.0f, 4.0f));
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

    void HandleSubsystem::RenderHandles()
    {
        TimeStep time_step(0, 1000);
        std::unordered_map<std::string, InstanceRefPtr<EntityInstance> >::iterator it = renderers.begin();
        while(it != renderers.end())
        {
            InstanceRefPtr<EntityInstance> handle_renderer = it->second;
            FunctionRefPtr func = handle_renderer[FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME]->functionVal;
            func->Before(time_step, handle_renderer);
            std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = handle_renderer->outgoing[renders_handle->uuid].begin();
            while (it2 != handle_renderer->outgoing[renders_handle->uuid].end())
            {
                func->Execute(time_step, (*it2));
                ++it2;
            }
            func->After(time_step, handle_renderer);
            ++it;
        }
        // render3dbox((*it).second[POS]->vec3Val, 1.0f, 1.0f, 1.0f, 0);
    }

    void HandleSubsystem::Drag(vec camdir)
    {
        spdlog::get("global")->debug() << "drag";
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
