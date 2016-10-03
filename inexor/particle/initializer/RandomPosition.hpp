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

            AttributeRefPtr Execute(TimeStep time_step, std::shared_ptr<EntityInstance> emitter_inst, std::shared_ptr<EntityInstance> initializer_inst, std::shared_ptr<EntityInstance> particle_inst);

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_RANDOM_POSITION_H_ */
