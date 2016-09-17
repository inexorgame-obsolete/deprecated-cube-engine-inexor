/*
 * Cube.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef ENTITY_SUBSYSTEM_PARTICLE_RENDERER_CUBE_H_
#define ENTITY_SUBSYSTEM_PARTICLE_RENDERER_CUBE_H_

#include "../../../EntitySystemBase.hpp"
#include "../ParticleSubsystem.hpp"
#include "../../../EntitySystem.hpp"
#include "../../../domain/graph/EntityFunction.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class Cube : public EntityFunction
    {
        public:

            Cube();
            virtual ~Cube();

            /**
             * Executed before particles are rendered.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             */
            void Before(TimeStep time_step, EntityInstance* renderer_inst);

            /**
             * Executed for each particle.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             * @param particle_inst The particle instance.
             */
            void Execute(TimeStep time_step, EntityInstance* renderer_inst, EntityInstance* particle_inst);

            /**
             * Executed after particles are rendered.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             */
            void After(TimeStep time_step, EntityInstance* renderer_inst);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(Cube);

    };

}
}
}

#endif /* ENTITY_SUBSYSTEM_PARTICLE_RENDERER_CUBE_H_ */
