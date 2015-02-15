/*
 * HandleSubsystem.h
 *
 *  Created on: 15.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_HANDLE_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_HANDLE_H_

#include "../EntitySystemBase.h"
#include "../provider/Handle.h"
#include "SubsystemBase.h"

namespace inexor {
namespace entity {

/**
 * This subsystems manages handles.
 */
class HandleSubsystem : public SubsystemBase
{
    public:
        HandleSubsystem();
        HandleSubsystem(
            CefRefPtr<EntityTypeManager> entity_type_manager,
            CefRefPtr<EntityInstanceManager> entity_instance_manager,
            CefRefPtr<RelationshipTypeManager> relationship_type_manager,
            CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
        );
        virtual ~HandleSubsystem();

        /**
         * Rendering of the handles.
         */
        void RenderHandles();

        /**
         * Creates a handle for the given entity.
         */
        InstanceRefPtr<EntityInstance> CreateHandle(InstanceRefPtr<EntityInstance> entity_instance);
        InstanceRefPtr<EntityInstance> CreateHandle(InstanceRefPtr<EntityInstance> entity_instance, int type, vec pos, vec dir, vec dim);

        /**
         * The modifier workers.
         */
        std::unordered_map<std::string, InstanceRefPtr<EntityInstance> > handles;

        void Update(TimeStep time_step);
        void Cleanup();
        void Reset();

        void DeleteAll();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(HandleSubsystem);
};

}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_HANDLE_H_ */
