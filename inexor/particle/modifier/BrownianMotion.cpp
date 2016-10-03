/*
 * BrownianMotion.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "BrownianMotion.hpp"

namespace inexor {
namespace entity {
namespace particle {

    BrownianMotion::BrownianMotion()
        : EntityFunction(MODIFIER_BROWNIAN_MOTION_FUNCTION)
    {
        gen = std::mt19937(rd());
        distribution = std::normal_distribution<float>(0.0f, 12.0f * 4.0f);
    }

    BrownianMotion::~BrownianMotion()
    {
    }

    AttributeRefPtr BrownianMotion::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle)
    {
        // Add velocity vector
        (*particle)[VELOCITY]->vec3Val.add(vec(
            distribution(gen) * time_step.time_factor,
            distribution(gen) * time_step.time_factor,
            distribution(gen) * time_step.time_factor
        ));
        return true;
    }

}
}
}
