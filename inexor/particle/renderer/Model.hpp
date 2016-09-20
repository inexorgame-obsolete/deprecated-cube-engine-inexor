/*
 * Model.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef ENTITY_SUBSYSTEM_PARTICLE_RENDERER_MODEL_H_
#define ENTITY_SUBSYSTEM_PARTICLE_RENDERER_MODEL_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/particle/subsystem/ParticleSubsystem.hpp"
#include "inexor/entity/EntitySystem.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class Model : public EntityFunction
    {
        public:

            Model();
            virtual ~Model();

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

            model *m;
            float yaw;
            float pitch;
            std::string model_name;
            vec offset;

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(Model);

    };

}
}
}

#endif /* ENTITY_SUBSYSTEM_PARTICLE_RENDERER_MODEL_H_ */
