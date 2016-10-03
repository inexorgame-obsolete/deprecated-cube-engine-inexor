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
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class RandomVelocity : public EntityFunction
    {
        public:

            RandomVelocity();
            virtual ~RandomVelocity();

            AttributeRefPtr Execute(TimeStep time_step, std::shared_ptr<EntityInstance> emitter_inst, std::shared_ptr<EntityInstance> initializer_inst, std::shared_ptr<EntityInstance> particle_inst);

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_VELOCITY_H_ */
