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

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"
#include "../../../domain/graph/EntityInstance.h"
#include "../ParticleModel.h"

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
