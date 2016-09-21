/*
 * Box.hpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef ENTITY_SUBSYSTEM_PARTICLE_RENDERER_CUBE_H_
#define ENTITY_SUBSYSTEM_PARTICLE_RENDERER_CUBE_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/EntitySystem.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"

namespace inexor {
namespace entity {

    class Box : public EntityFunction
    {
        public:

            Box();
            virtual ~Box();

            /**
             * Executed before handles are rendered.
             * @param time_step The time step.
             * @param handle_renderer The handle renderer instance.
             */
            void Before(TimeStep time_step, EntityInstance* handle_renderer);

            /**
             * Executed for each handle.
             * @param time_step The time step.
             * @param handle_renderer The handle renderer instance.
             * @param handle The handle instance.
             */
            void Execute(TimeStep time_step, RelationshipInstance* renders_handle_inst);

            /**
             * Executed after handles are rendered.
             * @param time_step The time step.
             * @param handle_renderer The handle renderer instance.
             */
            void After(TimeStep time_step, EntityInstance* handle_renderer);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(Box);

    };

}
}

#endif /* ENTITY_SUBSYSTEM_PARTICLE_RENDERER_CUBE_H_ */
