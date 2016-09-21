/*
 * HandleSubsystem.hpp
 *
 *  Created on: 15.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_HANDLE_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_HANDLE_H_

#include "../EntitySystemBase.hpp"
#include "../provider/Handle.hpp"
#include "SubsystemBase.hpp"
#include "inexor/util/Logging.hpp"

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
                std::shared_ptr<EntityTypeManager> entity_type_manager,
                std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager
            );
            virtual ~HandleSubsystem();

            /**
             * Rendering of the handles.
             */
            void RenderHandles();

            /**
             * Dragging a handle.
             */
            void Drag(vec camdir);

            /**
             * Creates a handle for the given entity.
             */
            InstanceRefPtr<EntityInstance> CreateHandle(InstanceRefPtr<EntityInstance> entity_instance);
            InstanceRefPtr<EntityInstance> CreateHandle(InstanceRefPtr<EntityInstance> entity_instance,
                                                        std::string handle_renderer_name, vec pos, vec dir, vec dim);
            InstanceRefPtr<EntityInstance> CreateHandle(InstanceRefPtr<EntityInstance> entity_instance,
                                                        InstanceRefPtr<EntityInstance> handle_renderer,
                                                        vec pos, vec dir, vec dim);

            /**
             * Creates a handle renderer.
             */
            InstanceRefPtr<EntityInstance> CreateHandleRenderer(std::string name, FunctionRefPtr function);

            /**
             * The handle renderers.
             */
            std::unordered_map<std::string, InstanceRefPtr<EntityInstance> > renderers;

            void Update(TimeStep time_step);
            void Cleanup();
            void Reset();

            void DeleteAll();

        private:

            TypeRefPtr<RelationshipType> handles;
            TypeRefPtr<RelationshipType> renders_handle;
    };

}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_HANDLE_H_ */
