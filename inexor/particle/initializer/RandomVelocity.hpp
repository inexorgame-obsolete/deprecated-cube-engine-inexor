/*
 * PulseInitializer.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_VELOCITY_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_VELOCITY_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class RandomVelocity : public EntityFunction
    {
        public:

            RandomVelocity();
            virtual ~RandomVelocity();

            void Execute(TimeStep time_step, EntityInstance* emitter_inst, EntityInstance* initializer_inst, EntityInstance* particle_inst);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(RandomVelocity);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_VELOCITY_H_ */
