/*
 * BrownianMotion.h
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_BROWNIAN_MOTION_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_BROWNIAN_MOTION_H_

#include <random>
#include <cmath>

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class BrownianMotion : public EntityFunction
    {
        public:

            BrownianMotion();
            virtual ~BrownianMotion();

            AttributeRefPtr Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle);

        private:

            std::random_device rd;
            std::mt19937 gen;
            std::normal_distribution<float> distribution;

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_BROWNIAN_MOTION_H_ */
