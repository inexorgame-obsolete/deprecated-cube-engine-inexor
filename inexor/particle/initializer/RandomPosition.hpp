/*
 * RandomPosition.h
 *
 *  Created on: 09.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_POSITION_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_POSITION_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class RandomPosition : public EntityFunction
    {
        public:

            RandomPosition();
            virtual ~RandomPosition();

            void Execute(TimeStep time_step, EntityInstance* emitter_inst, EntityInstance* initializer_inst, EntityInstance* particle_inst);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(RandomPosition);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_POSITION_H_ */
