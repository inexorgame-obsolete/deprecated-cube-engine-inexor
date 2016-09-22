/*
 * BoxEntityRenderer.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef INEXOR_ENTITY_RENDERING_BOX_ENTITY_RENDERER_HEADER
#define INEXOR_ENTITY_RENDERING_BOX_ENTITY_RENDERER_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/particle/subsystem/ParticleSubsystem.hpp"
#include "inexor/entity/EntitySystem.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"

namespace inexor {
namespace entity {
namespace rendering {

    class BoxEntityRenderer : public EntityFunction
    {
        public:

            BoxEntityRenderer();
            virtual ~BoxEntityRenderer();

            /**
             * Executed before particles are rendered.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             */
            void Before(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst);

            /**
             * Executed for each particle.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             * @param particle_inst The particle instance.
             */
            void Execute(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst, std::shared_ptr<EntityInstance> particle_inst);

            /**
             * Executed after particles are rendered.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             */
            void After(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst);

    };

}
}
}

#endif /* INEXOR_ENTITY_RENDERING_BOX_ENTITY_RENDERER_HEADER */
