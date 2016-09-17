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

#include "../../../EntitySystemBase.hpp"
#include "../../../domain/graph/EntityFunction.hpp"
#include "../../../domain/graph/EntityInstance.hpp"
#include "../ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class BrownianMotion : public EntityFunction
    {
        public:

            BrownianMotion();
            virtual ~BrownianMotion();

            void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

        private:

            std::random_device rd;
            std::mt19937 gen;
            std::normal_distribution<float> distribution;

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(BrownianMotion);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_BROWNIAN_MOTION_H_ */
